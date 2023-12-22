#include <winiette/window.h>

using namespace winiette::types;

static auto _DefaultWindowProcCallback(
	Hwnd hwnd,
	u32 msg,
	Wparam wparam,
	Lparam lparam
) -> Lresult
{ 
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

winiette::Window::Window(
	std::wstring_view title,
	Size size,
	Pos pos,
	Hbrush bg_color,
	Hicon icon,
	Hcursor cursor
)
	: winiette::Widget(title),
	bg_color_(bg_color),
	icon_(icon),
	cursor_(cursor),
	cb_(_DefaultWindowProcCallback)
{
	wco_.size = size;
	wco_.pos = pos;
	wco_.style = ws::OverlappedWindow;
}

auto winiette::Window::OnRun(WndProcCallback cb) -> void
{
	cb_ = cb;
}

auto winiette::Window::Show() -> void
{
	ShowWindow(hwnd_, SW_SHOW);
	UpdateWindow(hwnd_);
}

auto winiette::Window::Exec() -> i32
{
	Msg msg{ 0 };

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<i32>(msg.wParam);
}

auto winiette::Window::GetWindowClass() const -> winiette::WindowClass
{
	auto wc(Widget::GetWindowClass());

	wc.background(bg_color_);
	wc.icon(icon_);
	wc.cursor(cursor_);
	wc.class_name(L"__WinietteWindowClass__");
	wc.icon_sm(icon_);

	return wc;
}

auto winiette::Window::WindowProc(u32 msg, Wparam wparam, Lparam lparam) -> Lresult
{
	return cb_(hwnd_, msg, wparam, lparam);
}
