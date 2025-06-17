#define _CRT_SECURE_NO_WARNINGS
#include "gui.h"
#include <string>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#include "font/myFont.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include "vars.h"
#include "Click.h"

#define WNDPROC_FUNC LRESULT CALLBACK
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

WNDPROC_FUNC WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{
	case WM_SIZE: {
		if (gui::device && wideParameter != SIZE_MINIMIZED)
		{
			gui::presentParameters.BackBufferWidth = LOWORD(longParameter);
			gui::presentParameters.BackBufferHeight = HIWORD(longParameter);
			gui::ResetDevice();
		}
	}return 0;

	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
	}return 0;

	case WM_LBUTTONDOWN: {
		gui::position = MAKEPOINTS(longParameter); // set click points
	}return 0;

	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(longParameter);
			auto rect = ::RECT{ };

			GetWindowRect(gui::window, &rect);

			rect.left += points.x - gui::position.x;
			rect.top += points.y - gui::position.y;

			if (gui::position.x >= 0 &&
				gui::position.x <= gui::WIDTH &&
				gui::position.y >= 0 && gui::position.y <= 19)
				SetWindowPos(
					gui::window,
					HWND_TOPMOST,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
		}

	}return 0;

	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}

void gui::CreateHWindow(const char* windowName) noexcept
{
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = "class001";
	windowClass.hIconSm = 0;

	RegisterClassEx(&windowClass);

	window = CreateWindowEx(
		0,
		"class001",
		windowName,
		WS_POPUP,
		100,
		100,
		WIDTH,
		HEIGHT,
		0,
		0,
		windowClass.hInstance,
		0
	);

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

void gui::DestroyHWindow() noexcept
{
	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::CreateDevice() noexcept
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
		return false;

	ZeroMemory(&presentParameters, sizeof(presentParameters));

	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) < 0)
		return false;

	return true;
}

void gui::ResetDevice() noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto result = device->Reset(&presentParameters);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

void gui::DestroyDevice() noexcept
{
	if (device)
	{
		device->Release();
		device = nullptr;
	}

	if (d3d)
	{
		d3d->Release();
		d3d = nullptr;
	}
}

void gui::CreateImGui() noexcept
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ::ImGui::GetIO();

	io.IniFilename = NULL;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
}

void gui::DestroyImGui() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void gui::handleFont() noexcept
{
	ImFontConfig font_cfg;
	font_cfg.FontDataOwnedByAtlas = false;
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromMemoryTTF(CascadiaMono_Bold, CascadiaMono_BoldSize, 13.5f, &font_cfg);
}

void gui::BeginRender() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
		{
			isRunning = !isRunning;
			return;
		}
	}

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void gui::EndRender() noexcept
{
	ImGui::EndFrame();

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	if (device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}

	const auto result = device->Present(0, 0, 0, 0);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();
}

struct Config
{
	bool isLeftClick = false;
	bool isRightClick = false;
	bool isBothClick = false;
	int leftDebounce = 2;
	int rightDebounce = 2;

	int selectedOption1 = 2;
	int selectedOption2 = 2;
	int selectedOption3 = 2;
	int selectedOption4 = 2;
	int selectedOption5 = 2;
	int selectedOption6 = 2;
	int selectedOption7 = 2;
	int selectedOption8 = 2;
	int selectedOption9 = 2;

	
	const char* HoabarClickOption1[3] = { "left click","right click","none" };
	const char* HoabarClickOption2[3] = { "left click","right click","none" };
	const char* HoabarClickOption3[3] = { "left click","right click","none" };
	const char* HoabarClickOption4[3] = { "left click","right click","none" };
	const char* HoabarClickOption5[3] = { "left click","right click","none" };
	const char* HoabarClickOption6[3] = { "left click","right click","none" };
	const char* HoabarClickOption7[3] = { "left click","right click","none" };
	const char* HoabarClickOption8[3] = { "left click","right click","none" };
	const char* HoabarClickOption9[3] = { "left click","right click","none" };

