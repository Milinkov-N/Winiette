#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_DRAWER_H_
#define WINIETTE_INCLUDE_WINIETTE_DRAWER_H_

#include <optional>

#include <winiette/win32.h>
#include <winiette/types.h>
#include <winiette/font.h>

namespace winiette
{
	class TextColorGuard
	{
	public:
		TextColorGuard(Hdc hdc, Color color) noexcept;
		~TextColorGuard() noexcept;

	private:
		Hdc hdc_;
		ColorRef prev_color_;
	};

	class Drawer
	{
	public:
		explicit Drawer(Hwnd hwnd) noexcept;
		~Drawer() noexcept;

	public:
		constexpr auto hdc() const noexcept -> const Hdc&;
		auto Pixel(Pos position, Color color) -> void;
		[[nodiscard]] auto UsingTextColor(Color color) -> TextColorGuard;
		auto Text(Pos position, std::wstring_view text) -> void;
		auto Text(Pos position, std::wstring_view text, Font font) -> void;

	public:
		Drawer(const Drawer&) = delete;
		Drawer(Drawer&&) = delete;
		auto operator=(const Drawer&)->Drawer & = delete;
		auto operator=(Drawer&&)->Drawer & = delete;

	private:
		Hwnd hwnd_;
		PaintStruct ps_;
		Hdc hdc_;
	};

	constexpr auto Drawer::hdc() const noexcept -> const Hdc&
	{
		return hdc_;
	}
}  // namespace winiette

#endif  // WINIETTE_INCLUDE_WINIETTE_DRAWER_H_
