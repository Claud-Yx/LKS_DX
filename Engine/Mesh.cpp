#include "pch.h"
#include "Engine.h"
#include "Mesh.h"

void Mesh::Init( vector<Vertex>& vec )
{
	_vertex_count = static_cast<uint32>(vec.size());
	uint32 buffer_size = _vertex_count * sizeof( Vertex );

	D3D12_HEAP_PROPERTIES heap_property = CD3DX12_HEAP_PROPERTIES( D3D12_HEAP_TYPE_UPLOAD );
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer( buffer_size );

	// GPU 메모리에 공간 할당해서 리소스 생성
	DEVICE->CreateCommittedResource(
		&heap_property,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS( &_vertex_buffer )
	);

	// Copy the triangle data to the vertex buffer
	void* vertex_data_buffer{};
	CD3DX12_RANGE read_range( 0, 0 ); // We do not intend to read from this resource on the CPU
	_vertex_buffer->Map( 0, &read_range, &vertex_data_buffer );
	::memcpy( vertex_data_buffer, &vec[0], buffer_size );
	_vertex_buffer->Unmap( 0, nullptr );

	// Initialize the vertex buffer view
	_vertex_buffer_view.BufferLocation = _vertex_buffer->GetGPUVirtualAddress();
	_vertex_buffer_view.StrideInBytes = sizeof( Vertex ); // 정점 1개 크기
	_vertex_buffer_view.SizeInBytes = buffer_size; //버퍼 크기
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	CMD_LIST->IASetVertexBuffers( 0, 1, &_vertex_buffer_view ); // Slot: (0~15)
	CMD_LIST->DrawInstanced( _vertex_count, 1, 0, 0 );
}
