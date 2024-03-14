project(mytest)

#if (WIN32)
if (MSVC)
    # https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
    list(APPEND compiler_flags
        "/WX" "/W4" "/permissive-" "/Za"
		
		# suddenly:
		# 1) does not detect memory leaks (linux, here we go again)
		# 2) breaks running from terminal
		#    (cannot find clang_rt.asan_dynamic-x86_64.dll while VS can)
		#"/fsanitize=address"
		# MS fuckup https://learn.microsoft.com/en-us/cpp/build/reference/d-preprocessor-definitions?view=msvc-170
		"/D __STDC_WANT_SECURE_LIB__"

        # (not necessary) for runtime library static linkage
        "/MT"

        # (not necessary) use c++20
        "/std:c++20"
    )
else()
    list(APPEND compiler_flags
        # It is impossible to include all GCC warnings
        # https://stackoverflow.com/a/11720263
        "-Werror" "-Wall" "-Wextra" "-pedantic" "-fsanitize=address"
        "-static-libasan"

        # (not necessary) use c++20
        "-std=c++20"
    )
    list(APPEND linker_flags
        "-fsanitize=address"
        )
endif()

add_executable(main sorts.cpp)
target_compile_options(main PRIVATE ${compiler_flags})
target_link_options(main PRIVATE ${linker_flags})
