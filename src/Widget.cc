#include "winiette/widget.h"

#include <system_error>

winiette::Widget::Widget(Widget&& other) noexcept
    : hwnd_(std::exchange(other.hwnd_, nullptr)),
    title_(std::move(other.title_)),
    wco_(other.wco_)
{
}

auto winiette::Widget::operator=(Widget&& rhs) noexcept -> Widget&
{
    hwnd_ = std::exchange(rhs.hwnd_, nullptr);
    title_ = std::move(rhs.title_);
    wco_ = rhs.wco_;
    return *this;
}

auto winiette::Widget::Create(Hwnd parent, Hmenu menu) -> void
{
    auto wcex(GetWindowClass());

    // FIXME: Better error message (maybe custom exception)
    if (!wcex.is_builtin() && !wcex.Register() && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        throw std::system_error(GetLastError(), std::system_category());

    hwnd_ = CreateWindowExW(
        wco_.style_ex,
        wcex.class_name().data(),
        title_.data(),
        static_cast<Dword>(wco_.style),
        wco_.pos.x,
        wco_.pos.y,
        wco_.size.w,
        wco_.size.h,
        parent,
        wco_.menu,
        GetModuleHandleW(nullptr),
        this
    );

    // FIXME: Better error message (maybe custom exception)
    if (hwnd_ == nullptr)
        throw std::runtime_error("failed to initialize window");
}

auto winiette::Widget::GetMenuHandle() const -> Hmenu
{
    return GetMenu(hwnd_);
}

winiette::Widget::Widget(std::wstring_view title)
	: hwnd_(nullptr), title_(title)
{
}

auto winiette::Widget::GetWindowClass() const -> WindowClass
{
    WindowClass wc;

    wc.window_proc(&Widget::_MasterWndProc);
    wc.hinstance(GetModuleHandleW(nullptr));

	return wc;
}

auto winiette::Widget::WindowProc(u32 msg, Wparam wparam, Lparam lparam) -> Lresult
{
    return DefWindowProcW(hwnd_, msg, wparam, lparam);
}

auto winiette::Widget::_MasterWndProc(Hwnd hwnd, u32 msg, Wparam wparam, Lparam lparam) noexcept -> Lresult
{
    if (msg == WM_NCCREATE)
    {
        CreateStructPtr pcs = reinterpret_cast<CreateStructPtr>(lparam);
        Widget* p_widget = reinterpret_cast<Widget*>(pcs->lpCreateParams);

        p_widget->hwnd_ = hwnd;
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LongPtr>(p_widget));
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }

    Widget* p_widget = reinterpret_cast<Widget*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    Lresult res = 0;

    if (p_widget != nullptr)
    {
        res = p_widget->WindowProc(msg, wparam, lparam);
    }
    else
    {
        res = DefWindowProc(hwnd, msg, wparam, lparam);
    }

    return res;
}
