#include <thread>

#include "ThreadUtils.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <thread>
#endif

void ThreadUtils::sleepFor(int64_t microseconds) {
#ifdef _WIN32
	const DWORD milliseconds = static_cast<DWORD>(microseconds / 1000);
	Sleep(milliseconds); //sleep uses milliseconds
#else
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
#endif
}
