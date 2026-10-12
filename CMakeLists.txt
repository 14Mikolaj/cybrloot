cmake_minimum_required(VERSION 3.23)

project(cybrloot)

add_executable(cybrloot)

target_sources(cybrloot
    PRIVATE
    src/main.cpp
    src/Panel.cpp
    src/CybrUtil.cpp
    src/Element.cpp
    src/cybrloot.cpp
    src/UIManager.cpp
    src/Scene.cpp
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
    include
    FILES
    include/Panel.hpp
    include/BorderPalette.hpp
    include/CybrUtil.hpp
    include/Element.hpp
    include/cybrloot.hpp
    include/UIManager.hpp
    include/Scene.hpp
)

target_compile_features(cybrloot 
    PRIVATE
    cxx_std_20
)
