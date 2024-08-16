#pragma once

// Swap Chain (��ȯ �罽)
// - ���� ���� ���� �ִ� ��Ȳ�� ����
// - � �������� ��� ������� ������
// - GPU�� ������ ��� (����)
// - ������� �޾� ȭ�鿡 �׸�

// [���� �����]�� ��� ����?
// - � ����(Buffer)�� �׷��� �ǳ��޶�� ��Ź��
// - Ư�� ���̸� ���� -> ó���� �ǳ��� -> ������� �ش� ���̿� ����
// - �츮 ȭ�鿡 Ư�� ����(���� �����)�� ���

// [?]
// - �׷��� ȭ�鿡 ���� ������� ����ϴ� ���߿� ���� ȭ�� ���ֵ� �ðܾ� ��
// - ���� ȭ�� ������� �̹� ȭ�� ��¿� �����
// - Ư�� ���̸� 2�� ���� �ϳ��� ���� ȭ��, �ٸ� �ϳ��� ���ָ� �ñ�
// -> Double Buffering

// - [0] [1]
// ���� ȭ�� [0] <-> GPU �۾��� [1] BackBuffer

/**
* Note
*  - ���� ����, Double Buffing �ϴ� ����
*  - �ӽ�Ű�͵��� �ο�� ����� ���
*/

class SwapChain
{
public:
	void Init( const WindowInfo& win_info, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmd_queue );
	void Present();
	void SwapIndex();

	inline ComPtr<IDXGISwapChain> GetSwapChain() { return _swap_chain; }
	inline ComPtr<ID3D12Resource> GetRenderTarget( int32 index ) { return _render_targets[index]; }

	inline uint32 GetCurrentBackBufferIndex() { return _back_buffer_index; }
	inline ComPtr<ID3D12Resource> GetCurrentBackBufferResource() { return _render_targets[_back_buffer_index]; }

private:
	ComPtr<IDXGISwapChain>	_swap_chain;
	ComPtr<ID3D12Resource>	_render_targets[SWAP_CHAIN_BUFFER_COUNT];
	uint32					_back_buffer_index = 0;

};

