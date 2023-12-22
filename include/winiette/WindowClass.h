#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_WINDOW_CLASS_H_
#define WINIETTE_INCLUDE_WINIETTE_WINDOW_CLASS_H_

#include <string_view>

#include <winiette/win32.h>
#include <winiette/types.h>

namespace winiette
{
	class WindowClass
	{
	public:
		constexpr WindowClass();
		constexpr WindowClass(const WndClassEx& wcex, bool builtin = false);

	public:
		auto Register() const -> Atom;

		// getters
	public:
		constexpr auto inner()       const noexcept -> const WndClassEx&;
		constexpr auto window_proc() const noexcept -> const WndProc&;
		constexpr auto hinstance()   const noexcept -> const Hinstance&;
		constexpr auto icon()        const noexcept -> const Hicon&;
		constexpr auto cursor()      const noexcept -> const Hcursor&;
		constexpr auto background()  const noexcept -> const Hbrush&;
		constexpr auto class_name()  const noexcept -> std::wstring_view;
		constexpr auto icon_sm()     const noexcept -> const Hicon&;
		constexpr auto is_builtin()   const noexcept -> bool;

		// setters
	public:
		constexpr auto inner(const WndClassEx& wcex) noexcept -> void;
		constexpr auto window_proc(WndProc wnd_proc) noexcept -> void;
		constexpr auto hinstance(Hinstance hinstance) noexcept -> void;
		constexpr auto icon(Hicon hicon) noexcept -> void;
		constexpr auto cursor(Hcursor hcursor) noexcept -> void;
		constexpr auto background(Hbrush hbrush) noexcept -> void;
		constexpr auto class_name(std::wstring_view class_name) noexcept -> void;
		constexpr auto icon_sm(Hicon hicon_sm) noexcept -> void;
		constexpr auto is_builtin(bool is_builtin) noexcept -> void;

	private:
		WndClassEx wcex_;
		bool builtin_;
	};

	constexpr WindowClass::WindowClass()
		: wcex_{ 0 }, builtin_{ false }
	{
		wcex_.cbSize = sizeof(WndClassEx);
	}

	constexpr WindowClass::WindowClass(const WndClassEx& wcex, bool builtin)
		: wcex_(wcex), builtin_(builtin)
	{
	}

	constexpr auto WindowClass::inner() const noexcept -> const WndClassEx&
	{
		return wcex_;
	}

	constexpr auto WindowClass::window_proc() const noexcept -> const WndProc&
	{
		return wcex_.lpfnWndProc;
	}

	constexpr auto WindowClass::hinstance() const noexcept -> const Hinstance&
	{
		return wcex_.hInstance;
	}

	constexpr auto WindowClass::icon() const noexcept -> const Hicon&
	{
		return wcex_.hIcon;
	}

	constexpr auto WindowClass::cursor() const noexcept -> const Hcursor& {
		return wcex_.hCursor;
	}

	constexpr auto WindowClass::background() const noexcept -> const Hbrush&
	{
		return wcex_.hbrBackground;
	}

	constexpr auto WindowClass::class_name() const noexcept -> std::wstring_view
	{
		return wcex_.lpszClassName;
	}

	constexpr auto WindowClass::icon_sm() const noexcept -> const Hicon&
	{
		return wcex_.hIconSm;
	}
	
	constexpr auto WindowClass::is_builtin() const noexcept -> bool
	{
		return builtin_;
	}

	constexpr auto WindowClass::inner(const WndClassEx& wcex) noexcept -> void
	{
		wcex_ = wcex;
	}

	constexpr auto WindowClass::window_proc(WndProc wnd_proc) noexcept -> void
	{
		wcex_.lpfnWndProc = wnd_proc;
	}

	constexpr auto WindowClass::hinstance(Hinstance hinstance) noexcept -> void
	{
		wcex_.hInstance = hinstance;
	}

	constexpr auto WindowClass::icon(Hicon hicon) noexcept -> void
	{
		wcex_.hIcon = hicon;
	}

	constexpr auto WindowClass::cursor(Hcursor hcursor) noexcept -> void
	{
		wcex_.hCursor = hcursor;
	}
	constexpr auto WindowClass::background(Hbrush hbrush) noexcept -> void
	{
		wcex_.hbrBackground = hbrush;
	}

	constexpr auto WindowClass::class_name(std::wstring_view class_name) noexcept -> void
	{
		wcex_.lpszClassName = class_name.data();
	}

	constexpr auto WindowClass::icon_sm(Hicon hicon_sm) noexcept -> void
	{
		wcex_.hIconSm = hicon_sm;
	}

	constexpr auto WindowClass::is_builtin(bool builtin) noexcept -> void
	{
		builtin_ = builtin;
	}
}  // namespace winiette
#endif  // WINIETTE_INCLUDE_WINIETTE_WINDOW_CLASS_H_
