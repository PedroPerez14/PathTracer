# CMakeList.txt: proyecto de CMake para PathTracer, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Agregue un origen al ejecutable de este proyecto.
add_executable (PathTracer "PathTracer.cpp" "PathTracer.h" "Tracer/PathTracer.h" "Tracer/PathTracer.cpp" "Misc/CommonDefines.h" "DataTypes/Vector3.h" "DataTypes/Material.h")

# TODO: Agregue pruebas y destinos de instalación si es necesario.
