#include <tuple>

#include <winiette/types.h>
#include <winiette/window.h>
#include <winiette/button.h>
#include <winiette/msgbox.h>

using namespace winiette::types;

auto WinMain(Hinstance hinstance, i32 cmd_show) -> i32
{
	std::ignore = hinstance;
	std::ignore = cmd_show;

	winiette::Window mw(L"Winiette Basic Window", { 1080u, 720u }, { 100u, 100u });

	mw.OnRun([](Hwnd hwnd, u32 msg, Wparam wparam, Lparam lparam) -> Lresult
		{
			switch (msg)
			{
			case WM_CREATE:
			{
				winiette::Button btn(L"Push me", { 120u, 40u }, { 10u, 10u });
				btn.Create(hwnd, reinterpret_cast<Hmenu>(1));
				break;
			}
			case WM_COMMAND:
			{
				if (LOWORD(wparam) == 1)
				{
					winiette::MsgBox::Info(L"Ayo");
				}
				break;
			}
			case WM_DESTROY:
				PostQuitMessage(0);
				break;

			default:
				return DefWindowProc(hwnd, msg, wparam, lparam);
			}

			return 0;
		});

	mw.Create();
	mw.Show();

	return mw.Exec();
}
