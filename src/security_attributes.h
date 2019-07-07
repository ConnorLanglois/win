#ifndef SECURITY_ATTRIBUTES_H
#define SECURITY_ATTRIBUTES_H

#include <windows.h>

namespace win {
	class SecurityAttributes {
	public:
		SecurityAttributes() noexcept;
		SecurityAttributes(DWORD length, LPVOID pSecurityDescriptor, BOOL inheritHandle) noexcept;

		operator const LPSECURITY_ATTRIBUTES() noexcept;

		DWORD getLength() const noexcept;
		void setLength(DWORD length) noexcept;

		LPVOID getSecurityDescriptor() const noexcept;
		void setSecurityDescriptor(const LPVOID securityDescriptor) noexcept;

		BOOL getInheritHandle() const noexcept;
		void setInheritHandle(BOOL inheritHandle) noexcept;

	private:
		SECURITY_ATTRIBUTES securityAttributes;
	};
}

#endif
