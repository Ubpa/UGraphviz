cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(UGraphviz VERSION 0.1.3)
message(STATUS "[Project] ${PROJECT_NAME}")

include(cmake/InitUCMake.cmake)
Ubpa_InitUCMake()

Ubpa_InitProject()

Ubpa_AddSubDirsRec(src)

Ubpa_Export(DIRECTORIES "include")
