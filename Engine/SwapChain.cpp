#include "pch.h"
#include "SwapChain.h"

/**
* Note
*  - Scanline Ordering: ���÷��̿��� ������ �� �� ��ĵ����(������)�� �׷����� ����
*    - Progressive Scan (���� �ֻ�)
*      - ��� ��ĵ������ ������������, ��, ������ �Ʒ��� ���������� ȭ���� �׸�
*      - ���� ���÷���(��κ��� LCD����� ��)���� �Ϲ������� ����.
*      - �̹��� ǰ���� ���� ���� �������� ǥ���ϴµ� ����
*      -> DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE
*    - Interlaced Scan (���ͷ��̽� �ֻ�)
*      - Ȧ¦ ��ĵ������ �����ư��� �׸��� ���. Ȧ�� ���� �׸��� ������ ����
*      - 60fps�� ��, 1/60�ʿ� Ȧ��, 1/60�ʿ� ¦�� �� �׸��� ��
*      - ���� CRT �����, TV ��� ���Ǵ� ���
*      - �뿪�� ���࿡ �����ϳ� ���� �������� �������̳� �ܻ� ȿ���� ��Ÿ�� �� ����
*      -> DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST (¦�� ����)
*      -> DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST (Ȧ�� ����)
*    - Unspecifed (������)
*      - ��ĵ���� ������ ��������� �������� ����
*      - �ý��� �Ǵ� ����̹��� �⺻ ������ ���� ������ ó��
*      -> DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED
* 
*  - Scaling: ȭ�� �� �������� ���÷��� �ػ󵵿� ��ġ���� ���� ��, �ش� ������ ���� ���
*    - Centered (�߾� ��ġ)
*      - ���� �ػ��� �������� ȭ�� �߾ӿ� ��ġ, ���� �κ�(���÷��� �� ȭ���� ������ ����)�� ä���� ����
*      - ���� �κ��� �Ϲ������� ���������� ä����
*      - �̹��� �ְ��� ������ ȭ�� �Ϻ� ������ ��
*      -> DXGI_MODE_SCALING_CENTERED
*    - Stretched (Ȯ��)
*      - ���� �ػ��� �������� ȭ�� ��ü(���÷��� ���� �ػ�)�� ���ߵ��� �ø��ų� ����
*      - ȭ��� ���� ������ �̹��� �ְ��� �߻�
*      -> DXGI_MODE_SCALING_STRETCHED
*    - Aspect Ratio Preserved (���� ����)
*      - �������� ȭ��� �����ϸ鼭 ȭ�鿡 ���� ����(�ø��ų� ����)
*      - ���� �Ǵ� ���� �� �� �κ��� ȭ���� �� ���� ���� �� ������ ���� ���� �κ��� ���������� ä���� �� ����
*      - ���⼭�� ���� �츦 ���͹ڽ� �Ǵ� �ʷ��ڽ� ��� ��
*      -> DXGI ���� �������� ���� !!!
*    - Unspecified (������)
*      - Ư���� �������� ������ ����Ʈ ���� �Ǵ� �ý��� ������ ���� �ڵ� ó��
*      -> DXGI_MODE_SCALING_UNSPECIFIED
*/

void SwapChain::Init( const WindowInfo& win_info, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmd_queue )
{
	// ���� ������ ����, Init�� �� �� �Ѱ� �ƴ� �̻� ��� �ʿ� ����
	_swap_chain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width  = static_cast<uint32>(win_info.width);    // ���� �ػ� �ʺ�
	sd.BufferDesc.Height = static_cast<uint32>(win_info.height);   // ���� �ػ� ����
	sd.BufferDesc.RefreshRate.Numerator = 60;	// ȭ�� ���� ����(������ ��)
	sd.BufferDesc.RefreshRate.Denominator = 1;	// ȭ�� ���� ����(�� ��)
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// ������ ���÷��� ����
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1; // ��Ƽ ���ø� Off
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// �ĸ� ���ۿ� �������� ��
	sd.BufferCount = SWAP_CHAIN_BUFFER_COUNT;	// ���� + �ĸ� ����
	sd.OutputWindow = win_info.hwnd;
	sd.Windowed = win_info.windowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	// ���� �ĸ� ���� ��ü �� ���� ������ ���� ����
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	dxgi->CreateSwapChain( cmd_queue.Get(), &sd, &_swap_chain );

	for ( int32 i = 0; i < SWAP_CHAIN_BUFFER_COUNT; ++i )
	{
		_swap_chain->GetBuffer( i, IID_PPV_ARGS( &_render_targets[i] ) );
	}
}

void SwapChain::Present()
{
	// Present the frame
	_swap_chain->Present( 0, 0 );
}

void SwapChain::SwapIndex()
{
	_back_buffer_index = (_back_buffer_index + 1) % SWAP_CHAIN_BUFFER_COUNT;
}
