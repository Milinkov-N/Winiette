#include <winiette/font.h>

winiette::Font::Font(Hdc hdc, Hfont hfont) noexcept
	: hdc_(hdc), font_(hfont), prev_font_(nullptr)
{
}

winiette::Font::Font(Font&& other) noexcept
	: hdc_(std::exchange(other.hdc_, nullptr)),
	font_(std::exchange(other.font_, nullptr)),
	prev_font_(std::exchange(other.prev_font_, nullptr))
{
}

auto winiette::Font::operator=(Font&& rhs) noexcept -> Font&
{
	hdc_ = std::exchange(rhs.hdc_, nullptr);
	font_ = std::exchange(rhs.font_, nullptr);
	prev_font_ = std::exchange(rhs.prev_font_, nullptr);
	return *this;
}

winiette::Font::Font(const Font& other)
	: hdc_(other.hdc_), prev_font_(other.prev_font_), font_(other.font_)
{
}

 auto winiette::Font::operator=(const Font& rhs) -> Font
{
	hdc_ = rhs.hdc_;
	prev_font_ = rhs.prev_font_;
	font_ = rhs.font_;
	return *this;
}

winiette::Font::~Font() noexcept
{
	if (prev_font_ != nullptr)
		SelectObject(hdc_, prev_font_);
	DeleteObject(font_);
}

auto winiette::Font::Use() -> void
{
	if (font_ != nullptr)
		prev_font_ = reinterpret_cast<Hfont>(SelectObject(hdc_, font_));
}

auto winiette::Font::log_font() const -> LogFont
{
	LogFont lf{ 0 };
	GetObjectW(font_, sizeof(LogFont), &lf);
	return lf;
}

auto winiette::FontBuilder::Size(i32 size) -> void
{
	font_struct_.lfHeight = size;
}
auto winiette::FontBuilder::Width(i32 width) -> void
{
	font_struct_.lfWidth = width;
}
auto winiette::FontBuilder::Escapement(i32 esc) -> void
{
	font_struct_.lfEscapement = esc;
}
auto winiette::FontBuilder::Orientation(i32 orient) -> void
{
	font_struct_.lfOrientation = orient;
}
auto winiette::FontBuilder::Weight(FontWeight weight) -> void
{
	font_struct_.lfWeight = static_cast<i32>(weight);
}
auto winiette::FontBuilder::Italic() -> void
{
	font_struct_.lfItalic = true;
}
auto winiette::FontBuilder::Underline() -> void
{
	font_struct_.lfUnderline = true;
}
auto winiette::FontBuilder::StrikeOut() -> void
{
	font_struct_.lfStrikeOut = true;
}
auto winiette::FontBuilder::Charset(CharSet charset) -> void
{
	font_struct_.lfCharSet = static_cast<u8>(charset);
}
auto winiette::FontBuilder::OutPrecision(Dword out_precision) -> void
{
	font_struct_.lfOutPrecision = static_cast<u8>(out_precision);
}
auto winiette::FontBuilder::iClipPrecision(Dword clip_precision) -> void
{
	font_struct_.lfClipPrecision = static_cast<u8>(clip_precision);
}
auto winiette::FontBuilder::Quality(Dword quality) -> void
{
	font_struct_.lfQuality = static_cast<u8>(quality);
}
auto winiette::FontBuilder::PitchAndFamily(Dword pitch_and_family) -> void
{
	font_struct_.lfPitchAndFamily = static_cast<u8>(pitch_and_family);
}
auto winiette::FontBuilder::FaceName(std::wstring_view face_name) -> void
{
	face_name_ = face_name;
}
auto winiette::FontBuilder::Build() const noexcept -> Font
{
	return Font(hdc_, CreateFontW(
		font_struct_.lfHeight,
		font_struct_.lfWidth,
		font_struct_.lfEscapement,
		font_struct_.lfOrientation,
		font_struct_.lfWeight,
		font_struct_.lfItalic,
		font_struct_.lfUnderline,
		font_struct_.lfStrikeOut,
		font_struct_.lfCharSet,
		font_struct_.lfOutPrecision,
		font_struct_.lfClipPrecision,
		font_struct_.lfQuality,
		font_struct_.lfPitchAndFamily,
		face_name_.data()
	));
}

auto winiette::FontBuilder::BuildUnique() const noexcept -> std::unique_ptr<Font>
{
	return std::make_unique<Font>(hdc_, CreateFontW(
		font_struct_.lfHeight,
		font_struct_.lfWidth,
		font_struct_.lfEscapement,
		font_struct_.lfOrientation,
		font_struct_.lfWeight,
		font_struct_.lfItalic,
		font_struct_.lfUnderline,
		font_struct_.lfStrikeOut,
		font_struct_.lfCharSet,
		font_struct_.lfOutPrecision,
		font_struct_.lfClipPrecision,
		font_struct_.lfQuality,
		font_struct_.lfPitchAndFamily,
		face_name_.data()
	));
}
