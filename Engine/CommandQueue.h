#pragma once

class SwapChain;
class DescriptorHeap;

class CommandQueue
{
public:
	~CommandQueue();

public:
	void Init( ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swap_chain, shared_ptr<DescriptorHeap> desc_heap );
	void WaitSync();

	void RenderBegin( const D3D12_VIEWPORT* viewport, const D3D12_RECT* rect );
	void RenderEnd();

	inline ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _cmd_queue; }

private:
	// CommandQueue: DX12���� ����
	// - ���� ��û ��, �ϳ��� ��û�ϸ� ��ȿ����
	//   [���� ���]�� �ϰ��� �������� ����ߴٰ� �� �濡 ��û�ϴ� ��
	//   <Claudy> ��û�� �ҿ�Ǵ� ������尡 ū�ɱ�?
	//	 -> �ù� ������ �Ͱ� ���
	ComPtr<ID3D12CommandQueue>			_cmd_queue;
	ComPtr<ID3D12CommandAllocator>		_cmd_alloc;		// �ϰ��� �Ҵ��ϱ� ���� �Ҵ���(?)
	ComPtr<ID3D12GraphicsCommandList>	_cmd_list;		// �ϰ� ���

	// Fence: ��Ÿ��, ����ȭ(Sync)�� ���� ��ü
	// - CPU / GPU ����ȭ�� ���� ������ ����
	ComPtr<ID3D12Fence>					_fence;
	uint32								_fence_value = 0;
	HANDLE								_fence_event = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>				_swap_chain;
	shared_ptr<DescriptorHeap>			_desc_heap;
};
