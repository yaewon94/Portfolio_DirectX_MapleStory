#pragma once
#include "Asset.h"
#include "Texture.h"

// �������
struct CB_Flipbook
{
	Vec2 leftTopUV, sliceSizeUV;
	Vec2 backgroundSizeUV, offsetUV;
	int binding;
	byte padding[12];
};

// 2D ��Ʋ�� �ؽ�ó�� �ִϸ��̼�ó�� ����ϱ� ���� ������ ���� ����
class Flipbook final : public Asset
{
	NO_COPY_MOVE(Flipbook)
	ASSET_TYPE_DCL(ASSET_TYPE::FLIPBOOK)
	friend class FlipbookPlayer;

private:
	SharedPtr<Texture> m_atlas;
	vector<Vec2> m_leftTopUV, m_sliceSizeUV;
	vector<Vec2> m_backgroundSizeUV, m_offsetUV;

public:
	Flipbook(const string& Key, const string& relativePath);
	~Flipbook();

private: // FlipbookPlayer ���� ȣ��
	void Bind(size_t frameIndex);
	void Clear(size_t frameIndex);

public:
	size_t GetFrameCount() const { return m_leftTopUV.size(); }
	SharedPtr<Texture> GetAtlasTexture() const { return m_atlas; }
	// �ڵ����� uv ���� ��������
	void SetAtlasTexture(SharedPtr<Texture> atlasTex, UINT sliceRowCount, UINT sliceColCount, class GameObject* const obj);

	Vec2 GetLeftTopUV(size_t index) const { return m_leftTopUV.at(index); }
	void SetLeftTopUV(size_t index, Vec2 leftTopPixel)
	{
		if (index >= m_leftTopUV.size()) assert(nullptr);
		if (m_atlas == nullptr)
		{
			MessageBox(nullptr, L"��Ʋ�� �ؽ�ó�� null�Դϴ�", L"LeftTopUV ���� ����", MB_OK);
			return;
		}
		m_leftTopUV[index] = Vec2(leftTopPixel.x / (float)m_atlas->GetWidth()
								, leftTopPixel.y / (float)m_atlas->GetHeight());
	}

	Vec2 GetSliceSizeUV(size_t index) const { return m_sliceSizeUV.at(index); }
	void SetSliceSizeUV(size_t index, Vec2 sliceSizePixel)
	{
		if (index >= m_sliceSizeUV.size()) assert(nullptr);
		if (m_atlas == nullptr)
		{
			MessageBox(nullptr, L"��Ʋ�� �ؽ�ó�� null�Դϴ�", L"SliceUV ���� ����", MB_OK);
			return;
		}
		m_sliceSizeUV[index] = Vec2(sliceSizePixel.x / (float)m_atlas->GetWidth()
									, sliceSizePixel.y / (float)m_atlas->GetHeight());
	}

	Vec2 GetBackgroundSizeUV(size_t index) const { return m_backgroundSizeUV.at(index); }
	void SetBackgroundSizeUV(size_t index,Vec2 bgrSizePixel)
	{
		if (index >= m_backgroundSizeUV.size()) assert(nullptr);
		if (m_atlas == nullptr)
		{
			MessageBox(nullptr, L"��Ʋ�� �ؽ�ó�� null�Դϴ�", L"BackgroundUV ���� ����", MB_OK);
			return;
		}
		m_backgroundSizeUV[index] = Vec2(bgrSizePixel.x / (float)m_atlas->GetWidth()
										, bgrSizePixel.y / (float)m_atlas->GetHeight());
	}

	Vec2 GetOffsetUV(size_t index) const { return m_offsetUV.at(index); }
	void SetOffSetUV(size_t index, Vec2 offsetPixel)
	{
		if (index >= m_offsetUV.size()) assert(nullptr);
		if (m_atlas == nullptr)
		{
			MessageBox(nullptr, L"��Ʋ�� �ؽ�ó�� null�Դϴ�", L"OffsetUV ���� ����", MB_OK);
			return;
		}
		m_offsetUV[index] = Vec2(offsetPixel.x / (float)m_atlas->GetWidth()
								, offsetPixel.y / (float)m_atlas->GetHeight());
	}
};