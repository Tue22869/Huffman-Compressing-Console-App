add_subdirectory(library)
add_subdirectory(tests)

add_executable(archiver
        main.cpp
        )

target_link_libraries(archiver archiver_library)