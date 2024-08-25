#pragma once

// 3D모델링과 같이 정점으로 이루어진 물체
class Mesh
{
public:
	void Init( vector<Vertex>& vec );
	void Render();

private:
	ComPtr<ID3D12Resource>		_vertex_buffer;
	D3D12_VERTEX_BUFFER_VIEW	_vertex_buffer_view = {};
	uint32						_vertex_count = 0;
};

