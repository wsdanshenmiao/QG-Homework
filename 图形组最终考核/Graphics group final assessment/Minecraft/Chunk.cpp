#include "Chunk.h"

using namespace DirectX;

namespace DSM {

bool Chunk::m_EnableFrustumCulling = false;				// 视锥体裁剪关闭
int Chunk::m_Seed = 20050113;								// 默认种子
int Chunk::m_StoreChunkRadius = 2;						// 超过此半径的区块被卸载
Block Chunk::m_Block[5] = {};

void Chunk::InitBlock(TextureManager& tManager, ModelManager& mManager)
{
	// 初始化方块
	m_Block[0].GetBlock().SetModel(nullptr);
	m_Block[0].SetId(BlockId::Air);
	m_Block[1].GetBlock().SetModel(m_Block[1].GetBlockModel().GetDirtModel(tManager, mManager));
	m_Block[1].SetId(BlockId::Dirt);
	m_Block[2].GetBlock().SetModel(m_Block[2].GetBlockModel().GetStoneModel(tManager, mManager));
	m_Block[2].SetId(BlockId::Stone);
	m_Block[3].GetBlock().SetModel(m_Block[3].GetBlockModel().GetBedRockModel(tManager, mManager));
	m_Block[3].SetId(BlockId::BedRock);
	m_Block[4].GetBlock().SetModel(m_Block[4].GetBlockModel().GetGressModel(tManager, mManager));
	m_Block[4].SetId(BlockId::Gress);
}


Chunk::Chunk(DirectX::XMINT2 position)
	:m_Positon(position) {}

Chunk::Chunk(int x, int y)
	:m_Positon(DirectX::XMINT2(x, y)) {}

DirectX::XMINT2 Chunk::GetPositon()
{
	return m_Positon;
}

void Chunk::SetPosition(DirectX::XMINT2 position)
{
	m_Positon = position;
}

void Chunk::SetPosition(int x, int y)
{
	m_Positon = DirectX::XMINT2(x, y);
}

// 判断是否在区块中
bool Chunk::OutOfChunk(int x, int y, int z)
{
	if (y<0 || y>CHUNKHIGHEST) {
		return true;
	}
	if (x - GetPositon().x < 0) {
		return true;
	}
	if (z - GetPositon().y < 0) {
		return true;
	}
	return false;
}

bool Chunk::GetState()
{
	if (m_Loading) {
		return true;
	}
	return false;
}

std::vector<BasicEffect::InstancedData>& Chunk::GetDirtInstancedData()
{
	return Chunk::m_EnableFrustumCulling ? m_AcceptedData[0] : m_BlockInstancedData[0];
}

std::vector<BasicEffect::InstancedData>& Chunk::GetStoneInstancedData()
{
	return Chunk::m_EnableFrustumCulling ? m_AcceptedData[1] : m_BlockInstancedData[1];
}

std::vector<BasicEffect::InstancedData>& Chunk::GetBedRockInstancedData()
{
	return Chunk::m_EnableFrustumCulling ? m_AcceptedData[2] : m_BlockInstancedData[2];
}

std::vector<BasicEffect::InstancedData>& Chunk::GetGressInstancedData()
{
	return Chunk::m_EnableFrustumCulling ? m_AcceptedData[3] : m_BlockInstancedData[3];
}

std::vector<Transform>& Chunk::GetDirtTransform()
{
	return m_BlockTransforms[0];
}

std::vector<Transform>& Chunk::GetStoneTransform()
{
	return m_BlockTransforms[1];
}

std::vector<Transform>& Chunk::GetBedRockTransform()
{
	return m_BlockTransforms[2];
}

std::vector<Transform>& Chunk:: GetGressTransform()
{
	return m_BlockTransforms[3];
}

std::vector<BoundingBox>& Chunk::GetBlockBox()
{
	return m_BlockBox;
}

// 生成不同频率的柏林噪声
float Chunk::GetNoice(int x, int z)
{
	FastNoiseLite noice1(m_Seed);
	noice1.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noice1.SetFrequency(0.1f);
	FastNoiseLite noice2(m_Seed);
	noice2.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noice2.SetFrequency(0.04f);
	FastNoiseLite noice3(m_Seed);
	noice3.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noice3.SetFrequency(0.006f);
	float noice = (noice1.GetNoise((float)x, (float)z) * LOWAMPLITUDE + 
		noice2.GetNoise((float)x, (float)z) * NORMALAMPLITUDE + 
		noice3.GetNoise((float)x, (float)z) * HIGHAMPLITUDE);
	return noice;
}

// 获取方块种类
BlockId Chunk::GetBlock(int x, int y, int z)
{
	if (OutOfChunk(x, y, z)) {
		return BlockId::Air;
	}
	//创建随机数引擎
	std::random_device rd;
	std::mt19937 gen(rd());
	//指定随机数的类型和范围
	std::uniform_int_distribution<size_t> dis(0, BLOCKRANDOM);
	// 获取的柏林噪声
	float noice = GetNoice(x, z);
	if (y < 1 + dis(gen)) {
		return BlockId::BedRock;
	}
	else if (y < SEALEVEL - DIRTTHICKNESS + (int)noice + dis(gen)) {
		return BlockId::Stone;
	}
	else if (y < SEALEVEL + (int)noice) {
		return BlockId::Dirt;
	}
	else if (y == SEALEVEL + (int)noice){
		return BlockId::Gress;
	}
	else {
		return BlockId::Air;
	}
}



#if 0
// 设置方块种类
void Chunk::SetBlock(int x, int y, int z, Block& block, TextureManager& tManager, ModelManager& mManager)
{
	BlockModel bModel = block.GetBlockModel();
	if (OutOfChunk(x, y, z)) {
		return;
	}
	block.SetId(GetBlock(x, y, z));	//获取Id
	switch (block.GetId())
	{
	case BlockId::Air:
		block.GetBlock().SetModel(nullptr); break;
	case BlockId::Dirt:
		block.GetBlock().SetModel(bModel.GetDirtModel(tManager, mManager)); break;
	case BlockId::Stone:
		block.GetBlock().SetModel(bModel.GetStoneModel(tManager, mManager)); break;
	case BlockId::BedRock:
		block.GetBlock().SetModel(bModel.GetBedRockModel(tManager, mManager)); break;
	default:
		break;
	}
}

void Chunk::LoadChunk(TextureManager& tManager, ModelManager& mManager)
{
	m_Loading = true;
	m_Block.resize(CHUNKSIZE * CHUNKSIZE * CHUNKHIGHEST);
	for (int y = 0; y < CHUNKHIGHEST; y++) {	//每一层
		for (int z = 0; z < CHUNKSIZE; z++) {
			for (int x = 0; x < CHUNKSIZE; x++) {
				int mx = m_Positon.x;
				int mz = m_Positon.y;
				int ly = y * CHUNKSIZE * CHUNKSIZE;
				int lz = z * CHUNKSIZE;
				SetBlock(mx + x, y, mz + z, m_Block[ly + lz + x] , tManager, mManager);
				m_Block[ly + lz + x].GetBlock().GetTransform().SetPosition(mx + x, y, mz + z);
			}
		}
	}
}

void Chunk::DrawChunk(ID3D11DeviceContext* deviceContext, IEffect& effect)
{
	for (auto block : m_Block) {
		if (block.GetBlock().GetModel()) {
			block.GetBlock().Draw(deviceContext, effect);
		}
	}
}

#else

void Chunk::LoadChunk()
{
	PROFILE_FUNCTION();

	m_Loading = true;

	// 生成方块
	m_BlockInstancedData[0].reserve(2200);
	m_BlockTransforms[0].reserve(2200);
	m_BlockInstancedData[1].reserve(18000);
	m_BlockTransforms[1].reserve(18000);
	m_BlockInstancedData[2].reserve(680);
	m_BlockTransforms[2].reserve(680);
	m_BlockInstancedData[3].reserve(256);
	m_BlockTransforms[3].reserve(256);

	m_BlockBox.resize(CHUNKSIZE * CHUNKSIZE * CHUNKHIGHEST);

	Transform transform;
	for (int y = 0; y < CHUNKHIGHEST; y++) {	//每一层 16 * 16
		for (int z = 0; z < CHUNKSIZE; z++) {
			for (int x = 0; x < CHUNKSIZE; x++) {
				int mx = m_Positon.x;
				int mz = m_Positon.y;
				transform.SetPosition(mx + x, y, mz + z);
				BasicEffect::InstancedData instanceData;
				XMMATRIX W = transform.GetLocalToWorldMatrixXM();
				XMStoreFloat4x4(&instanceData.world, XMMatrixTranspose(W));
				XMStoreFloat4x4(&instanceData.worldInvTranspose, XMMatrixTranspose(XMath::InverseTranspose(W)));
				
				XMFLOAT3 center(mx + x + 0.5f, y + 0.5f, mz + z + 0.5f);
				XMFLOAT3 extents(0.5f, 0.5f, 0.5f);
				switch (GetBlock(mx + x, y, mz + z)){
				case BlockId::Air:
					m_BlockBox[y * CHUNKSIZE * CHUNKSIZE + z * CHUNKSIZE + x] = 
						BoundingBox(center, XMFLOAT3(0.0f, 0.0f, 0.0f));
					break;
				case BlockId::Dirt:
					m_BlockTransforms[0].push_back(transform);
					m_BlockInstancedData[0].push_back(instanceData);
					m_BlockBox[y * CHUNKSIZE * CHUNKSIZE + z * CHUNKSIZE + x] = BoundingBox(center, extents);
					break;
				case BlockId::Stone:
					m_BlockTransforms[1].push_back(transform);
					m_BlockInstancedData[1].push_back(instanceData);
					m_BlockBox[y * CHUNKSIZE * CHUNKSIZE + z * CHUNKSIZE + x] = BoundingBox(center, extents);
					break;
				case BlockId::BedRock:
					m_BlockTransforms[2].push_back(transform);
					m_BlockInstancedData[2].push_back(instanceData);
					m_BlockBox[y * CHUNKSIZE * CHUNKSIZE + z * CHUNKSIZE + x] = BoundingBox(center, extents);
					break;
				case BlockId::Gress:
					m_BlockTransforms[3].push_back(transform);
					m_BlockInstancedData[3].push_back(instanceData);
					m_BlockBox[y * CHUNKSIZE * CHUNKSIZE + z * CHUNKSIZE + x] = BoundingBox(center, extents);
					break;
				}
			}
		}
	}

	std::ifstream ifs;
	std::string fileName = std::string("World\\" + std::to_string(DSM::Chunk::m_Seed) + "\\") + 'x' + std::to_string(m_Positon.x) + 'y' + std::to_string(m_Positon.y);
	ifs.open(fileName, std::ios::in | std::ios::binary);

	for (DSM::BlockId blockId; ifs.read((char*)&blockId, sizeof(DSM::BlockId));) {
		int pos = 0;
		switch (blockId)
		{
		case DSM::BlockId::Dirt:
			pos = 0;break;
		case DSM::BlockId::Stone:
			pos = 1;break;
		case DSM::BlockId::BedRock:
			pos = 2;break;
		case DSM::BlockId::Gress:
			pos = 3;break;
		default:
			break;
		}
		XMFLOAT3 position;
		ifs.read((char*)&position, sizeof(XMFLOAT3));
		Transform transform;
		transform.SetPosition(position);
		BasicEffect::InstancedData instanceData;
		XMMATRIX W = transform.GetLocalToWorldMatrixXM();
		XMStoreFloat4x4(&instanceData.world, XMMatrixTranspose(W));
		XMStoreFloat4x4(&instanceData.worldInvTranspose, XMMatrixTranspose(XMath::InverseTranspose(W)));
		m_BlockTransforms[pos].push_back(transform);
		m_BlockInstancedData[pos].push_back(instanceData);
		XMFLOAT3 localPosition(position.x - m_Positon.x, position.y, position.z - m_Positon.y);
		m_BlockBox[localPosition.y * CHUNKSIZE * CHUNKSIZE + localPosition.z * CHUNKSIZE + localPosition.x] =
			BoundingBox(XMFLOAT3(position.x + 0.5f, position.y + 0.5f, position.z + 0.5f), XMFLOAT3(0.5f, 0.5f, 0.5f));
	}

	ifs.close();

	// 收缩内存方便存到文件
	std::vector<BasicEffect::InstancedData>(m_BlockInstancedData[0]).swap(m_BlockInstancedData[0]);
	std::vector<Transform>(m_BlockTransforms[0]).swap(m_BlockTransforms[0]);
	std::vector<BasicEffect::InstancedData>(m_BlockInstancedData[1]).swap(m_BlockInstancedData[1]);
	std::vector<Transform>(m_BlockTransforms[1]).swap(m_BlockTransforms[1]);
	std::vector<BasicEffect::InstancedData>(m_BlockInstancedData[2]).swap(m_BlockInstancedData[2]);
	std::vector<Transform>(m_BlockTransforms[2]).swap(m_BlockTransforms[2]);
	std::vector<BasicEffect::InstancedData>(m_BlockInstancedData[3]).swap(m_BlockInstancedData[3]);
	std::vector<Transform>(m_BlockTransforms[3]).swap(m_BlockTransforms[3]);
}

bool Chunk::UnloadChunk(const XMINT2& centerChunk)
{
	int xDistance = abs(m_Positon.x - centerChunk.x);
	int yDistance = abs(m_Positon.y - centerChunk.y);
	return (xDistance > m_StoreChunkRadius * CHUNKSIZE || yDistance > m_StoreChunkRadius * CHUNKSIZE);
}

void Chunk::FrustumCulling(std::shared_ptr<FirstPersonCamera> camera)
{
	for (int i = 0; i < 4; i++) {
		m_AcceptedData[i].clear();
		BoundingFrustum frustum;
		BoundingFrustum::CreateFromMatrix(frustum, camera->GetProjMatrixXM());
		XMMATRIX V = camera->GetViewMatrixXM();
		BoundingOrientedBox localOrientedBox, orientedBox;
		BoundingOrientedBox::CreateFromBoundingBox(localOrientedBox, m_Block->GetBlock().GetBoundingBox());
		for (size_t j = 0; j < m_BlockInstancedData[i].size(); ++j) {
			// 将有向包围盒从局部坐标系变换到视锥体所在的局部坐标系(观察坐标系)中
			localOrientedBox.Transform(orientedBox, m_BlockTransforms[i][j].GetLocalToWorldMatrixXM() * V);
			// 相交检测
			if (frustum.Intersects(orientedBox)) {
				m_AcceptedData[i].push_back(m_BlockInstancedData[i][j]);
			}
		}
	}
}

void Chunk::DrawChunk(ID3D11Device* device, ID3D11DeviceContext* deviceContext, BasicEffect& effect, std::shared_ptr<FirstPersonCamera> camera)
{
	if (m_EnableFrustumCulling) {
		FrustumCulling(camera);
	}
	for (int i = 0; i < 4; i++) {
		const auto& refData = m_EnableFrustumCulling ? m_AcceptedData[i] : m_BlockInstancedData[i];

		m_pInstancedBuffer[i] = std::make_shared<Buffer>(device,
			CD3D11_BUFFER_DESC(sizeof(BasicEffect::InstancedData) * refData.size(), D3D11_BIND_VERTEX_BUFFER,
				D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE));
		if (m_pInstancedBuffer[i]->GetBuffer()) {
			m_pInstancedBuffer[i]->SetDebugObjectName("InstancedBuffer");
			// 硬件实例化绘制
			// 上传实例数据
			memcpy_s(m_pInstancedBuffer[i]->MapDiscard(deviceContext),
				m_pInstancedBuffer[i]->GetByteWidth(), refData.data(), refData.size() * sizeof(BasicEffect::InstancedData));
			m_pInstancedBuffer[i]->Unmap(deviceContext);
			effect.DrawInstanced(deviceContext, *m_pInstancedBuffer[i], m_Block[i + 1].GetBlock(), (uint32_t)refData.size());
		}
	}
}


bool Chunk::InitFromFile()
{
	std::ifstream ifs;
	std::string fileName = "World\\" + std::to_string(DSM::Chunk::m_Seed);

	ifs.open(fileName + "\\Chunk.dat", std::ios::in | std::ios::binary);
	if (!ifs.is_open()) {
		return false;
	}
	if (!ifs.read((char*)&m_Positon, sizeof(XMINT2))) {
		return false;
	}
	ifs.read((char*)&m_Loading, sizeof(bool));

	size_t size;
	for (int i = 0; i < 4; ++i) {
		ifs.read((char*)&size, sizeof(size_t));
		m_BlockInstancedData[i].reserve(size);
		for (size_t j = 0; j < size; ++j) {
			BasicEffect::InstancedData instanceData;
			ifs.read((char*)&instanceData, sizeof(BasicEffect::InstancedData));
			m_BlockInstancedData[i].push_back(std::move(instanceData));
		}
		ifs.read((char*)&size, sizeof(size_t));
		m_BlockTransforms[i].reserve(size);
		for (size_t j = 0; j < size; ++j) {
			Transform transform;
			ifs.read((char*)&transform, sizeof(Transform));
			m_BlockTransforms[i].push_back(std::move(transform));
		}
	}

	ifs.read((char*)&size, sizeof(size_t));
	m_BlockBox.reserve(size);
	for (size_t i = 0; i < size; ++i) {
		BoundingBox box;
		ifs.read((char*)&box, sizeof(BoundingBox));
		m_BlockBox.push_back(std::move(box));
	}

	ifs.close();

	return true;
}

// 区块只存储位置、状态、加载区块的到的方块数据和包围盒三维数组
void Chunk::SaveToFile()
{
	std::ofstream ofs;
	std::string fileName = "World\\" + std::to_string(DSM::Chunk::m_Seed);

	ofs.open(fileName + "\\Chunk.dat", std::ios::out | std::ios::binary | std::ios::app);

	ofs.write((char*)&m_Positon, sizeof(XMINT2));
	ofs.write((char*)&m_Loading, sizeof(bool));

	size_t size;
	for (int i = 0; i < 4; ++i) {
		size = m_BlockInstancedData[i].size();
		ofs.write((char*)&size, sizeof(size_t));
		ofs.write((char*)m_BlockInstancedData[i].data(), sizeof(BasicEffect::InstancedData) * size);

		size = m_BlockTransforms[i].size();
		ofs.write((char*)&size, sizeof(size_t));
		ofs.write((char*)m_BlockTransforms[i].data(), sizeof(Transform) * size);
	}

	size = m_BlockBox.size();
	ofs.write((char*)&size, sizeof(size_t));
	ofs.write((char*)m_BlockBox.data(), sizeof(BoundingBox) * size);

	ofs.close();
}




}

#endif
