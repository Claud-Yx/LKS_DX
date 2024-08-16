#include "pch.h"
#include "Engine.h"
#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "DescriptorHeap.h"

void Engine::Init( const WindowInfo& win_info )
{
	_window = win_info;
	ResizeWindow( win_info.width, win_info.height );

	// 그려질 화면 크기 설정
	_viewport = { 0, 0, static_cast<FLOAT>(win_info.width), static_cast<FLOAT>(win_info.height), 0.f, 1.f };
	_scissor_rect = CD3DX12_RECT( 0, 0, win_info.width, win_info.height );

	_device = make_shared<Device>();
	_cmd_queue = make_shared<CommandQueue>();
	_swap_chain = make_shared<SwapChain>();
	_desc_heap = make_shared<DescriptorHeap>();

	_device->Init();
	_cmd_queue->Init(_device->GetDevice(), _swap_chain, _desc_heap);
	_swap_chain->Init( win_info, _device->GetDxgi(), _cmd_queue->GetCmdQueue() );
	_desc_heap->Init( _device->GetDevice(), _swap_chain );
}

void Engine::Render()
{
	RenderBegin();

	// TODO: 나머지 물체를 그림

	RenderEnd();
}

void Engine::RenderBegin()
{
	_cmd_queue->RenderBegin( &_viewport, &_scissor_rect );
}

void Engine::RenderEnd()
{
	_cmd_queue->RenderEnd();
}

void Engine::ResizeWindow( int32 width, int32 height )
{
	_window.width = width;
	_window.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false );
	::SetWindowPos( _window.hwnd, 0, 100, 100, width, height, 0 );
}
