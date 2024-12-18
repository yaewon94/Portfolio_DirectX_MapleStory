#ifndef _GLOBAL
#define _GLOBAL
// =============================================
// 상수 버퍼
// =============================================
// 개별 인스턴스
cbuffer Instance : register(b0)
{
    float g_inst_dir;
}

// 오브젝트 좌표, 크기, 각도
cbuffer Transform : register(b1) // 레지스터 번호
{
    // * row major : 행 우선 행렬
    row_major matrix g_matWorld, g_matView, g_matProj;
    row_major matrix g_matWV; // world * view
    row_major matrix g_matWVP; // world * view * proj
};

// 재질
cbuffer Material : register(b2)
{
    float4 g_mtrl_color;
    float g_mtrl_alpha;
    int g_bTex_0;
}

// 애니메이션
cbuffer Flipbook : register(b3)
{
    float2 g_leftTopUV;
    float2 g_sliceSizeUV;
    float2 g_bgrSizeUV;
    float2 g_offsetUV;
    int g_bFlipbook;
}

// =============================================
// 텍스처
// =============================================
Texture2D g_tex_0 : register(t0);
Texture2D g_flipbookTex : register(t1);

// =============================================
// 샘플링
// =============================================
SamplerState g_sampler0 : register(s0); // 이방성 필터링
SamplerState g_sampler1 : register(s1); // MIN_MAG_POINT 필터링

// =============================================
// 전역함수
// =============================================
// 텍스처가 바인딩되어 있지 않을 때 호출됨
float4 GetDebugColor(float2 uv, int level)
{
    float2 texPos = uv * level;
    int col = floor(texPos.x);
    int row = floor(texPos.y);
    
    if ((col + row) % 2) 
        return float4(1.f, 0.f, 1.f, 1.f);
    else
        return float4(0.f, 0.f, 0.f, 1.f);
}
#endif