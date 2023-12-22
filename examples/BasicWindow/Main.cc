#include <tuple>

#include <winiette/types.h>
#include <winiette/window.h>

using namespace winiette::types;

auto WinMain(Hinstance hinstance, i32 cmd_show) -> i32
{
	std::ignore = hinstance;
	std::ignore = cmd_show;

	winiette::Window mw(L"Winiette Basic Window", { 1080u, 720u }, { 100u, 100u });

	mw.Create();
	mw.Show();

	return mw.Exec([](Hwnd hwnd, u32 msg, Wparam wparam, Lparam lparam) -> Lresult
		{
			switch (msg)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				break;

			default:
				return DefWindowProc(hwnd, msg, wparam, lparam);
			}

			return 0;
		});
}
