#pragma once

// Swap Chain (교환 사슬)
// - 현재 게임 세상에 있는 상황을 묘사
// - 어떤 공식으로 어떻게 계산할지 던져줌
// - GPU가 열심히 계산 (외주)
// - 결과물을 받아 화면에 그림

// [외주 결과물]을 어디에 받지?
// - 어떤 종이(Buffer)에 그려서 건내달라고 부탁함
// - 특수 종이를 만듦 -> 처음에 건내줌 -> 결과물을 해당 종이에 받음
// - 우리 화면에 특수 종이(외주 결과물)를 출력

// [?]
// - 그런데 화면에 현재 결과물을 출력하는 와중에 다음 화면 외주도 맡겨야 함
// - 현재 화면 결과물은 이미 화면 출력에 사용중
// - 특수 종이를 2개 만들어서 하나는 현재 화면, 다른 하나는 외주를 맡김
// -> Double Buffering

// - [0] [1]
// 현재 화면 [0] <-> GPU 작업중 [1] BackBuffer

/**
* Note
*  - 쉽게 말해, Double Buffing 하는 애임
*  - 머스키터들이 싸우는 방식을 상상
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

