include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(DCC_EINTests ${SRC})

sanitize("address,undefined")

target_common_warnings(DCC_EINTests PRIVATE)

cpmaddpackage("gh:google/googletest#main")

target_link_libraries(DCC_EINTests PRIVATE DCC_EIN::DCC_EIN GTest::gtest
                                           GTest::gmock)

gtest_discover_tests(DCC_EINTests)
