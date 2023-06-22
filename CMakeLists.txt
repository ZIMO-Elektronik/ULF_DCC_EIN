cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  CMakeModules
  GIT_REPOSITORY https://github.com/ZIMO-Elektronik/CMakeModules
  GIT_TAG v0.0.7
  SOURCE_DIR ${CMAKE_BINARY_DIR}/CMakeModules)
FetchContent_MakeAvailable(CMakeModules)

project(
  DCC_EIN
  VERSION ${VERSION_FROM_GIT}
  LANGUAGES CXX)

set(DCC_EIN_RX_MIN_STR_LEN
    17uz
    CACHE STRING "Minimum string length of 'senddcc' string")

add_library(DCC_EIN INTERFACE ${SRC})
add_library(DCC_EIN::DCC_EIN ALIAS DCC_EIN)

target_compile_features(DCC_EIN INTERFACE cxx_std_23)

target_compile_definitions(
  DCC_EIN INTERFACE DCC_EIN_RX_MIN_STR_LEN=${DCC_EIN_RX_MIN_STR_LEN})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  target_include_directories(DCC_EIN INTERFACE include)
else()
  target_include_directories(DCC_EIN SYSTEM INTERFACE include)
endif()

cpmaddpackage("gh:ZIMO-Elektronik/DCC@0.27.0")

target_link_libraries(DCC_EIN INTERFACE DCC::DCC)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

if(BUILD_TESTING
   AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME
   AND CMAKE_SYSTEM_NAME STREQUAL CMAKE_HOST_SYSTEM_NAME)
  add_subdirectory(examples)
  add_subdirectory(tests)
endif()
