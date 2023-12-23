#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_UTILITY_H_
#define WINIETTE_INCLUDE_WINIETTE_UTILITY_H_

#include <winiette/win32.h>
#include <winiette/types.h>

namespace winiette
{
	namespace utility
	{
		enum class SystemIconId
		{
			App = 32512,
			Error = 32513,
			Question = 32514,
			Warning = 32515,
			Info = 32516,
			WinLogo = 32517,
			Shield = 32518,
		};

		enum class SystemCursorId
		{
			Arrow = 32512,
			Ibeam = 32513,
			Wait = 32514,
			Cross = 32515,
			UpArrow = 32516,
			SizeNwse = 32642,
			SizeNesw = 32643,
			SizeWe = 32644,
			SizeNs = 32645,
			SizeAll = 32646,
			No = 32648,
			Hand = 32649,
			AppStarting = 32650,
			Help = 32651,
			Pin = 32671,
			Person = 32672,
		};

		struct SystemColorBrush
		{
			inline static auto White() -> Hbrush { return GetSysColorBrush(HOLLOW_BRUSH); }
			inline static auto Gray() -> Hbrush { return GetSysColorBrush(GRAY_BRUSH); }
			inline static auto DarkGray() -> Hbrush { return GetSysColorBrush(DKGRAY_BRUSH); }
		};

		inline auto LoadSystemIcon(SystemIconId icon_id) -> Hicon
		{
			auto p_icon = MAKEINTRESOURCE(icon_id);
			return LoadIconW(nullptr, p_icon);
		}

		inline auto LoadSystemCursor(SystemCursorId cursor_id) -> Hcursor
		{
			auto p_cursor = MAKEINTRESOURCE(cursor_id);
			return LoadCursorW(nullptr, p_cursor);
		}
	}  // namespace utility
}  // namespace winiette

#endif  // WINIETTE_INCLUDE_WINIETTE_UTILITY_H_
