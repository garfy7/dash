
# Copyright (c) 2011-2012 Stefan Eilemann <Stefan.Eilemann@epfl.ch>

configure_file("version.in.h" "${OUTPUT_INCLUDE_DIR}/dash/version.h" @ONLY)

set(DASH_HEADERS # public, installed
  api.h
  dash.h
  types.h
  attribute.h
  commit.h
  context.h
  node.h
  nodeVisitor.h
  "${OUTPUT_INCLUDE_DIR}/dash/version.h"
  visitorResult.h
)

set(DASH_DETAIL_HEADERS # private, installed
  detail/attribute.h
  detail/attributeIterator.h
  detail/change.h
  detail/childIterator.h
  detail/commit.h
  detail/commitChange.h
  detail/context.h
  detail/contextCommit.h
  detail/contextPtr.h
  detail/node.h
  detail/parentIterator.h
  detail/serializable.h
  detail/types.h
)

set(DASH_SOURCES
  attribute.cpp
  context.cpp
  commit.cpp
  node.cpp
  version.cpp
)

set(DASH_DETAIL_SOURCES
  detail/attribute.cpp
  detail/change.cpp
  detail/commit.cpp
  detail/commitChange.cpp
  detail/context.cpp
  detail/contextChange.cpp
  detail/contextChange.h
  detail/contextCommit.cpp
  detail/node.cpp
)

set(DASH_ALL ${DASH_HEADERS} ${DASH_SOURCES})
set(DASH_DETAIL_ALL ${DASH_DETAIL_HEADERS} ${DASH_DETAIL_SOURCES})

source_group(\\ FILES CMakeLists.txt ${DASH_ALL})
source_group(detail FILES ${DASH_DETAIL_ALL})

set(LIBRARY dash)
set(LIB_INCLUDE ${LIBRARY})

add_library(${LIBRARY} SHARED ${DASH_ALL} ${DASH_DETAIL_ALL})
target_link_libraries(${LIBRARY} ${LUNCHBOX_LIBRARIES} pthread ${Boost_LIBRARIES})
set_target_properties(${LIBRARY}
  PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION_ABI}
  COMPILE_DEFINITIONS DASH_SHARED
)

install(FILES ${DASH_HEADERS} DESTINATION include/${LIBRARY} COMPONENT dev)
install(FILES ${DASH_DETAIL_HEADERS} DESTINATION include/${LIBRARY}/detail
        COMPONENT dev)
install(TARGETS ${LIBRARY}
        ARCHIVE DESTINATION lib COMPONENT dev
        RUNTIME DESTINATION bin COMPONENT lib
        LIBRARY DESTINATION lib COMPONENT lib)
