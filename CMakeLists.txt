cmake_minimum_required(VERSION 3.8)

PROJECT(chsrc)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
#ModuleSetWinCompilerFlags()

#set(CMAKE_C_STANDARD 99)

if (WIN32)
    add_definitions(/utf-8)
    enable_language(RC)
endif()

if (UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
endif()


if (WIN32)
    add_executable(chsrc src/chsrc.c icon/chsrc.ico)

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
    set(CPACK_PACKAGE_NAME "chsrc") # 设置包的名字
    set(CPACK_PACKAGE_VENDOR "RubyMetric") # 设置包的作者
    set(CPACK_PACKAGE_DESCRIPTION "RubyMetric chsrc") # 设置包的描述
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "RubyMetric chsrc summary")
    set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\icon\\\\chsrc.png") # 设置包的图标
    set(CPACK_PACKAGE_CONTACT "https://github.com/RubyMetric/chsrc")
    set(CPACK_PACKAGE_VERSION "1.0.1")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")

    set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\icon\\\\chsrc.ico") # 设置安装界面的图标
    set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\icon\\\\chsrc.ico") # 设置安装程序的图标
    set(CPACK_NSIS_MUI_UNICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\icon\\\\chsrc.ico") # 设置卸载程序的图标
    set(CPACK_NSIS_INSTALLED_ICON_NAME "${CMAKE_CURRENT_SOURCE_DIR}\\\\icon\\\\chsrc.ico") # 设置可执行程序的图标

    # NSIS 特定配置
    set(CPACK_NSIS_DISPLAY_NAME "chsrc") # 设置在“添加/删除程序”中显示的名称
    set(CPACK_NSIS_MODIFY_PATH ON) # 允许用户将程序目录添加到 PATH

    set(CPACK_CMD "cpack -V -G NSIS64")

    include(CPack)
else()
    add_executable(chsrc src/chsrc.c)

    AddInstall(chsrc)
    #get_target_property(LINK_FLAGS chsrc LINK_FLAGS)
    #message(STATUS "Linker Flags for chsrc: ${LINK_FLAGS}")

    # 打印全局链接器参数
    #message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
endif()