#include "pch.h"
#include "Flipbook.h"
#include "Device.h"
#include "GameObject.h"
#include "Transform.h"

Flipbook::Flipbook(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath)
{
	m_leftTopUV.resize(0);
	m_sliceSizeUV.resize(0);
	m_backgroundSizeUV.resize(0);
	m_offsetUV.resize(0);
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
	info.binding = true;

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

void Flipbook::SetAtlasTexture(SharedPtr<Texture> atlasTex, UINT sliceRowCount, UINT sliceColCount, class GameObject* const obj)
{
	if (atlasTex == nullptr) return;
	m_atlas = atlasTex;

	// vector 사이즈 초기화
	const UINT Size = sliceRowCount * sliceColCount;
	m_leftTopUV.resize(Size);
	m_sliceSizeUV.resize(Size);
	m_backgroundSizeUV.resize(Size);
	m_offsetUV.resize(Size);

	// uv 계산
	// sliceUV, backgroundUV 값이 모두 같게 설정되는데도 개별 vector로 선언한 이유는
	// 에디터모드에서 sliceUV를 프레임 인덱스 마다 조절할 수 있게 하기 위해서
	const Vec2 SliceUV = Vec2(1.f / (float)sliceColCount, 1.f / (float)sliceRowCount);
	const Vec2 bgrUV = Vec2(obj->GetTransform()->GetLocalScale().x / (float)m_atlas->GetWidth()
							, obj->GetTransform()->GetLocalScale().y / (float)m_atlas->GetHeight());

	for (UINT row = 0; row < sliceRowCount; ++row)
	{
		for (UINT col = 0; col < sliceColCount; ++col)
		{
			UINT index = (row * col) + col;
			m_leftTopUV[index] = Vec2(SliceUV.x * col, SliceUV.y * row);
			m_sliceSizeUV[index] = SliceUV;
			m_backgroundSizeUV[index] = bgrUV;
			m_offsetUV[index] = Vec2(0.f, 0.f); // 기존 offset이 Vec2::Zero가 아닌 경우가 있기 때문에 명시적 초기화
		}
	}
}