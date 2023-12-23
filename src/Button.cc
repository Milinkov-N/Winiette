#include <winiette/button.h>

winiette::Button::Button(std::wstring_view caption, Size size, Pos pos)
    : Widget(caption), cb_([](auto) {})
{
    wco_.size = size;
    wco_.pos = pos;
    wco_.style = Ws::Visible | Ws::Child;
}

auto winiette::Button::OnClick(Callback callback) -> void
{
    cb_ = callback;
}

auto winiette::Button::HandleClick(Hwnd hwnd) -> void
{
    OnClickInterface(hwnd);
}

auto winiette::Button::OnClickInterface(Hwnd hwnd) const -> void
{
    cb_(hwnd);
}

auto winiette::Button::GetWindowClass() const -> WindowClass
{
    WindowClass wc;

    wc.class_name(L"button");
    wc.is_builtin(true);

    return wc;
}
