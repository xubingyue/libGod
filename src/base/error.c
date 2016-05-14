#include <god/base/error.h>

#ifdef _GOD_WINDOWS_
god_error_t god_last_error() {
    return ::GetLastError();
}

void god_set_last_error(god_error_t e) {
    SetLastError(e);
}
#else
god_error_t god_last_error() {
    return errno;
}

void god_set_last_error(god_error_t e) {
    errno = e;
}
#endif

