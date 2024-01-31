#pragma once

#include "tools/defs.h"

#include <string>
#include <cstdint>

namespace libs::utils {

#ifdef __linux__
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
    uint32_t gettid() {
        return syscall(SYS_gettid);
    }
#endif //__linux__

#ifdef __APPLE__
#include <pthread.h>
    uint32_t gettid() {
        std::uint64_t tid;
        if (0 != pthread_threadid_np(NULL, &tid)) {
            return 0;
        }
        return (std::uint32_t) tid;
    }
#endif //__MACH__

#ifdef _WIN32
#include <process.h>
#include <winbase.h>
#include <windows.h>
    uint32_t gettid() {
        return GetCurrentThreadId();
    }
#endif // _WIN32


    /// Timer
    static constexpr const char *DEFAULT_GMTIME_FORMAT = "%Y-%m-%d %H:%M:%S GMT";
    static constexpr const char *DEFAULT_LOCALTIME_FORMAT = "%Y-%m-%d %H:%M:%S %z";
    /**
     * Format local time
     * @param time System time
     * @param format Format string in strftime() format, extended by "%f" for microseconds.
     */
    std::string format_localtime(SystemTime time, const char *format = DEFAULT_LOCALTIME_FORMAT);
} // namespace libs::utils
