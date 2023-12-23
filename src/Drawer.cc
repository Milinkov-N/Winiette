#include <winiette/drawer.h>

winiette::Drawer::Drawer(Hwnd hwnd) noexcept
	: hwnd_(hwnd), ps_{ 0 }, hdc_(BeginPaint(hwnd_, &ps_))
{
}

winiette::Drawer::~Drawer() noexcept
{
	EndPaint(hwnd_, &ps_);
}

auto winiette::Drawer::Pixel(Pos position, Color color) -> void
{
	SetPixel(hdc_, position.x, position.y, color);
}
