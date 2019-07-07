#include "process.h"

#include <windows.h>
#include <tlhelp32.h>

#include <string>
#include <unordered_map>

namespace win {
	namespace mem {
		Process::Process(const DWORD pid, const HANDLE handle) noexcept : pid(pid), pHandle(std::make_shared<Handle>(handle)) {}

		const Process Process::open(const AccessRights desiredAccess, const BOOL inheritHandle, const std::string processName) {
			return open(desiredAccess, inheritHandle, getPid(processName));
		}
		const Process Process::open(const AccessRights desiredAccess, const BOOL inheritHandle, const DWORD pid) noexcept {
			return Process(pid, OpenProcess(static_cast<DWORD>(desiredAccess), inheritHandle, pid));
		}

		const Process Process::getCurrent() noexcept {
			const HANDLE handle = GetCurrentProcess();

			return Process(GetProcessId(handle), handle);
		}

		DWORD Process::getPid(const std::string name) {
			return Process::getList().at(name).getPid();
		}

		const std::unordered_map<std::string, Process::ProcessEntry> Process::getList() noexcept {
			std::unordered_map<std::string, ProcessEntry> processEntries;

			const HANDLE hProcessSnap = CreateToolhelp32Snapshot(static_cast<DWORD>(TH32CSFlags::SNAPPROCESS), 0);
			ProcessEntry processEntry;

			for (BOOL copied = Process32First(hProcessSnap, processEntry); copied; copied = Process32Next(hProcessSnap, processEntry)) {
				processEntries[processEntry.getName()] = processEntry;
			}

			CloseHandle(hProcessSnap);

			return processEntries;
		}

		BOOL Process::read(const LPCVOID baseAddress, const LPVOID buffer, const SIZE_T size, SIZE_T* const numberOfBytesRead) const noexcept {
			return ReadProcessMemory(*pHandle, baseAddress, buffer, size, numberOfBytesRead);
		}

		BOOL Process::write(const LPVOID baseAddress, const LPCVOID buffer, const SIZE_T size, SIZE_T* const numberOfBytesWritten) const noexcept {
			return WriteProcessMemory(*pHandle, baseAddress, buffer, size, numberOfBytesWritten);
		}

		const Handle Process::createThread(const LPSECURITY_ATTRIBUTES pThreadAttributes, const SIZE_T stackSize, const LPTHREAD_START_ROUTINE pStartAddress, const LPVOID pParameter, const DWORD creationFlags, const LPDWORD pThreadId) const noexcept {
			return CreateRemoteThread(*pHandle, pThreadAttributes, stackSize, pStartAddress, pParameter, creationFlags, pThreadId);
		}

		const BYTE* Process::getModuleBase(const std::string name) const {
			return getModules().at(name).getBaseAddress();
		}

		const std::unordered_map<std::string, Process::ModuleEntry> Process::getModules() const noexcept {
			std::unordered_map<std::string, ModuleEntry> modules;

			const HANDLE hSnapshot = CreateToolhelp32Snapshot(static_cast<DWORD>(TH32CSFlags::SNAPMODULE) | static_cast<DWORD>(TH32CSFlags::SNAPMODULE32), pid);
			ModuleEntry moduleEntry;

			for (BOOL copied = Module32First(hSnapshot, moduleEntry); copied; copied = Module32Next(hSnapshot, moduleEntry)) {
				modules[moduleEntry.getName()] = moduleEntry;
			}

			return modules;
		}

		BOOL Process::close() noexcept {
			pHandle.reset();

			return true;
		}

		Process::ProcessEntry::ProcessEntry() noexcept {
			processEntry.dwSize = sizeof(PROCESSENTRY32);
		}

		Process::ProcessEntry::operator LPPROCESSENTRY32() noexcept {
			return &processEntry;
		}

		DWORD Process::ProcessEntry::getSize() const noexcept {
			return processEntry.dwSize;
		}

		DWORD Process::ProcessEntry::getPid() const noexcept {
			return processEntry.th32ProcessID;
		}

		DWORD Process::ProcessEntry::getNumThreads() const noexcept {
			return processEntry.cntThreads;
		}

		DWORD Process::ProcessEntry::getParentPid() const noexcept {
			return processEntry.th32ParentProcessID;
		}

		LONG Process::ProcessEntry::getBasePriority() const noexcept {
			return processEntry.pcPriClassBase;
		}

		const TCHAR* Process::ProcessEntry::getName() const noexcept {
			return processEntry.szExeFile;
		}

		Process::ModuleEntry::ModuleEntry() noexcept {
			moduleEntry.dwSize = sizeof(MODULEENTRY32);
		}

		Process::ModuleEntry::operator LPMODULEENTRY32() noexcept {
			return &moduleEntry;
		}

		DWORD Process::ModuleEntry::getPid() const noexcept {
			return moduleEntry.th32ProcessID;
		}

		const BYTE* Process::ModuleEntry::getBaseAddress() const noexcept {
			return moduleEntry.modBaseAddr;
		}

		DWORD Process::ModuleEntry::getBaseSize() const noexcept {
			return moduleEntry.dwSize;
		}

		HMODULE Process::ModuleEntry::getHandle() const noexcept {
			return moduleEntry.hModule;
		}

		const TCHAR* Process::ModuleEntry::getName() const noexcept {
			return moduleEntry.szModule;
		}

		const TCHAR* Process::ModuleEntry::getPath() const noexcept {
			return moduleEntry.szExePath;
		}
	}
}
