#pragma once
#include "included.h"
#include "../menu.h"
#include "create.h"
#include "finish.h"

struct {

    int init(ImVec2 pos, ImVec2 size) {

        wnd.wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
        RegisterClassEx(&wnd.wc);

        menu::get().hDCScreen = GetDC(NULL);
        int Horres = GetDeviceCaps(menu::get().hDCScreen, HORZRES);
        int Vertres = GetDeviceCaps(menu::get().hDCScreen, VERTRES);
        ReleaseDC(NULL, menu::get().hDCScreen);

        wnd.hwnd = CreateWindow(_T("ImGui Example"), _T("shuffle_app"), WS_POPUP, pos.x, pos.y, size.x, size.y, NULL, NULL, wnd.wc.hInstance, NULL);

        if ((wnd.pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        {
            UnregisterClass(_T("ImGui Example"), wnd.wc.hInstance);
            return 0;
        }
        ZeroMemory(&m_device.g_d3dpp, sizeof(m_device.g_d3dpp));
        m_device.g_d3dpp.Windowed = TRUE;
        m_device.g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        m_device.g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
        m_device.g_d3dpp.EnableAutoDepthStencil = TRUE;
        m_device.g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
        m_device.g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

        if (wnd.pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, wnd.hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_device.g_d3dpp, &m_device.g_pd3dDevice) < 0)
        {
            wnd.pD3D->Release();
            UnregisterClass(_T("ImGui Example"), wnd.wc.hInstance);
            return 0;
        }


        ImGui::CreateContext();

    }

    void process_msg() {

        MSG msg;
        // Main loop
        ZeroMemory(&msg, sizeof(msg));
        ShowWindow(wnd.hwnd, SW_SHOWDEFAULT);
        UpdateWindow(wnd.hwnd);

        while (msg.message != WM_QUIT)
        {
            if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                continue;
            }

            m_directx.new_frame(); {
                menu::get().init();
            }
            m_directx.finish_frame();


            m_directx.create_state();
        }
    }

} window;