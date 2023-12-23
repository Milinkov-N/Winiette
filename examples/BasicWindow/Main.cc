#include <ctime>
#include <tuple>

#include <winiette/winiette.h>

using namespace winiette::types;

auto WinMain(Hinstance hinstance, i32 cmd_show) -> i32
{
	std::ignore = hinstance;
	std::ignore = cmd_show;

	winiette::Window mw(L"Winiette Basic Window", { 1080u, 720u }, { 100u, 100u });
	u64 btn_id = 101;

	mw.EmplaceWidget<winiette::Button>(
		btn_id,
		L"Push me",
		winiette::Size(120u, 40u),
		winiette::Pos(10u, 10u)
	);
	mw.Connect(btn_id, [] { winiette::MsgBox::Info(L"Ayo"); });

	mw.Create();
	mw.Show();

	return mw.Exec();
}
