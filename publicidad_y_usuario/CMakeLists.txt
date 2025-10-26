cmake_minimum_required(VERSION 3.16)

project(publicidad_y_usuario LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(publicidad_y_usuario main.cpp
    anuncios.h)

include(GNUInstallDirs)
install(TARGETS publicidad_y_usuario
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
