#include "pch.h"
#include "SwapChain.h"

/**
* Note
*  - Scanline Ordering: 디스플레이에서 렌더링 시 각 스캔라인(가로줄)이 그려지는 순서
*    - Progressive Scan (순차 주사)
*      - 모든 스캔라인을 순ㅊ차적으로, 즉, 위에서 아래로 연속적으로 화면을 그림
*      - 현대 디스플레이(대부분의 LCD모니터 등)에서 일반적으로 사용됨.
*      - 이미지 품질이 고르고 빠른 움직임을 표현하는데 유리
*      -> DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE
*    - Interlaced Scan (인터레이스 주사)
*      - 홀짝 스캔라인을 번갈아가며 그리는 방식. 홀수 줄을 그리는 것으로 시작
*      - 60fps일 때, 1/60초에 홀수, 1/60초에 짝수 를 그리는 식
*      - 예전 CRT 모니터, TV 등에서 사용되던 방식
*      - 대역폭 절약에 유리하나 빠른 움직에서 깜빡임이나 잔산 효과가 나타날 수 있음
*      -> DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST (짝수 먼저)
*      -> DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST (홀수 먼저)
*    - Unspecifed (미지정)
*      - 스캔라인 순서를 명시적으로 지정하지 않음
*      - 시스템 또는 드라이버가 기본 설정에 따라 적절히 처리
*      -> DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED
* 
*  - Scaling: 화면 내 콘텐츠가 디스플레이 해상도와 일치하지 않을 때, 해당 콘텐츠 조정 방법
*    - Centered (중앙 배치)
*      - 원본 해상도의 콘텐츠가 화면 중앙에 배치, 남는 부분(디스플레이 상 화면의 나머지 영역)은 채우지 않음
*      - 남는 부분은 일반적으로 검은색으로 채워짐
*      - 이미지 왜곡은 없지만 화면 일부 영역이 빔
*      -> DXGI_MODE_SCALING_CENTERED
*    - Stretched (확장)
*      - 원본 해상도의 컨텐츠를 화면 전체(디스플레이 상의 해상도)에 맞추도록 늘리거나 줄임
*      - 화면비가 맞지 않으면 이미지 왜곡이 발생
*      -> DXGI_MODE_SCALING_STRETCHED
*    - Aspect Ratio Preserved (비율 유지)
*      - 콘텐츠의 화면비를 유지하면서 화면에 맞춰 조정(늘리거나 줄임)
*      - 가로 또는 세로 중 한 부분의 화면이 꽉 차지 않을 수 있으며 역시 남는 부분은 검은색으로 채워질 수 있음
*      - 여기서의 검은 띠를 레터박스 또는 필러박스 라고 함
*      -> DXGI 에서 지원하지 않음 !!!
*    - Unspecified (미지정)
*      - 특별히 지정하지 않으며 디폴트 설정 또는 시스템 설정에 따라 자동 처리
*      -> DXGI_MODE_SCALING_UNSPECIFIED
*/

void SwapChain::Init( const WindowInfo& win_info, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmd_queue )
{
	// 이전 정보를 날림, Init을 두 번 한게 아닌 이상 사실 필요 없음
	_swap_chain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width  = static_cast<uint32>(win_info.width);    // 버퍼 해상도 너비
	sd.BufferDesc.Height = static_cast<uint32>(win_info.height);   // 버퍼 해상도 높이
	sd.BufferDesc.RefreshRate.Numerator = 60;	// 화면 갱신 비율(프레임 수)
	sd.BufferDesc.RefreshRate.Denominator = 1;	// 화면 갱신 비율(초 당)
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 버퍼의 디스플레이 형식
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1; // 멀티 샘플링 Off
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// 후면 버퍼에 랜더링할 것
	sd.BufferCount = SWAP_CHAIN_BUFFER_COUNT;	// 전면 + 후면 버퍼
	sd.OutputWindow = win_info.hwnd;
	sd.Windowed = win_info.windowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	// 전면 후면 버퍼 교체 시 이전 프레임 정보 버림
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
