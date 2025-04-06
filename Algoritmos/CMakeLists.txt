cmake_minimum_required(VERSION 3.29)
project(Ayda2)

set(CMAKE_CXX_STANDARD 20)

#incluir subproyectos
    add_subdirectory(STL)
    add_subdirectory(TDAGrafo)
    add_subdirectory(DFS)
    add_subdirectory(BFS)
add_subdirectory(TopSort)
add_subdirectory(PuntosArticulacion)
add_subdirectory(Kruskal)
add_subdirectory(Sets)
add_subdirectory(Dijkstra)
add_subdirectory(Prim)

