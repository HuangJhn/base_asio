

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -O2")

# include_directories(/usr/local/include/)
# include_directories(/usr/include/)
# must
link_directories(/usr/local/lib/boost/)
link_directories(/usr/lib/)

# file(GLOB_RECURSE timer_practice "timer/*.cpp")
# file(GLOB_RECURSE timer_class_practice "timer_class/*.cpp")

# file(GLOB_RECURSE thread_timer "thread_timer/*.cpp")

# add_executable(timer_practice ${timer_practice})
# add_executable(timer_class_practice ${timer_class_practice})
# add_executable(thread_timer ${thread_timer})

# target_link_libraries(thread_timer libboost_thread.so)
# target_link_libraries(thread_timer libboost_system.so)
# target_link_libraries(thread_timer libboost_timer.so)
# target_link_libraries(thread_timer libboost_system.so)
# target_link_libraries(thread_timer libboost_context.so)
# target_link_libraries(thread_timer libpthread.so)

add_subdirectory(./timer_class/)
add_subdirectory(./thread_timer/)
add_subdirectory(./timer/)
add_subdirectory(./daytime_client/)
add_subdirectory(./daytime_server/)
add_subdirectory(./echo_server/)
add_subdirectory(./echo_client/)
add_subdirectory(./timer_clock/)
add_subdirectory(./daytime_server_class/)

# target_link_libraries()

