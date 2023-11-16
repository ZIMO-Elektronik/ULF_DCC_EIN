include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(ULF_DCC_EINTests ${SRC})

sanitize("address,undefined")

target_common_warnings(ULF_DCC_EINTests PRIVATE)

cpmaddpackage("gh:google/googletest#main")

target_link_libraries(ULF_DCC_EINTests PRIVATE ULF::DCC_EIN GTest::gtest
                                               GTest::gmock)

gtest_discover_tests(ULF_DCC_EINTests)
