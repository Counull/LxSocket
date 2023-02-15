include_directories(../include)
aux_source_directory(. SRC)

find_library(WSOCK32_LIBRARY wsock32)
find_library(WS2_32_LIBRARY ws2_32)
message("******************************************")




add_library(LxSocket STATIC ${SRC})



if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
target_link_libraries(LxSocket PUBLIC wsock32 ws2_32)
endif()



