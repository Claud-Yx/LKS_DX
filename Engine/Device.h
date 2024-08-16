#pragma once

// 인력 사무소
// - GPU와 상호작용
// - 예전에는 거의 모든 기능을 담당했음
class Device
{
public:
	void Init();

	inline ComPtr<IDXGIFactory> GetDxgi() { return _dxgi; }
	inline ComPtr<ID3D12Device> GetDevice() { return _device; }

private:
	// COM(Component Object Model)
	// - DX의 프로그래밍 언어 독립성과 하위 호환성을 가능하게 하는 기술
	// - COM 객체(COM 인터페이스)를 사용, 세부 사항은 우리한테 숨겨짐
	// - ComPtr: 일종의 스마트 포인터
	ComPtr<ID3D12Debug>			_debug_controller;
	ComPtr<IDXGIFactory>		_dxgi;				// 화면 관련 기능들
	ComPtr<ID3D12Device>		_device;			// 각종 객체 생성
};

