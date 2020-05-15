# CMakeList.txt : CMake project for test_NDI, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("test_NDI")
add_definitions(-std=c++17)

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

option (_MSC_VER
       "Windows" ON)
# 
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
# 


INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/inc/ffmpeg ${PROJECT_SOURCE_DIR}/inc/NDI)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

aux_source_directory(. DIR_SRCS)


add_subdirectory(Lib.Base)
add_subdirectory(Lib.Config)
add_subdirectory(Lib.FrameConsumerNDI)
add_subdirectory(Lib.FrameProviderYuvFile)

# Add source to this project's executable.
add_executable (test_NDI ${DIR_SRCS})

# WINDOWS
if (_MSC_VER)
    target_link_libraries(test_NDI Shlwapi.lib)
    target_link_libraries(test_NDI ${PROJECT_SOURCE_DIR}/lib/Processing.NDI.Lib.x64.lib)
    target_link_libraries(test_NDI ${PROJECT_SOURCE_DIR}/lib/avutil.lib)
    target_link_libraries(test_NDI ${PROJECT_SOURCE_DIR}/lib/swresample.lib)
elseif(!_MSC_VER)
    target_link_libraries(test_NDI test.lib)
    target_link_libraries(test_NDI ${PROJECT_SOURCE_DIR}/lib/Processing.NDI.Lib.x64.lib)
    target_link_libraries(test_NDI ${PROJECT_SOURCE_DIR}/lib/avutil.lib)
    target_link_libraries(test_NDI ${PROJECT_SOURCE_DIR}/lib/swresample.lib)
endif (_MSC_VER)

# TODO: Add tests and install targets if needed.


target_link_libraries(test_NDI Lib.Base Lib.Config Lib.FrameConsumerNDI Lib.FrameProviderYuvFile)
