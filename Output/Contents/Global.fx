#ifndef _GLOBAL
#define _GLOBAL
// =============================================
// ��� ����
// =============================================
// ���� �ν��Ͻ�
cbuffer Instance : register(b0)
{
    float g_inst_dir;
}

// ������Ʈ ��ǥ, ũ��, ����
cbuffer Transform : register(b1) // �������� ��ȣ
{
    // * row major : �� �켱 ���
    row_major matrix g_matWorld, g_matView, g_matProj;
    row_major matrix g_matWV; // world * view
    row_major matrix g_matWVP; // world * view * proj
};

// ����
cbuffer Material : register(b2)
{
    float4 g_mtrl_color;
    float g_mtrl_alpha;
    int g_bTex_0;
}

// �ִϸ��̼�
cbuffer Flipbook : register(b3)
{
    float2 g_leftTopUV;
    float2 g_sliceSizeUV;
    float2 g_bgrSizeUV;
    float2 g_offsetUV;
    int g_bFlipbook;
}

// =============================================
// �ؽ�ó
// =============================================
Texture2D g_tex_0 : register(t0);
Texture2D g_flipbookTex : register(t1);

// =============================================
// ���ø�
// =============================================
SamplerState g_sampler0 : register(s0); // �̹漺 ���͸�
SamplerState g_sampler1 : register(s1); // MIN_MAG_POINT ���͸�

// =============================================
// �����Լ�
// =============================================
// �ؽ�ó�� ���ε��Ǿ� ���� ���� �� ȣ���
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