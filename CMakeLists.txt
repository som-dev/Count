cmake_minimum_required (VERSION 2.6)

project (Count)

set(CMAKE_CXX_STANDARD 11)

file(GLOB Count_HEADERS "*.hpp")
file(GLOB CountUnitTest_SOURCES "*_test.cpp")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

##############################
# Google Test
# Based on instructions in https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.gtest.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(
        ${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif ()

###########################
include(CTest)
enable_testing()

add_executable(Count_test ${CountUnitTest_SOURCES})

target_include_directories( Count_test PRIVATE
            ${CountUnitTest_HEADERS} )

target_link_libraries(Count_test gtest_main)

add_test(gtest ${PROJECT_BINARY_DIR}/Count_test)
