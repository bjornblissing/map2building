# Target name
SET(TARGET_TARGETNAME Map2Building)

# Target source files
SET(TARGET_SRC
	main.cpp
	building.cpp
	buildinglibrary.cpp
	heighttile.cpp
	material.cpp
	materiallibrary.cpp
	polygon.cpp
	shapetile.cpp
	texturelibrary.cpp
	worldbuilder.cpp
	# XML Library
	${PUGIXML_INCLUDE_DIR}/pugixml.cpp
)

# Target headerfiles
SET(TARGET_H
	building.h
	buildinglibrary.h
	heighttile.h
	material.h
	materiallibrary.h
	polygon.h
	shapetile.h
	texturelibrary.h
	worldbuilder.h
)

#####################################################################
# Create executable
#####################################################################

IF(MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251 /wd4351")
ENDIF(MSVC)

ADD_EXECUTABLE(${TARGET_TARGETNAME} ${TARGET_SRC} ${TARGET_H})

#####################################################################
# Linker options
#####################################################################

# Link to open gl libs
TARGET_LINK_LIBRARIES(${TARGET_TARGETNAME}  ${OPENGL_LIBRARIES} )

# Link to OpenSceneGraph libs
TARGET_LINK_LIBRARIES(${TARGET_TARGETNAME}  ${OPENSCENEGRAPH_LIBRARIES} )

# Link to GDAL libs
TARGET_LINK_LIBRARIES(${TARGET_TARGETNAME}  "${OSG_THIRD_PARTY_DIR}/lib/gdal_i.lib" )

####################################################################
# Create user file for correct environment string
#####################################################################
IF(WIN32)
    IF(MSVC)
		IF (OPENSCENEGRAPH_FOUND)
			# Build path
			SET(USERFILE_ENVIRONMENT_DEBUG "PATH=")
			SET(USERFILE_ENVIRONMENT_RELEASE "PATH=")

			# Add OpenSceneGraph to path
			IF (EXISTS "${OSG_DIR}/bin")
				SET(OSG_BIN_DIR "${OSG_DIR}/bin" CACHE PATH "Path where to find OpenSceneGraph binaries")
			ELSE (EXISTS "${OSG_DIR}/bin")
				SET (OSG_BIN_DIR CACHE PATH "Path where to find OpenSceneGraph binaries")
			ENDIF(EXISTS "${OSG_DIR}/bin")
			SET(USERFILE_ENVIRONMENT_DEBUG "${USERFILE_ENVIRONMENT_DEBUG}${OSG_BIN_DIR}")
			SET(USERFILE_ENVIRONMENT_RELEASE "${USERFILE_ENVIRONMENT_RELEASE}${OSG_BIN_DIR}")

			IF (OSG_THIRD_PARTY_DIR)
				# Add third party to path
				SET(USERFILE_ENVIRONMENT_DEBUG "${USERFILE_ENVIRONMENT_DEBUG};${OSG_THIRD_PARTY_DIR}/bin")
				SET(USERFILE_ENVIRONMENT_RELEASE "${USERFILE_ENVIRONMENT_RELEASE};${OSG_THIRD_PARTY_DIR}/bin")
			ELSE (OSG_THIRD_PARTY_DIR)
				MESSAGE("Warning: OpenSceneGraph 3rd Party Directory not found.")
			ENDIF(OSG_THIRD_PARTY_DIR)

			# For visual studio 10
			IF(MSVC10)
				CONFIGURE_FILE(${TARGET_TARGETNAME}.vcxproj.template ${TARGET_TARGETNAME}.vcxproj.user @ONLY)
			ENDIF(MSVC10)

		ENDIF (OPENSCENEGRAPH_FOUND)
    ENDIF(MSVC)
ENDIF(WIN32)
