#include "pch.h"
#include "Flipbook.h"
#include "Device.h"
#include "GameObject.h"
#include "Transform.h"
#include "FileManager.h"
#include "AssetManager.h"

Flipbook::Flipbook(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath)
	, m_frameCount(0)
{
}

Flipbook::~Flipbook()
{
}

int Flipbook::Load()
{
	if (AssetManager::GetInstance()->FindAsset<Flipbook>(GetKey()) != nullptr)
	{
#ifdef _DEBUG
		assert(nullptr);
#else
		return E_FAIL;
#endif // _DEBUG
	}

	if (FAILED(FileManager::GetInstance()->Open(GetFullPathA(), FILE_MODE::READ_TEXT))) return E_FAIL;

	char buff[256];
	if (FAILED(FileManager::GetInstance()->ReadJsonValue("AtlasPath", buff))) return E_FAIL;
	m_atlas = AssetManager::GetInstance()->AddAsset<Texture>(GetKey(), buff);

	if (FAILED(FileManager::GetInstance()->ReadJsonValue("FrameCount", buff))) return E_FAIL;
	m_frameCount = ToInteger(buff);
	m_leftTopUV.resize(m_frameCount);
	m_sliceSizeUV.resize(m_frameCount);
	m_backgroundSizeUV.resize(m_frameCount);
	m_offsetUV.resize(m_frameCount);

	for (size_t i = 0; i < m_frameCount; ++i)
	{
		if (FAILED(FileManager::GetInstance()->ReadJsonValue("LeftTopUV_X", buff, i))) return E_FAIL;
		m_leftTopUV[i].x = ToFloat(buff);
	}

	for (size_t i = 0; i < m_frameCount; ++i)
	{
		if (FAILED(FileManager::GetInstance()->ReadJsonValue("LeftTopUV_Y", buff, i))) return E_FAIL;
		m_leftTopUV[i].y = ToFloat(buff);
	}

	for (size_t i = 0; i < m_frameCount; ++i)
	{
		if (FAILED(FileManager::GetInstance()->ReadJsonValue("SliceUV_X", buff, i))) return E_FAIL;
		m_sliceSizeUV[i].x = ToFloat(buff);
	}

	for (size_t i = 0; i < m_frameCount; ++i)
	{
		if (FAILED(FileManager::GetInstance()->ReadJsonValue("SliceUV_Y", buff, i))) return E_FAIL;
		m_sliceSizeUV[i].y = ToFloat(buff);
	}

	for (size_t i = 0; i < m_frameCount; ++i)
	{
		if (FAILED(FileManager::GetInstance()->ReadJsonValue("BgrUV_X", buff, i))) return E_FAIL;
		m_backgroundSizeUV[i].x = ToFloat(buff);
	}

	for (size_t i = 0; i < m_frameCount; ++i)
	{
		if (FAILED(FileManager::GetInstance()->ReadJsonValue("BgrUV_Y", buff, i))) return E_FAIL;
		m_backgroundSizeUV[i].y = ToFloat(buff);
	}

	for (size_t i = 0; i < m_frameCount; ++i)
	{
		if (FAILED(FileManager::GetInstance()->ReadJsonValue("OffsetUV_X", buff, i))) return E_FAIL;
		m_offsetUV[i].x = ToFloat(buff);
	}

	for (size_t i = 0; i < m_frameCount; ++i)
	{
		if (FAILED(FileManager::GetInstance()->ReadJsonValue("OffsetUV_Y", buff, i))) return E_FAIL;
		m_offsetUV[i].y = ToFloat(buff);
	}

	FileManager::GetInstance()->Close();

	return S_OK;
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

void Flipbook::AdjustObjSize(GameObject* const obj, size_t frameIndex)
{
#ifdef _DEBUG
	if (m_atlas == nullptr) assert(nullptr);
	if (frameIndex >= m_frameCount) assert(nullptr);
#endif // _DEBUG

	obj->GetTransform()->SetLocalScale(Vec3(m_atlas->GetWidth() * m_backgroundSizeUV[frameIndex].x
											, m_atlas->GetHeight() * m_backgroundSizeUV[frameIndex].y
											, 1.f));
}

void Flipbook::SetAtlasTexture(SharedPtr<Texture> atlasTex, UINT sliceRowCount, UINT sliceColCount)
{
	if (atlasTex == nullptr) return;
	m_atlas = atlasTex;

	// vector 사이즈 초기화
	m_frameCount = sliceRowCount * sliceColCount;
	m_leftTopUV.resize(m_frameCount);
	m_sliceSizeUV.resize(m_frameCount);
	m_backgroundSizeUV.resize(m_frameCount);
	m_offsetUV.resize(m_frameCount);

	// uv 계산
	// sliceUV, backgroundUV 값이 모두 같게 설정되는데도 개별 vector로 선언한 이유는
	// 에디터모드에서 sliceUV를 프레임 인덱스 마다 조절할 수 있게 하기 위해서
	const Vec2 SliceSize = Vec2(atlasTex->GetWidth() / (float)sliceColCount, atlasTex->GetHeight() / (float)sliceRowCount);
	const Vec2 SliceUV = Vec2(1.f / (float)sliceColCount, 1.f / (float)sliceRowCount);
	Vec2 bgrUV;
	if (SliceSize.x >= SliceSize.y)
	{
		bgrUV.x = SliceUV.x;
		bgrUV.y = SliceUV.y * (SliceSize.x / SliceSize.y);
	}
	else
	{
		bgrUV.y = SliceUV.y;
		bgrUV.x = SliceUV.x * (SliceSize.y / SliceSize.x);
	}

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