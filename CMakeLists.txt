cmake_minimum_required(VERSION 3.16)
project(SudokuGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

if (WIN32)
    add_executable(SudokuGame WIN32)
else()
    add_executable(SudokuGame)
endif()

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.h)

target_sources(SudokuGame PRIVATE
    ${SRC_FILES}
    ${HEADER_FILES}
)

target_include_directories(SudokuGame PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(SudokuGame PRIVATE Qt6::Widgets)

# Add icon to Windows
if (WIN32)
    set(RESOURCE_FILES ${PROJECT_SOURCE_DIR}/assets/logo/icon.rc)
    target_sources(SudokuGame PRIVATE ${RESOURCE_FILES})
endif()

# Add icon for Linux (for future)
if (UNIX)
    install(FILES ${PROJECT_SOURCE_DIR}/assets/logo/icon.png DESTINATION share/icons/hicolor/256x256/apps RENAME SudokuGame.png)
endif()

# Install rules (final build)
install(TARGETS SudokuGame
    RUNTIME DESTINATION .
)