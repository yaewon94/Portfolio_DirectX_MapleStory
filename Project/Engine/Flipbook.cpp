#include "pch.h"
#include "Flipbook.h"
#include "Device.h"
#include "Texture.h"

Flipbook::Flipbook(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath)
{
}

Flipbook::~Flipbook()
{
}

void Flipbook::Bind(size_t frameIndex)
{
	ConstBuffer* cb = Device::GetInstance()->GetConstBuffer(CONST_BUFFER_TYPE::FLIPBOOK);
	CB_Flipbook info = {};

	m_atlas->Binding_GS(TEXTURE_PARAM::FLIPBOOK);

	info.leftTopUV = m_leftTopUV.at(frameIndex);
	info.sliceSizeUV = m_sliceSizeUV.at(frameIndex);
	info.backgroundSizeUV = m_backgroundSizeUV.at(frameIndex);
	info.offsetUV = m_offsetUV.at(frameIndex);

	cb->SetData(&info);
	cb->Binding_GS();
}

void Flipbook::Clear(size_t frameIndex)
{
	ConstBuffer* cb = Device::GetInstance()->GetConstBuffer(CONST_BUFFER_TYPE::FLIPBOOK);
	CB_Flipbook info = {};

	cb->SetData(&info);
	cb->Binding_GS();

	m_atlas->Clear_GS();
}

void Flipbook::SetAtlasTexture(SharedPtr<Texture> atlasTex, UINT sliceRowCount, UINT sliceColCount)
{
	if (atlasTex == nullptr) return;
	m_atlas = atlasTex;

	// vector ������ �ʱ�ȭ
	const UINT Size = sliceRowCount * sliceColCount;
	m_leftTopUV.resize(Size);
	m_sliceSizeUV.resize(Size);
	m_backgroundSizeUV.resize(Size);
	m_offsetUV.resize(Size);

	// uv ���
	// sliceUV, backgroundUV ���� ��� ���� �����Ǵµ��� ���� vector�� ������ ������
	// �����͸�忡�� sliceUV�� ������ �ε��� ���� ������ �� �ְ� �ϱ� ���ؼ�
	const Vec2 SliceUV = Vec2(1.f / (float)sliceColCount, 1.f / (float)sliceRowCount);
	const Vec2 AtlasSize = Vec2(m_atlas->GetWidth(), m_atlas->GetHeight());
	Vec2 bgrUV;
	if(AtlasSize.x > AtlasSize.y) bgrUV = Vec2(SliceUV.x, AtlasSize.x / AtlasSize.y);
	else bgrUV = Vec2(AtlasSize.y / AtlasSize.x, SliceUV.y);

	for (UINT row = 0; row < sliceRowCount; ++row)
	{
		for (UINT col = 0; col < sliceColCount; ++col)
		{
			UINT index = (row * col) + col;
			m_leftTopUV[index] = Vec2(SliceUV.x * col, SliceUV.y * row);
			m_sliceSizeUV[index] = SliceUV;
			m_backgroundSizeUV[index] = bgrUV;
			m_offsetUV[index] = Vec2(0.f, 0.f); // ���� offset�� Vec2::Zero�� �ƴ� ��찡 �ֱ� ������ ������ �ʱ�ȭ
		}
	}
}