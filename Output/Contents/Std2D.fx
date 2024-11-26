#ifndef _STD2D // 파일명
#define _STD2D
#include "Global.fx"

// Vertex Shader
struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float3 worldPos : POSITION;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Std2D(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // ======================== 좌표 ============================
    // 상대좌표 => 절대좌표
    //float3 pos = (input.pos * objScale.xyz) + objPos.xyz;
    //output.pos = float4(pos, 1.f);
    //float4 worldPos = mul(float4(input.pos, 1.f), g_worldMatrix);
    // 절대좌표 => view 공간
    //float4 viewPos = mul(worldPos, g_viewMatrix);
    // view 공간 => 투영공간
    //output.pos = mul(viewPos, g_projMatrix);
    output.pos = mul(float4(input.pos, 1.f), g_matWVP);
    output.worldPos = mul(float4(input.pos, 1.f), g_matWorld);
    
    // ======================== UV 좌표 =========================
    output.uv = input.uv;
    
    return output;
}

// Pixel Shader
float4 PS_Std2D(VS_OUT vs) : SV_Target
{
    float4 color = (float4) 0.f;
    
    if (g_bTex_0)
        color = g_tex_0.Sample(g_sampler0, vs.uv);
    else
        color = GetDebugColor(vs.uv, 2);
   
    return color;
}
#endif