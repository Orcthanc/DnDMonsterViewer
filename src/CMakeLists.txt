project (DnDMonsterViewerExe)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE DnDMonsterViewer_SOURCES "*.c")

list( FILTER DnDMonsterViewer_SOURCES EXCLUDE REGEX ".*main.c$" )

add_library( DnDMonsterViewerLib ${DnDMonsterViewer_SOURCES} )

add_executable( DnDMonsterViewerExe main.c )

target_include_directories( DnDMonsterViewerLib PUBLIC "." )
target_link_libraries( DnDMonsterViewerLib PUBLIC "ncurses" )
target_link_libraries( DnDMonsterViewerExe PUBLIC DnDMonsterViewerLib )
