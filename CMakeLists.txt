CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF("${bluetooth_frwk}" STREQUAL "ntb")
PROJECT("Tizen Bluetooth Framework" C)

ADD_DEFINITIONS("-DNTB")
SET(TEST_INSTALL_DIR "${LIB_INSTALL_DIR}/capi-network-bluetooth-test/")
SET(PLUGIN_INSTALL_DIR "${LIB_INSTALL_DIR}/bluetooth-service/plugins/")
SET(CMAKE_C_FLAGS "-O3 -Wall -Werror -DPLUGINDIR=\\\"${PLUGIN_INSTALL_DIR}\\\"")

SET(TEST "test-flags")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include/ ${CMAKE_SOURCE_DIR}/src/ntb/include)

INCLUDE(FindPkgConfig)
pkg_check_modules(${TEST} REQUIRED
			glib-2.0
			dbus-1
			gio-2.0
			gio-unix-2.0)

FOREACH(flag ${${TEST}_CFLAGS})
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}")
ENDFOREACH(flag)

IF(platform STREQUAL "Mobile")
SET(MOBILE_FLAGS "mobile-flags")
pkg_check_modules(${MOBILE_FLAGS} REQUIRED
			msg-service
			email-service
			vconf)
FOREACH(flag ${${MOBILE_FLAGS}_CFLAGS})
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}")
ENDFOREACH(flag)

FOREACH(flag ${${MOBILE_FLAGS}_LDFLAGS})
	SET(${TEST}_LDFLAGS "${${TEST}_LDFLAGS} ${flag}")
ENDFOREACH(flag)

ADD_DEFINITIONS(-DTIZEN_2_MOBILE)
ENDIF()

IF(platform STREQUAL "GEEK")
SET(TIZEN_FLAGS "tizen-flags")
pkg_check_modules(${TIZEN_FLAGS} REQUIRED
			dlog
			syspopup-caller
			notification
			capi-base-common)

FOREACH(flag ${${TIZEN_FLAGS}_CFLAGS})
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}")
ENDFOREACH(flag)

FOREACH(flag ${${TIZEN_FLAGS}_LDFLAGS})
	SET(${TEST}_LDFLAGS "${${TEST}_LDFLAGS} ${flag}")
ENDFOREACH(flag)
	ADD_DEFINITIONS(-DTIZEN)
ENDIF()

IF(platform STREQUAL "Tizen3")
SET(TIZEN3_FLAGS "tizen3-flags")
pkg_check_modules(${TIZEN3_FLAGS} REQUIRED
			dlog
			vconf
			notification
			capi-base-common)
FOREACH(flag ${${TIZEN3_FLAGS}_CFLAGS})
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}")
ENDFOREACH(flag)

FOREACH(flag ${${TIZEN3_FLAGS}_LDFLAGS})
	SET(${TEST}_LDFLAGS "${${TEST}_LDFLAGS} ${flag}")
ENDFOREACH(flag)
	ADD_DEFINITIONS(-DTIZEN)
	ADD_DEFINITIONS(-DTIZEN_3)
ENDIF()

# BLUETOOTH-SERVICE
SET(BLUETOOTH-SERVICE "bluetooth-service")

IF(platform STREQUAL "Mobile")
SET(SOURCES_BLUETOOTH_SERVICE
	src/ntb/src/main.c
	src/ntb/src/manager.c
	src/ntb/src/plugin.c
	src/ntb/src/vertical.c
	src/ntb/src/pairing.c
	src/ntb/src/opp.c
	src/ntb/src/map_agent.c
	src/ntb/src/map_bmessage.c
	src/ntb/src/bluetooth_map_agent.c
	src/ntb/lib/bluez.c
	src/ntb/lib/bluez-hdp.c
	src/ntb/lib/common.c
	src/ntb/lib/obex.c
   )
