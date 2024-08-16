#pragma once

class SwapChain;

// [기안서]
// 외주를 맡길 때 필요한 정보를 같이 넘기는데 필요한 서류 양식
// - 지정된 양식대로 요청해야만 함
// - 각종 리소스를 어떤 용도로 사용하는지 꼼꼼히 적어서 넘기는 용도
// - D3D11 이전에는 View 라 불림

/**
* Note
*  - GPU가 알아먹게끔 포장해주는 Wrapping Class 로 이해하면 될 듯
*/

class DescriptorHeap
{
public:
	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swap_chain);

	inline D3D12_CPU_DESCRIPTOR_HANDLE		GetRtv( int32 index ) { return _rtv_handle[index]; }
	D3D12_CPU_DESCRIPTOR_HANDLE				GetBackBufferView();

private:
	ComPtr<ID3D12DescriptorHeap>		_rtv_heap;
	uint32								_rtv_heap_size = 0;
	D3D12_CPU_DESCRIPTOR_HANDLE			_rtv_handle[SWAP_CHAIN_BUFFER_COUNT];

	shared_ptr<SwapChain>				_swap_chain;

};

