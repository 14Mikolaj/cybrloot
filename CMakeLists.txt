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
    src/TerminalWrapper.cpp
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
    include/TerminalWrapper.hpp
)

target_compile_features(cybrloot 
    PRIVATE
    cxx_std_20
)

# Lightweight layout tests; no external test framework needed.
include(CTest)
if(BUILD_TESTING)
    add_executable(layout_tests
        tests/layout_tests.cpp
        src/Panel.cpp
        src/Scene.cpp
        src/Element.cpp
    )
    target_include_directories(layout_tests PRIVATE include)
    target_compile_features(layout_tests PRIVATE cxx_std_20)
    add_test(NAME panel_layout COMMAND layout_tests)
endif()
