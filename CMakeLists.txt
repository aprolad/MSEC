
project(MSEC)

cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
#pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
add_compile_options(-Wl,-export-dynamic)



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

file(GLOB SOURCES "src/*.cpp")
add_executable(MSEC ${SOURCES})

set_property(TARGET MSEC PROPERTY CXX_STANDARD 20)


target_include_directories (MSEC PRIVATE src)

target_link_libraries(MSEC PRIVATE ${GTKMM_LIBRARIES})
target_compile_definitions(MSEC PRIVATE ${GTKMM_CFLAGS_OTHER})
target_include_directories(MSEC PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(MSEC PRIVATE ${GTKMM_LIBRARY_DIRS})

