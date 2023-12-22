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
	}  // namespace types

	using namespace types;
}  // namespace winiette
#endif  //  WINIETTE_INCLUDE_WINIETTE_TYPES_H_
