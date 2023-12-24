#pragma once
#ifndef WINIETTE_INCLUDE_WINIETTE_FONT_H_
#define WINIETTE_INCLUDE_WINIETTE_FONT_H_

#include <string_view>

#include <winiette/win32.h>
#include <winiette/types.h>

namespace winiette
{
	enum class FontWeight : i32
	{
		DontCare = 0,
		Thin = 100,
		ExtraLight = 200,
		Light = 300,
		Regular = 400,
		Medium = 500,
		SemiBold = 600,
		Bold = 700,
		ExtraBold = 800,
		Black = 900,
	};

	enum class CharSet : Dword
	{
		Ansi = ANSI_CHARSET,
		Baltic = BALTIC_CHARSET,
		ChineseBigFive = CHINESEBIG5_CHARSET,
		EastEurope = EASTEUROPE_CHARSET,
		Gb2312 = GB2312_CHARSET,
		Greek = GREEK_CHARSET,
		Hangul = HANGUL_CHARSET,
		Mac = MAC_CHARSET,
		Russian = RUSSIAN_CHARSET,
		Shiftjis = SHIFTJIS_CHARSET,
		Symbol = SYMBOL_CHARSET,
		Turkish = TURKISH_CHARSET,
		Vietnamese = VIETNAMESE_CHARSET,
		Johab = JOHAB_CHARSET,
		Arabic = ARABIC_CHARSET,
		Hebrew = HEBREW_CHARSET,
		Thai = THAI_CHARSET,
	};

	class FontBuilder;

	class Font
	{
	public:
		constexpr Font() noexcept;
		Font(Hdc hdc, Hfont hfont) noexcept;
		Font(Font&& other) noexcept;
		auto operator=(Font&& rhs) noexcept -> Font&;
		~Font() noexcept;

	public:
		constexpr static auto Builder(Hdc hdc) -> FontBuilder;
		auto Use() -> void;
		constexpr operator Hfont();

	public:
		Font(const Font&) = delete;
		auto operator=(const Font&) = delete;

	private:
		Hdc hdc_;
		Hfont font_;
		Hfont prev_font_;
	};

	constexpr Font::Font() noexcept
		: hdc_(nullptr), font_(nullptr), prev_font_(nullptr)
	{
	}

	constexpr Font::operator Hfont()
	{
		return font_;
	}

	class FontBuilder
	{
	public:
		constexpr FontBuilder(Hdc hdc) noexcept;

	public:
		auto Size(i32 size) -> void;
		auto Width(i32 width) -> void;
		auto Escapement(i32 esc) -> void;
		auto Orientation(i32 orient) -> void;
		auto Weight(FontWeight weight) -> void;
		auto Italic() -> void;
		auto Underline() -> void;
		auto StrikeOut() -> void;
		auto Charset(CharSet charset) -> void;
		auto OutPrecision(Dword out_precision) -> void;
		auto iClipPrecision(Dword clip_precision) -> void;
		auto Quality(Dword quality) -> void;
		auto PitchAndFamily(Dword pitch_and_family) -> void;
		auto FaceName(std::wstring_view face_name) -> void;
		auto Build() const noexcept -> Font;
	private:
		Hdc hdc_;
		LogFont font_struct_;
		std::wstring_view face_name_;
	};

	constexpr auto Font::Builder(Hdc hdc) -> FontBuilder
	{
		return FontBuilder(hdc);
	}

	constexpr FontBuilder::FontBuilder(Hdc hdc) noexcept
		: hdc_(hdc), font_struct_{ 0 }
	{
	}
}  // namespace winiette

#endif // WINIETTE_INCLUDE_WINIETTE_FONT_H_
