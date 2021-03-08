#pragma once
#include "window_process.h"
#include "../menu.h"
#include "included.h"
#include "create.h"

struct {


	void finish() {
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        if (m_device.g_pd3dDevice) m_device.g_pd3dDevice->Release();
        if (wnd.pD3D) wnd.pD3D->Release();
        DestroyWindow(wnd.hwnd);
        UnregisterClass(_T("ImGui Example"), wnd.wc.hInstance);
	}

    void create_state() {
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        m_device.g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
        m_device.g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
        m_device.g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f), (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
        //g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (m_device.g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            m_device.g_pd3dDevice->EndScene();
        }
        HRESULT result = m_device.g_pd3dDevice->Present(NULL, NULL, NULL, NULL);


        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && m_device.g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
            m_device.g_pd3dDevice->Reset(&m_device.g_d3dpp);
            ImGui_ImplDX9_CreateDeviceObjects();
        }
    }
    void init32() {
        ImGui_ImplWin32_Init(wnd.hwnd);
        ImGui_ImplDX9_Init(m_device.g_pd3dDevice);
    }
    void new_frame() {

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();
    }
    void finish_frame() {

        ImGui::EndFrame();
    }

} m_directx ;