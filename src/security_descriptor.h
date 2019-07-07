#ifndef SECURITY_DESCRIPTOR_H
#define SECURITY_DESCRIPTOR_H

#include <windows.h>

namespace win {
	class SecurityDescriptor {
		SecurityDescriptor() noexcept;

		enum class SecurityDescriptorControl : DWORD {
			DACL_AUTO_INHERIT_REQ = SE_DACL_AUTO_INHERIT_REQ,
			DACL_AUTO_INHERITED = SE_DACL_AUTO_INHERITED,
			DACL_DEFAULTED = SE_DACL_DEFAULTED,
			DACL_PRESENT = SE_DACL_PRESENT,
			DACL_PROTECTED = SE_DACL_PROTECTED,
			GROUP_DEFAULTED = SE_GROUP_DEFAULTED,
			OWNER_DEFAULTED = SE_OWNER_DEFAULTED,
			RM_CONTROL_VALID = SE_RM_CONTROL_VALID,
			SACL_AUTO_INHERIT_REQ = SE_SACL_AUTO_INHERIT_REQ,
			SACL_AUTO_INHERITED = SE_SACL_AUTO_INHERITED,
			SACL_DEFAULTED = SE_SACL_DEFAULTED,
			SACL_PRESENT = SE_SACL_PRESENT,
			SACL_PROTECTED = SE_SACL_PROTECTED,
			SELF_RELATIVE = SE_SELF_RELATIVE
		};

		BOOL initialize(DWORD revision) noexcept;
		BOOL isValid() noexcept;

		BOOL getControl(SecurityDescriptorControl* pControl, LPDWORD pRevision) noexcept;

		BOOL getDacl(LPBOOL pDaclPresent, PACL* pDacl, LPBOOL pDaclDefaulted) noexcept;
		BOOL setDacl(BOOL daclPresent, PACL pDacl, BOOL daclDefaulted) noexcept;
		
		BOOL getGroup(PSID* pGroup, LPBOOL pGroupDefaulted) noexcept;
		BOOL setGroup(PSID pGroup, BOOL groupDefaulted) noexcept;
		
		DWORD getLength() noexcept;

		BOOL getOwner(PSID* pOwner, LPBOOL pOwnerDefaulted) noexcept;
		BOOL setOwner(PSID pOwner, BOOL ownerDefaulted) noexcept;
		
		DWORD getRMControl(PUCHAR rMControl) noexcept;
		DWORD setRMControl(PUCHAR rMControl) noexcept;

		BOOL getSacl(LPBOOL pSaclPresent, PACL* pSacl, LPBOOL pSaclDefaulted) noexcept;
		BOOL setSacl(BOOL saclPresent, PACL pSacl, BOOL saclDefaulted) noexcept;

		operator const PSECURITY_DESCRIPTOR() noexcept;

	private:
		SECURITY_DESCRIPTOR securityDescriptor;
	};
}

#endif
