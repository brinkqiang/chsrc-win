cmake_minimum_required(VERSION 3.8)

PROJECT(chsrc-win C CXX)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

set(CMAKE_C_STANDARD 99)

if (WIN32)
    add_definitions(/utf-8)
    enable_language(RC)
endif()

if (UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
endif()

add_executable(chsrc-win src/chsrc.c src/chsrc.rc)

IF(WIN32)
ADD_CUSTOM_COMMAND(
TARGET chsrc-win
PRE_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/env/install.bat $<TARGET_FILE_DIR:chsrc-win>
COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/env/uninstall.bat $<TARGET_FILE_DIR:chsrc-win>
COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/env/dmpath.exe $<TARGET_FILE_DIR:chsrc-win>
)
ENDIF(WIN32)


install(DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/
        DESTINATION bin
        FILES_MATCHING PATTERN "*"
        PATTERN "debug" EXCLUDE
        PATTERN "*.pdb" EXCLUDE
        PATTERN "*.lib" EXCLUDE
        PATTERN "*.zip" EXCLUDE
        )

# 配置 CPack 打包选项
set(CPACK_GENERATOR "ZIP;NSIS64") # 选择打包格式，这里以 ZIP 为例
set(CPACK_PACKAGE_NAME "chsrc-win") # 设置包的名字
set(CPACK_PACKAGE_VENDOR "RubyMetric") # 设置包的作者
set(CPACK_PACKAGE_DESCRIPTION "RubyMetric chsrc-win") # 设置包的描述
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "RubyMetric chsrc-win summary")
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\icon\\\\chsrc-win.png") # 设置包的图标
set(CPACK_PACKAGE_CONTACT "https://github.com/RubyMetric/chsrc | https://github.com/brinkqiang/chsrc-win")
set(CPACK_PACKAGE_VERSION "1.0.1")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")

set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\icon\\\\chsrc-win.ico") # 设置安装界面的图标
set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\icon\\\\chsrc-win.ico") # 设置安装程序的图标
set(CPACK_NSIS_MUI_UNICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\icon\\\\chsrc-win.ico") # 设置卸载程序的图标
set(CPACK_NSIS_INSTALLED_ICON_NAME "${CMAKE_CURRENT_SOURCE_DIR}\\\\icon\\\\chsrc-win.ico") # 设置可执行程序的图标

# NSIS 特定配置
set(CPACK_NSIS_DISPLAY_NAME "chsrc-win") # 设置在“添加/删除程序”中显示的名称
# set(CPACK_NSIS_MODIFY_PATH ON) # 允许用户将程序目录添加到 PATH # 这个功能 收到 path 环境变量长度限制，不建议开启, 这里用自定义程序dmpath处理

set(CPACK_CMD "cpack -V -G NSIS64")
# Windows 特定配置
IF(WIN32)
    # 指定生成桌面快捷方式
    set(CPACK_NSIS_CREATE_ICONS_EXTRA
        "CreateShortCut \\\"$DESKTOP\\\\chsrc-win.lnk\\\" \\\"$INSTDIR\\\\bin\\\\RelWithDebInfo\\\\chsrc-win.exe\\\"")
        
    set(CPACK_NSIS_DELETE_ICONS_EXTRA
        "Delete \\\"$DESKTOP\\\\chsrc-win.lnk\\\"")
    # 安装时执行的额外命令
    SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
    ExecWait '\\\"$INSTDIR\\\\bin\\\\RelWithDebInfo\\\\install.bat\\\"'
    ")

    # 卸载时执行的额外命令
    SET(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
    ExecWait '\\\"$INSTDIR\\\\bin\\\\RelWithDebInfo\\\\uninstall.bat\\\"'
    ")
ENDIF(WIN32)

include(CPack)
