// [구성 : Release] 파일 우클릭 > 속성 > 일반 > 빌드에서 제외 > 예 
#ifndef _DEBUG
#define _DEBUG
#include "Global.fx"

#define COLOR g_vec4_0

// Vertex Shader
struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Debug(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.pos = mul(float4(input.pos, 1.f), g_matWVP);
    output.uv = input.uv;
    
    return output;
}

// Pixel Shader
float4 PS_Debug(VS_OUT vs) : SV_Target
{
    return COLOR;
}
#endif