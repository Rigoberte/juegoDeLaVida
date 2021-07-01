cmake_minimum_required(VERSION 3.5)
project(juegoDeLaVida)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(SDL2_PATH "C:/Users/inaki/SDL2-2.0.12/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)

set(SOURCE_FILES_TEST
		main.cpp
        ejercicios.cpp
        auxiliares.cpp
		tests/EJ01_toroideValidoTEST.cpp
		tests/EJ02_toroideMuertoTEST.cpp
		tests/EJ03_posicionesVivasTEST.cpp
		tests/EJ04_densidadPoblacionTEST.cpp
		tests/EJ05_cantidadVecinosVivosTEST.cpp
		tests/EJ06_evolucionDePosicionTEST.cpp
		tests/EJ07_evolucionToroideTEST.cpp
		tests/EJ08_evolucionMultipleTEST.cpp
		tests/EJ09_esPeriodicoTEST.cpp
		tests/EJ10_primosLejanosTEST.cpp
		tests/EJ11_seleccionNaturalTEST.cpp
		tests/EJ12_fusionarTEST.cpp
		tests/EJ13_vistaTrasladadaTEST.cpp
		tests/EJ14_menorSuperficieVivaTEST.cpp
        )
add_executable(juegoDeLaVidaTest ${SOURCE_FILES_TEST})

set_target_properties(juegoDeLaVidaTest PROPERTIES COMPILE_FLAGS "-g --coverage")
set_target_properties(juegoDeLaVidaTest PROPERTIES LINK_FLAGS "-g --coverage")

target_link_libraries(juegoDeLaVidaTest gtest gtest_main)

if(SDL2_FOUND)
	set(SOURCE_FILES_GUI juegoDeLaVida.cpp auxiliares.cpp auxiliares.h ejercicios.h ejercicios.cpp definiciones.h es.h es.cpp maxiopt.h maxiopt.cpp)
	add_executable(juegoDeLaVida ${SOURCE_FILES_GUI})

	set_target_properties(juegoDeLaVida PROPERTIES COMPILE_FLAGS "-O3")

	target_include_directories(juegoDeLaVida PUBLIC ${SDL2_INCLUDE_DIR})
	target_link_libraries(juegoDeLaVida ${SDL2_LIBRARY})
#	target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2main SDL2)
endif()

set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

# -g: Hace que podamos debuggear el programa.
# --coverage: Hace que se pueda calcular el cubrimiento de los casos de test.
#set(CMAKE_CXX_FLAGS "-g --coverage")
# Un temita de gcov que no se lleva tan bien con CMake,
# y entonces hay que poner esta línea.
# Para más información, ver https://texus.me/2015/09/06/cmake-and-gcov/.
#set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)