option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "-extra-arg=-Wno-unknown-warning-option")
    endif()
endif()

add_library(tictactoe_lib STATIC tictactoe.cpp)
target_include_directories(tictactoe_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tictactoe main.cpp)
target_link_libraries(tictactoe tictactoe_lib)