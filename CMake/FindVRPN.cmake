# _____________________________________________________________________________
#
# VRPN 
# _____________________________________________________________________________
# Assume not found.
SET(VRPN_FOUND FALSE)

# PATH ________________________________________________________________________

if (VRPN_PATH)
    # Set by user...
else (VRPN_PATH)
    find_path(VRPN_PATH include/vrpn_Tracker.h
	HINTS ${VRPN_ROOT} $ENV{VRPN_ROOT}
        /usr/local/
        /opt/VRPN
        "C:/Program Files/VRPN"
        /opt
        /sw/VRPN)
endif (VRPN_PATH)

find_library(VRPN_LIBRARIES NAMES vrpn PATHS ${VRPN_PATH}/lib NO_DEFAULT_PATH)

if(VRPN_PATH AND VRPN_LIBRARIES)
  set(VRPN_FOUND TRUE)
  set(VRPN_INCLUDE_DIRS ${VRPN_PATH}/include)
  if(NOT VRPN_FIND_QUIETLY)
    message(STATUS "Found VRPN in ${VRPN_INCLUDE_DIRS};${VRPN_LIBRARIES}")
  endif()
else()
  if(VRPN_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find VRPN")
  elseif(NOT VRPN_FIND_QUIETLY)
    if(NOT VRPN_PATH)
      message(STATUS "Could not find VRPN header vrpn_Tracker.h")
    else()
      message(STATUS "Could not find libvrpn in ${VRPN_PATH}")
    endif()
  endif()
endif()

if (NOT VRPN_FOUND)
   if (VRPN_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find VRPN")
   endif (VRPN_FIND_REQUIRED)
endif (NOT VRPN_FOUND)
  

