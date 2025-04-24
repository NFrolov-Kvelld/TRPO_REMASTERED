add_library(tictactoe_lib STATIC tictactoe.cpp)
target_include_directories(tictactoe_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tictactoe main.cpp)
target_link_libraries(tictactoe tictactoe_lib)