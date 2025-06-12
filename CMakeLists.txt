cmake_minimum_required(VERSION 3.11)
project(c-quickstart LANGUAGES C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MONGOC REQUIRED libmongoc-1.0)

add_executable(quickstart.out quickstart.c)

target_include_directories(quickstart.out PRIVATE ${MONGOC_INCLUDE_DIRS})
target_link_libraries(quickstart.out PRIVATE ${MONGOC_LIBRARIES})

target_compile_options(quickstart.out PRIVATE ${MONGOC_CFLAGS_OTHER})