ELSE()
SET(SOURCES_BLUETOOTH_SERVICE
	src/ntb/src/main.c
	src/ntb/src/manager.c
	src/ntb/src/plugin.c
	src/ntb/src/vertical.c
	src/ntb/src/pairing.c
	src/ntb/src/opp.c
	src/ntb/lib/bluez.c
	src/ntb/lib/bluez-hdp.c
	src/ntb/lib/common.c
	src/ntb/lib/obex.c
   )
ENDIF()

ADD_EXECUTABLE(${BLUETOOTH-SERVICE} ${SOURCES_BLUETOOTH_SERVICE})
TARGET_LINK_LIBRARIES(${BLUETOOTH-SERVICE} ${${TEST}_LDFLAGS} -ldl)
SET_TARGET_PROPERTIES(${BLUETOOTH-SERVICE} PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/ntb/src)
INSTALL(TARGETS ${BLUETOOTH-SERVICE} DESTINATION bin)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/packaging/bluezlib.conf
					DESTINATION /etc/dbus-1/system.d)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/packaging/bluezobex.conf
					DESTINATION /etc/dbus-1/system.d)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/packaging/bluetooth-service.conf
					DESTINATION /etc/dbus-1/system.d)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/packaging/org.tizen.comms.service
					DESTINATION share/dbus-1/system-services)

# BLUEZ-TEST
SET(BLUEZ-TEST "bluez-lib-test")

SET(SOURCES_BLUEZ_TEST
	src/ntb/lib/common.c
	src/ntb/lib/bluez.c
	src/ntb/lib/bluez-hdp.c
	src/ntb/test/bluez-lib-test.c
   )

ADD_EXECUTABLE(${BLUEZ-TEST} ${SOURCES_BLUEZ_TEST})
TARGET_LINK_LIBRARIES(${BLUEZ-TEST} ${${TEST}_LDFLAGS})
SET_TARGET_PROPERTIES(${BLUEZ-TEST} PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/ntb/test)
INSTALL(TARGETS ${BLUEZ-TEST} DESTINATION ${TEST_INSTALL_DIR})
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/packaging/bluez-lib-test.conf
					DESTINATION /etc/dbus-1/system.d)

# OBEX-TEST
SET(OBEX-TEST "obex-lib-test")

SET(SOURCES_OBEX_TEST
	src/ntb/lib/common.c
	src/ntb/lib/obex.c
	src/ntb/test/obex-lib-test.c
   )

ADD_EXECUTABLE(${OBEX-TEST} ${SOURCES_OBEX_TEST})
TARGET_LINK_LIBRARIES(${OBEX-TEST} ${${TEST}_LDFLAGS})
SET_TARGET_PROPERTIES(${OBEX-TEST} PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/ntb/test)
INSTALL(TARGETS ${OBEX-TEST} DESTINATION ${TEST_INSTALL_DIR})

# BT-SERVICE-TEST
SET(BT-SERVICE-TEST "bt-serivce-lib-test")

SET(SOURCES_BT_SERVICE_TEST
	src/ntb/lib/common.c
	src/ntb/lib/bluetooth-service.c
	src/ntb/test/bt-service-lib-test.c
   )

ADD_EXECUTABLE(${BT-SERVICE-TEST} ${SOURCES_BT_SERVICE_TEST})
TARGET_LINK_LIBRARIES(${BT-SERVICE-TEST} ${${TEST}_LDFLAGS})
SET_TARGET_PROPERTIES(${BT-SERVICE-TEST} PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/ntb/test)
INSTALL(TARGETS ${BT-SERVICE-TEST} DESTINATION ${TEST_INSTALL_DIR})

# CAPI-BLUETOOTH
SET(CAPI-BLUETOOTH "capi-network-bluetooth")

