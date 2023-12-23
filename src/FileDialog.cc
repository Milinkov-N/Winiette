#include <winiette/filedialog.h>

#include <sstream>

winiette::FileDialog::FileDialog() : ofn_{ 0 }
{
	ofn_.lStructSize = sizeof(ofn_);
	ofn_.lpstrFile = filename_.data();
	ofn_.nMaxFile = sizeof(wchar_t[MAX_PATH]);
	ofn_.nFilterIndex = 1;
	ofn_.lpstrInitialDir = nullptr;
	ofn_.lpstrFileTitle = nullptr;
	ofn_.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}

winiette::FileDialog::FileDialog(Hwnd hwnd) : FileDialog()
{
	ofn_.hwndOwner = hwnd;
}

auto winiette::FileDialog::AddFilter(std::pair<std::wstring_view, std::wstring_view> filter)
-> void
{
	filters_.push_back(filter);
}

auto winiette::FileDialog::InitialDir(std::wstring_view dir) -> void
{
	ofn_.lpstrInitialDir = dir.data();
}

auto winiette::FileDialog::FileTitle(std::wstring_view title) -> void
{
	ofn_.lpstrTitle = title.data();
}

auto winiette::FileDialog::Open() -> std::optional<std::wstring_view>
{
	auto str = _ConstructFilters();
	ofn_.lpstrFilter = str.data();

	if (!GetOpenFileNameW(&ofn_))
		return {};
	else
		return { ofn_.lpstrFile };
}

auto winiette::FileDialog::Save() -> std::optional<std::wstring_view>
{
	auto str = _ConstructFilters();
	ofn_.lpstrFilter = str.data();

	if (!GetSaveFileNameW(&ofn_))
		return {};
	else
		return { ofn_.lpstrFile };
}

auto winiette::FileDialog::_ConstructFilters() -> std::wstring
{
	std::wstringstream wss;

	for (const auto& f : filters_)
		wss << f.name() << '\0' << f.filter() << '\0';
	wss << '\0';

	return wss.str();
}
