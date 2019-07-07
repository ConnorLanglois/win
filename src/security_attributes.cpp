#include "security_attributes.h"

#include <windows.h>

namespace win {
	SecurityAttributes::SecurityAttributes() noexcept : SecurityAttributes(0, NULL, 0) {}

	SecurityAttributes::SecurityAttributes(const DWORD length, LPVOID const pSecurityDescriptor, const BOOL inheritHandle) noexcept {
		securityAttributes.nLength = length;
		securityAttributes.lpSecurityDescriptor = pSecurityDescriptor;
		securityAttributes.bInheritHandle = inheritHandle;
	}

	SecurityAttributes::operator const LPSECURITY_ATTRIBUTES() noexcept {
		return &securityAttributes;
	}

	DWORD SecurityAttributes::getLength() const noexcept {
		return securityAttributes.nLength;
	}

	void SecurityAttributes::setLength(const DWORD length) noexcept {
		securityAttributes.nLength = length;
	}

	LPVOID SecurityAttributes::getSecurityDescriptor() const noexcept {
		return securityAttributes.lpSecurityDescriptor;
	}

	void SecurityAttributes::setSecurityDescriptor(const LPVOID pSecurityDescriptor) noexcept {
		securityAttributes.lpSecurityDescriptor = pSecurityDescriptor;
	}

	BOOL SecurityAttributes::getInheritHandle() const noexcept {
		return securityAttributes.bInheritHandle;
	}

	void SecurityAttributes::setInheritHandle(const BOOL inheritHandle) noexcept {
		securityAttributes.bInheritHandle = inheritHandle;
	}
}
