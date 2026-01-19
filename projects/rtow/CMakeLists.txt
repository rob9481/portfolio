cmake_minimum_required(VERSION 3.10)
project(rtow)

set(CMAKE_CXX_STANDARD 20)

add_executable(rtow
  Camera.h
  Camera.cpp
  Color.h
  Common.h
  Hittable.h
  HittableList.cpp
  HittableList.h
  Material.cpp
  Material.h
  Ray.h
  Sphere.cpp
  Sphere.h
  Vec3.h
  main.cpp)
