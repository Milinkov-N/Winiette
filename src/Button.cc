#include <winiette/button.h>

winiette::Button::Button(u64 id, std::wstring_view caption, Size size, Pos pos)
    : Widget(caption)
{
    wco_.size = size;
    wco_.pos = pos;
    wco_.style = Ws::Visible | Ws::Child;
    wco_.menu = reinterpret_cast<Hmenu>(id);
}

auto winiette::Button::GetWindowClass() const -> WindowClass
{
    WindowClass wc;

    wc.class_name(L"button");
    wc.is_builtin(true);

    return wc;
}
