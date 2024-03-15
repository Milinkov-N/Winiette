#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_WIDGET_H_
#define WINIETTE_INCLUDE_WINIETTE_WIDGET_H_

#include <winiette/win32.h>
#include <winiette/types.h>
#include <winiette/windowclass.h>

#include <string_view>

namespace winiette
{
	enum class WidgetStyle : i64
	{
		Overlapped = 0x00000000L,
		Popup = 0x80000000L,
		Child = 0x40000000L,
		Minimize = 0x20000000L,
		Visible = 0x10000000L,
		Disabled = 0x08000000L,
		ClipSiblings = 0x04000000L,
		ClipChildren = 0x02000000L,
		Maximize = 0x01000000L,
		Caption = 0x00C00000L,
		Border = 0x00800000L,
		DialogFrame = 0x00400000L,
		Vscroll = 0x00200000L,
		Hscroll = 0x00100000L,
		SysMenu = 0x00080000L,
		Thickframe = 0x00040000L,
		Group = 0x00020000L,
		TabStop = 0x00010000L,
		MinimizeBox = 0x00020000L,
		MaximizeBox = 0x00010000L,
		OverlappedWindow = Overlapped
			| Caption
			| SysMenu
			| Thickframe
			| MinimizeBox
			| MaximizeBox,
		PopupWindow = Popup
			| Border
			| SysMenu,
	};

	using Ws = WidgetStyle;

	constexpr auto operator|(const Ws& lhs, const Ws& rhs) -> Ws
	{
		return static_cast<Ws>(static_cast<Dword>(lhs) | static_cast<Dword>(rhs));
	}

	struct WidgetCreateOptions
	{
		Size size;
		Pos pos;
		WidgetStyle style;
		Dword style_ex;
		Hmenu menu;

		constexpr WidgetCreateOptions() noexcept;
	};

	constexpr WidgetCreateOptions::WidgetCreateOptions() noexcept
		: style(Ws::Overlapped), style_ex(0), menu(nullptr)
	{
	}

	class Widget
	{
	public:
		// Widget() = delete;
		Widget(Widget&& other) noexcept;

		auto operator=(Widget&& rhs) noexcept -> Widget&;

	public:
		auto Create(Hwnd parent = nullptr, Hmenu menu = nullptr) -> void;
		constexpr auto GetWindowHandle() const noexcept -> const Hwnd&;
		auto GetMenuHandle() const -> Hmenu;
		constexpr auto GetCreateOptions() const noexcept -> const WidgetCreateOptions&;

	public:
		Widget(const Widget&) = delete;
		auto operator=(const Widget&) = delete;

	protected:
		explicit Widget(std::wstring_view title = L"");

	protected:
		virtual auto GetWindowClass() const->WindowClass;
		virtual auto WindowProc(u32 msg, Wparam wparam, Lparam lparam) -> Lresult;

	protected:
		Hwnd hwnd_;
		std::wstring_view title_;
		WidgetCreateOptions wco_;

	private:
		static auto CALLBACK _MasterWndProc(
			Hwnd hwnd,
			u32 msg,
			Wparam wparam,
			Lparam lparam
		) noexcept -> Lresult;
	};

	constexpr auto Widget::GetWindowHandle() const noexcept -> const Hwnd&
	{
		return hwnd_;
	}

	constexpr auto Widget::GetCreateOptions() const noexcept -> const WidgetCreateOptions&
	{
		return wco_;
	}
} // namespace winiette
#endif  // WINIETTE_INCLUDE_WINIETTE_WIDGET_H_
