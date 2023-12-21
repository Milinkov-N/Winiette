#include <tuple>

#include <winiette/winiette.h>

using namespace winiette::types;

class MainWindow : public winiette::Widget
{
public:
	MainWindow() : winiette::Widget(L"Winiette Basic Window")
	{
		wco_.width = 1080u;
		wco_.height = 720u;
		wco_.x = 100u;
		wco_.y = 100u;
		wco_.style = WS_OVERLAPPEDWINDOW;
		wco_.style_ex = 0;
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

		wc.background(reinterpret_cast<Hbrush>(COLOR_WINDOW + 1));
		wc.icon(LoadIconW(nullptr, IDI_APPLICATION));
		wc.cursor(LoadCursorW(nullptr, IDC_ARROW));
		wc.class_name(L"MainWindowClass");
		wc.icon_sm(LoadIconW(nullptr, IDI_APPLICATION));

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

	MainWindow mw;

	mw.Create();
	mw.Show();

	return mw.Exec();
}
