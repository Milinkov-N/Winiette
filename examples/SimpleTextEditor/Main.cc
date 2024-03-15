#include <fstream>
#include <sstream>

#include <winiette/winiette.h>

using namespace winiette::types;

constexpr auto BUTTON_SIZE = winiette::Size(120u, 40u);

auto WinMain(Hinstance hinst, i32 show_cmd) -> int
{
	winiette::Window main_window(L"Text Editor", { 1080u, 720u }, { 100u, 100u });
	auto& edit = main_window.EmplaceWidget<winiette::Edit>(201);
	std::wstring edit_text = L"Hello there";
	u64 of_btn_id = 101, cf_btn_id = 102;
	
	main_window.EmplaceWidget<winiette::Button>(
		of_btn_id,
		L"Open file",
		BUTTON_SIZE,
		winiette::Pos(10u, 10u)
	);

	main_window.EmplaceWidget<winiette::Button>(
		cf_btn_id,
		L"Save file",
		BUTTON_SIZE,
		winiette::Pos(BUTTON_SIZE.width + 20u, 10u)
	);

	main_window.OnSize([&](auto hwnd)
		{
			RECT client_rect = { 0 };
			GetClientRect(hwnd, &client_rect);
			edit.GetCreateOptions().pos.x;
			SetWindowPos(
				edit.GetWindowHandle(),
				nullptr,
				edit.GetCreateOptions().pos.x,
				edit.GetCreateOptions().pos.y,
				client_rect.right - 25,
				client_rect.bottom - edit.GetCreateOptions().pos.y - 25,
				SWP_NOZORDER);
			return 0;
		});

	main_window.Connect(of_btn_id, [&]()
		{
			winiette::FileDialog fd(main_window.GetWindowHandle());
			fd.AddFilter({ L"All files(*.*)", L"*.*" });
			auto filename = fd.Open();

			if (!filename) return;

			std::wifstream ifs(filename.value().data());

			if (!ifs.is_open())
			{
				winiette::MsgBox::Error(L"Couldn't open the file");
				return;
			}

			std::wstringstream wss;
			std::wstring buf;

			while (std::getline(ifs, buf)) wss << buf << "\r\n";
			edit_text = std::move(wss.str());
			SendMessageW(edit.GetWindowHandle(), WM_SETTEXT, 0, (Lparam)edit_text.data());

		});

	main_window.Connect(cf_btn_id, [&]()
		{
			winiette::FileDialog fd(main_window.GetWindowHandle());
			fd.AddFilter({ L"All files(*.*)", L"*.*" });
			auto filename = fd.Save();

			if (!filename) return;

			std::wofstream ifs(filename.value().data());

			if (!ifs.is_open())
			{
				winiette::MsgBox::Error(L"Couldn't open the file");
				return;
			}

			ifs << edit_text;
		});

	main_window.Create();
	main_window.Show();

	return main_window.Exec();
}
