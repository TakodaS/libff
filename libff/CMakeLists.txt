set(FF_EXTRASRCS)
set(FF_EXTRALIBS)
add_library(
  ff
  STATIC

  algebra/fields/binary/gf32.cpp
  algebra/fields/binary/gf64.cpp
  algebra/fields/binary/gf128.cpp
  algebra/fields/binary/gf192.cpp
  algebra/fields/binary/gf256.cpp
  common/double.cpp
  common/profiling.cpp
  common/utils.cpp

  ${FF_EXTRASRCS}
)
target_link_libraries(
  ff

  GMP::gmp
  ${PROCPS_LIBRARIES}
  ${FF_EXTRALIBS}
)
target_include_directories(
  ff
  PUBLIC ..
)

# Sodium for binary fields.
 find_path(
   SODIUM_INCLUDE_DIR
   sodium.h
   HINTS ${LIBSODIUM_INCLUDE_DIRS}
   /usr/local/include /opt/local/include /opt/include
 )
 find_library(
   SODIUM_LIBRARY
   NAMES sodium
   HINTS ${LIBSODIUM_LIBRARY_DIRS}
   /usr/local/lib /opt/local/lib /opt/lib
 )

 target_include_directories(
   ff
   PUBLIC
   ${SODIUM_INCLUDE_DIR}
 )
 target_compile_options(
   ff
   PUBLIC
   ${LIBSODIUM_CFLAGS} ${LIBSODIUM_CFLAGS_OTHER}
 )
 target_link_libraries(
   ff
   ${SODIUM_LIBRARY} ${LIBSODIUM_LDFLAGS_OTHER}
 )

install(
  DIRECTORY "" DESTINATION "include/libff"
  FILES_MATCHING
  PATTERN "*.hpp"
  PATTERN "*.tcc"
  PATTERN "tests" EXCLUDE
  PATTERN "examples" EXCLUDE
)

install(
  TARGETS ff DESTINATION lib
)
# Tests
if ("${IS_LIBFF_PARENT}")

  add_executable(
    algebra_binary_fields_test
    EXCLUDE_FROM_ALL

    algebra/fields/tests/test_binary_fields.cpp
  )
  target_link_libraries(
    algebra_binary_fields_test

    ff
    gtest_main
  )

  add_executable(
    common_test
    EXCLUDE_FROM_ALL

    common/tests/test_common.cpp
  )
  target_link_libraries(
    common_test

    ff
    gtest_main
  )

  include(CTest)
  add_test(
    NAME algebra_binary_fields_test
    COMMAND algebra_binary_fields_test
  )
  add_test(
    NAME common_test
    COMMAND common_test
  )

  add_dependencies(check algebra_binary_fields_test)
  add_dependencies(check common_test)

  find_package(OpenSSL REQUIRED)
  INCLUDE_DIRECTORIES(${OPENSSL_INCLUDE_DIR})

  add_dependencies(profile multiexp_profile)
endif()
