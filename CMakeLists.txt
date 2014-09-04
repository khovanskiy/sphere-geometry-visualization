# Set minimum CMake version (Qt 5 requires at least CMake version 2.8.3)
cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

# Set project name
set(PROJECT Geometry2)
project(${PROJECT})

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#add_definitions(-O2 -D_FILE_OFFSET_BITS=64 -fPIC)

# Set compiler
set(CMAKE_PREFIX_PATH $ENV{QTDIR})

# Add Qt packages
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# Add headers to compile
set(HEADERS
headers/visualization.h
headers/exampleclass.h
headers/vector2d.h
headers/vector3d.h
headers/console.h
headers/axisview.h
headers/view.h
headers/random.h
)

# Add sources to compile
set(
SOURCES sources/main.cpp
sources/visualization.cpp
sources/exampleclass.cpp
sources/vector2d.cpp
sources/vector3d.cpp
sources/axisview.cpp
sources/view.cpp
sources/random.cpp
)

#INCLUDE_DIRECTORIES(${QT_QTOPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} )

# Activate C++11 features
SET(CMAKE_CXX_FLAGS "-std=c++11")

# Build & Compile
add_executable(${PROJECT} ${HEADERS} ${SOURCES})

#target_link_libraries(${PROJECT} ${OPENGL_LIBRARIES} ${QT_LIBRARIES})

# Add qt modules (IMPORTTANT! this must be after add_executable)
qt5_use_modules(${PROJECT} Core Gui Widgets OpenGL)

# Fix OpenGL "undefined reference" problem
target_link_libraries(${PROJECT} OpenGL32)
