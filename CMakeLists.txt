cmake_minimum_required(VERSION 3.14)

set(namespace kero)

set(library_name variant_utils)
set(library_test_name ${library_name}_test)

set(package_name ${namespace}_${library_name})
set(package_config_version_path
    ${CMAKE_CURRENT_BINARY_DIR}/${package_name}ConfigVersion.cmake)
set(package_config_path ${CMAKE_CURRENT_BINARY_DIR}/${package_name}Config.cmake)
set(package_config_install_dir lib/cmake/${package_name})
set(package_targets_name ${package_name}Targets)

project(
  ${package_name}
  VERSION 0.4.1
  LANGUAGES CXX)

add_library(${library_name} INTERFACE)
add_library(${namespace}::${library_name} ALIAS ${library_name})
target_include_directories(
  ${library_name} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                            $<INSTALL_INTERFACE:include>)
target_compile_features(${library_name} INTERFACE cxx_std_17)

if(BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2)
  FetchContent_MakeAvailable(googletest)
  enable_testing()

  add_executable(${library_test_name}
                 ${CMAKE_CURRENT_SOURCE_DIR}/tests/${library_test_name}.cc)
  target_link_libraries(${library_test_name} ${library_name} GTest::gtest_main
                        GTest::gmock_main)

  include(GoogleTest)
  gtest_discover_tests(${library_test_name})

  add_subdirectory(examples)
endif()

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  ${package_config_version_path}
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in ${package_config_path}
  INSTALL_DESTINATION ${package_config_install_dir})

install(TARGETS ${library_name} EXPORT ${package_targets_name})
install(
  EXPORT ${package_targets_name}
  FILE ${package_targets_name}.cmake
  NAMESPACE ${namespace}::
  DESTINATION ${package_config_install_dir})
install(FILES ${package_config_path} ${package_config_version_path}
        DESTINATION ${package_config_install_dir})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${namespace}/${library_name}.h
        DESTINATION include/${namespace})
