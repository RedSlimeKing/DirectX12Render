#pragma once
#define WIN32_LEAN_AND_MEAN

// DirectX 12 specific headers.
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3dcompiler.lib")



// Windows Runtime Library. Needed for Microsoft::WRL::ComPtr<> template class.
#include <wrl.h>

#include "Rect.h"

class DirectXAPI{
public:
	static DirectXAPI* GetInstance();

	void Init(HWND windowhandle, Rect windowRect);
	void Render();
	void Resize(uint32_t width, uint32_t height);
	void Destroy();
private:
	// For init DirectX
	void EnableDebugLayer();
	Microsoft::WRL::ComPtr<IDXGIAdapter4> GetAdapter(bool useWarp);
	Microsoft::WRL::ComPtr<ID3D12Device2> CreateDevice(Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter);
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> CreateCommandQueue(Microsoft::WRL::ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
	bool CheckTearingSupport();
	Microsoft::WRL::ComPtr<IDXGISwapChain4> CreateSwapChain(HWND hWnd, Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue, uint32_t width, uint32_t height, uint32_t bufferCount);
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(Microsoft::WRL::ComPtr<ID3D12Device2> device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors);
	void UpdateRenderTargetViews(Microsoft::WRL::ComPtr<ID3D12Device2> device, Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap);

	// Waiting for frame
	void WaitForPreviousFrame();

	// Temp here so I can load the triangle
	void LoadAssets();

	// Pre commands 
	void PopulateCommandList();
private:
	static DirectXAPI* instance;
	
	// Set to true once the DX12 objects have been initialized.
	bool mIsInitialized = false;
	// By default, enable V-Sync.
	bool mVSync = true;
	bool mTearingSupported = false;
	// By default, use windowed mode.
	bool mFullscreen = false;
	// Use WARP adapter - software rasterizer (Windows Advanced Rasterization Platform - WARP) 
	bool mUseWarp = false;
	// The number of back buffers for the swap chain.
	static const uint8_t mNumFrames = 4;
	D3D12_VIEWPORT m_viewport;
	D3D12_RECT m_scissorRect;

	// Pipline objects
	Microsoft::WRL::ComPtr<ID3D12Device2> mDevice;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>  mCommandQueue;
	// IDXGISwapChain4 interface defines swap chain - Responsible for resenting the rendered image to window
	// Created with a number of back buffers resources
	Microsoft::WRL::ComPtr<IDXGISwapChain4> mSwapChain;
	// all back buffers &  textures  are referenced by ID3D12Resource
	Microsoft::WRL::ComPtr<ID3D12Resource> mRenderTargets[mNumFrames];
	// Used to store descriptor heap that contains render target views for swap chain back buffers
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRTVDescriptorHeap;
	// Serves as backing memory for recording Gpu commands into command list cannot be reused unless all 
	//commands that have been recorded are finished executing on gpu
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mCommandAllocator;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> mRootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> mPipelineState;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> mCommandList;
	UINT mRTVDescriptorSize;

	// Synchronization objects
	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
	// handle to OS event object used to receive the notification that fence has reached value
	HANDLE mFenceEvent;
	// the next fence value to signal is stored below
	uint64_t mFenceValue;
	UINT mframeIndex;

private:
	struct Vertex
	{
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 color;
	};

	float mAspectRatio;

	// App resources.
	Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
};

