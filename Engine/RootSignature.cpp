#include "pch.h"
#include "RootSignature.h"

void RootSignature::Init( ComPtr<ID3D12Device> device )
{
	D3D12_ROOT_SIGNATURE_DESC sig_desc = CD3DX12_ROOT_SIGNATURE_DESC( D3D12_DEFAULT );
	sig_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT; // 입력 조립기 단계

	ComPtr<ID3DBlob> blob_signature;
	ComPtr<ID3DBlob> blob_error;
	::D3D12SerializeRootSignature( &sig_desc, D3D_ROOT_SIGNATURE_VERSION_1, &blob_signature, &blob_error );
	device->CreateRootSignature( 0, blob_signature->GetBufferPointer(), blob_signature->GetBufferSize(), IID_PPV_ARGS( &_signature ) );
}
