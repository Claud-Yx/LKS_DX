#pragma once

// �η� �繫��
// - GPU�� ��ȣ�ۿ�
// - �������� ���� ��� ����� �������
class Device
{
public:
	void Init();

	inline ComPtr<IDXGIFactory> GetDxgi() { return _dxgi; }
	inline ComPtr<ID3D12Device> GetDevice() { return _device; }

private:
	// COM(Component Object Model)
	// - DX�� ���α׷��� ��� �������� ���� ȣȯ���� �����ϰ� �ϴ� ���
	// - COM ��ü(COM �������̽�)�� ���, ���� ������ �츮���� ������
	// - ComPtr: ������ ����Ʈ ������
	ComPtr<ID3D12Debug>			_debug_controller;
	ComPtr<IDXGIFactory>		_dxgi;				// ȭ�� ���� ��ɵ�
	ComPtr<ID3D12Device>		_device;			// ���� ��ü ����
};

