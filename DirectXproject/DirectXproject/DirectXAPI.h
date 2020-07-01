#pragma once
#define WIN32_LEAN_AND_MEAN

// DirectX 12 specific headers.
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// STL Headers
#include <algorithm>
#include <cassert>
#include <chrono>

// Windows Runtime Library. Needed for Microsoft::WRL::ComPtr<> template class.
#include <wrl.h>
using namespace Microsoft::WRL;

class DirectXAPI{
public:
	static DirectXAPI* GetInstance();

	void Init();
	void StartRender();
	void Render();
	void Resize(uint32_t width, uint32_t height);
	void Destroy();
private:
	void EnableDebugLayer();
	ComPtr<IDXGIAdapter4> GetAdapter(bool useWarp);
	ComPtr<ID3D12Device2> CreateDevice(ComPtr<IDXGIAdapter4> adapter);
	ComPtr<ID3D12CommandQueue> CreateCommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
	bool CheckTearingSupport();
	ComPtr<IDXGISwapChain4> CreateSwapChain(HWND hWnd, ComPtr<ID3D12CommandQueue> commandQueue, uint32_t width, uint32_t height, uint32_t bufferCount);
	ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(ComPtr<ID3D12Device2> device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors);
	void UpdateRenderTargetViews(ComPtr<ID3D12Device2> device, ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descriptorHeap);
	ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
	ComPtr<ID3D12GraphicsCommandList> CreateCommandList(ComPtr<ID3D12Device2> device, ComPtr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type);
	ComPtr<ID3D12Fence> CreateFence(ComPtr<ID3D12Device2> device);
	HANDLE CreateEventHandle();
	uint64_t Signal(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue);
	void WaitForFenceValue(ComPtr<ID3D12Fence> fence, uint64_t fenceValue, HANDLE fenceEvent, std::chrono::milliseconds duration);
	void Flush(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue, HANDLE fenceEvent);

private:
	static DirectXAPI* instance;
	// The number of back buffers for the swap chain.
	static const uint8_t g_NumFrames = 3;
	// Use WARP adapter - software rasterizer (Windows Advanced Rasterization Platform - WARP) 
	bool g_UseWarp = false;

	uint32_t g_ClientWidth = 1280;
	uint32_t g_ClientHeight = 720;

	// Set to true once the DX12 objects have been initialized.
	bool g_IsInitialized = false;

	// Window rectangle (used to toggle fullscreen state).
	RECT g_WindowRect;

	// DirectX 12 Objects
	// Dx12 Device object
	ComPtr<ID3D12Device2> g_Device;
	// Dx12 command queue
	ComPtr<ID3D12CommandQueue> g_CommandQueue;
	// IDXGISwapChain4 interface defines swap chain - Responsible for resenting the rendered image to window
	// Created with a number of back buffers resources
	ComPtr<IDXGISwapChain4> g_SwapChain;
	// Pointers to said back buffers tracked
	// all back buffers &  textures  are referenced by ID3D12Resource
	ComPtr<ID3D12Resource> g_BackBuffers[g_NumFrames];
	// GPU commands are recorded into ID3D12GraphicsCommandList - uses a single thread with more commandList using different threads
	ComPtr<ID3D12GraphicsCommandList> g_CommandList;
	
	ComPtr<ID3D12CommandAllocator> g_CommandAllocators[g_NumFrames];
	// Used to store descriptor heap that contains render target views for swap chain back buffers
	ComPtr<ID3D12DescriptorHeap> g_RTVDescriptorHeap;
	// size of single rvt descriptor 
	UINT g_RTVDescriptorSize;
	// Depending on flip odel of swap chain the index of current back buffer may not be sequential / hold creent index
	UINT g_CurrentBackBufferIndex;

	// Synchronization objects
	ComPtr<ID3D12Fence> g_Fence;
	// the next fence alue to signal is stored below
	uint64_t g_FenceValue = 0;
	// ised to track fence values that used to signal command queue for particular frame
	uint64_t g_FrameFenceValues[g_NumFrames] = {};
	// handle to OS event object used to receive the notification that fence has reached value
	HANDLE g_FenceEvent;

	// By default, enable V-Sync.
	// Can be toggled with the V key.
	bool g_VSync = true;
	bool g_TearingSupported = false;
	// By default, use windowed mode.
	// Can be toggled with the Alt+Enter or F11
	bool g_Fullscreen = false;

	//Rendering space
	// Serves as backing memory for recording Gpu commands into command list cannot be reused unless all commands that have been recorded
	// are finished executing on gpu
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12Resource> backBuffer;

};



/*
	- Register the window class
	- Create the window
	- Query the GPU adapters
	- Create a DirectX 12 device
	- Create a command queue
	- Create a swap chain
	- Create command allocator & command list
	- Handle GPU synchronization
	- Update & Render
	- Handle resizing
	- Handle full-screen toggling
*/