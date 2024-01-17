#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_BUTTON_H_
#define WINIETTE_INCLUDE_WINIETTE_BUTTON_H_

#include <string_view>

#include <winiette/types.h>
#include <winiette/widget.h>

namespace winiette
{
	class Button : public Widget
	{
	public:
		Button(u64 id, std::wstring_view caption, Size size, Pos pos);

	protected:
		auto GetWindowClass() const->WindowClass final;
	};
}  // namespace winiette

#endif  // WINIETTE_INCLUDE_WINIETTE_BUTTON_H_
