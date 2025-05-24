
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

#ifdef _WIN32
#include <windows.h>
#endif

class WindowsVirtualTerminal {
public:
    WindowsVirtualTerminal() = delete;
    ~WindowsVirtualTerminal() = delete;
    WindowsVirtualTerminal(const WindowsVirtualTerminal&) = delete;
    WindowsVirtualTerminal& operator=(const WindowsVirtualTerminal&) = delete;

private:
    struct Initializer {
        Initializer() {
#ifdef _WIN32
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            if (hStdOut != INVALID_HANDLE_VALUE) {
                // 仅当句柄指向字符设备（如控制台）时才尝试设置模式
                if (GetFileType(hStdOut) == FILE_TYPE_CHAR) {
                    DWORD dwOriginalOutMode = 0;
                    if (GetConsoleMode(hStdOut, &dwOriginalOutMode)) {
                        if (!(dwOriginalOutMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
                            SetConsoleMode(hStdOut, dwOriginalOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
                        }
                    }
                }
            }

            HANDLE hStdErr = GetStdHandle(STD_ERROR_HANDLE);
            if (hStdErr != INVALID_HANDLE_VALUE) {
                // 仅当句柄指向字符设备（如控制台）时才尝试设置模式
                if (GetFileType(hStdErr) == FILE_TYPE_CHAR) {
                    DWORD dwOriginalErrMode = 0;
                    if (GetConsoleMode(hStdErr, &dwOriginalErrMode)) {
                        if (!(dwOriginalErrMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
                            SetConsoleMode(hStdErr, dwOriginalErrMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
                        }
                    }
                }
            }
#else
            // 在非 Windows 平台上 (如 Linux, macOS),
            // 现代终端通常默认支持 ANSI 转义序列，
            // 一般不需要程序进行额外的显式启用操作。
            // 因此此处为空或可用于其他特定于平台的终端初始化（如果需要）。
#endif
        }
    };

    static inline Initializer initializer;
};

#endif // __DMFIX_WIN_CONSOLE_H_INCLUDE__