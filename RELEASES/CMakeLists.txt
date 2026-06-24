cmake_minimum_required(VERSION 3.28)
project(AllReleases LANGUAGES CXX)

# 1. Identifichiamo tutte le cartelle che rappresentano una release.
# Usiamo il pattern che identifica le tue cartelle (es. FCG_VisualizzatoreCamminata-*)
file(GLOB RELEASE_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "FCG_VisualizzatoreCamminata-*")

message(STATUS "Trovate ${#RELEASE_DIRS} release da compilare.")

# 2. Cicliamo su ogni cartella trovata
foreach(RELEASE_DIR ${RELEASE_DIRS})
    # Verifichiamo che esista un file CMakeLists.txt all'interno della cartella
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${RELEASE_DIR}/CMakeLists.txt")
        message(STATUS "Aggiunta release: ${RELEASE_DIR}")
        
        # Aggiungiamo la sottocartella al progetto principale.
        # CMake gestirà la compilazione di ogni singola release come parte di questo unico progetto.
        add_subdirectory(${RELEASE_DIR})
    else()
        message(WARNING "Saltata cartella ${RELEASE_DIR}: CMakeLists.txt non trovato.")
    endif()
endforeach()
