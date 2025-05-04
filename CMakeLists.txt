cmake_minimum_required(VERSION 3.19)
project(ServerManager LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui Network Designer)

qt_standard_project_setup()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h)

file(GLOB_RECURSE UIS CONFIGURE_DEPENDS src/*.ui)

qt_add_executable(ServerManager
    WIN32 MACOSX_BUNDLE
    ${SOURCES}
    ${HEADERS}
    ${UIS}
)

target_include_directories(ServerManager
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/widget/dial ### For whatever reason it can't finds the dial (it do finds the spinbox tho...)
)

target_link_libraries(ServerManager
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Gui
        Qt::Network
        Qt::Designer
)

include(GNUInstallDirs)

install(TARGETS ServerManager
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ServerManager
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
