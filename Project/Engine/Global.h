#pragma once

// C++ STL
#include <string>
using std::string;
using std::wstring;
#include <array>
using std::array;
#include <vector>
using std::vector;
#include <map>
using std::map;
using std::make_pair;
#include <unordered_map>
using std::unordered_map;
#include <unordered_set>
using std::unordered_set;

// DirectX 11
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

#include "SimpleMath.h"
typedef DirectX::SimpleMath::Vector2 Vec2;
typedef DirectX::SimpleMath::Vector3 Vec3;
typedef DirectX::SimpleMath::Vector4 Vec4;
typedef DirectX::SimpleMath::Matrix Matrix;

// DirectxTex
#include <DirectxTex/DirectXTex.h>

#ifdef _DEBUG
#pragma comment(lib, "DirectxTex\\DirectXTex_debug")
#else
#pragma comment(lib, "DirectxTex\\DirectXTex")
#endif

// ComPtr
#include <wrl.h>
using namespace Microsoft::WRL;

// 커스텀 헤더파일
#include "Singleton.h" // 싱글톤 클래스 정의
#include "SharedPtr.h" // 공유 스마트포인터