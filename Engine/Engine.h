﻿#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"

class Engine
{
public:
	void Init(const WindowInfo& win_info );
	void Render();

public:
	inline shared_ptr<Device> GetDevice() { return _device; }
	inline shared_ptr<CommandQueue> GetCommandQueue() { return _cmd_queue; }
	inline shared_ptr<SwapChain> GetSwapChain() { return _swap_chain; }

public:
	// Command Queue에 요청 사항을 넣는 부분
	void RenderBegin();

	// Command Queue에 있는 요청 사항을 꺼내 GPU에 요청하는 부분
	void RenderEnd();

	void ResizeWindow( int32 width, int32 height );

private:
	// 그려질 화면 관련 클래스
	WindowInfo		_window;
	D3D12_VIEWPORT	_viewport{};
	D3D12_RECT		_scissor_rect{};

	shared_ptr<Device> _device;
	shared_ptr<CommandQueue> _cmd_queue;
	shared_ptr<SwapChain> _swap_chain;
};
