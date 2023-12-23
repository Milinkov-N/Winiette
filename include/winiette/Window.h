#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_WINDOW_H_
#define WINIETTE_INCLUDE_WINIETTE_WINDOW_H_

#include <string_view>
#include <map>
#include <functional>
#include <memory>

#include <winiette/winiette.h>

namespace winiette
{
	class Window : public Widget
	{
	public:
		using WndProcCallback = std::function<Lresult(Hwnd, u32, Wparam, Lparam)>;
		using Handler = std::function<void()>;
		using DestroyCallback = std::function<i32()>;

	public:

		Window(
			std::wstring_view title,
			Size size,
			Pos pos,
			Hbrush bg_color = SystemColorBrush::White(),
			Hicon icon = LoadSystemIcon(SystemIconId::App),
			Hcursor cursor = LoadSystemCursor(SystemCursorId::Arrow)
		);

	public:
		auto OnRun(WndProcCallback cb) -> void;
		template<class W, class... Args>
		auto EmplaceWidget(Args... args) -> void;
		auto Connect(u64 id, Handler handler) -> void;
		auto OnDestroy(DestroyCallback destroy_cb) -> void;
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
		std::vector<std::unique_ptr<Widget>> widgets_;
		DestroyCallback destroy_cb_;
		std::map<Hmenu, Handler> handlers_;
	};

	template<class W, class ...Args>
	inline auto Window::EmplaceWidget(Args ...args) -> void
	{
		widgets_.push_back(std::make_unique<W>(args...));
	}
}  // namespace winiette

#endif  // WINIETTE_INCLUDE_WINIETTE_WINDOW_H_
