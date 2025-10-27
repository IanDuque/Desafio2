cmake_minimum_required(VERSION 3.16)

project(clases LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(clases main.cpp
    cancion.h cancion.cpp
    usuario.cpp
    precarga.cpp
    album.cpp
    artista.cpp
    artista.h
    usuario.h
    precarga.h
    album.h
    anuncios.cpp
    anuncios.h
    menu.h
    menu.cpp
    metricas.h
    metricas.cpp)

include(GNUInstallDirs)
install(TARGETS clases
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
