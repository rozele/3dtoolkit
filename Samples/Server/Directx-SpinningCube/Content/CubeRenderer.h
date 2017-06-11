#pragma once

#include "DeviceResources.h"

namespace Toolkit3DSample
{
	// Constant buffer used to send MVP matrices to the vertex shader.
	struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

	// Used to send per-vertex data to the vertex shader.
	struct VertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};

	class CubeRenderer
	{
	public:
												CubeRenderer(DX::DeviceResources* deviceResources);
		void									InitGraphics();
		void									InitPipeline();
		void									Update();
		void									Render();
#ifdef STEREO_OUTPUT_MODE
		void									UpdateViewMatrices(const DirectX::XMFLOAT4X4& viewLeft, const DirectX::XMFLOAT4X4& viewRight);
#endif // STEREO_OUTPUT_MODE

	private:
		// Cached pointer to device resources.
		DX::DeviceResources*					m_deviceResources;

		// Direct3D resources for cube geometry.
		ID3D11Buffer*							m_vertexBuffer;
		ID3D11Buffer*							m_indexBuffer;
		ID3D11Buffer*							m_constantBuffer;
		ID3D11VertexShader*						m_vertexShader;
		ID3D11PixelShader*						m_pixelShader;
		ID3D11InputLayout*						m_inputLayout;

		// System resources for cube geometry.
#ifdef STEREO_OUTPUT_MODE
		ModelViewProjectionConstantBuffer		m_constantBufferDataLeft;
		ModelViewProjectionConstantBuffer		m_constantBufferDataRight;
#else // STEREO_OUTPUT_MODE
		ModelViewProjectionConstantBuffer		m_constantBufferData;
#endif // STEREO_OUTPUT_MODE
		uint32_t								m_indexCount;

		// Variables used with the rendering loop.
		float									m_degreesPerSecond;
	};
}
