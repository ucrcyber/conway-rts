# LITERAL MAGIC by JACK :pray: :pray:
# https://stackoverflow.com/a/75848101/21507383

add_subdirectory(libuv)
add_subdirectory(zlib)
add_subdirectory(uSockets)
add_subdirectory(uWebSockets)

include_directories(${external_include_dirs})
set(external_include_dirs ${external_include_dirs} PARENT_SCOPE)