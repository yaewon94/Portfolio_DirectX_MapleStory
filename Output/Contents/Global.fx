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
    int g_int_0, g_int_1, g_int_2, g_int_3;
    float g_float_0, g_float_1, g_float_2, f_float_3;
    float2 g_vec2_0, g_vec2_1, g_vec2_2, g_vec2_3;
    float4 g_vec4_0, g_vec4_1, g_vec4_2, g_vec4_3;
    row_major Matrix g_matrix_0, g_matrix_1;
    int g_bTex_0, g_bTex_1, g_bTex_2, g_bTex_3, g_bTex_4, g_bTex_5;
    int g_bTexArr_0, g_bTexArr_1, g_bTexArr_2, g_bTexArr_3;
    int g_bTexCube_0, g_TexCube_1;
}

// =============================================
// �ؽ�ó
// =============================================
Texture2D g_tex_0 : register(t0);

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