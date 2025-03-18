#pragma once

// [일감 기술서] 외주 인력들이 뭘 해야할지 기술
class Shader
{
public:
	void Init( const wstring& path );
	void Update();

private:
	void CreateShader(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shader_byte_code );
	void CreateVertexShader(const wstring& path, const string& name, const string& version);
	void CreatePixelShader(const wstring& path, const string& name, const string& version);

private:
	ComPtr<ID3DBlob>					_vs_blob;
	ComPtr<ID3DBlob>					_ps_blob;
	ComPtr<ID3DBlob>					_err_blob;

	ComPtr<ID3D12PipelineState>			_pipeline_state;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC	_pipeline_desc = {};
};

