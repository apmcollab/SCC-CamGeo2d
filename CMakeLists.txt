cmake_minimum_required (VERSION 3.15)
project (CamGeo2d)

file(GLOB Library_Sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" ) 

add_library (CamGeo2d STATIC ${Library_Sources})

target_compile_features    (CamGeo2d PUBLIC cxx_std_11)
target_include_directories (CamGeo2d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (CamGeo2d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)


