cbuffer CBChangesEveryFrame : register(b0)
{
    matrix g_ViewProj;
    
    float3 g_EyePosW;
    float g_GameTime;
    
    float g_TimeStep;
    float3 g_EmitDirW;
    
    float3 g_EmitPosW;
    float g_EmitInterval;
    
    float g_AliveTime;
}

cbuffer CBFixed : register(b1)
{
    // ���ڼ��������˶��ļ��ٶ�
    float3 g_AccelW;
}

// ������ͼ�������ϵ�����
Texture2D g_TextureInput : register(t0);

// ��������ɫ�������������������
Texture1D g_TextureRandom : register(t1);

SamplerState g_SamLinear : register(s0);


float3 RandUnitVec3(float offset)
{
    // ʹ����Ϸʱ�����ƫ��ֵ�������������
    float u = (g_GameTime + offset);
    
    // ����ֵ��[-1,1]
    float3 v = g_TextureRandom.SampleLevel(g_SamLinear, u, 0).xyz;
    
    // ͶӰ����λ��
    return normalize(v);
}

float3 RandVec3(float offset)
{
    // ʹ����Ϸʱ�����ƫ��ֵ�������������
    float u = (g_GameTime + offset);
    
    // ����ֵ��[-1,1]
    float3 v = g_TextureRandom.SampleLevel(g_SamLinear, u, 0).xyz;
    
    return v;
}

#define PT_EMITTER 0
#define PT_PARTICLE 1

struct VertexParticle
{
    float3 initialPosW : POSITION;
    float3 initialVelW : VELOCITY;
    float2 sizeW : SIZE;
    float age : AGE;
    uint type : TYPE;
};


// �������
struct VertexOut
{
    float3 posW : POSITION;
    uint Type : TYPE;
};

struct GeoOut
{
    float4 posH : SV_position;
    float2 tex : TEXCOORD;
};
