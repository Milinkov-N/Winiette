#include <winiette/window.h>

using namespace winiette::types;

static const auto DEFAULT_MESSAGE_CALLBACK = [](Hwnd) { return 0; };

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
	cb_(_DefaultWindowProcCallback),
	create_cb_(DEFAULT_MESSAGE_CALLBACK),
	paint_cb_(DEFAULT_MESSAGE_CALLBACK),
	size_cb_(DEFAULT_MESSAGE_CALLBACK),
	destroy_cb_(DEFAULT_MESSAGE_CALLBACK)
{
	wco_.size = size;
	wco_.pos = pos;
	wco_.style = Ws::OverlappedWindow;
}

auto winiette::Window::Connect(u64 id, Handler handler) -> void
{
	handlers_.insert({ reinterpret_cast<Hmenu>(id), handler });
}

auto winiette::Window::OnCreate(MessageCallback create_cb) -> void
{
	create_cb_ = create_cb;
}

auto winiette::Window::OnPaint(MessageCallback paint_cb) -> void
{
	paint_cb_ = paint_cb;
}

auto winiette::Window::OnSize(MessageCallback size_cb) -> void
{
	size_cb_ = size_cb;
}

auto winiette::Window::OnDestroy(MessageCallback destroy_cb) -> void
{
	destroy_cb_ = destroy_cb;
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
	switch (msg)
	{
	case WM_CREATE:
	{
		for (const auto& w : widgets_) w->Create(hwnd_);
		create_cb_(hwnd_);
		break;
	}
	case WM_PAINT:
	{
		paint_cb_(hwnd_);
		break;
	}
	case WM_COMMAND:
	{
		auto handler = handlers_.find(reinterpret_cast<Hmenu>(LOWORD(wparam)));
		if (handler != handlers_.end()) handler->second();
		break;
	}
	case WM_SIZE:
		size_cb_(hwnd_);
		break;
	case WM_DESTROY:
		PostQuitMessage(destroy_cb_(hwnd_));
		break;
	}
	return cb_(hwnd_, msg, wparam, lparam);
}
