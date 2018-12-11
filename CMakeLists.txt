cmake_minimum_required( VERSION 3.6 )

project( DNDMonsterViewer )
add_subdirectory( external )
add_subdirectory( src )

enable_testing()
add_subdirectory( test )
