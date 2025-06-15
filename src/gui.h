#pragma once
#include <d3d9.h>
#include <string>
#include <cstring> // For std::memcpy or std::strncpy
#include <Windows.h>

namespace gui
{
	// constant window size
	constexpr int WIDTH = 550;
	constexpr int HEIGHT = 440;

	// when this changes, exit threads
	// and close menu :)
	inline bool isRunning = true;

	// winapi window vars
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };

	// points for window movement
	inline POINTS position = { };

	// direct x state vars
	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	// handle window creation & destruction
	void CreateHWindow(const char* windowName) noexcept;
	void DestroyHWindow() noexcept;

	// handle device creation & destruction
	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	// handle ImGui creation & destruction
	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	// handle ImGui fonts
	void handleFont() noexcept;
	// render function
	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;
}