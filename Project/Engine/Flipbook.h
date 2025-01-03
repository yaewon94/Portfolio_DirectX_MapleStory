#pragma once
#include "Asset.h"
#include "Texture.h"

// 상수버퍼
struct CB_Flipbook
{
	Vec2 leftTopUV, sliceSizeUV;
	Vec2 backgroundSizeUV, offsetUV;
	int binding;
	byte padding[12];
};

// 2D 아틀라스 텍스처를 애니메이션처럼 재생하기 위한 정보를 담은 에셋
class Flipbook final : public Asset
{
	NO_COPY_MOVE(Flipbook)
	ASSET_TYPE_DCL(ASSET_TYPE::FLIPBOOK)
	friend class FlipbookPlayer;

private:
	SharedPtr<Texture> m_atlas;
	vector<Vec2> m_leftTopUV, m_sliceSizeUV;
	vector<Vec2> m_backgroundSizeUV, m_offsetUV;
	size_t m_frameCount;
	Vec2 m_objSize, m_colliderOffset, m_colliderScale; // Flipbook 크기에 맞게 변경할 게임오브젝트 사이즈, 콜라이더 오프셋, 콜라이더 배율

public:
	Flipbook(const string& Key, const string& relativePath);
	~Flipbook();

private: // AssetManager 에서 Asset* 으로 호출
	virtual int Load() final;

private: // FlipbookPlayer 에서 호출
	void Bind(size_t frameIndex);
	void Clear(size_t frameIndex);
	void AdjustObjSize(GameObject* const obj);

	size_t GetFrameCount() const { return m_frameCount; }

public:
	SharedPtr<Texture> GetAtlasTexture() const { return m_atlas; }
	// 자동으로 uv 값들 설정해줌
	void SetAtlasTexture(SharedPtr<Texture> atlasTex, UINT sliceRowCount, UINT sliceColCount);

	Vec2 GetLeftTopUV(size_t index) const { return m_leftTopUV.at(index); }
	void SetLeftTopUV(size_t index, Vec2 leftTopUV)
	{
		if (index >= m_leftTopUV.size()) assert(nullptr);
		m_leftTopUV[index] = XMVectorSaturate(leftTopUV);
	}

	Vec2 GetSliceSizeUV(size_t index) const { return m_sliceSizeUV.at(index); }
	void SetSliceSizeUV(size_t index, Vec2 sliceSizeUV)
	{
		if (index >= m_sliceSizeUV.size()) assert(nullptr);
		m_sliceSizeUV[index] = XMVectorSaturate(sliceSizeUV);
	}

	Vec2 GetBackgroundSizeUV(size_t index) const { return m_backgroundSizeUV.at(index); }
	void SetBackgroundSizeUV(size_t index,Vec2 bgrSizeUV)
	{
		if (index >= m_backgroundSizeUV.size()) assert(nullptr);
		if (bgrSizeUV.x <= 0.f || bgrSizeUV.y <= 0.f) return;
		m_backgroundSizeUV[index] = bgrSizeUV;
	}

	Vec2 GetOffsetUV(size_t index) const { return m_offsetUV.at(index); }
	void SetOffSetUV(size_t index, Vec2 offsetUV)
	{
		if (index >= m_offsetUV.size()) assert(nullptr);
		m_offsetUV[index] = offsetUV;
	}
};