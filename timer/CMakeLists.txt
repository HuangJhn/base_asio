

cmake_minimum_required(VERSION 3.10)

project(timer)

file(GLOB_RECURSE source_cpp  ./*.cpp)

add_executable(${PROJECT_NAME} ${source_cpp})

# target_link_libraries(${timer_class} )
target_link_libraries(${PROJECT_NAME} libboost_thread.so)
target_link_libraries(${PROJECT_NAME} libboost_system.so)
target_link_libraries(${PROJECT_NAME} libboost_timer.so)
target_link_libraries(${PROJECT_NAME} libboost_system.so)
target_link_libraries(${PROJECT_NAME} libboost_context.so)
target_link_libraries(${PROJECT_NAME} libpthread.so)
