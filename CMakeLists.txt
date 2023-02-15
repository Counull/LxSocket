cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_EXPORT_COMPILECOMMANDS ON)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
set(CMAKE_TOOLCHAIN_FILE "/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")
message(${CMAKE_TOOLCHAIN_FILE})
  set(VCPKG_TARGET_TRIPLET x64-linux)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
set(CMAKE_TOOLCHAIN_FILE "E:\\programTools\\tool\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
  set(VCPKG_TARGET_TRIPLET x64-windows)
endif()

project(LxSocket)



include(CheckCXXCompilerFlag)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -ast-print -fsyntax-only")
if(NOT CMAKE_BUILD_TYPE)
  message("Build Type not set, defaulting to Debug...")
  set(CMAKE_BUILD_TYPE Debug)
endif()

message("Build type:" ${CMAKE_BUILD_TYPE})

if(CMAKE_BUILD_TYPE STREQUAL Debug)

  # check_cxx_compiler_flag("-fstandalone-debug" COMPILER_SUPPORTS_DEBUG)
  # if(COMPILER_SUPPORTS_DEBUG)
  #   set(CMAKE_CXX_FLAGS
  #       "${CMAKE_CXX_FLAGS} -fstandalone-debug -D_GLIBCXX_DEBUG ")
  #   message("Set debug flags " ${COMPILER_SUPPORTS_DEBUG})
  # endif()

endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")
# check_cxx_compiler_flag("-std=c++23" COMPILER_SUPPORTS_CXX23)
# check_cxx_compiler_flag("-std=c++2b" COMPILER_SUPPORTS_CXX20)

# if(COMPILER_SUPPORTS_CXX23)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++23")
# elseif(COMPILER_SUPPORTS_CXX20) #
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")

# else()
#   message(
#     STATUS
#       "The compiler ${CMAKE_CXX_COMPILER} has no C++20 support. Please use a different C++ compiler."
#   )
# endif()

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -ast-print -fsyntax-only")
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
