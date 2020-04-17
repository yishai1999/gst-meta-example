cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x -g -fpermissive")

find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)

set(GSTREAMER_MINIMUM_VERSION 1.14.0)

pkg_check_modules(GST1_TEST gstreamer-1.0)
if ( GST1_TEST_FOUND AND NOT ${GST1_TEST_VERSION} VERSION_LESS ${GSTREAMER_MINIMUM_VERSION} )
	pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
	pkg_check_modules(GSTBASE REQUIRED gstreamer-base-1.0)
	add_definitions(-DGST_API_VERSION_1=1)
else()
	message(FATAL_ERROR "No correct gstreamer version was found")
endif()

file(GLOB PROJECT_SOURCES
	src/*.c
	src/*.cpp
)

project(examplemeta)
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
target_include_directories(
	${PROJECT_NAME}
	PUBLIC
	${GSTREAMER_INCLUDE_DIRS}
	${GSTBASE_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}
	)
target_link_libraries(
	${PROJECT_NAME}
	${GSTREAMER_LIBRARIES}
	${GSTBASE_LIBRARIES}
	pthread
	${GLIB_LIBRARIES}
	${GLIB_GIO_LIBRARIES}
	${GLIB_GOBJECT_LIBRARIES}
	)