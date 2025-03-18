#include "pch.h"
#include "Shader.h"
#include "Engine.h"

void Shader::Init( const wstring& path )
{
	CreateVertexShader( path, "VS_Main", "vs_5_0" );
	CreatePixelShader( path, "PS_Main", "ps_5_0" );

	D3D12_INPUT_ELEMENT_DESC desc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
	};

	_pipeline_desc.InputLayout = { desc, _countof( desc ) };
	_pipeline_desc.pRootSignature = ROOT_SIGNATURE.Get();

	_pipeline_desc.RasterizerState = CD3DX12_RASTERIZER_DESC( D3D12_DEFAULT );
	_pipeline_desc.BlendState = CD3DX12_BLEND_DESC( D3D12_DEFAULT );
	_pipeline_desc.DepthStencilState.DepthEnable = FALSE;
	_pipeline_desc.DepthStencilState.StencilEnable = FALSE;
	_pipeline_desc.SampleMask = UINT_MAX;
	_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	_pipeline_desc.NumRenderTargets = 1;
	_pipeline_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	_pipeline_desc.SampleDesc.Count = 1;

	DEVICE->CreateGraphicsPipelineState( &_pipeline_desc, IID_PPV_ARGS( &_pipeline_state ) );
}

void Shader::Update()
{
	CMD_LIST->SetPipelineState( _pipeline_state.Get() );
}

void Shader::CreateShader( const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shader_byte_code )
{
	uint32 compile_flag = 0;

#ifdef _DEBUG
	compile_flag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	if ( FAILED( ::D3DCompileFromFile( path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, name.c_str(), version.c_str(), compile_flag, 0, &blob, &_err_blob ) ) )
	{
		::MessageBoxA( nullptr, "Shader Create Failed !", nullptr, MB_OK );
	}

	shader_byte_code = { blob->GetBufferPointer(), blob->GetBufferSize() };
}

void Shader::CreateVertexShader( const wstring& path, const string& name, const string& version )
{
	CreateShader( path, name, version, _vs_blob, _pipeline_desc.VS );
}

void Shader::CreatePixelShader( const wstring& path, const string& name, const string& version )
{
	CreateShader( path, name, version, _ps_blob, _pipeline_desc.PS );
}
