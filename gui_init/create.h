#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include "included.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "../gui/gui.h"

class device {
public:
    LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
    D3DPRESENT_PARAMETERS    g_d3dpp;
};
device m_device;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void null_(){};
int forward;
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (m_device.g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
            m_device.g_d3dpp.BackBufferWidth = LOWORD(lParam);
            m_device.g_d3dpp.BackBufferHeight = HIWORD(lParam);
            HRESULT hr = m_device.g_pd3dDevice->Reset(&m_device.g_d3dpp);
            if (hr == D3DERR_INVALIDCALL)
                IM_ASSERT(0);
            ImGui_ImplDX9_CreateDeviceObjects();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_MOUSEWHEEL:
        gui::get().global_mouse_scroll += GET_WHEEL_DELTA_WPARAM(wParam);
        break;
    }


    return DefWindowProc(hWnd, msg, wParam, lParam);
}