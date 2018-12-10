cmake_minimum_required(VERSION 3.3.1)

project(HelloOpenCV)

find_package(OpenCV	3.2.0	REQUIRED)

include_directories(
	${OpenCV_INCLUDE_DIRS}
)

add_executable(HelloOpenCV
	main.cpp
	question.hpp
	question.cpp
)

target_link_libraries(HelloOpenCV
	${OpenCV_LIBS}
)