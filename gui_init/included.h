#pragma once
#include "../im_manager/imgui.h"
#include "../im_manager/imgui_impl_dx9.h"
#include "../im_manager/imgui_impl_win32.h"
#include "../im_manager/imgui_internal.h"
#include <dinput.h>
#include <tchar.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

struct {
    HWND            hwnd;
    WNDCLASSEX      wc;
    LPDIRECT3D9     pD3D;
}wnd;