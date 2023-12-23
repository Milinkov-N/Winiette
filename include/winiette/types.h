#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_TYPES_H_
#define WINIETTE_INCLUDE_WINIETTE_TYPES_H_

#include <cstdint>

#include <winiette/win32.h>

namespace winiette
{
	namespace types
	{
		using WndClassEx = WNDCLASSEX;
		using Hinstance = HINSTANCE;
		using Hwnd = HWND;
		using Hmenu = HMENU;
		using Hbrush = HBRUSH;
		using Hicon = HICON;
		using Hcursor = HCURSOR;
		using Hdc = HDC;
		using Hfont = HFONT;
		using WndProc = WNDPROC;
		using Wparam = WPARAM;
		using Lparam = LPARAM;
		using Msg = MSG;
		using Atom = ATOM;
		using Dword = DWORD;
		using CreateStructPtr = LPCREATESTRUCT;
		using LongPtr = LONG_PTR;
		using WideStrPtr = LPCWSTR;
		using Lresult = LRESULT;
		using PaintStruct = PAINTSTRUCT;
		using OpenFileNameStruct = OPENFILENAME;
		using ChooseColorStruct = CHOOSECOLOR;
		using ChooseFontStruct = CHOOSEFONT;
		using ColorRef = COLORREF;
		using LogFont = LOGFONT;

		using u8 = uint8_t;
		using i8 = int8_t;
		using u16 = uint16_t;
		using i16 = int16_t;
		using u32 = uint32_t;
		using i32 = int32_t;
		using u64 = uint64_t;
		using i64 = int64_t;
		using usize = uint64_t;
		using isize = int64_t;
		using f32 = float;
		using f64 = double;

		struct Size
		{
			union
			{
				u32 width;
				u32 w;
			};

			union
			{
				u32 height;
				u32 h;
			};

			constexpr Size() noexcept;
			constexpr Size(u32 w, u32 h) noexcept;
		};

		constexpr Size::Size() noexcept : w(0), h(0)
		{
		}

		constexpr Size::Size(u32 w, u32 h) noexcept : w(w), h(h)
		{
		}

		struct Pos
		{
			u32 x;
			u32 y;

			constexpr Pos() noexcept;
			constexpr Pos(u32 x, u32 y) noexcept;
		};

		constexpr Pos::Pos() noexcept : x(0), y(0)
		{
		}

		constexpr Pos::Pos(u32 x, u32 y) noexcept : x(x), y(y)
		{
		}

		struct Color
		{
			u8 r, g, b;

			constexpr Color() noexcept;
			constexpr Color(u8 r, u8 g, u8 b) noexcept;

			constexpr operator ColorRef() const noexcept;
		};

		constexpr Color::Color() noexcept : r(0), g(0), b(0)
		{
		}

		constexpr Color::Color(u8 r, u8 g, u8 b) noexcept : r(r), g(g), b(b)
		{
		}

		constexpr Color::operator ColorRef() const noexcept
		{
			return RGB(r, g, b);
		}
	}  // namespace types

	using namespace types;
}  // namespace winiette
#endif  //  WINIETTE_INCLUDE_WINIETTE_TYPES_H_
