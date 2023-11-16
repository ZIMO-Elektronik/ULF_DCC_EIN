file(GLOB_RECURSE SRC *.cpp)
add_executable(ULF_DCC_EINExamples ${SRC})

target_common_warnings(ULF_DCC_EINExamples PRIVATE)

target_link_libraries(ULF_DCC_EINExamples PRIVATE ULF::DCC_EIN)
