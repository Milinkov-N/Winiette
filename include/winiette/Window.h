#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_WINDOW_H_
#define WINIETTE_INCLUDE_WINIETTE_WINDOW_H_

#include <string_view>
#include <functional>

#include <winiette/winiette.h>

namespace winiette
{
	class Window : public Widget
	{
	public:
		using WndProcCallback = std::function<Lresult(Hwnd, u32, Wparam, Lparam)>;
	public:

		explicit Window(
			std::wstring_view title,
			Size size,
			Pos pos,
			Hbrush bg_color = SystemColorBrush::White(),
			Hicon icon = LoadSystemIcon(SystemIconId::App),
			Hcursor cursor = LoadSystemCursor(SystemCursorId::Arrow)
		);

	public:
		auto OnRun(WndProcCallback cb) -> void;
		auto Show() -> void;
		auto Exec() -> i32;

	private:
		auto GetWindowClass() const->winiette::WindowClass final;
		auto WindowProc(u32 msg, Wparam wparam, Lparam lparam) -> Lresult override;

	private:
		Hbrush bg_color_;
		Hicon icon_;
		Hcursor cursor_;
		WndProcCallback cb_;
	};
}  // namespace winiette

#endif  // WINIETTE_INCLUDE_WINIETTE_WINDOW_H_
