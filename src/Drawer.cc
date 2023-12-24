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

auto winiette::Drawer::UsingTextColor(Color color) -> TextColorGuard
{
	return TextColorGuard(hdc_, color);
}

auto winiette::Drawer::Text(Pos position, std::wstring_view text) -> void
{
	TextOutW(hdc_, position.x, position.y, text.data(), static_cast<i32>(text.size()));
}

auto winiette::Drawer::Text(
	Pos position,
	std::wstring_view text,
	Font font
) -> void
{
	font.Use();
	TextOutW(hdc_, position.x, position.y, text.data(), static_cast<i32>(text.size()));
}

winiette::TextColorGuard::TextColorGuard(Hdc hdc, Color color) noexcept
	: hdc_(hdc), prev_color_(GetTextColor(hdc))
{
	SetTextColor(hdc, color);
}

winiette::TextColorGuard::~TextColorGuard() noexcept
{
	SetTextColor(hdc_, prev_color_);
}
