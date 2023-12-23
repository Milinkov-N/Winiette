#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_MSG_BOX_H_
#define WINIETTE_INCLUDE_WINIETTE_MSG_BOX_H_

#include <string_view>

#include <winiette/win32.h>
#include <winiette/types.h>

namespace winiette
{
	enum class MsgBoxStyle : u32
	{
		// buttons
		AbortRetryIgnore = 0x00000002UL,
		CancelTryContinue = 0x00000006UL,
		Help = 0x00004000UL,
		Ok = 0x00000000UL,
		OkCancel = 0x00000001UL,
		RetryCancel = 0x00000005UL,
		YesNo = 0x00000004UL,
		YesNoCancel = 0x00000003UL,
		// icons
		IconExclamation = 0x00000030UL,
		IconWarn = 0x00000030UL,
		IconInfo = 0x00000040UL,
		IconAsterisk = 0x00000040UL,
		IconQuestion = 0x00000020UL,
		IconError = 0x00000010UL,
	};

	using Mbs = MsgBoxStyle;

	constexpr auto operator|(const Mbs& lhs, const Mbs& rhs) -> Mbs
	{
		return static_cast<Mbs>(static_cast<u32>(lhs) | static_cast<u32>(rhs));
	}

	enum class MsgBoxReturnStatus
	{
		Ok = 1,
		Cancel = 2,
		Abort = 3,
		Retry = 4,
		Ignore = 5,
		Yes = 6,
		No = 7,
		TryAgain = 10,
		Continue = 11,
	};

	struct MsgBox
	{
		using Status = MsgBoxReturnStatus;

		static auto Error(
			std::wstring_view text,
			std::wstring_view caption = L"Error",
			Mbs options = Mbs::IconError
		) -> Status;

		static auto Info(
			std::wstring_view text,
			std::wstring_view caption = L"Info",
			Mbs options = Mbs::IconInfo
		) -> Status;
	};
}  // namespace winiette

#endif  // WINIETTE_INCLUDE_WINIETTE_MSG_BOX_H_
