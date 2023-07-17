file(GLOB_RECURSE SRC *.cpp)
add_executable(DCC_EINExamples ${SRC})

target_common_warnings(DCC_EINExamples PRIVATE)

target_link_libraries(DCC_EINExamples PRIVATE DCC_EIN::DCC_EIN)
