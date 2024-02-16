cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED PROJECT_NAME)
    set(NOT_SUBPROJECT ON)
else()
    set(NOT_SUBPROJECT OFF)
endif()

project(libendian
        LANGUAGES CXX
        DESCRIPTION "Integral types with known byte order"
)

include(CMakeDependentOption)
cmake_dependent_option(LIBENDIAN_TEST "Build libendian tests tests" ON "NOT_SUBPROJECT" OFF)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE  include)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

if (${LIBENDIAN_TEST})
    enable_testing()
    add_subdirectory(test)
endif()
