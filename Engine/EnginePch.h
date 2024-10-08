﻿#pragma once

// Include
#include <Windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>

using namespace std;

#include "d3dx12.h"
#include <d3d12.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>

using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;

// Library
#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

// Typedef
using int8   = __int8;
using int16  = __int16;
using int32  = __int32;
using int64  = __int64;
using uint8  = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using Vec2   = XMFLOAT2;
using Vec3   = XMFLOAT3;
using Vec4   = XMFLOAT4;
using Mat4   = XMMATRIX;

// enum
enum
{
	SWAP_CHAIN_BUFFER_COUNT = 2
};

// Predeclaration
class Engine;

// 출력 창(윈도우)의 정보를 담을 구조체
struct WindowInfo
{
	HWND	hwnd;	// 출력 윈도우
	int32	width;
	int32	height;
	bool	windowed;
};

#define DEVICE GEngine->GetDevice()->GetDivice();
#define CMD_LIST GEngine->GetCommandQueue()->GetCommandList();

extern unique_ptr<Engine> GEngine;