	std::string hobar1_key;
	std::string hobar2_key;
	std::string hobar3_key;
	std::string hobar4_key;
	std::string hobar5_key;
	std::string hobar6_key;
	std::string hobar7_key;
	std::string hobar8_key;
	std::string hobar9_key;
	std::string inventory_key;
};
Config config;
bool saveConfig(const std::string& filename)
{
	using namespace rapidjson;
	Document doc(kObjectType);
	Document::AllocatorType& allocator = doc.GetAllocator();
	doc.AddMember("isLeftClick", config.isLeftClick, allocator);
	doc.AddMember("isRightClick", config.isRightClick, allocator);
	doc.AddMember("isBothClick", config.isBothClick, allocator);
	doc.AddMember("leftDebounce", config.leftDebounce, allocator);
	doc.AddMember("rightDebounce", config.rightDebounce, allocator);
	// Key bindings
	doc.AddMember("hobar1_key", Value(config.hobar1_key.c_str(), allocator), allocator);
	doc.AddMember("hobar2_key", Value(config.hobar2_key.c_str(), allocator), allocator);
	doc.AddMember("hobar3_key", Value(config.hobar3_key.c_str(), allocator), allocator);
	doc.AddMember("hobar4_key", Value(config.hobar4_key.c_str(), allocator), allocator);
	doc.AddMember("hobar5_key", Value(config.hobar5_key.c_str(), allocator), allocator);
	doc.AddMember("hobar6_key", Value(config.hobar6_key.c_str(), allocator), allocator);
	doc.AddMember("hobar7_key", Value(config.hobar7_key.c_str(), allocator), allocator);
	doc.AddMember("hobar8_key", Value(config.hobar8_key.c_str(), allocator), allocator);
	doc.AddMember("hobar9_key", Value(config.hobar9_key.c_str(), allocator), allocator);
	// somehow i forgot this line
	doc.AddMember("inventory_key", Value(config.inventory_key.c_str(), allocator), allocator);
	// Combo box selections
	doc.AddMember("selectedOption1", config.selectedOption1, allocator);
	doc.AddMember("selectedOption2", config.selectedOption2, allocator);
	doc.AddMember("selectedOption3", config.selectedOption3, allocator);
	doc.AddMember("selectedOption4", config.selectedOption4, allocator);
	doc.AddMember("selectedOption5", config.selectedOption5, allocator);
	doc.AddMember("selectedOption6", config.selectedOption6, allocator);
	doc.AddMember("selectedOption7", config.selectedOption7, allocator);
	doc.AddMember("selectedOption8", config.selectedOption8, allocator);
	doc.AddMember("selectedOption9", config.selectedOption9, allocator);
	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, filename.c_str(), "wb");
	if (err != 0 || !fp) return false;

	char writeBuffer[256];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	PrettyWriter<FileWriteStream> writer(os);
	doc.Accept(writer);

	fclose(fp);
	return true;
}