SET(SOURCE_CAPI_BLUETOOTH
	src/ntb/lib/common.c
	src/ntb/lib/bluez.c
	src/ntb/lib/bluez-hdp.c
	src/ntb/capi/bluetooth.c
	src/ntb/lib/obex.c
	src/ntb/capi/bluetooth-obex.c
	src/ntb/lib/bluetooth-service.c
	src/bluetooth-common.c
	src/bluetooth-adapter.c
	src/bluetooth-device.c
	src/bluetooth-socket.c
	src/bluetooth-opp-server.c
	src/bluetooth-opp-client.c
	src/bluetooth-pan.c
	src/bluetooth-hdp.c
	src/bluetooth-hid.c
	src/bluetooth-audio.c
	src/bluetooth-avrcp.c
	src/bluetooth-gatt.c
   )

ADD_LIBRARY(${CAPI-BLUETOOTH} SHARED ${SOURCE_CAPI_BLUETOOTH})
TARGET_LINK_LIBRARIES(${CAPI-BLUETOOTH} ${${TEST}_LDFALGS})

SET_TARGET_PROPERTIES(${CAPI-BLUETOOTH}
     PROPERTIES
     VERSION ${FULLVER}
     SOVERSION ${MAJORVER}
     CLEAN_DIRECT_OUTPUT 1
     LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/ntb/capi
)

INSTALL(
        DIRECTORY include/ DESTINATION include/network
        FILES_MATCHING
        PATTERN "*_private.h" EXCLUDE
        PATTERN "include/*.h"
        )

INSTALL(TARGETS ${CAPI-BLUETOOTH} DESTINATION ${LIB_INSTALL_DIR})
CONFIGURE_FILE(
    src/ntb/capi-network-bluetooth.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/${CAPI-BLUETOOTH}.pc
    @ONLY
)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${CAPI-BLUETOOTH}.pc DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)

# BLUEZ-CAPI-TEST
SET(BLUEZ-CAPI-TEST "bluez-capi-test")

SET(SOURCE_BLUEZ_CAPI_TEST
	src/ntb/test/bluez-capi-test.c
   )

ADD_EXECUTABLE(${BLUEZ-CAPI-TEST} ${SOURCE_BLUEZ_CAPI_TEST})
TARGET_LINK_LIBRARIES(${BLUEZ-CAPI-TEST} ${CAPI-BLUETOOTH} ${${TEST}_LDFLAGS})
SET_TARGET_PROPERTIES(${BLUEZ-CAPI-TEST} PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/ntb/test)
INSTALL(TARGETS ${BLUEZ-CAPI-TEST} DESTINATION ${TEST_INSTALL_DIR})

# BLUETOOH PLUGIN
IF(platform STREQUAL "GEEK")
	ADD_DEFINITIONS("-DGEEK")
	# geek plugin
	SET(PLUGIN_BLUETOOTH "bluetooth-geek")

	SET(SOURCE_PLUGIN_BLUETOOTH
		src/ntb/plugins/bluetooth-geek.c
		src/ntb/plugins/brcm_patchram_plus.c
	   )

	ADD_LIBRARY(${PLUGIN_BLUETOOTH} SHARED ${SOURCE_PLUGIN_BLUETOOTH})
	TARGET_LINK_LIBRARIES(${PLUGIN_BLUETOOTH} ${CAPI-BLUETOOTH} ${${TEST}_LDFLAGS})
	SET_TARGET_PROPERTIES(${PLUGIN_BLUETOOTH} PROPERTIES PREFIX "")
	SET_TARGET_PROPERTIES(${PLUGIN_BLUETOOTH} PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/ntb/plugins)
	INSTALL(TARGETS ${PLUGIN_BLUETOOTH} DESTINATION ${PLUGIN_INSTALL_DIR})
ENDIF()

