cmake_minimum_required(VERSION 3.3.1)

project(TestCV)

find_package(OpenCV	3.4.3	REQUIRED)

include_directories(
	${OpenCV_INCLUDE_DIRS}
)

add_executable(TestCV
	main.cpp
	cv.cpp
	cv.hpp
	question.cpp
	question.hpp
)

target_link_libraries(TestCV
	${OpenCV_LIBS}
)