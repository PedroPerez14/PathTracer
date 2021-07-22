# CMakeList.txt: proyecto de CMake para PathTracer, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Agregue un origen al ejecutable de este proyecto.
add_executable (PathTracer "MainPathTracer.cpp" "MainPathTracer.h" "Tracer/PathTracer.h" "Tracer/PathTracer.cpp" "Misc/CommonDefines.h" "DataTypes/Vector3.h" "DataTypes/Material.h" "DataTypes/Camera.h" "Geometry/Shape.h" "Geometry/Cylinder.h" "Geometry/Plane.h" "Geometry/Quad.h" "Geometry/Sphere.h" "Concurrency/BoundedQueue.cpp" "Concurrency/BoundedQueue.h" "Concurrency/ConcurrentBoundedQueue.cpp" "Concurrency/ConcurrentBoundedQueue.h" "Concurrency/Semaphore.cpp" "Concurrency/Semaphore.h" "Geometry/Cylinder.h" "DataTypes/PointLight.h" "DataTypes/Image.h" "DataTypes/Texture.h" "Scenes/PrebakedScenes.h" "Misc/Transform.h")

# TODO: Agregue pruebas y destinos de instalación si es necesario.
