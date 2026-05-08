cmake_minimum_required(VERSION 3.31)
project(starter
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# https://cmake.org/cmake/help/latest/module/FindPkgConfig.html
find_package(PkgConfig)
if(PkgConfig_FOUND)
  pkg_check_modules(GTK4 gtk4)
  if(GTK4_FOUND)
    add_executable(${PROJECT_NAME}_gtk main_gtk.cpp)
    target_include_directories(${PROJECT_NAME}_gtk PRIVATE ${GTK4_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME}_gtk ${GTK4_LIBRARIES})
    target_compile_options(${PROJECT_NAME}_gtk PRIVATE -Wall -Wextra -Wpedantic)
  endif()
endif()

# https://cmake.org/cmake/help/v3.31/manual/cmake-qt.7.html
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 COMPONENTS Core Gui Widgets)
if(Qt6_FOUND)
  add_executable(${PROJECT_NAME}_qt main_qt.cpp main_qt.h)
  target_link_libraries(${PROJECT_NAME}_qt Qt::Widgets)
  target_compile_options(${PROJECT_NAME}_qt PRIVATE -Wall -Wextra -Wpedantic)
endif()
