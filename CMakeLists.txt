cmake_minimum_required(VERSION 3.10)
project(mongodb_crud_c VERSION 1.0)

set(SOURCE_FILES server_ping.c test1_bson.c json2bson.c)

foreach(SOURCE_PATH ${SOURCE_FILES})
        get_filename_component(EXECUTABLE_NAME ${SOURCE_PATH} NAME_WE)
        add_executable(${EXECUTABLE_NAME} ${SOURCE_PATH})

        target_link_libraries(${EXECUTABLE_NAME} -lmongoc-1.0)
        target_link_libraries(${EXECUTABLE_NAME} -lbson-1.0)
        # target_link_libraries(${EXECUTABLE_NAME} -L/usr/include/libmongoc-1.0/)
        target_include_directories(${EXECUTABLE_NAME} PRIVATE /usr/include/libmongoc-1.0/)
        target_include_directories(${EXECUTABLE_NAME} PRIVATE /usr/include/libbson-1.0/)
endforeach(SOURCE_PATH ${SOURCE_FILES})

add_executable(test_query conn.c test_query.c)
target_link_libraries(test_query -lmongoc-1.0)
target_link_libraries(test_query -lbson-1.0)
target_include_directories(test_query PRIVATE /usr/include/libmongoc-1.0/)
target_include_directories(test_query PRIVATE /usr/include/libbson-1.0/)

add_executable(test_bson bson/test_01.c)
target_link_libraries(test_bson -lbson-1.0)
target_include_directories(test_bson PRIVATE /usr/include/libbson-1.0/)