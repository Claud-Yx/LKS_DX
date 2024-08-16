#include "pch.h"

#include "CommandQueue.h"
#include "SwapChain.h"
#include "DescriptorHeap.h"

/**
* Note
*  - device�� �ϰ��� �������ְ��ֳ�?
*/

CommandQueue::~CommandQueue()
{
	::CloseHandle( _fence_event );
}

void CommandQueue::Init( ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swap_chain, shared_ptr<DescriptorHeap> desc_heap )
{
	_swap_chain = swap_chain;
	_desc_heap = desc_heap;

	D3D12_COMMAND_QUEUE_DESC queue_desc{};
	queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	device->CreateCommandQueue( &queue_desc, IID_PPV_ARGS( &_cmd_queue ) );

	// - D3D12_COMMAND_LIST_TYPE_DIRECT: GPU�� ���� �����ϴ� ��� ���
	device->CreateCommandAllocator( D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS( &_cmd_alloc ) );

	// GPU�� �ϳ��� �ý����� 0
	// DIRECT or BUNDLE
	// Allocator
	// �ʱ� ���� (�׸��� ����� nullptr ����)
	device->CreateCommandList( 0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmd_alloc.Get(), nullptr, IID_PPV_ARGS( &_cmd_list ) );

	// CommandList�� Close / Open ���°� ����
	// Open ����: Command ����
	// Close ����: ���� ���� �ؾ� ��
	// <ClaudY> file access �� ����� ��
	_cmd_list->Close();

	// CreateFence
	// - CPU�� GPU�� ����ȭ ����
	device->CreateFence( 0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS( &_fence ) );
	_fence_event = ::CreateEvent( nullptr, FALSE, FALSE, nullptr );

}

void CommandQueue::WaitSync()
{
	// Advance the fence value to mark commands up to this vence point.
	++_fence_value;

	// Add an instruction to the command queue to set a new fence point.
	// Because we are on the GPU timeline, the new fence point won't be set until the GPU
	// finishes processing all the commands prior to this Signal().
	_cmd_queue->Signal( _fence.Get(), _fence_value );

	// Wait until the GPU has compoleted commands up to this fence point.
	if ( _fence->GetCompletedValue() < _fence_value )
	{
		// Fire event when GPU hits current fence.
		_fence->SetEventOnCompletion( _fence_value, _fence_event );

		// Wait until the GPU hits current fence event is fired.
		::WaitForSingleObject( _fence_event, INFINITE );
	}
}

void CommandQueue::RenderBegin( const D3D12_VIEWPORT* viewport, const D3D12_RECT* rect )
{
	_cmd_alloc->Reset();
	_cmd_list->Reset( _cmd_alloc.Get(), nullptr );

	// ���� ����� ���ҽ�(ȭ�� �����)�� ���� ����������� �ٲ�
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swap_chain->GetCurrentBackBufferResource().Get(),
		D3D12_RESOURCE_STATE_PRESENT,		// ȭ�� ���
		D3D12_RESOURCE_STATE_RENDER_TARGET	// ���� �����
	);

	_cmd_list->ResourceBarrier( 1, &barrier );

	// Set the viewport and scissor rect. This needs to be reset whenever the command list is reset.
	_cmd_list->RSSetViewports( 1, viewport );
	_cmd_list->RSSetScissorRects( 1, rect );

	// Specify the buffers we are going to render to.
	D3D12_CPU_DESCRIPTOR_HANDLE back_buffer_view = _desc_heap->GetBackBufferView();
	_cmd_list->ClearRenderTargetView( back_buffer_view, Colors::LightSteelBlue, 0, nullptr );
	_cmd_list->OMSetRenderTargets( 1, &back_buffer_view, FALSE, nullptr );
}

void CommandQueue::RenderEnd()
{
	// Begin������ ������ �ݴ�, �ٽ� swap ��
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swap_chain->GetCurrentBackBufferResource().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,	// ���� �����
		D3D12_RESOURCE_STATE_PRESENT		// ȭ�� ���
	);

	_cmd_list->ResourceBarrier( 1, &barrier );
	_cmd_list->Close();

	// Ŀ�ǵ� ����Ʈ ����
	ID3D12CommandList* cmd_list_array[] = { _cmd_list.Get() };
	_cmd_queue->ExecuteCommandLists( _countof( cmd_list_array ), cmd_list_array );

	_swap_chain->Present();	// ������ ������ �ϴ� �Լ�

	// Wait until frame commands are complete. This waiting is inefficient and is
	// done for simplicity. Later we will show how to organize our rendering code
	// so we do not have to wait per frame.
	WaitSync();	// Command Queue�� �ϰ��� ���� �� ���� ��ٸ�

	_swap_chain->SwapIndex();
}
