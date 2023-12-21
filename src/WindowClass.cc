#include <winiette/windowclass.h>


auto winiette::WindowClass::Register() const -> Atom
{
	return RegisterClassExW(&wcex_);
}
