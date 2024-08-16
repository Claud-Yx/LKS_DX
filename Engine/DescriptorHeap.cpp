#include "pch.h"
#include "DescriptorHeap.h"
#include "SwapChain.h"

void DescriptorHeap::Init( ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swap_chain )
{
	_swap_chain = swap_chain;

	// Descriptor (DX12) = View (~DX11)
	// [������ ��] ���� RTV(Render Target View) ����
	// DX11�� RTV, DSV(Depth Stencil View)
	// CBV(Constant Buffer View), SRV(Shader Resource View), UAV(UnorderedAccessView) ����

	_rtv_heap_size = device->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );

	D3D12_DESCRIPTOR_HEAP_DESC rd;
	rd.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rd.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
	rd.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rd.NodeMask = 0;

	// ���� ������ �����ͳ��� �迭�� ����
	// RTV ���: [] []
	device->CreateDescriptorHeap( &rd, IID_PPV_ARGS( &_rtv_heap ) );

	D3D12_CPU_DESCRIPTOR_HANDLE rtv_heap_begin = _rtv_heap->GetCPUDescriptorHandleForHeapStart();

	for ( int32 i{}; i < SWAP_CHAIN_BUFFER_COUNT; ++i )
	{
		_rtv_handle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE( rtv_heap_begin, i * _rtv_heap_size );
		device->CreateRenderTargetView( swap_chain->GetRenderTarget( i ).Get(), nullptr, _rtv_handle[i] );
	}
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetBackBufferView()
{
	return GetRtv(_swap_chain->GetCurrentBackBufferIndex());
}
