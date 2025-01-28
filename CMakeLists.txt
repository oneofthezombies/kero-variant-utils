cmake_minimum_required(VERSION 3.14)
project(
  KeroVariantUtils
  VERSION 0.1.0
  LANGUAGES CXX)

add_library(KeroVariantUtils INTERFACE)
target_include_directories(
  KeroVariantUtils INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                             $<INSTALL_INTERFACE:include>)

target_compile_features(KeroVariantUtils INTERFACE cxx_std_17)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/KeroVariantUtilsConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/KeroVariantUtilsConfig.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/KeroVariantUtilsConfig.cmake @ONLY)

install(TARGETS KeroVariantUtils EXPORT KeroVariantUtilsTargets)
install(
  EXPORT KeroVariantUtilsTargets
  FILE KeroVariantUtilsTargets.cmake
  NAMESPACE kero::
  DESTINATION lib/cmake/KeroVariantUtils)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/KeroVariantUtilsConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/KeroVariantUtilsConfigVersion.cmake
        DESTINATION lib/cmake/KeroVariantUtils)
install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/kero_variant_utils/kero_variant_utils.h
  DESTINATION include/kero_variant_utils)

add_subdirectory(examples)
