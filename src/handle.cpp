#include "handle.h"

#include <windows.h>

namespace win {
	Handle::Handle(const HANDLE handle) noexcept : handle(handle) {}

	Handle::~Handle() noexcept  {
		CloseHandle(handle);
	}

	Handle::operator const HANDLE() const noexcept {
		return handle;
	}
}
