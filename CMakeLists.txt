cmake_minimum_required(VERSION 3.14)
project(
  kero_variant_utils
  VERSION 0.1.0
  LANGUAGES CXX)

add_library(kero_variant_utils INTERFACE)
target_include_directories(
  kero_variant_utils
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<INSTALL_INTERFACE:include>)
target_compile_features(kero_variant_utils INTERFACE cxx_std_17)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
  kero_variant_utils_test
  ${CMAKE_CURRENT_SOURCE_DIR}/src/kero_variant_utils/kero_variant_utils_test.cc)
target_link_libraries(kero_variant_utils_test kero_variant_utils
                      GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(kero_variant_utils_test)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/kero_variant_utilsConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/kero_variant_utilsConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/kero_variant_utilsConfig.cmake @ONLY)

install(TARGETS kero_variant_utils EXPORT kero_variant_utilsTargets)
install(
  EXPORT kero_variant_utilsTargets
  FILE kero_variant_utilsTargets.cmake
  NAMESPACE kero::
  DESTINATION lib/cmake/kero_variant_utils)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kero_variant_utilsConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/kero_variant_utilsConfigVersion.cmake
        DESTINATION lib/cmake/kero_variant_utils)
install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/kero_variant_utils/kero_variant_utils.h
  DESTINATION include/kero_variant_utils)

add_subdirectory(examples)
