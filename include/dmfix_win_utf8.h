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

#ifndef __DMFIX_WIN_UTF8_H_INCLUDE__
#define __DMFIX_WIN_UTF8_H_INCLUDE__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <windows.h>
/*
 * Note: <fcntl.h> and <io.h> from the C++ example are not strictly needed
 * for SetConsoleOutputCP/SetConsoleCP. They would be relevant for functions like _setmode
 * if one wanted to set stdout/stdin to _O_U8TEXT or _O_WTEXT for printf/scanf.
 * The original C++ example's Initializer did not use them.
 */
#else
#include <locale.h> // For setlocale
#endif

#define DMFIX_INTERNAL_CODE_PAGE_UTF8 65001 // Windows code page for UTF-8

static inline void dm_win_utf8_internal_setup(void) {
#ifdef _WIN32
    SetConsoleOutputCP(DMFIX_INTERNAL_CODE_PAGE_UTF8);
    SetConsoleCP(DMFIX_INTERNAL_CODE_PAGE_UTF8);
#else
    /*
     * Attempts to set the program's locale to UTF-8.
     * Common locale strings for UTF-8 include "en_US.utf8", "C.UTF-8".
     * The specific string "en_US.utf8" might not be available on all systems.
     * setlocale(LC_ALL, "") would use the system's environment-defined locale.
     * Sticking to "en_US.utf8" to match the C++ example's behavior.
     */
    setlocale(LC_ALL, "en_US.utf8");
#endif
}

/*
 * "Automatic" initialization for C:
 * This static variable's initializer calls the setup function.
 * If this header is included in multiple C files (translation units),
 * this variable (being static) will be defined in each, and its
 * initializer will run for each. This is generally acceptable because
 * SetConsoleOutputCP, SetConsoleCP, and setlocale (when called repeatedly
 * with the same arguments) are idempotent or have benign side effects.
 *
 * To disable this automatic initialization, define DMFIX_WIN_UTF8_AUTO_INIT_DISABLED
 * before including this header.
 */
#if !defined(DMFIX_WIN_UTF8_AUTO_INIT_DISABLED)
static int dm_win_utf8_auto_init_do_not_use_ = (dm_win_utf8_internal_setup(), 0);
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __DMFIX_WIN_UTF8_H_INCLUDE__