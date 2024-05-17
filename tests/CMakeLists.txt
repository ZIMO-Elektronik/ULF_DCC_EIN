include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(ULF_DCC_EINTests ${SRC})

sanitize(address,undefined)

target_common_warnings(ULF_DCC_EINTests PRIVATE)

cpmaddpackage(
  NAME
  googletest
  GITHUB_REPOSITORY
  "google/googletest"
  GIT_TAG
  main
  SYSTEM
  YES
  OPTIONS
  "INSTALL_GTEST OFF")

target_link_libraries(ULF_DCC_EINTests PRIVATE ULF::DCC_EIN GTest::gtest
                                               GTest::gmock)

gtest_discover_tests(ULF_DCC_EINTests)
