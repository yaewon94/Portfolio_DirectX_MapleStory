#ifndef _GLOBAL
#define _GLOBAL
// =============================================
// ��� ����
// =============================================
// ������Ʈ ��ǥ, ũ��, ����
cbuffer Transform : register(b0) // �������� ��ȣ
{
    // * row major : �� �켱 ���
    row_major matrix g_matWorld, g_matView, g_matProj;
    row_major matrix g_matWV; // world * view
    row_major matrix g_matWVP; // world * view * proj
};

// ����
cbuffer Material : register(b1)
{
    int g_int_0;
    float g_float_0, g_float_1;
    float2 g_vec2_0;
    float4 g_vec4_0;
    row_major Matrix g_matrix_0;
    int g_bTex_0;
}

// �ִϸ��̼�
cbuffer Flipbook : register(b2)
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