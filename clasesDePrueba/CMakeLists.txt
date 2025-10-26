cmake_minimum_required(VERSION 3.16)

project(clasesDePrueba LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(clasesDePrueba main.cpp
    album.h album.cpp
    artista.h artista.cpp
    precarga.h precarga.cpp
    cancion.h cancion.cpp)

include(GNUInstallDirs)
install(TARGETS clasesDePrueba
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
