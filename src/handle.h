#ifndef HANDLE_H
#define HANDLE_H

#include <windows.h>

namespace win {
	class Handle {
	public:
		Handle(HANDLE handle) noexcept;
		~Handle() noexcept;
		
		operator const HANDLE() const noexcept;

	private:
		const HANDLE handle;
	};
}

#endif
