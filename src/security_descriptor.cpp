#include "security_descriptor.h"

#include <windows.h>

namespace win {
	SecurityDescriptor::SecurityDescriptor() noexcept {}

	BOOL SecurityDescriptor::initialize(const DWORD revision) noexcept {
		return InitializeSecurityDescriptor(&securityDescriptor, revision);
	}

	BOOL SecurityDescriptor::isValid() noexcept {
		return IsValidSecurityDescriptor(&securityDescriptor);
	}

	BOOL SecurityDescriptor::getControl(SecurityDescriptorControl* const pControl, const LPDWORD pRevision) noexcept {
		return GetSecurityDescriptorControl(&securityDescriptor, reinterpret_cast<PSECURITY_DESCRIPTOR_CONTROL>(pControl), pRevision);
	}

	BOOL SecurityDescriptor::getDacl(const LPBOOL pDaclPresent, PACL* const pDacl, const LPBOOL pDaclDefaulted) noexcept {
		return GetSecurityDescriptorDacl(&securityDescriptor, pDaclPresent, pDacl, pDaclDefaulted);
	}

	BOOL SecurityDescriptor::setDacl(const BOOL daclPresent, const PACL pDacl, const BOOL daclDefaulted) noexcept {
		return SetSecurityDescriptorDacl(&securityDescriptor, daclPresent, pDacl, daclDefaulted);
	}

	BOOL SecurityDescriptor::getGroup(PSID* const pGroup, const LPBOOL pGroupDefaulted) noexcept {
		return GetSecurityDescriptorGroup(&securityDescriptor, pGroup, pGroupDefaulted);
	}

	BOOL SecurityDescriptor::setGroup(const PSID pGroup, const BOOL groupDefaulted) noexcept {
		return SetSecurityDescriptorGroup(&securityDescriptor, pGroup, groupDefaulted);
	}

	DWORD SecurityDescriptor::getLength() noexcept {
		return GetSecurityDescriptorLength(&securityDescriptor);
	}

	BOOL SecurityDescriptor::getOwner(PSID* const pOwner, const LPBOOL pOwnerDefaulted) noexcept {
		return GetSecurityDescriptorOwner(&securityDescriptor, pOwner, pOwnerDefaulted);
	}

	BOOL SecurityDescriptor::setOwner(const PSID pOwner, const BOOL ownerDefaulted) noexcept {
		return SetSecurityDescriptorOwner(&securityDescriptor, pOwner, ownerDefaulted);
	}

	DWORD SecurityDescriptor::getRMControl(const PUCHAR rMControl) noexcept {
		return GetSecurityDescriptorRMControl(&securityDescriptor, rMControl);
	}

	DWORD SecurityDescriptor::setRMControl(const PUCHAR rMControl) noexcept {
		return SetSecurityDescriptorRMControl(&securityDescriptor, rMControl);
	}
	
	BOOL SecurityDescriptor::getSacl(const LPBOOL pSaclPresent, PACL* const pSacl, const LPBOOL pSaclDefaulted) noexcept {
		return GetSecurityDescriptorSacl(&securityDescriptor, pSaclPresent, pSacl, pSaclDefaulted);
	}

	BOOL SecurityDescriptor::setSacl(const BOOL saclPresent, const PACL pSacl, const BOOL saclDefaulted) noexcept {
		return SetSecurityDescriptorSacl(&securityDescriptor, saclPresent, pSacl, saclDefaulted);
	}

	SecurityDescriptor::operator const PSECURITY_DESCRIPTOR() noexcept {
		return &securityDescriptor;
	}
}
