cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  CMakeModules
  GIT_REPOSITORY https://github.com/ZIMO-Elektronik/CMakeModules
  GIT_TAG v0.3.0
  SOURCE_DIR ${CMAKE_BINARY_DIR}/CMakeModules)
FetchContent_MakeAvailable(CMakeModules)

version_from_git()
project(
  ULF_DCC_EIN
  VERSION ${VERSION_FROM_GIT}
  LANGUAGES CXX)

add_library(ULF_DCC_EIN INTERFACE ${SRC})
add_library(ULF::DCC_EIN ALIAS ULF_DCC_EIN)

target_compile_features(ULF_DCC_EIN INTERFACE cxx_std_23)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  target_include_directories(ULF_DCC_EIN INTERFACE include)
else()
  target_include_directories(ULF_DCC_EIN SYSTEM INTERFACE include)
endif()

target_common_warnings(ULF_DCC_EIN INTERFACE)

if(NOT TARGET DCC::DCC)
  cpmaddpackage("gh:ZIMO-Elektronik/DCC@0.30.0")
endif()

target_link_libraries(ULF_DCC_EIN INTERFACE DCC::DCC)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
  file(
    DOWNLOAD
    https://raw.githubusercontent.com/ZIMO-Elektronik/.clang-format/master/.clang-format
    ${CMAKE_CURRENT_LIST_DIR}/.clang-format)
  file(GLOB_RECURSE SRC include/*.*pp tests/*.*pp)
  add_clang_format_target(ULF_DCC_EINFormat OPTIONS -i FILES ${SRC})
endif()

if(BUILD_TESTING
   AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME
   AND CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME)
  add_subdirectory(examples)
  add_subdirectory(tests)
endif()
