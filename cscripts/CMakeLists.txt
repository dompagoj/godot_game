cmake_minimum_required(VERSION 3.17)
project(MyLibrary)

#option(ARCHITECTURE "x64 or x86 CPU Architecture" "x64")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/${ARCHITECTURE}")
#set(CXX=/usb/bin/clang++)
set(CMAKE_CXX_STANDARD 20)
include(project_settings.cmake)

add_subdirectory(godot-cpp)
add_subdirectory(epic-online-services)


include_directories(include)
include_directories(src)
include_directories(epic-online-services/SDK/Include)

add_library(MyLibrary SHARED
        src/Macros.hpp
        src/MyLibrary.cpp
        src/Units/BaseUnit.cpp
        src/Units/Marine.cpp
        src/Game.cpp
        src/SceneLoader.cpp
        src/UnitManager.cpp
        src/Utils.hpp
        src/MyCamera.cpp
    )

if (NOT MSVC)
  target_compile_options(MyLibrary PRIVATE -Werror -fno-exceptions)
endif()

target_link_libraries(MyLibrary PUBLIC godot-cpp)
target_link_libraries(MyLibrary PUBLIC ${EOS_SDK_LIBRARIES})
