#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_DRAWER_H_
#define WINIETTE_INCLUDE_WINIETTE_DRAWER_H_

#include <winiette/win32.h>
#include <winiette/types.h>

namespace winiette
{
	class Drawer
	{
	public:
		explicit Drawer(Hwnd hwnd) noexcept;
		~Drawer() noexcept;

	public:
		auto Pixel(Pos position, Color color) -> void;

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
}  // namespace winiette

#endif  // WINIETTE_INCLUDE_WINIETTE_DRAWER_H_
