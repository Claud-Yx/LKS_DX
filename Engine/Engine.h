#pragma once

class Device;
class CommandQueue;
class SwapChain;
class DescriptorHeap;

class Engine
{
public:
	void Init(const WindowInfo& win_info );
	void Render();

public:
	// Command Queue�� ��û ������ �ִ� �κ�
	void RenderBegin();

	// Command Queue�� �ִ� ��û ������ ���� GPU�� ��û�ϴ� �κ�
	void RenderEnd();

	void ResizeWindow( int32 width, int32 height );

private:
	// �׷��� ȭ�� ���� Ŭ����
	WindowInfo		_window;
	D3D12_VIEWPORT	_viewport{};
	D3D12_RECT		_scissor_rect{};

	shared_ptr<Device> _device;
	shared_ptr<CommandQueue> _cmd_queue;
	shared_ptr<SwapChain> _swap_chain;
	shared_ptr<DescriptorHeap> _desc_heap;
};

