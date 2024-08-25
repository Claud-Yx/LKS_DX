#pragma once

// [계약서 / 결재]

// CPU  [        ]  | GPU    [        ]
// 한국 [        ]  | 베트남 [        ]

// Note:
// - 어떤 공간을 사용하고 어떤 리소스를 사용할지 작성하고 적는 계약서 같은?

class RootSignature
{
public:
	void Init( ComPtr<ID3D12Device> device );

	ComPtr<ID3D12RootSignature> GetSignature() { return _signature; }

private:
	ComPtr<ID3D12RootSignature> _signature;
};

