#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_WINDOW_H_
#define WINIETTE_INCLUDE_WINIETTE_WINDOW_H_

#include <string_view>
#include <map>
#include <functional>
#include <memory>

#include <winiette/win32.h>
#include <winiette/types.h>
#include <winiette/widget.h>
#include <winiette/utility.h>

namespace winiette
{
	class Window : public Widget
	{
	public:
		using WndProcCallback = std::function<Lresult(Hwnd, u32, Wparam, Lparam)>;
		using Handler = std::function<void()>;
		using MessageCallback = std::function<i32(Hwnd)>;

	public:

		Window(
			std::wstring_view title,
			Size size,
			Pos pos,
			Hbrush bg_color = utility::SystemColorBrush::White(),
			Hicon icon = utility::LoadSystemIcon(utility::SystemIconId::App),
			Hcursor cursor = utility::LoadSystemCursor(utility::SystemCursorId::Arrow)
		);

	public:
		template<class W, class... Args>
		auto EmplaceWidget(Args... args) -> Widget&;
		auto Connect(u64 id, Handler handler) -> void;
		auto OnCreate(MessageCallback create_cb) -> void;
		auto OnPaint(MessageCallback paint_cb) -> void;
		auto OnSize(MessageCallback size_cb) -> void;
		auto OnDestroy(MessageCallback destroy_cb) -> void;
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
		MessageCallback create_cb_;
		MessageCallback paint_cb_;
		MessageCallback size_cb_;
		MessageCallback destroy_cb_;
		std::map<Hmenu, Handler> handlers_;
	};

	template<class W, class ...Args>
	inline auto Window::EmplaceWidget(Args ...args) -> Widget&
	{
		widgets_.push_back(std::make_unique<W>(args...));
		return *widgets_.back().get();
	}
}  // namespace winiette

#endif  // WINIETTE_INCLUDE_WINIETTE_WINDOW_H_
