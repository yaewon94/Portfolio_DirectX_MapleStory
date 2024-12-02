#ifndef _STD2D // 파일명
#define _STD2D
#include "Global.fx"

#define DIRECTION g_float_0

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

float4 PS_Flipbook(VS_OUT vs) : SV_Target;

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
    
    vs.uv.x *= DIRECTION;
    
    if (g_bTex_0)
        color = g_tex_0.Sample(g_sampler0, vs.uv);
    else if(g_bFlipbook)
        color = PS_Flipbook(vs);
    else
        color = GetDebugColor(vs.uv, 2);
   
    return color;
}

float4 PS_Flipbook(VS_OUT vs) : SV_Target
{
    float4 color = (float4) 0.f;
    float2 bgrLeftTop = g_leftTopUV + (g_sliceSizeUV - g_bgrSizeUV) / 2.f;
    float2 spriteUV = bgrLeftTop + (vs.uv * g_bgrSizeUV) - g_offsetUV;
    bool isDiscard = false;
    
    // ERROR : 왼쪽으로 방향전환하면(vs.uv.x 값이 음수가 되게 구현했음) discard되서 주석처리
    //// X축
    //if (g_bgrSizeUV.x >= g_sliceSizeUV.x)
    //{
    //    if (spriteUV.x < g_leftTopUV.x || spriteUV.x > g_leftTopUV.x + g_sliceSizeUV.x)
    //    {
    //        isDiscard = true;
    //        discard;
    //    }
    //}
    //else
    //{
    //    if (spriteUV.x < bgrLeftTop.x || spriteUV.x > bgrLeftTop.x + g_bgrSizeUV.x)
    //    {
    //        isDiscard = true;
    //        discard;
    //    }
    //}
            
    //// Y축
    //if (!isDiscard && g_bgrSizeUV.y >= g_sliceSizeUV.y)
    //{
    //    if (spriteUV.y < g_leftTopUV.y || spriteUV.y > g_leftTopUV.y + g_sliceSizeUV.y)
    //    {
    //        isDiscard = true;
    //        discard;
    //    }
    //}
    //else
    //{
    //    if (spriteUV.y < bgrLeftTop.y || spriteUV.y > bgrLeftTop.y + g_bgrSizeUV.y)
    //    {
    //        isDiscard = true;
    //        discard;
    //    }
    //}
            
    // 출력
    if (!isDiscard)
    {
        color = g_flipbookTex.Sample(g_sampler0, spriteUV);
    }
    return color;
}
#endif