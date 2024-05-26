#include "Particle.hlsli"

[maxvertexcount(6)]
void GS(point VertexParticle gIn[1], inout PointStream<VertexParticle> output)
{
    gIn[0].age += g_TimeStep;
    
    if (gIn[0].type == PT_EMITTER)
    {
        // �Ƿ�ʱ�䷢���µ�����
        if (gIn[0].age > g_EmitInterval)
        {
            [unroll]
            for (int i = 0; i < 5; ++i)
            {
                // ��������Ϸ�����������ν���
                float3 vRandom = 30.0f * RandVec3((float) i / 5.0f);
                vRandom.y = 20.0f;
                
                VertexParticle p;
                p.initialPosW = g_EmitPosW.xyz + vRandom;
                p.initialVelW = float3(0.0f, 0.0f, 0.0f);
                p.sizeW = float2(1.0f, 1.0f);
                p.age = 0.0f;
                p.type = PT_PARTICLE;
                
                output.Append(p);
            }
            
            // ����ʱ��׼����һ�η���
            gIn[0].age = 0.0f;
        }
        
        // ���Ǳ���������
        output.Append(gIn[0]);
    }
    else
    {
        // ��������������Ŀ�������ض����������ڲ�ͬ������ϵͳ����Ҳ�����仯
        if (gIn[0].age <= g_AliveTime)
            output.Append(gIn[0]);
    }
}
