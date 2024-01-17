#include <tuple>

#include <winiette/winiette.h>

using namespace winiette::types;

auto WinMain(Hinstance hinstance, i32 show_cmd) -> i32
{
	std::ignore = hinstance;
	std::ignore = show_cmd;

	winiette::Window mw(L"Winiette Drawing Example", { 1080u, 720u }, { 100u, 100u });


	mw.OnPaint([](Hwnd hwnd)
		{
			winiette::Drawer drawer(hwnd);
			i32 offset = 0;

			// Drawing text using custom font
			{
				auto fb = winiette::Font::Builder(drawer.hdc());
				fb.Size(48);
				fb.FaceName(L"Cascadia Mono");

				auto tc_guard = drawer.UsingTextColor(Color(178, 56, 243));
				auto font_guard = drawer.UsingFont(fb.BuildUnique());

				offset = drawer.Text(
					{ 10, 0 },
					L"Hello from Winiette Framework\nGive a star on GitHub :)"
				);
			}

			drawer.Text({ 10, static_cast<u32>(offset) + 32u }, L"Text with default fontface");

			// multiline text
			drawer.Text({ 10, 150 }, L"First Line\nSecond Line\nThird Line");

			drawer.Pixel({ 500, 500 }, Color(255, 0, 0));
			drawer.Pixel({ 500, 501 }, Color(255, 0, 0));
			drawer.Pixel({ 501, 500 }, Color(255, 0, 0));
			drawer.Pixel({ 501, 501 }, Color(255, 0, 0));

			return 0;
		});

	mw.Create();
	mw.Show();

	return mw.Exec();
}