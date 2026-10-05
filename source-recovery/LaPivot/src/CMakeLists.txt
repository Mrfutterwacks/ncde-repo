cmake_minimum_required(VERSION 3.24)
project(LaPivot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 6.11 REQUIRED COMPONENTS Core Gui Qml Quick OpenGL DBus Network)
find_package(PkgConfig REQUIRED)
pkg_check_modules(XCB REQUIRED IMPORTED_TARGET
    xcb xcb-render xcb-renderutil xcb-shape xcb-randr xcb-xfixes xcb-screensaver xcb-xinput xcb-icccm xcb-keysyms)
pkg_check_modules(PULSE REQUIRED IMPORTED_TARGET libpulse)
pkg_check_modules(CRYPT REQUIRED IMPORTED_TARGET libcrypt)
find_package(OpenGL REQUIRED COMPONENTS OpenGL GLX)

set(LAPIVOT_ASSET_BASE "/usr/share/ncde/" CACHE STRING
    "Absolute default directory for LaPivot QML and assets")
if(NOT IS_ABSOLUTE "${LAPIVOT_ASSET_BASE}")
    message(FATAL_ERROR "LAPIVOT_ASSET_BASE must be an absolute path")
endif()
if(NOT LAPIVOT_ASSET_BASE MATCHES "/$")
    string(APPEND LAPIVOT_ASSET_BASE "/")
endif()

file(GLOB LAPIVOT_CPP CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB LAPIVOT_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(LaPivot
    ${LAPIVOT_CPP}
    ${LAPIVOT_HEADERS}
    resources/lelan.qrc
)
# The shell is LaPivot. "LaPivot-L2" was only the side-by-side test name (operator 2026-10-01: "it will
# just be called LaPivot, L2 was a way to tell them apart"); -DLAPIVOT_OUTPUT_NAME=LaPivot-L2 still builds it.
set(LAPIVOT_OUTPUT_NAME "LaPivot" CACHE STRING "Installed binary name")
set_target_properties(LaPivot PROPERTIES OUTPUT_NAME "${LAPIVOT_OUTPUT_NAME}")

target_compile_options(LaPivot PRIVATE -Wall -Wextra)
# /usr/lib/ncde/ncde-notify.so (LD_PRELOAD from the session script) looks up NotificationManager::notify
# with dlsym first, and only falls back to a fixed offset taken from the OLD binary. The oracle never
# exported it, so it always used that offset; in a source build the offset lands in some other function.
# Export exactly this symbol so dlsym finds it and the offset path is never taken (N1, 2026-10-01).
target_link_options(LaPivot PRIVATE
    "LINKER:--export-dynamic-symbol=_ZN19NotificationManager6notifyERK7QStringS2_S2_i")
target_compile_definitions(LaPivot PRIVATE
    "LAPIVOT_ASSET_BASE=\"${LAPIVOT_ASSET_BASE}\""
)
target_link_libraries(LaPivot PRIVATE
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::OpenGL Qt6::DBus Qt6::Network
    PkgConfig::XCB PkgConfig::PULSE PkgConfig::CRYPT
    OpenGL::OpenGL OpenGL::GLX
)

install(TARGETS LaPivot RUNTIME DESTINATION /usr/local/bin)
install(CODE "
    execute_process(
        COMMAND setcap cap_sys_nice+ep \"\$ENV{DESTDIR}/usr/local/bin/${LAPIVOT_OUTPUT_NAME}\"
        COMMAND_ERROR_IS_FATAL ANY
    )
")
