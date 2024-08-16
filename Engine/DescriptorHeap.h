#pragma once

class SwapChain;

// [��ȼ�]
// ���ָ� �ñ� �� �ʿ��� ������ ���� �ѱ�µ� �ʿ��� ���� ���
// - ������ ��Ĵ�� ��û�ؾ߸� ��
// - ���� ���ҽ��� � �뵵�� ����ϴ��� �Ĳ��� ��� �ѱ�� �뵵
// - D3D11 �������� View �� �Ҹ�

/**
* Note
*  - GPU�� �˾Ƹ԰Բ� �������ִ� Wrapping Class �� �����ϸ� �� ��
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

