#include "Octagon.hlsli"

//������ɫ��
VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.posH = float4(vIn.posH, 1.0f); //ת��Ϊ�������
    vOut.color = vIn.color;
	return vOut;
}