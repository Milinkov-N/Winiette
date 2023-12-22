#include <tuple>

#include <winiette/winiette.h>

using winiette::ws;
using namespace winiette::types;
using SysIcon = winiette::SystemIconId;
using SysCursor = winiette::SystemCursorId;

class BasicWindow : public winiette::Widget
{
public:
	BasicWindow() : winiette::Widget(L"Winiette Basic Window")
	{
		wco_.size = { 1080u, 720u };
		wco_.pos = { 100u, 100u };
		wco_.style = ws::OverlappedWindow;
	}

public:
	auto Show() -> void
	{
		ShowWindow(hwnd_, SW_SHOW);
		UpdateWindow(hwnd_);
	}

	auto Exec() -> i32
	{
		Msg msg{ 0 };

		while (GetMessage(&msg, nullptr, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return static_cast<i32>(msg.wParam);
	}

private:
	auto GetWindowClass() const->winiette::WindowClass final
	{
		auto wc(Widget::GetWindowClass());

		wc.background(winiette::SystemColorBrush::White());
		wc.icon(winiette::LoadSystemIcon(SysIcon::App));
		wc.cursor(winiette::LoadSystemCursor(SysCursor::Arrow));
		wc.class_name(L"BasicWindowClass");
		wc.icon_sm(winiette::LoadSystemIcon(SysIcon::App));

		return wc;
	}

	auto WindowProc(u32 msg, Wparam wparam, Lparam lparam) -> Lresult final
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hwnd_, msg, wparam, lparam);
			break;
		}

		return 0;
	}
};

auto WinMain(Hinstance hinstance, i32 cmd_show) -> i32
{
	std::ignore = hinstance;
	std::ignore = cmd_show;

	BasicWindow mw;

	mw.Create();
	mw.Show();

	return mw.Exec();
}
