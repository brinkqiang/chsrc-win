// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// cmake env 
// add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#ifndef __DMFIX_WIN_CONSOLE_H_INCLUDE__
#define __DMFIX_WIN_CONSOLE_H_INCLUDE__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <windows.h>
#include <stdbool.h>
#endif

static inline bool dm_win_console_internal_setup(void) {
#ifdef _WIN32
    bool overall_success_flag = false;
    bool console_handle_processed = false;
    HANDLE handles_to_check[2] = { GetStdHandle(STD_OUTPUT_HANDLE), GetStdHandle(STD_ERROR_HANDLE) };

    for (int i = 0; i < 2; ++i) {
        HANDLE hCurrent = handles_to_check[i];
        if (hCurrent != INVALID_HANDLE_VALUE && GetFileType(hCurrent) == FILE_TYPE_CHAR) {
            console_handle_processed = true;
            DWORD dwOriginalMode = 0;
            if (GetConsoleMode(hCurrent, &dwOriginalMode)) {
                if (!(dwOriginalMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
                    if (SetConsoleMode(hCurrent, dwOriginalMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
                        overall_success_flag = true;
                    } else {
                        return false;
                    }
                } else {
                    overall_success_flag = true;
                }
            } else {
                return false;
            }
        }
    }

    if (!console_handle_processed) {
        return false;
    }
    return overall_success_flag;
#else
    return true;
#endif
}
#if defined(_WIN32) && !defined(DMFIX_WIN_CONSOLE_AUTO_INIT_DISABLED)
static int dm_win_console_auto_init_do_not_use_ = (dm_win_console_internal_setup(), 0);
#endif

#ifdef __cplusplus
}
#endif

#endif // __DMFIX_WIN_CONSOLE_H_INCLUDE__