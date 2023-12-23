#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_FILE_DIALOG_H_
#define WINIETTE_INCLUDE_WINIETTE_FILE_DIALOG_H_

#include <array>
#include <string_view>
#include <utility>
#include <vector>
#include <optional>

#include <winiette/win32.h>
#include <winiette/types.h>

namespace winiette
{
	class FileFilter
	{
	public:
		FileFilter() = default;
		constexpr FileFilter(std::pair<std::wstring_view, std::wstring_view> filter);

	public:
		constexpr auto inner() const noexcept -> std::pair<std::wstring_view, std::wstring_view>;
		constexpr auto name() const noexcept -> std::wstring_view;
		constexpr auto filter() const noexcept -> std::wstring_view;

	private:
		std::pair<std::wstring_view, std::wstring_view> filter_;
	};

	constexpr FileFilter::FileFilter(std::pair<std::wstring_view, std::wstring_view> filter)
		: filter_(filter)
	{
	}

	constexpr auto FileFilter::inner() const noexcept
		-> std::pair<std::wstring_view, std::wstring_view>
	{
		return filter_;
	}

	constexpr auto FileFilter::name() const noexcept -> std::wstring_view
	{
		return filter_.first;
	}

	constexpr auto FileFilter::filter() const noexcept -> std::wstring_view
	{
		return filter_.second;
	}

	class FileDialog
	{
	public:
		FileDialog();
		FileDialog(Hwnd hwnd);

	public:
		auto AddFilter(std::pair<std::wstring_view, std::wstring_view> filter) -> void;
		auto InitialDir(std::wstring_view dir) -> void;
		auto FileTitle(std::wstring_view title) -> void;
		[[nodiscard]] auto Open() -> std::optional<std::wstring_view>;
		[[nodiscard]] auto Save() -> std::optional<std::wstring_view>;

	private:
		auto _ConstructFilters() -> std::wstring;

	private:
		OpenFileNameStruct ofn_;
		std::array<wchar_t, MAX_PATH> filename_;
		std::vector<FileFilter> filters_;
	};
}  // namespace winiette

#endif  // WINIETTE_INCLUDE_WINIETTE_FILE_DIALOG_H_
