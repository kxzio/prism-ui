#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include "singleton.hpp"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class menu : public singleton <menu> {
public:

	void init();
	ImFont* my_font;
	HDC hDCScreen;
	HWND hWnd;

};

