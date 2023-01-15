cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(PreTrainedApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_APPLE_SILICON_PROCESSOR arm64)

include(dependency.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
set(TS_FILES PreTrainedApp_ko_KR.ts)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(OUTPUT_ELF ${CMAKE_PROJECT_NAME}_v${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

set(PROJECT_SOURCES
        mainwindow.ui
        ${TS_FILES}
        MainWindow.cpp
        main.cpp
        )

qt_add_executable(${OUTPUT_ELF}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        )

target_include_directories(${OUTPUT_ELF} PRIVATE
        ./inc
        ${DEP_INCLUDE_DIRS}
        )

target_link_directories(${OUTPUT_ELF} PRIVATE
        ${DEP_LIBRARY_DIRS}
        )

target_link_libraries(${OUTPUT_ELF} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        ${DEP_LIBRARIES}
        )

set_target_properties(${OUTPUT_ELF} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${OUTPUT_ELF}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${OUTPUT_ELF})
endif()

target_compile_definitions( ${OUTPUT_ELF} PUBLIC
        EXCUTABLE_OUTPUT_PATH="${EXECUTABLE_OUTPUT_PATH}/.."
        )

target_compile_options(${OUTPUT_ELF} PUBLIC -Wall -Wextra -pedantic)