bool loadConfig(const std::string& filename)
{
	using namespace rapidjson;
	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, filename.c_str(), "rb");
	if (err != 0 || !fp) return false;
	char readBuffer[256];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document doc;
	doc.ParseStream(is);
	fclose(fp);

	if (doc.HasParseError()) return false;
	if (doc.HasMember("isLeftClick") && doc["isLeftClick"].IsBool())
	{
		config.isLeftClick = doc["isLeftClick"].GetBool();
	}

	if (doc.HasMember("isRightClick") && doc["isRightClick"].IsBool())
	{
		config.isRightClick = doc["isRightClick"].GetBool();
	}

	if (doc.HasMember("isBothClick") && doc["isBothClick"].IsBool())
	{
		config.isBothClick = doc["isBothClick"].GetBool();
	}

	if (doc.HasMember("leftDebounce") && doc["leftDebounce"].IsInt())
	{
		config.leftDebounce = doc["leftDebounce"].GetInt();
	}

	if (doc.HasMember("rightDebounce") && doc["rightDebounce"].IsInt())
	{
		config.rightDebounce = doc["rightDebounce"].GetInt();
	}
	// hardcoded 
	if (doc.HasMember("hobar1_key") && doc["hobar1_key"].IsString())
	{
		config.hobar1_key = doc["hobar1_key"].GetString();
	}

	if (doc.HasMember("hobar2_key") && doc["hobar2_key"].IsString()) 
	{
		config.hobar2_key = doc["hobar2_key"].GetString();
	}

	if (doc.HasMember("hobar3_key") && doc["hobar3_key"].IsString()) 
	{
		config.hobar3_key = doc["hobar3_key"].GetString();
	}

	if (doc.HasMember("hobar4_key") && doc["hobar4_key"].IsString()) 
	{
		config.hobar4_key = doc["hobar4_key"].GetString();
	}

	if (doc.HasMember("hobar5_key") && doc["hobar5_key"].IsString()) 
	{
		config.hobar5_key = doc["hobar5_key"].GetString();
	}

	if (doc.HasMember("hobar6_key") && doc["hobar6_key"].IsString()) 
	{
		config.hobar6_key = doc["hobar6_key"].GetString();
	}

	if (doc.HasMember("hobar7_key") && doc["hobar7_key"].IsString()) 
	{
		config.hobar7_key = doc["hobar7_key"].GetString();
	}

	if (doc.HasMember("hobar8_key") && doc["hobar8_key"].IsString())
	{
		config.hobar8_key = doc["hobar8_key"].GetString();
	}

	if (doc.HasMember("hobar9_key") && doc["hobar9_key"].IsString()) 
	{
		config.hobar9_key = doc["hobar9_key"].GetString();
	}

	if (doc.HasMember("inventory_key") && doc["inventory_key"].IsString())
	{
		config.inventory_key = doc["inventory_key"].GetString();
	}

	if (doc.HasMember("selectedOption1")) config.selectedOption1 = doc["selectedOption1"].GetInt();
	if (doc.HasMember("selectedOption2")) config.selectedOption2 = doc["selectedOption2"].GetInt();
	if (doc.HasMember("selectedOption3")) config.selectedOption3 = doc["selectedOption3"].GetInt();
	if (doc.HasMember("selectedOption4")) config.selectedOption4 = doc["selectedOption4"].GetInt();
	if (doc.HasMember("selectedOption5")) config.selectedOption5 = doc["selectedOption5"].GetInt();
	if (doc.HasMember("selectedOption6")) config.selectedOption6 = doc["selectedOption6"].GetInt();
	if (doc.HasMember("selectedOption7")) config.selectedOption7 = doc["selectedOption7"].GetInt();
	if (doc.HasMember("selectedOption8")) config.selectedOption8 = doc["selectedOption8"].GetInt();
	if (doc.HasMember("selectedOption9")) config.selectedOption9 = doc["selectedOption9"].GetInt();
	return true;
}
std::thread doubleClickThread;
void gui::Render() noexcept
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::Begin(
		"DOUBLE CLICKER [by nullzsh]",
		&isRunning,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove
	);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	// CSS stuff
	// credits to: https://github.com/xy8q
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.04f, 0.04f, 0.04f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.48f, 0.26f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.37f, 0.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.21f, 0.16f, 0.48f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.45f, 0.26f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.41f, 0.00f, 1.00f, 0.40f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.48f, 0.26f, 0.98f, 0.52f);
	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.34f, 0.06f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.15f, 0.15f, 0.15f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.13f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.26f, 0.98f, 0.50f);
	colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.20f, 0.58f, 0.73f);
	colors[ImGuiCol_TabSelected] = ImVec4(0.29f, 0.20f, 0.68f, 1.00f);
	colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_TabDimmed] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
	colors[ImGuiCol_NavCursor] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	// Own by https://github.com/xy8q he posted this design in https://github.com/ocornut/imgui/issues/707 
	//
	if(ImGui::Checkbox("Left click", &config.isLeftClick))
	{
		isLeft = config.isLeftClick;
		config.isRightClick = false;
		config.isBothClick = false;
	}
	
	if (ImGui::Checkbox("Right click", &config.isRightClick))
	{
		isRight = config.isRightClick;
		config.isLeftClick = false;
		config.isBothClick = false;
	}

	if (ImGui::Checkbox("Both click", &config.isBothClick))
	{
		isBoth = config.isBothClick;
		config.isLeftClick = false;
		config.isRightClick = false;
	}

	ImGui::PushItemWidth(164);
	if (ImGui::SliderInt("Left debounce", &config.leftDebounce, 1, 4, "%d"))
	{
		leftDebounceClick = config.leftDebounce;
	}

	if (ImGui::SliderInt("Right debounce", &config.rightDebounce, 1, 4, "%d"))
	{
		rightDebounceClick = config.rightDebounce;
	}
	ImGui::PopItemWidth();
	
	ImGui::PushItemWidth(100);
	// handle about hobar input . I dont have another way.
	static char hobar1Buffer[10];
	static char hobar2Buffer[10];
	static char hobar3Buffer[10];
	static char hobar4Buffer[10];
	static char hobar5Buffer[10];
	static char hobar6Buffer[10];
	static char hobar7Buffer[10];
	static char hobar8Buffer[10];
	static char hobar9Buffer[10];
	// inventory
	static char inventoryBuffer[10];

	if (config.hobar1_key.size() < 10) strcpy_s(hobar1Buffer, config.hobar1_key.c_str());
	if (config.hobar2_key.size() < 10) strcpy_s(hobar2Buffer, config.hobar2_key.c_str());
	if (config.hobar3_key.size() < 10) strcpy_s(hobar3Buffer, config.hobar3_key.c_str());
	if (config.hobar4_key.size() < 10) strcpy_s(hobar4Buffer, config.hobar4_key.c_str());
	if (config.hobar5_key.size() < 10) strcpy_s(hobar5Buffer, config.hobar5_key.c_str());
	if (config.hobar6_key.size() < 10) strcpy_s(hobar6Buffer, config.hobar6_key.c_str());
	if (config.hobar7_key.size() < 10) strcpy_s(hobar7Buffer, config.hobar7_key.c_str());
	if (config.hobar8_key.size() < 10) strcpy_s(hobar8Buffer, config.hobar8_key.c_str());
	if (config.hobar9_key.size() < 10) strcpy_s(hobar9Buffer, config.hobar9_key.c_str());
	if (config.inventory_key.size() < 10) strcpy_s(inventoryBuffer, config.inventory_key.c_str());

	ImGui::Text("Hobar[1]");
	ImGui::SameLine();
	if (ImGui::InputText("##Hobar 1",hobar1Buffer,IM_ARRAYSIZE(hobar1Buffer)))
	{
		config.hobar1_key = hobar1Buffer;
		// key handle getkeyfromuser()
	}
	ImGui::SameLine();
	ImGui::Combo("##HoBar 1 Action", &config.selectedOption1, "left click\0right click\0none\0");

	ImGui::Text("Hobar[2]");
	ImGui::SameLine();
	if (ImGui::InputText("##Hobar 2", hobar2Buffer, IM_ARRAYSIZE(hobar2Buffer)))
	{
		config.hobar2_key = hobar2Buffer;

		// key handle getkeyfromuser()
	}
	ImGui::SameLine();
	ImGui::Combo("##HoBar 2 Action", &config.selectedOption2, "left click\0right click\0none\0");

	ImGui::Text("Hobar[3]");
	ImGui::SameLine();
	if (ImGui::InputText("##Hobar 3", hobar3Buffer, IM_ARRAYSIZE(hobar3Buffer)))
	{
		config.hobar3_key = hobar3Buffer;
		// key handle getkeyfromuser()
	}
	ImGui::SameLine();
	ImGui::Combo("##HoBar 3 Action", &config.selectedOption3, "left click\0right click\0none\0");

	ImGui::Text("Hobar[4]");
	ImGui::SameLine();
	if (ImGui::InputText("##Hobar 4", hobar4Buffer, IM_ARRAYSIZE(hobar4Buffer)))
	{
		config.hobar4_key = hobar4Buffer;
		// key handle getkeyfromuser()
	}
	ImGui::SameLine();
	ImGui::Combo("##HoBar 4 Action", &config.selectedOption4, "left click\0right click\0none\0");

	ImGui::Text("Hobar[5]");
	ImGui::SameLine();
	if (ImGui::InputText("##Hobar 5", hobar5Buffer, IM_ARRAYSIZE(hobar5Buffer)))
	{
		config.hobar5_key = hobar5Buffer;
		// key handle getkeyfromuser()
	}
	ImGui::SameLine();
	ImGui::Combo("##HoBar 5 Action", &config.selectedOption5, "left click\0right click\0none\0");

	ImGui::Text("Hobar[6]");
	ImGui::SameLine();
	if (ImGui::InputText("##Hobar 6", hobar6Buffer, IM_ARRAYSIZE(hobar6Buffer)))
	{
		config.hobar6_key = hobar6Buffer;
		// key handle getkeyfromuser()
	}
	ImGui::SameLine();
	ImGui::Combo("##HoBar 6 Action", &config.selectedOption6, "left click\0right click\0none\0");

	ImGui::Text("Hobar[7]");
	ImGui::SameLine();
	if (ImGui::InputText("##Hobar 7", hobar7Buffer, IM_ARRAYSIZE(hobar7Buffer)))
	{
		config.hobar7_key = hobar7Buffer;
		// key handle getkeyfromuser()
	}
	ImGui::SameLine();
	ImGui::Combo("##HoBar 7 Action", &config.selectedOption7, "left click\0right click\0none\0");

	ImGui::Text("Hobar[8]");
	ImGui::SameLine();
	if (ImGui::InputText("##Hobar 8", hobar8Buffer, IM_ARRAYSIZE(hobar8Buffer)))
	{
		config.hobar8_key = hobar8Buffer;
		// key handle getkeyfromuser()
	}
	ImGui::SameLine();
	ImGui::Combo("##HoBar 8 Action", &config.selectedOption8, "left click\0right click\0none\0");

	ImGui::Text("Hobar[9]");
	ImGui::SameLine();
	if (ImGui::InputText("##Hobar 9", hobar9Buffer, IM_ARRAYSIZE(hobar9Buffer)))
	{
		config.hobar9_key = hobar9Buffer;
		// key handle getkeyfromuser()
	}
	ImGui::SameLine();
	ImGui::Combo("##HoBar 9 Action", &config.selectedOption9, "left click\0right click\0none\0");

	ImGui::Text("Inventory");
	ImGui::SameLine();
	if (ImGui::InputText("##Inventory", inventoryBuffer, IM_ARRAYSIZE(inventoryBuffer)))
	{
		config.inventory_key = inventoryBuffer;
	}


	ImGui::PopItemWidth();

	/*
	ImGui::Combo("HoBar 1 Action", &config.selectedOption1, "left click\0right click\0none\0");
	ImGui::Combo("HoBar 2 Action", &config.selectedOption2, "left click\0right click\0none\0");
	ImGui::Combo("HoBar 3 Action", &config.selectedOption3, "left click\0right click\0none\0");
	ImGui::Combo("HoBar 4 Action", &config.selectedOption4, "left click\0right click\0none\0");
	ImGui::Combo("HoBar 5 Action", &config.selectedOption5, "left click\0right click\0none\0");
	ImGui::Combo("HoBar 6 Action", &config.selectedOption6, "left click\0right click\0none\0");
	ImGui::Combo("HoBar 7 Action", &config.selectedOption7, "left click\0right click\0none\0");
	ImGui::Combo("HoBar 8 Action", &config.selectedOption8, "left click\0right click\0none\0");
	ImGui::Combo("HoBar 9 Action", &config.selectedOption9, "left click\0right click\0none\0");
	*/



	if (ImGui::Button("Load settings"))
	{
		if (loadConfig("config.json"))
		{
			isLeft = config.isLeftClick;
			isRight = config.isRightClick;
			isBoth = config.isBothClick;
			leftDebounceClick = config.leftDebounce;
			rightDebounceClick = config.rightDebounce;
			hobar1 = getKeyBind(config.hobar1_key);
			hobar2 = getKeyBind(config.hobar2_key);
			hobar3 = getKeyBind(config.hobar3_key);
			hobar4 = getKeyBind(config.hobar4_key);
			hobar5 = getKeyBind(config.hobar5_key);
			hobar6 = getKeyBind(config.hobar6_key);
			hobar7 = getKeyBind(config.hobar7_key);
			hobar8 = getKeyBind(config.hobar8_key);
			hobar9 = getKeyBind(config.hobar9_key);
			inventoryKey = getKeyBind(config.inventory_key);

		}
	}

	if (ImGui::Button("Save settings"))
	{
		if (saveConfig("config.json"))
		{
			// cout<< successfully
		}
	}

	static std::string applyMessage;// current message
	if (ImGui::Button("Apply"))
	{

		if (isActive)
		{
			isActive = false;
			if (doubleClickThread.joinable()) doubleClickThread.join();
			applyMessage = "Unapplied. Click 'Apply' button again to apply";
		}

		else
		{
			isActive = true;
			soption1 = config.selectedOption1;
			soption2 = config.selectedOption2;
			soption3 = config.selectedOption3;
			soption4 = config.selectedOption4;
			soption5 = config.selectedOption5;
			soption6 = config.selectedOption6;
			soption8 = config.selectedOption7;
			soption9 = config.selectedOption9;
			applyMessage = "Successfully applied! Press 'L' key to toggle.";
			// the int option not work so i try this
			doubleClickThread = std::thread(doubleClick, std::ref(isActive),hobar1,hobar2,hobar3,hobar4,hobar5,hobar6,hobar7,hobar8,hobar9,inventoryKey);
		}
	}
	
	if (!applyMessage.empty())
	{
		ImGui::Text("%s", applyMessage.c_str());
	}

	



	ImGui::End();
}