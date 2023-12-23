#include <winiette/MsgBox.h>

auto winiette::MsgBox::Error(std::wstring_view text, std::wstring_view caption, Mbs options) -> Status
{
	return static_cast<Status>(MessageBoxW(nullptr, text.data(), caption.data(), static_cast<u32>(options)));
}

auto winiette::MsgBox::Info(std::wstring_view text, std::wstring_view caption, Mbs options) -> Status
{
	return static_cast<Status>(MessageBoxW(nullptr, text.data(), caption.data(), static_cast<u32>(options)));
}
