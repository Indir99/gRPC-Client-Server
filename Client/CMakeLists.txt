#
# Dependencies
#
find_package(Threads)

#
# Sources
#
set(SOURCES
    src/main.cpp
    src/Client.h
    src/Client.cpp
    src/ClientInfo.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})


#
# Target
#
add_executable(client ${SOURCES})
target_link_libraries(client
    PRIVATE
        myproto
)
