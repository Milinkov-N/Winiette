#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_WIDGET_H_
#define WINIETTE_INCLUDE_WINIETTE_WIDGET_H_

#include <winiette/win32.h>
#include <winiette/types.h>
#include <winiette/windowclass.h>

#if STDCXX_17_OR_HIGHER
#include <string_view>
#else
#include <string>
#endif  // STDCXX_17_OR_HIGHER

namespace winiette
{
	struct WidgetCreateOptions
	{
		u32 width;
		u32 height;
		u32 x;
		u32 y;
		Dword style;
		Dword style_ex;

		constexpr WidgetCreateOptions() noexcept;
	};

	constexpr WidgetCreateOptions::WidgetCreateOptions() noexcept
		: width(0), height(0), x(0), y(0), style(0), style_ex(0)
	{
	}

	class Widget
	{
	public:
		Widget() = delete;
		Widget(Widget&& other) noexcept;

		auto operator=(Widget&& rhs) noexcept -> Widget&;

	public:
		auto Create(Hwnd parent = nullptr, Hmenu menu = nullptr) -> void;

	public:
		Widget(const Widget&) = delete;
		auto operator=(const Widget&) = delete;

	protected:
#if STDCXX_17_OR_HIGHER
		explicit Widget(std::wstring_view title = L"");
#else
		explicit Widget(std::wstring title = L"");
#endif  // STDCXX_17_OR_HIGHER

	protected:
		virtual auto GetWindowClass() const -> WindowClass;
		virtual auto WindowProc(u32 msg, Wparam wparam, Lparam lparam) -> Lresult;

	protected:
		Hwnd hwnd_;
#if STDCXX_17_OR_HIGHER
		std::wstring_view title_;
#else
		std::wstring title_;
#endif  // STDCXX_17_OR_HIGHER
		WidgetCreateOptions wco_;

	private:
		static auto CALLBACK _MasterWndProc(
			Hwnd hwnd,
			u32 msg,
			Wparam wparam,
			Lparam lparam
		) noexcept -> Lresult;
	};
} // namespace winiette
#endif  // WINIETTE_INCLUDE_WINIETTE_WIDGET_H_
