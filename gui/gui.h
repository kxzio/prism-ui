#pragma once
#include "../singleton.hpp"
#include "../gui_init/included.h"
#include <vector>
#include <string>
#include "../fnv1a.h"

/*	error cods :

	1 - user input is empty/cleared or now restoring

*/

//pos
typedef ImVec2 pos;

//elements/window/data id
typedef ImGuiID gui_id;

//sz
typedef ImVec2 size;

//this class is using for window handle system
class c_internal_window_form {
public:
	//window name
	const char* name_str;
	//window id
	gui_id id;
	//window position
	ImVec2 pos;
	//poses 1 tick before position
	ImVec2 last_tick_pos;
	//window size
	ImVec2 size;
	//moving frame speed
	float frame_move_speed;
	//debug logger
	int debug_logs_count;
	//flags
	int flags;
	//bool if slider is grabbing and we dont need to move menu
	bool lock_menu;
	//scroll process
	int scroll_offset;
};

class c_pos_parameters {
public:
	ImVec2 pos;
	//window size
	ImVec2 size;
};

enum __style_color : int
{
	text,
	permissible_text,
	unactive_obj,
	active_obj,
	selectable_default,
	selectable_hovered,
	selectable_active,
	window_background,
	window_oultine,
	element_outline,
	titlebar_background,
	frame_default,
	frame_hovered,
	frame_active,
	childwindow_bg,
	color_count
};

enum __style_value : int
{
	item_spacing_x,   item_spacing_y,
	window_padding_x, window_padding_y,
	value_style_count
};

enum __flags : int
{
	none,
	no_background,
	no_move,
	no_titlebar,
	no_outline,
	child,
	flags_count
};

//this class is not the same, this structure is user-friendly version for custom input
class c_external_window_form {
public:
	//window name
	const char* name_str;

	//clear or restore
	c_external_window_form () { name_str = "dx_empty_err_code_1"; }

	//setup
	c_external_window_form (const char* str) { name_str = str; }

};

class c_modify_presset {
	//grl
	int p_unxored;
	//load
	c_modify_presset(std::string input) { p_unxored = modulate_en(input.c_str()); }
};

//create copy of class, but with another name
typedef c_external_window_form c_window_form;

// gui class init
class gui : public singleton < gui > {

	//gui files, easy to use
	public:
	enum AnimationTypes { STATIC, DYNAMIC, INTERP };
	//start render
	void go();
	//render window
	void think (c_window_form* __this, int flags);
	//color style array
	std::array < ImColor, color_count> style;
	float global_mouse_scroll;
	//style_quantity style
	std::array < float, value_style_count> style_quantity;
	//window style mod
	ImColor& __colorstyle(__style_color i);
	//float& gui::__style(__value_color i)
	float& __style(__style_value i);
	//window create
	void begin_frame(std::string __strname, pos start_pos, size start_size, int flags = 0);
	//get/set cursor pos
	pos& __brush_pos();
	//configurate new brush pos
	void offset_brush_pos(pos p);
	//plus
	void plus_brush_pos(pos p);
	//child window
	void begin_child_window(const char* str, size sz, int flags = 0);
	//end frame
	void end();

	//elements :::
	void text(const char* __char);
	void checkbox(const char* __char, bool* __bool);
	void slider_engine(const char* title, float* val, float maximal);
	void slider_float(const char* title, float* val, float maximal);
	void slider_int(const char* title, int* val, int maximal);
	void combo(const char* title, int* element, const char* text_array[], int arr_sz);
	void multi(const char* title, bool elements[], const char* text_array[], int arr_sz);
	bool button(const char* label, size size = pos(0, 0));
	void color_picker(const char* title, float col[4]);
	void custom_slider(const char* title, float* val, float maximal, pos p);
	void list(const char* title, int* element, const char* text[], int count);
	void input(const char* title, std::string& input);
	void text_box(const char* title, const char* text[], int count);
	bool toggle_button(const char* label, bool* v, size ssize = pos(0, 0));
	void hotkey(const char* title, int* key, int* mode);

	private:
	//window data of size and pos
	std::vector < c_pos_parameters > pos_parameter;

	public:
	//window size, pos
	void set_window_config(pos p1, pos p2);
	gui_id last_hovered_window;
	//window, that is focused now
	gui_id focus_target_id;

	std::vector < c_internal_window_form* > window_manifold;
	//internal window functions
	private :
	//global brush position
	pos brush_pos = pos(0, 0);
	//whole window counter to finaly draw
	//old data of inversed tick_count
	std::vector < c_internal_window_form* > old_window_manifold;
	std::vector <pos> window_poses ;
	//window, that is dragging rn
	gui_id drag_target_id;
	//bool to dont clear target
	bool dont_restore_drag_target;
	//fix random button clicks
	bool is_able_to_click;
	//mouse pos
	POINT cursor;
	//is mouse hovering rect
	bool is_hovered(pos p1, pos p2, bool popup_status = true);
	//is left button clicked one time?
	bool is_clicked_once(int i = 0);
	//is left button down?
	bool is_holding(int i = 0);
	//focus window
	void focus_handle(gui_id id);
	//for window dragg
	bool move_rect_by_mouse(std::string buf_name, pos* p1, size p2);
	//get id for elements/arrays/windows/etc
	gui_id get_propper_id(std::string buf);
	//debug func : 
	void add_window_debug_log(std::string __str);
	//get latest window form info
	c_internal_window_form* get_current_manifold_lib();
	//get last tick - 1 window form info
	c_internal_window_form* get_old_manifold_lib();
	//pos setting
	c_pos_parameters* get_pos_settings();
	//draw window features
	void draw_window_features();
	//add vec2 to brush pos
	void add_element(size sz);
	//calc sz for element
	float calc_frame_w();
	//get frame color
	ImColor get_frame_color(bool hovered, bool active = false);
	float lerp_animate(const char* label, const char* second_label, bool if_, float Maximal_, float Speed_, int type);

};
