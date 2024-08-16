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
	// CommandQueue: DX12에서 등장
	// - 외주 요청 시, 하나씩 요청하면 비효율적
	//   [외주 목록]에 일감을 차곡차곡 기록했다가 한 방에 요청하는 것
	//   <Claudy> 요청에 소요되는 오버헤드가 큰걸까?
	//	 -> 택배 보내는 것과 비슷
	ComPtr<ID3D12CommandQueue>			_cmd_queue;
	ComPtr<ID3D12CommandAllocator>		_cmd_alloc;		// 일감을 할당하기 위한 할당자(?)
	ComPtr<ID3D12GraphicsCommandList>	_cmd_list;		// 일감 목록

	// Fence: 울타리, 동기화(Sync)를 위한 객체
	// - CPU / GPU 동기화를 위한 간단한 도구
	ComPtr<ID3D12Fence>					_fence;
	uint32								_fence_value = 0;
	HANDLE								_fence_event = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>				_swap_chain;
	shared_ptr<DescriptorHeap>			_desc_heap;
};
