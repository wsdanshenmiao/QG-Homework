#include "Particle.hlsli"

VertexOut VS(VertexParticle vIn)
{
    VertexOut vOut;
    
    float t = vIn.age;
    
    // �㶨���ٶȵ�ʽ
    vOut.posW = 0.5f * t * t * g_AccelW + t * vIn.initialVelW + vIn.initialPosW;
    
    vOut.Type = vIn.type;
    
    return vOut;
}
