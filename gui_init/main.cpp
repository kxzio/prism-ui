#define _CRT_SECURE_NO_WARNINGS

#include "included.h"
#include "create.h"
#include "window_process.h"
#include <vector>
#include <sstream>
#include "../fnv1a.h"
#include <time.h>
#include "../gui/gui.h"

using namespace ImGui;
float screen_max[]{ GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };

int main()
{
    /* First argument if window pos - position, where will be rendered window and size, how big window will be */
    window.init( ImVec2{ 0, 0 }, ImVec2{ screen_max[0], screen_max[1] } );
    auto& IO = GetIO();

    ImFontConfig font_config;
    font_config.OversampleH = 1; //or 2 is the same
    font_config.OversampleV = 1;
    font_config.PixelSnapH = 1;

    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x044F, // Cyrillic
        0,
    };

    menu::get().my_font = IO.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/verdana.ttf", 14.f, &font_config);

    /* DIRECTX & wndproc initialization */
    m_directx.  init32(); 
    window.     process_msg();
    /* code shutdown  UPD: fixed crash in time of process closing & (device lost) */ 
    m_directx.  finish();

    return 0;
};

void menu::init() {
   
    //debug background
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(4000, 4000), ImColor(25, 25, 25), 0.0);

    //start
    gui::get().go();

    //style :::
    gui::get().__colorstyle(__style_color::text) = ImColor(225, 225, 225);
    gui::get().__colorstyle(__style_color::permissible_text) = ImColor(120, 120, 120);
    gui::get().__colorstyle(__style_color::window_background) = ImColor(20, 20, 20);
    gui::get().__colorstyle(__style_color::childwindow_bg) = ImColor(24, 24, 24);
    gui::get().__colorstyle(__style_color::titlebar_background) = ImColor(30, 30, 30);
    gui::get().__colorstyle(__style_color::window_oultine) = ImColor(60, 60, 60, 38);
    gui::get().__colorstyle(__style_color::element_outline) = ImColor(60, 60, 60, 38);
    //elements
    gui::get().__colorstyle(__style_color::frame_default) = ImColor(30, 30, 30);
    gui::get().__colorstyle(__style_color::frame_hovered) = ImColor(35, 35, 35);
    gui::get().__colorstyle(__style_color::frame_active)  = ImColor(40, 40, 40);

    gui::get().__colorstyle(__style_color::selectable_default) = ImColor(25, 25, 25);
    gui::get().__colorstyle(__style_color::selectable_hovered) = ImColor(30, 30, 30);
    gui::get().__colorstyle(__style_color::selectable_active) = ImColor(35, 35, 35);
    gui::get().__colorstyle(__style_color::active_obj) = ImColor(15, 186, 224);
    gui::get().__colorstyle(__style_color::unactive_obj) = ImColor(35, 35, 35);

    //window
    gui::get().__style(__style_value::window_padding_x) = 8.f;
    gui::get().__style(__style_value::window_padding_y) = 15.f;
    //items
    gui::get().__style(__style_value::item_spacing_x) = 8.f;
    gui::get().__style(__style_value::item_spacing_y) = 8.f;

    //gui solve : 
    gui::get().begin_frame("GUI", pos(30, 30), size(585, 430), __flags::none );
    {
        const char* tabs[] {"Home", "Inbox", "Profile", "Settings", "Features"};
        for (int i = 0; i < 5; i++) {
            gui::get().offset_brush_pos(pos(25 + (i * 110), 383));
            gui::get().button(tabs[i], pos(94, 32));
        }

        gui::get().offset_brush_pos(pos(25, 50));
        gui::get().begin_child_window("General", size(162, 323));
        {
            //child elements
            gui::get().text("Elements examples : ");

            static bool bln = true;
            gui::get().checkbox("Checkbox active", &bln);

            static bool bln2 = false;
            gui::get().checkbox("Checkbox disabled", &bln2);

            static float test_fl;
            gui::get().slider_float("Float slider", &test_fl, 100);

            static int test_int;
            gui::get().slider_int("Integer slider", &test_int, 100);

            static int combo_int;
            const char* combo_text_[]{"Selection1", "Selection2", "Selection3"};
            gui::get().combo("Combo selection", &combo_int, combo_text_, ARRAYSIZE(combo_text_));

            gui::get().button("Button");
                
        }
        gui::get().end();

        gui::get().offset_brush_pos(pos(50 + 162, 50));
        gui::get().begin_child_window("Settings", size(162, 323));
        {
            static float col[4] {1.f, 0.f, 0.f, 1.f};
            gui::get().color_picker("Colorpicker", col);

            static bool multibox_test[5];
            const char* combo_text_[]{ "Selection1", "Selection2", "Selection3" };
            gui::get().multi("Multibox selection", multibox_test, combo_text_, ARRAYSIZE(combo_text_));

            static std::string input;
            gui::get().input("Text input", input);

            static bool bln2 = false;
            gui::get().checkbox("Another checkbox", &bln2);

        }
        gui::get().end();


        gui::get().offset_brush_pos(pos(75 + 162 * 2, 50));
        gui::get().begin_child_window("Conditions", size(162, 323));
        {
            static int list_element;
            const char* list_text[]{ "Selection1", "Selection2", "Selection3"};
            gui::get().list("Listbox", &list_element, list_text, ARRAYSIZE(list_text));

            const char* textbox[] 
            { 
                "Hello, it is textbox", 
                "It is text in frame",
                "You may use textbox -",
                "1.Pay attention of user",
                "2.Just share info"
            };
            gui::get().text_box("Textbox", textbox, ARRAYSIZE(textbox));
            static bool v;
            gui::get().toggle_button("Toggle button", &v, size(95, 30));
            static int key, mode;
            gui::get().hotkey("Hotkey", &key, &mode);
        }
        gui::get().end();

    }
    gui::get().end();




}

