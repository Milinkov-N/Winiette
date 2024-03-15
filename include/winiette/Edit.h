#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_EDIT_H_
#define WINIETTE_INCLUDE_WINIETTE_EDIT_H_

#include <winiette/win32.h>
#include <winiette/types.h>
#include <winiette/widget.h>

namespace winiette
{
	enum class EditStyle
	{
		Left = 0x0000L,
		Center = 0x0001L,
		Right = 0x0002L,
		Multiline = 0x0004L,
		Uppercase = 0x0008L,
		Lowercase = 0x0010L,
		Password = 0x0020L,
		AutoVscroll = 0x0040L,
		AutoHscroll = 0x0080L,
		Nohidesel = 0x0100L,
		OemConvert = 0x0400L,
		ReadOnly = 0x0800L,
		WantReturn = 0x1000L,
	};

	using Es = EditStyle;

	constexpr auto operator|(const Es& lhs, const Es& rhs) -> Es
	{
		return static_cast<Es>(static_cast<Dword>(lhs) | static_cast<Dword>(rhs));
	}

	constexpr auto operator|(const Ws& lhs, const Es& rhs) -> winiette::Ws
	{
		return static_cast<Ws>(static_cast<Dword>(lhs) | static_cast<Dword>(rhs));
	}

	class Edit : public Widget
	{
	public:
		Edit(u64 id)
		{
			wco_.pos = { 10, 100 };
			wco_.size = { 500, 500 };
			wco_.style = winiette::Ws::Visible
				| winiette::Ws::Child
				| winiette::Ws::Vscroll
				| Es::Multiline
				| Es::AutoVscroll;
			wco_.menu = reinterpret_cast<Hmenu>(id);
		}

	private:
		auto GetWindowClass() const-> WindowClass final
		{
			WindowClass wc;
			ES_MULTILINE;
			wc.class_name(L"edit");
			wc.is_builtin(true);
			return wc;
		}
	};
}  // namespace winiette

#endif  // WINIETTE_INCLUDE_WINIETTE_EDIT_H_
