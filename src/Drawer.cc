#include <winiette/drawer.h>

#include <string>
#include <sstream>

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

auto winiette::Drawer::UsingFont(std::unique_ptr<Font> font) -> FontGuard
{
	font_ = std::move(font);
	return FontGuard(*this);
}

auto winiette::Drawer::ReleaseFont() -> void
{
	font_.reset();
}

//auto winiette::Drawer::Text(Pos position, std::wstring_view text) -> i32
//{
//	std::wstringstream wss(text.data());
//	i32 font_height = 16;
//	i32 offset = 0, margin = font_height / 2;
//
//	for (std::wstring line; std::getline(wss, line); offset += font_height)
//		TextOutW(hdc_, position.x, position.y + margin + offset, line.data(), static_cast<i32>(line.size()));
//
//	return offset;
//}

auto winiette::Drawer::Text(Pos position, std::wstring_view text) -> i32
{
	std::wstringstream wss(text.data());
	i32 font_height = font_.has_value() ? font_->get()->log_font().lfHeight : 16;
	i32 offset = 0, margin = font_height / 2;

	if (font_.has_value()) font_->get()->Use();

	for (std::wstring line; std::getline(wss, line); offset += font_height)
		TextOutW(hdc_, position.x, position.y + margin + offset, line.data(), static_cast<i32>(line.size()));

	return offset;
}

auto winiette::Drawer::Text(
	Pos position,
	std::wstring_view text,
	Font font
) -> i32
{
	std::wstringstream wss(text.data());
	i32 font_height = font.log_font().lfHeight;
	i32 offset = 0, margin = font_height / 2;

	font.Use();

	for (std::wstring line; std::getline(wss, line); offset += font_height)
		TextOutW(hdc_, position.x, position.y + margin + offset, line.data(), static_cast<i32>(line.size()));

	return offset;
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

winiette::FontGuard::FontGuard(Drawer& drawer) noexcept
	: drawer_(drawer)
{
}

winiette::FontGuard::~FontGuard() noexcept
{
	drawer_.ReleaseFont();
}