IF(platform STREQUAL "Tizen3")
	SET(PLUGIN_BLUETOOTH "bluetooth-tizen3")

	SET(SOURCE_PLUGIN_BLUETOOTH src/ntb/plugins/bluetooth-tizen3.c)

	ADD_LIBRARY(${PLUGIN_BLUETOOTH} SHARED ${SOURCE_PLUGIN_BLUETOOTH})
	TARGET_LINK_LIBRARIES(${PLUGIN_BLUETOOTH} ${${TEST}_LDFLAGS})
	SET_TARGET_PROPERTIES(${PLUGIN_BLUETOOTH} PROPERTIES PREFIX "")
	SET_TARGET_PROPERTIES(${PLUGIN_BLUETOOTH} PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/src/ntb/plugins)
	INSTALL(TARGETS ${PLUGIN_BLUETOOTH} DESTINATION ${PLUGIN_INSTALL_DIR})
ENDIF()

ELSE()

SET(fw_name "capi-network-bluetooth")

PROJECT(${fw_name})

SET(CMAKE_INSTALL_PREFIX /usr)
SET(PREFIX ${CMAKE_INSTALL_PREFIX})

SET(INC_DIR include)
INCLUDE_DIRECTORIES(${INC_DIR})

SET(dependents "dlog glib-2.0 capi-base-common bluetooth-api")
SET(pc_dependents "capi-base-common")

INCLUDE(FindPkgConfig)
pkg_check_modules(${fw_name} REQUIRED ${dependents})
FOREACH(flag ${${fw_name}_CFLAGS})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -fPIC -Wall -Werror")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g")

IF("${ARCH}" STREQUAL "arm")
    ADD_DEFINITIONS("-DTARGET")
ENDIF("${ARCH}" STREQUAL "arm")

ADD_DEFINITIONS("-DPREFIX=\"${CMAKE_INSTALL_PREFIX}\"")
ADD_DEFINITIONS("-DTIZEN_DEBUG")

SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=${LIB_INSTALL_DIR}")

SET(SOURCES
src/bluetooth-common.c
src/bluetooth-adapter.c
src/bluetooth-device.c
src/bluetooth-socket.c
src/bluetooth-opp-server.c
src/bluetooth-opp-client.c
src/bluetooth-pan.c
src/bluetooth-hdp.c
src/bluetooth-hid.c
src/bluetooth-audio.c
src/bluetooth-avrcp.c
src/bluetooth-gatt.c
)

ADD_LIBRARY(${fw_name} SHARED ${SOURCES})

TARGET_LINK_LIBRARIES(${fw_name} ${${fw_name}_LDFLAGS})

SET_TARGET_PROPERTIES(${fw_name}
     PROPERTIES
     VERSION ${FULLVER}
     SOVERSION ${MAJORVER}
     CLEAN_DIRECT_OUTPUT 1
)

INSTALL(TARGETS ${fw_name} DESTINATION ${LIB_INSTALL_DIR})
INSTALL(
        DIRECTORY ${INC_DIR}/ DESTINATION include/network
        FILES_MATCHING
        PATTERN "*_private.h" EXCLUDE
        PATTERN "${INC_DIR}/*.h"
        )

SET(PC_NAME ${fw_name})
SET(PC_REQUIRED ${pc_dependents})
SET(PC_LDFLAGS -l${fw_name})

CONFIGURE_FILE(
    capi-network-bluetooth.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc
    @ONLY
)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)

ADD_SUBDIRECTORY(test)

IF(UNIX)

ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
ADD_CUSTOM_COMMAND(
        DEPENDS clean 
        COMMENT "distribution clean"
        COMMAND find
        ARGS    . 
        -not -name config.cmake -and \(
        -name tester.c -or
        -name Testing -or
        -name CMakeFiles -or
        -name cmake.depends -or
        -name cmake.check_depends -or
        -name CMakeCache.txt -or
        -name cmake.check_cache -or
        -name *.cmake -or
        -name Makefile -or
        -name core -or
        -name core.* -or
        -name gmon.out -or
        -name install_manifest.txt -or
        -name *.pc -or
        -name *~ \)
        | grep -v TC | xargs rm -rf
        TARGET  distclean
        VERBATIM
)

ENDIF(UNIX)

ENDIF()
