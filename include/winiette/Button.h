#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_BUTTON_H_
#define WINIETTE_INCLUDE_WINIETTE_BUTTON_H_

#include <string_view>
#include <functional>

#include <winiette/types.h>
#include <winiette/widget.h>

namespace winiette
{
	class Button : public Widget
	{
	public:
		using Callback = std::function<void(Hwnd)>;

	public:
		Button(std::wstring_view caption, Size size, Pos pos);

	public:
		auto OnClick(Callback callback) -> void;
		auto HandleClick(Hwnd hwnd) -> void;

	protected:
		virtual auto OnClickInterface(Hwnd hwnd) const -> void;
		auto GetWindowClass() const->WindowClass final;

	private:
		Callback cb_;
	};
}  // namespace winiette

#endif  // WINIETTE_INCLUDE_WINIETTE_BUTTON_H_
