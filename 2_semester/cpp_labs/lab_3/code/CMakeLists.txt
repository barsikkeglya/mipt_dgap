project(mytest)

#if (WIN32)
if (MSVC)
    # https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
    list(APPEND compiler_flags
        "/WX" "/W4" "/permissive-" "/Za" "/fsanitize=address"

        # (not necessary) for runtime library static linkage
        "/MT"

        # (not necessary) use c++20
        "/std=c++2a"
    )
else()
    list(APPEND compiler_flags
        # It is impossible to include all GCC warnings
        # https://stackoverflow.com/a/11720263
        "-Werror" "-Wall" "-Wextra" "-pedantic" "-fsanitize=address"
        "-static-libasan"

        # (not necessary) use c++20
        "-std=c++2a"
    )
    list(APPEND linker_flags
        "-fsanitize=address"
        )
endif()

add_executable(t1 task1.cpp)
target_compile_options(t1 PRIVATE ${compiler_flags})
target_link_options(t1 PRIVATE ${linker_flags})
add_executable(t2 task2.cpp)
target_compile_options(t2 PRIVATE ${compiler_flags})
target_link_options(t2 PRIVATE ${linker_flags})
add_executable(t3 task3.cpp)
target_compile_options(t3 PRIVATE ${compiler_flags})
target_link_options(t3 PRIVATE ${linker_flags})
