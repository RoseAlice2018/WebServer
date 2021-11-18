cmake_minimum_required(VERSION 3.20)
project(WebServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(WebServer main.cpp log/log.h lock/locker.h log/block_queue.h log/log.cpp threadpool/threadpool.h CGImysql/sql_connection_pool.h)
