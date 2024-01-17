
## About

Winiette is a free and open source C++ wrapper (framework in future, hopefully) for writing GUI applications using native WinApi.

This is a hobby project for now, so if I can keep myself motivated to support it - more features will be added, but for now it is just a small library with main abstraction completed: `Widget` class

## Features

This project is currently in early development, so it doesn't have many features, and API is not stable. But here the list of supported features:

- `Widget` class - allows to build any *Windows* widget in OOP way
- Native `Button` class - just a convinience class derived from `Widget` and wraps common behavior of a standard button
- `Window` class - convinience class for creating separate windows. Currenty have API as an Object, but planned in future to be more OOP-friendly.
- `FileDialog` class - simple abstraction of `OpenFileName` / `SaveFileName` functions with nicer and more modern API.
- `Drawer` class - *WinApi's* `Gdi` library abstraction


## Installation

This project is currently supported only as Visual Studio Solution. You can directly clone this repo in Visual Studio start screen or via `PowerShell`:

```powershell
git clone https://github.com/Milinkov-N/Winiette.git
```

Then you can build and/or add it as a dependency to existing project or directly copy *include/* folder and `Winiette.lib` file where you need.
    
## Usage/Examples

### Window

Example of a creating a simple window with Winiette.

```c++
#include <winiette/winiette.h>

using namespace winiette::types;

auto WinMain(Hinstance, i32) -> i32
{
    winiette::Window window(L"Winiette Window",
        { 720u, 420u }, { 150u, 150u });

    window.Create();
    window.Show();

    return window.Exec();
}
```

### Custom Widget

You can create completely custom widget with `Widget` class

```c++
#include <winiette/winiette.h>
#include <winiette/utility.h>

using namespace winiette::types;

using winiette::utility::SystemColorBrush;
using winiette::utility::LoadSystemIcon;
using winiette::utility::LoadSystemCursor;
using winiette::utility::SystemCursorId;

class MyWidget : public winiette::Widget
{
    public:
        MyWidget() : winiette::Widget(L"MyWidget title") {}

    protected:
        auto GetWindowClass() const->winiette::WindowClass override
        {
            auto wc(winiette::Widget::GetWindowClass());

            	wc.background(SystemColorBrush::White());
                wc.icon(LoadSystemIcon(SystemIconId::App));
                wc.cursor(LoadSystemCursor(SystemCursorId::Arrow));
                wc.class_name(L"MyWidgetClass");
                wc.icon_sm(LoadSystemIcon(SystemIconId::App));

            return wc;
        }

        auto WindowProc(u32 msg, Wparam wparam, Lparam lparam) -> Lresult override
        {
            switch (msg)
            {
            case WM_CREATE:
            {
                // Your code...
                break;
            }
            case WM_PAINT:
            {
                // Your code...
                break;
            }
            case WM_COMMAND:
            {
                // Your code...
                break;
            }
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            }
            return DefWindowProc(hwnd_, msg, wparam, lparam);
        }
};

auto WinMain(Hinstance, i32) -> i32
{
    MyWidget my_widget;

    return 0;
}
```
