cmake_minimum_required(VERSION 3.8)

PROJECT(chsrc C CXX)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

set(CMAKE_C_STANDARD 99)

if (WIN32)
    add_definitions(/utf-8)
endif()

if (UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
endif()

include_directories(include)
add_executable(chsrc src/chsrc.c)

IF(WIN32)
ADD_CUSTOM_COMMAND(
TARGET chsrc
PRE_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/task/dmbeyondcompare.exe $<TARGET_FILE_DIR:chsrc>
COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/task/nssm.exe $<TARGET_FILE_DIR:chsrc>
COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/task/install.bat $<TARGET_FILE_DIR:chsrc>
COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/task/uninstall.bat $<TARGET_FILE_DIR:chsrc>
COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE $<TARGET_FILE_DIR:chsrc>
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
set(CPACK_PACKAGE_NAME "chsrc") # 设置包的名字
set(CPACK_PACKAGE_VENDOR "RubyMetric") # 设置包的作者
set(CPACK_PACKAGE_DESCRIPTION "RubyMetric chsrc") # 设置包的描述
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "RubyMetric chsrc summary")
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\icon\\\\chsrc.png") # 设置包的图标
set(CPACK_PACKAGE_CONTACT "https://github.com/RubyMetric/chsrc")
set(CPACK_PACKAGE_VERSION "1.0.1")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")

set(CPACK_CMD "cpack -V -G NSIS64")

include(CPack)
