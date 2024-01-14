#
# Dependencies
#
find_package(Threads)

#
# Sources
#
set(SOURCES
    src/main.cpp
    src/Server.h
    src/Server.cpp
    src/ServerInfo.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})


#
# Target
#
add_executable(server ${SOURCES})
target_link_libraries(server
    PRIVATE
        myproto
)
