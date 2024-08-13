cmake_minimum_required(VERSION 3.10)
project(mongodb_crud_c VERSION 1.0)

# set(SOURCE server_ping.c)
add_executable(mongodb_crud server_ping.c)

target_link_libraries(mongodb_crud -lmongoc-1.0)
target_link_libraries(mongodb_crud -lbson-1.0)
# target_link_libraries(mongodb_crud -L/usr/include/libmongoc-1.0/)
target_include_directories(mongodb_crud PRIVATE /usr/include/libmongoc-1.0/)
target_include_directories(mongodb_crud PRIVATE /usr/include/libbson-1.0/)