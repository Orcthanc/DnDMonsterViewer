project (DnDMonsterViewer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "*.c")

list( FILTER ${PROJECT_NAME}_SOURCES EXCLUDE REGEX ".*main.c$" )

add_library( ${PROJECT_NAME}Lib ${${PROJECT_NAME}_SOURCES} )

target_link_libraries( ${PROJECT_NAME}Lib PUBLIC JSONParserLib "ncurses" )
target_include_directories( ${PROJECT_NAME}Lib PUBLIC JSONParserLib ${PROJECT_SOURCE_DIR} )
set_property(TARGET ${PROJECT_NAME}Lib PROPERTY C_STANDARD 99)

add_executable( ${PROJECT_NAME}Exe main.c )

target_link_libraries( ${PROJECT_NAME}Exe PUBLIC ${PROJECT_NAME}Lib )
set_property(TARGET ${PROJECT_NAME}Exe PROPERTY C_STANDARD 99)
