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

			// Drawing text using custom font
			{
				auto guard = drawer.UsingTextColor(Color(178, 56, 243));

				auto fb = winiette::Font::Builder(drawer.hdc());
				fb.Size(48);
				fb.FaceName(L"Time New Roman");

				auto font = fb.Build();
				drawer.Text({ 10, 10 }, L"Hello from Winiette Framework", std::move(font));
			}

			drawer.Text({ 10, 82 }, L"Text with default fontface");

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