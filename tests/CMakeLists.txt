include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(ULF_DCC_EINTests ${SRC})

sanitize(address,undefined)

target_common_warnings(ULF_DCC_EINTests PRIVATE)
target_common_errors(ULF_DCC_EINTests PRIVATE -Werror)

cpmaddpackage(URI "gh:google/googletest#main" OPTIONS "INSTALL_GTEST OFF")

target_link_libraries(ULF_DCC_EINTests PRIVATE ULF::DCC_EIN GTest::gtest
                                               GTest::gmock)

gtest_discover_tests(ULF_DCC_EINTests)
