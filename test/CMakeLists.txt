include(FetchContent)

FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2
)

FetchContent_MakeAvailable(Catch2)


add_executable(libendian_tests endian_test.cpp)
target_link_libraries(libendian_tests PRIVATE libendian::libendian Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(libendian_tests)