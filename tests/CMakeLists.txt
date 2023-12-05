
include(FetchContent)
FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    include(GoogleTest)


add_executable( test_vector math_vector.cc math_vector_test.cpp )
target_compile_options( test_vector PUBLIC -O -Wall -Wextra -Wpedantic)
target_link_libraries( test_vector PUBLIC gmock)
# gtest_add_tests(TARGET QnToolsCorrectionTests  )
