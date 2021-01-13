cmake_minimum_required(VERSION 3.13)
project(loe VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/keinr/LoE")

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# Thanks stack https://stackoverflow.com/a/61381440/10821333
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall)
endif()

# file(GLOB_RECURSE sources src/*.cpp)
set(sources 
    src/main.cpp
)
set(libs
    deps/GLAD/glad.c
    deps/stb/stb_image.c
    deps/stb/stb_vorbis.c
    deps/dr/dr_wav.c
)

add_executable(loe ${sources} ${libs})

find_package(glm REQUIRED)
find_package(glfw3 3.2 REQUIRED)

target_include_directories(Danzun
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include"
    PUBLIC "deps"
    PUBLIC "${GLFW_INCLUDE_DIRS}"
    PUBLIC "${GLM_INCLUDE_DIRS}"
)

target_link_libraries(Danzun
    glfw
    stdc++fs
)

# Configuration

set(LOE_VERSION "${CMAKE_PROJECT_VERSION}")

configure_file(src/cmake/config.h.in include/cmake/config.h)

# Packaging

install(
    TARGETS loe
    RUNTIME DESTINATION bin
)

if (UNIX)

    # ty Stack https://stackoverflow.com/a/41592428/10821333
    find_program(LSB_RELEASE_EXEC lsb_release)
    execute_process(COMMAND ${LSB_RELEASE_EXEC} -is
        OUTPUT_VARIABLE DISTRO
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if (DISTRO MATCHES "Debian" OR DISTRO MATCHES "Ubuntu")

        message(STATUS "Using debain packages")

        set(CPACK_DEBIAN_PACKAGE_VERSION ${VERSION})
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Orion Musselman <orionmusselman@gmail.com>")
        set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A game")
        set(CPACK_DEBIAN_PACKAGE_SECTION "games")
        set(CPACK_DEBIAN_PACKAGE_DEBUG ON)
        set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
        set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
        set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS_POLICY ">=")
        set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "${CMAKE_PROJECT_HOMEPAGE_URL}")
        set(CPACK_DEBIAN_FILE_NAME "LoE-${DANZUN_VERSION}-${DISTRO}-${CMAKE_SYSTEM_PROCESSOR}.deb")

        set(CPACK_GENERATOR ${CPACK_GENERATOR} DEB)

    endif()

    set(CPACK_GENERATOR ${CPACK_GENERATOR} TGZ)

else()

    set(CPACK_GENERATOR ${CPACK_GENERATOR} ZIP)

endif()

include(CPack)

