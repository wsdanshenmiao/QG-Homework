#include "Particle.hlsli"

[maxvertexcount(6)]
void GS(point VertexOut gIn[1], inout LineStream<GeoOut> output)
{
    // ��Ҫ�������ڲ������ӵĶ���
    if (gIn[0].Type != PT_EMITTER)
    {
        // ʹ�߶�����һ�����ٶȷ�����б
        float3 p0 = gIn[0].posW;
        float3 p1 = gIn[0].posW + 0.07f * g_AccelW;
        
        GeoOut v0;
        v0.posH = mul(float4(p0, 1.0f), g_ViewProj);
        v0.tex = float2(0.0f, 0.0f);
        output.Append(v0);
        
        GeoOut v1;
        v1.posH = mul(float4(p1, 1.0f), g_ViewProj);
        v1.tex = float2(0.0f, 0.0f);
        output.Append(v1);
    }
}
