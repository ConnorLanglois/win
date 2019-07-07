#ifndef PROCESS_H
#define PROCESS_H

#include "handle.h"

#include <windows.h>
#include <tlhelp32.h>

#include <memory>
#include <string>
#include <unordered_map>

namespace win {
	namespace mem {
		class Process {
		public:
			explicit Process(DWORD pid, HANDLE handle) noexcept;

			enum class AccessRights : DWORD {
				ALL_ACCESS = PROCESS_ALL_ACCESS,
				CREATE_PROCESS = PROCESS_CREATE_PROCESS,
				CREATE_THREAD = PROCESS_CREATE_THREAD,
				DUP_HANDLE = PROCESS_DUP_HANDLE,
				QUERY_INFORMATION = PROCESS_QUERY_INFORMATION,
				QUERY_LIMITED_INFORMATION = PROCESS_QUERY_LIMITED_INFORMATION,
				SET_INFORMATION = PROCESS_SET_INFORMATION,
				SET_QUOTA = PROCESS_SET_QUOTA,
				SUSPEND_RESUME = PROCESS_SUSPEND_RESUME,
				SYNCHRONIZE_ = SYNCHRONIZE,
				TERMINATE = PROCESS_TERMINATE,
				VM_OPERATION = PROCESS_VM_OPERATION,
				VM_READ = PROCESS_VM_READ,
				VM_WRITE = PROCESS_VM_WRITE
			};

			static const Process open(AccessRights desiredAccess, BOOL inheritHandle, const std::string processName);
			static const Process open(AccessRights desiredAccess, BOOL inheritHandle, DWORD pid) noexcept;
			static const Process getCurrent() noexcept;


			template <typename T>
			T Process::read(const Process);
			
			BOOL read(LPCVOID baseAddress, LPVOID buffer, SIZE_T size, SIZE_T* numberOfBytesRead = NULL) const noexcept;
			BOOL write(LPVOID baseAddress, LPCVOID buffer, SIZE_T size, SIZE_T* numberOfBytesWritten = NULL) const noexcept;
			const BYTE* getModuleBase(std::string name) const;
			const Handle createThread(LPSECURITY_ATTRIBUTES pThreadAttributes, SIZE_T stackSize, LPTHREAD_START_ROUTINE pStartAddress, LPVOID pParameter, DWORD creationFlags, LPDWORD pThreadId) const noexcept;
			BOOL close() noexcept;

		private:
			class ProcessEntry {
			public:
				ProcessEntry() noexcept;

				operator LPPROCESSENTRY32() noexcept;

				DWORD getSize() const noexcept;
				DWORD getPid() const noexcept;
				DWORD getNumThreads() const noexcept;
				DWORD getParentPid() const noexcept;
				LONG getBasePriority() const noexcept;
				const TCHAR* getName() const noexcept;

			private:
				PROCESSENTRY32 processEntry;
			};

			class ModuleEntry {
			public:
				ModuleEntry() noexcept;

				operator LPMODULEENTRY32() noexcept;

				DWORD getPid() const noexcept;
				const BYTE* getBaseAddress() const noexcept;
				DWORD getBaseSize() const noexcept;
				HMODULE getHandle() const noexcept;
				const TCHAR* getName() const noexcept;
				const TCHAR* getPath() const noexcept;

			private:
				MODULEENTRY32 moduleEntry;
			};

			enum class TH32CSFlags : DWORD {
				INHERIT = TH32CS_INHERIT,
				SNAPALL = TH32CS_SNAPALL,
				SNAPHEAPLIST = TH32CS_SNAPHEAPLIST,
				SNAPMODULE = TH32CS_SNAPMODULE,
				SNAPMODULE32 = TH32CS_SNAPMODULE32,
				SNAPPROCESS = TH32CS_SNAPPROCESS,
				SNAPTHREAD = TH32CS_SNAPTHREAD
			};

			static DWORD getPid(const std::string name);
			static const std::unordered_map<std::string, ProcessEntry> getList() noexcept;

			const std::unordered_map<std::string, ModuleEntry> getModules() const noexcept;

			const DWORD pid;
			std::shared_ptr<Handle> pHandle;
		};
	}
}

#endif
