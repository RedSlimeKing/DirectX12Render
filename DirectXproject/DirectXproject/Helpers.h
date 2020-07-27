#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h> // For HRESULT

#include <exception>
#include <iostream>

void CheckHResult(HRESULT hr);

inline void ThrowIfFailed(HRESULT hr){
	if(FAILED(hr)) {
		CheckHResult(hr);
		std::cout << "Failed!" << std::endl;
		throw std::exception();
	}
}

inline void CheckHResult(HRESULT hr){
	switch(hr){
		case S_OK:
			//std::cout << "No error occurred" << std::endl;
			break;
		case D3D12_ERROR_ADAPTER_NOT_FOUND:
			std::cout << "The specified cached PSO was created on a different adapter and cannot be reused on the current adapter." << std::endl;
			break;
		case D3D12_ERROR_DRIVER_VERSION_MISMATCH:
			std::cout << "The specified cached PSO was created on a different driver version and cannot be reused on the current adapter." << std::endl;
			break;
			// This used to be D3DERR_INVALIDCALL 
		case DXGI_ERROR_INVALID_CALL:
			std::cout << "The method call is invalid. For example, a method's parameter may not be a valid pointer." << std::endl;
			break;
			// This used to be DXGI_ERROR_WAS_STILL_DRAWING 
		case DXGI_ERROR_WAS_STILL_DRAWING:
			std::cout << "The previous blit operation that is transferring information to or from this surface is incomplete." << std::endl;
			break;
		case E_FAIL:
			std::cout << "Attempted to create a device with the debug layer enabled and the layer is not installed." << std::endl;
			break;
		case E_INVALIDARG:
			std::cout << "An invalid parameter was passed to the returning function." << std::endl;
			break;
		case E_OUTOFMEMORY:
			std::cout << "Direct3D could not allocate sufficient memory to complete the call." << std::endl;
			break;
		case E_NOTIMPL:
			std::cout << "The method call isn't implemented with the passed parameter combination." << std::endl;
			break;
		case S_FALSE:
			std::cout << "Alternate success value, indicating a successful but nonstandard completion" << std::endl;
			break;
		case ERROR_FILE_NOT_FOUND:
			std::cout << "File not found" << std::endl;
			break;
	}
}