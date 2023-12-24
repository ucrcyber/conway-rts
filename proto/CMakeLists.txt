include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

set(Protobuf_IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
# message("protobuf IMPORT DIRS= ${Protobuf_IMPORT_DIRS}")

set(PROTO_FILES
  vector2.proto
  client.proto
  team.proto
  room.proto

  life_grid.proto
  structure_lookup.proto
  structure_properties.proto
  structure.proto

  event_base.proto # build, initialize
  event_room.proto # create, leave, join
  event.proto
)

add_library(proto)

foreach(PROTO_FILE ${PROTO_FILES})
  protobuf_generate_cpp(PROTO_SRC PROTO_HEADER ${PROTO_FILE})

  # message("--- ${PROTO_FILE} ---")
  # message(SRC=${PROTO_SRC})
  # message(HDR=${PROTO_HEADER})

  # idk why this works but it works https://stackoverflow.com/a/29348507/21507383
  set_source_files_properties(${PROTO_SRC} ${PROTO_HEADER} PROPERTIES GENERATED TRUE)

  target_sources(proto PUBLIC ${PROTO_HEADER} PUBLIC ${PROTO_SRC})
  # set(PROTO_OUTPUT_FILES "${PROTO_OUTPUT_FILES} ${PROTO_HEADER} ${PROTO_SRC}")
endforeach()

target_include_directories(proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# message(OUT=${PROTO_OUTPUT_FILES})
# add_library(proto ${PROTO_OUTPUT_FILES})
# add_library(proto ${PROTO_HEADER} ${PROTO_SRC})