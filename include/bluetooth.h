/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 

#ifndef __TIZEN_NETWORK_BLUETOOTH_H__
#define __TIZEN_NETWORK_BLUETOOTH_H__

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <tizen_error.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @file        bluetooth.h
 * @brief       API to control the Bluetooth adapter and devices and communications.
 * @ingroup     CAPI_NETWORK_BLUETOOTH_MODULE
 */


/**
 * @addtogroup CAPI_NETWORK_BLUETOOTH_MODULE
 * @{
 */

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief  Enumerations of connected Bluetooth device event role.
 */
typedef enum
{
	BT_SOCKET_UNKNOWN = 0x00, /**< Unknown role*/
	BT_SOCKET_SERVER , /**< Server role*/
	BT_SOCKET_CLIENT, /**< Client role*/
} bt_socket_role_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_MODULE
 * @brief Enumerations of Bluetooth error codes.
 */
typedef enum
{
	BT_ERROR_NONE = TIZEN_ERROR_NONE, /**< Successful*/
	BT_ERROR_CANCELLED = TIZEN_ERROR_CANCELED, /**< Operation cancelled */
	BT_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
	BT_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY, /**< Out of memory */
	BT_ERROR_RESOURCE_BUSY = TIZEN_ERROR_RESOURCE_BUSY, /**< Device or resource busy */
	BT_ERROR_TIMED_OUT = TIZEN_ERROR_TIMED_OUT, /**< Timeout error */
	BT_ERROR_NOW_IN_PROGRESS = TIZEN_ERROR_NOW_IN_PROGRESS, /**< Operation now in progress */
	BT_ERROR_NOT_INITIALIZED = TIZEN_ERROR_NETWORK_CLASS|0x0101, /**< Local adapter not initialized */
	BT_ERROR_NOT_ENABLED = TIZEN_ERROR_NETWORK_CLASS|0x0102, /**< Local adapter not enabled */
	BT_ERROR_ALREADY_DONE = TIZEN_ERROR_NETWORK_CLASS|0x0103, /**< Operation already done  */
	BT_ERROR_OPERATION_FAILED = TIZEN_ERROR_NETWORK_CLASS|0x0104, /**< Operation failed */
	BT_ERROR_NOT_IN_PROGRESS = TIZEN_ERROR_NETWORK_CLASS|0x0105, /**< Operation not in progress */
	BT_ERROR_REMOTE_DEVICE_NOT_BONDED = TIZEN_ERROR_NETWORK_CLASS|0x0106, /**< Remote device not bonded */
	BT_ERROR_AUTH_REJECTED = TIZEN_ERROR_NETWORK_CLASS|0x0107, /**< Authentication rejected */
	BT_ERROR_AUTH_FAILED = TIZEN_ERROR_NETWORK_CLASS|0x0108, /**< Authentication failed */
	BT_ERROR_REMOTE_DEVICE_NOT_FOUND = TIZEN_ERROR_NETWORK_CLASS|0x0109, /**< Remote device not found */
	BT_ERROR_SERVICE_SEARCH_FAILED = TIZEN_ERROR_NETWORK_CLASS|0x010A, /**< Service search failed */
} bt_error_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Enumerations of the Bluetooth adapter state.
 */
typedef enum
{
	BT_ADAPTER_DISABLED = 0x00, /**< Bluetooth adapter is disabled */
	BT_ADAPTER_ENABLED, /**< Bluetooth adapter is enabled */
} bt_adapter_state_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Enumerations of the Bluetooth visibility mode.
 */
typedef enum
{
	BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE = 0x00,  /**< Other devices cannot find your device via discovery */
	BT_ADAPTER_VISIBILITY_MODE_GENERAL_DISCOVERABLE,  /**< Discoverable mode */
	BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE,  /**< Discoverable mode with time limit. After specific period, 
							    it is changed to #BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE.*/
} bt_adapter_visibility_mode_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Enumerations of the discovery state of Bluetooth device.
 *
 */
typedef enum
{
	BT_ADAPTER_DEVICE_DISCOVERY_STARTED, /**< Device discovery is started */
	BT_ADAPTER_DEVICE_DISCOVERY_FINISHED, /**< Device discovery is finished */
	BT_ADAPTER_DEVICE_DISCOVERY_FOUND, /**< The remote Bluetooth device is found */
} bt_adapter_device_discovery_state_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Enumerations of device authorization state.
 */
typedef enum
{
	BT_DEVICE_AUTHORIZED, /**< The remote Bluetooth device is authorized */
	BT_DEVICE_UNAUTHORIZED, /**< The remote Bluetooth device is unauthorized */
} bt_device_authorization_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief  Enumerations of Bluetooth socket connection state.
 */
typedef enum
{
	BT_SOCKET_CONNECTED, /**< Socket is connected */
	BT_SOCKET_DISCONNECTED, /**< Socket is disconnected */
} bt_socket_connection_state_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Enumerations of major service class.
 */
typedef enum
{
	BT_MAJOR_SERVICE_CLASS_LIMITED_DISCOVERABLE_MODE  = 0x002000, /**< Limited discoverable mode */
	BT_MAJOR_SERVICE_CLASS_POSITIONING                = 0x010000, /**< Positioning class */
	BT_MAJOR_SERVICE_CLASS_NETWORKING                 = 0x020000, /**< Networking class */
	BT_MAJOR_SERVICE_CLASS_RENDERING                  = 0x040000, /**< Rendering class */
	BT_MAJOR_SERVICE_CLASS_CAPTURING                  = 0x080000, /**< Capturing class */
	BT_MAJOR_SERVICE_CLASS_OBJECT_TRANSFER            = 0x100000, /**< Object transferring class */
	BT_MAJOR_SERVICE_CLASS_AUDIO                      = 0x200000, /**< Audio class*/
	BT_MAJOR_SERVICE_CLASS_TELEPHONY                  = 0x400000, /**< Telephony class */
	BT_MAJOR_SERVICE_CLASS_INFORMATION                = 0x800000, /**< Information class */
} bt_major_service_class_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Enumerations of major device class.
 */
typedef enum
{
	BT_MAJOR_DEVICE_CLASS_MISC = 0x00, /**< Miscellaneous major device class*/
	BT_MAJOR_DEVICE_CLASS_COMPUTER = 0x01, /**< Computer major device class */
	BT_MAJOR_DEVICE_CLASS_PHONE = 0x02, /**< Phone major device class */
	BT_MAJOR_DEVICE_CLASS_LAN_NETWORK_ACCESS_POINT = 0x03, /**< LAN/Network access point major device class */
	BT_MAJOR_DEVICE_CLASS_AUDIO_VIDEO = 0x04, /**< Audio/Video major device class */
	BT_MAJOR_DEVICE_CLASS_PERIPHERAL = 0x05, /**< Peripheral major device class */
	BT_MAJOR_DEVICE_CLASS_IMAGING = 0x06, /**< Imaging major device class */
	BT_MAJOR_DEVICE_CLASS_WEARABLE = 0x07, /**< Wearable device class */
	BT_MAJOR_DEVICE_CLASS_TOY = 0x08, /**< Toy device class */
	BT_MAJOR_DEVICE_CLASS_HEALTH = 0x09, /**< Health device class */
	BT_MAJOR_DEVICE_CLASS_UNCATEGORIZED = 0x1F, /**< Uncategorized major device class */
} bt_major_device_class_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Enumerations of minor device class.
 */
typedef enum
{
	BT_MINOR_DEVICE_CLASS_COMPUTER_UNCATEGORIZED = 0x00, /**< Uncategorized minor device class of computer */
	BT_MINOR_DEVICE_CLASS_COMPUTER_DESKTOP_WORKSTATION = 0x04, /**< Desktop workstation minor device class of computer */
	BT_MINOR_DEVICE_CLASS_COMPUTER_SERVER_CLASS = 0x08, /**< Server minor device class of computer */
	BT_MINOR_DEVICE_CLASS_COMPUTER_LAPTOP = 0x0C, /**< Laptop minor device class of computer */
	BT_MINOR_DEVICE_CLASS_COMPUTER_HANDHELD_PC_OR_PDA = 0x10, /**< Handheld PC/PDA minor device class of computer */
	BT_MINOR_DEVICE_CLASS_COMPUTER_PALM_SIZED_PC_OR_PDA = 0x14, /**< Palm sized PC/PDA minor device class of computer */
	BT_MINOR_DEVICE_CLASS_COMPUTER_WEARABLE_COMPUTER = 0x18, /**< Wearable(watch sized) minor device class of computer */

	BT_MINOR_DEVICE_CLASS_PHONE_UNCATEGORIZED = 0x00, /**< Uncategorized minor device class of phone */
	BT_MINOR_DEVICE_CLASS_PHONE_CELLULAR = 0x04, /**< Cellular minor device class of phone */
	BT_MINOR_DEVICE_CLASS_PHONE_CORDLESS = 0x08, /**< Cordless minor device class of phone */
	BT_MINOR_DEVICE_CLASS_PHONE_SMART_PHONE = 0x0C, /**< Smart phone minor device class of phone */
	BT_MINOR_DEVICE_CLASS_PHONE_WIRED_MODEM_OR_VOICE_GATEWAY = 0x10, /**< Wired modem or voice gateway minor device class of phone */
	BT_MINOR_DEVICE_CLASS_PHONE_COMMON_ISDN_ACCESS = 0x14, /**< Common ISDN minor device class of phone */

	BT_MINOR_DEVICE_CLASS_LAN_NETWORK_ACCESS_POINT_FULLY_AVAILABLE = 0x04, /**< Fully available minor device class of LAN/Network access point */
	BT_MINOR_DEVICE_CLASS_LAN_NETWORK_ACCESS_POINT_1_TO_17_PERCENT_UTILIZED = 0x20, /**< 1-17% utilized minor device class of LAN/Network access point */
	BT_MINOR_DEVICE_CLASS_LAN_NETWORK_ACCESS_POINT_17_TO_33_PERCENT_UTILIZED = 0x40, /**< 17-33% utilized minor device class of LAN/Network access point */
	BT_MINOR_DEVICE_CLASS_LAN_NETWORK_ACCESS_POINT_33_TO_50_PERCENT_UTILIZED = 0x60, /**< 33-50% utilized minor device class of LAN/Network access point */
	BT_MINOR_DEVICE_CLASS_LAN_NETWORK_ACCESS_POINT_50_to_67_PERCENT_UTILIZED = 0x80, /**< 50-67% utilized minor device class of LAN/Network access point */
	BT_MINOR_DEVICE_CLASS_LAN_NETWORK_ACCESS_POINT_67_TO_83_PERCENT_UTILIZED = 0xA0, /**< 67-83% utilized minor device class of LAN/Network access point */
	BT_MINOR_DEVICE_CLASS_LAN_NETWORK_ACCESS_POINT_83_TO_99_PERCENT_UTILIZED = 0xC0, /**< 83-99% utilized minor device class of LAN/Network access point */
	BT_MINOR_DEVICE_CLASS_LAN_NETWORK_ACCESS_POINT_NO_SERVICE_AVAILABLE = 0xE0, /**< No service available minor device class of LAN/Network access point */

	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_UNCATEGORIZED = 0x00, /**< Uncategorized minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_WEARABLE_HEADSET = 0x04, /**< Wearable headset minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_HANDS_FREE = 0x08, /**< Hands-free minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_MICROPHONE = 0x10, /**< Microphone minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_LOUDSPEAKER = 0x14, /**< Loudspeaker minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_HEADPHONES = 0x18, /**< Headphones minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_PORTABLE_AUDIO = 0x1C, /**< Portable audio minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_CAR_AUDIO = 0x20, /**< Car audio minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_SET_TOP_BOX = 0x24, /**< Set-top box minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_HIFI_AUDIO_DEVICE = 0x28, /**< Hifi audio minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_VCR = 0x2C, /**< VCR minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_VIDEO_CAMERA = 0x30, /**< Video camera minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_CAMCORDER = 0x34, /**< Camcorder minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_VIDEO_MONITOR = 0x38, /**< Video monitor minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_VIDEO_DISPLAY_LOUDSPEAKER = 0x3C, /**< Video display and loudspeaker minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_VIDEO_CONFERENCING = 0x40, /**< Video conferencing minor device class of audio/video */
	BT_MINOR_DEVICE_CLASS_AUDIO_VIDEO_GAMING_TOY = 0x48, /**< Gaming/toy minor device class of audio/video */

	BT_MINOR_DEVICE_CLASS_PERIPHERA_UNCATEGORIZED = 0x00, /**< Uncategorized minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_KEY_BOARD = 0x40, /**< Key board minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_POINTING_DEVICE = 0x80, /**< Pointing device minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_COMBO_KEYBOARD_POINTING_DEVICE = 0xC0, /**< Combo keyboard or pointing device minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_JOYSTICK = 0x04, /**< Joystick minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_GAME_PAD = 0x08, /**< Game pad minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_REMOTE_CONTROL = 0x0C, /**< Remote control minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_SENSING_DEVICE = 0x10, /**< Sensing device minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_DIGITIZER_TABLET = 0x14, /**< Digitizer minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_CARD_READER = 0x18, /**< Card reader minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_DIGITAL_PEN = 0x1C, /**< Digital pen minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_HANDHELD_SCANNER = 0x20, /**< Handheld scanner minor device class of peripheral */
	BT_MINOR_DEVICE_CLASS_PERIPHERAL_HANDHELD_GESTURAL_INPUT_DEVICE = 0x24, /**< Handheld gestural input device minor device class of peripheral */

	BT_MINOR_DEVICE_CLASS_IMAGING_DISPLAY = 0x10, /**< Display minor device class of imaging */
	BT_MINOR_DEVICE_CLASS_IMAGING_CAMERA = 0x20, /**< Camera minor device class of imaging */
	BT_MINOR_DEVICE_CLASS_IMAGING_SCANNER = 0x40, /**< Scanner minor device class of imaging */
	BT_MINOR_DEVICE_CLASS_IMAGING_PRINTER = 0x80, /**< Printer minor device class of imaging */

	BT_MINOR_DEVICE_CLASS_WEARABLE_WRIST_WATCH = 0x04, /**< Wrist watch minor device class of wearable */
	BT_MINOR_DEVICE_CLASS_WEARABLE_PAGER = 0x08, /**< Pager minor device class of wearable */
	BT_MINOR_DEVICE_CLASS_WEARABLE_JACKET = 0x0C, /**< Jacket minor device class of wearable */
	BT_MINOR_DEVICE_CLASS_WEARABLE_HELMET = 0x10, /**< Helmet minor device class of wearable */
	BT_MINOR_DEVICE_CLASS_WEARABLE_GLASSES = 0x14, /**< Glasses minor device class of wearable */

	BT_MINOR_DEVICE_CLASS_TOY_ROBOT = 0x04, /**< Robot minor device class of toy */
	BT_MINOR_DEVICE_CLASS_TOY_VEHICLE = 0x08, /**< Vehicle minor device class of toy */
	BT_MINOR_DEVICE_CLASS_TOY_DOLL_ACTION = 0x0C, /**< Doll/Action minor device class of toy */
	BT_MINOR_DEVICE_CLASS_TOY_CONTROLLER = 0x10, /**< Controller minor device class of toy */
	BT_MINOR_DEVICE_CLASS_TOY_GAME = 0x14, /**< Game minor device class of toy */

	BT_MINOR_DEVICE_CLASS_HEATH_UNCATEGORIZED = 0x00, /**< Uncategorized minor device class of health */
	BT_MINOR_DEVICE_CLASS_HEATH_BLOOD_PRESSURE_MONITOR = 0x04, /**< Blood pressure monitor minor device class of health */
	BT_MINOR_DEVICE_CLASS_HEATH_THERMOMETER = 0x08, /**< Thermometer minor device class of health */
	BT_MINOR_DEVICE_CLASS_HEATH_WEIGHING_SCALE = 0x0C, /**< Weighing scale minor device class of health */
	BT_MINOR_DEVICE_CLASS_HEATH_GLUCOSE_METER = 0x10, /**< Glucose minor device class of health */
	BT_MINOR_DEVICE_CLASS_HEATH_PULSE_OXIMETER = 0x14, /**< Pulse oximeter minor device class of health */
	BT_MINOR_DEVICE_CLASS_HEATH_HEART_PULSE_RATE_MONITOR = 0x18, /**< Heart/Pulse rate monitor minor device class of health */
	BT_MINOR_DEVICE_CLASS_HEATH_DATA_DISPLAY = 0x1C, /**< Health data display minor device class of health */
	BT_MINOR_DEVICE_CLASS_HEATH_STEP_COUNTER = 0x20, /**< Step counter minor device class of health */    
	BT_MINOR_DEVICE_CLASS_HEATH_BODY_COMPOSITION_ANALYZER = 0x24, /**< Body composition analyzer minor device class of health */    
	BT_MINOR_DEVICE_CLASS_HEATH_PEAK_FLOW_MONITOR = 0x28, /**< Peak flow monitor minor device class of health */    
	BT_MINOR_DEVICE_CLASS_HEATH_MEDICATION_MONITOR = 0x2C, /**< Medication monitor minor device class of health */    
	BT_MINOR_DEVICE_CLASS_HEATH_KNEE_PROSTHESIS = 0x30, /**< Knee prosthesis minor device class of health */    
	BT_MINOR_DEVICE_CLASS_HEATH_ANKLE_PROSTHESIS = 0x34, /**< Ankle prosthesis minor device class of health */    
} bt_minor_device_class_e;

/**
 * @}
 */

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Class structure of device and service.
 *
 * @see #bt_device_info_s
 * @see #bt_adapter_device_discovery_info_s
 * @see bt_device_bond_created_cb()
 * @see bt_adapter_device_discovery_state_changed_cb()
 */
typedef struct
{
	bt_major_device_class_e major_device_class;	/**< Major device class. */
	bt_minor_device_class_e minor_device_class;	/**< Minor device class. */
	int major_service_class_mask;	/**< Major service class mask. 
	This value can be a combination of #bt_major_service_class_e like #BT_MAJOR_SERVICE_CLASS_RENDERING | #BT_MAJOR_SERVICE_CLASS_AUDIO */
} bt_class_s;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Structure of device discovery information.
 *
 * @see #bt_class_s
 * @see bt_adapter_device_discovery_state_changed_cb()
 */
typedef struct
{
	char* remote_address;	/**< The address of remote device */
	char* remote_name;	/**< The name of remote device */
	bt_class_s bt_class;	/**< The Bluetooth classes */
	int rssi;	/**< The strength indicator of received signal  */
	bool is_bonded;	/**< The bonding state */
} bt_adapter_device_discovery_info_s;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Device information structure used for identifying pear device.
 *
 * @see #bt_class_s
 * @see bt_device_bond_created_cb()
 */
typedef struct
{
	char* remote_address;	/**< The address of remote device */
	char* remote_name;	/**< The name of remote device */
	bt_class_s bt_class;	/**< The Bluetooth classes */
	char** service_uuid;  /**< The UUID list of service */
	int service_count;	/**< The number of services */     
	bool is_bonded;	/**< The bonding state */
	bool is_connected;	/**< The connection state */
	bool is_authorized;	/**< The authorization state */
} bt_device_info_s;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Service Discovery Protocol (SDP) data structure.
 *
 * @details This protocol is used for discovering available services or pear device,
 * and finding one to connect with. 
 *
 * @see bt_device_service_searched_cb()
 */
typedef struct
{
	char* remote_address;   /**< The address of remote device */
	char** service_uuid;  /**< The UUID list of service */
	int service_count;    /**< The number of services. */
} bt_device_sdp_info_s;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 *
 * @brief Rfcomm connection data used for exchanging data between Bluetooth devices.
 *
 * @see bt_socket_connection_state_changed_cb()
 */
typedef struct
{
	int socket_fd;	/**< The socket fd */
	bt_socket_role_e local_role;	/**< The local device role in this connection */
	char* remote_address;	/**< The remote device address. */
} bt_socket_connection_s;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 *
 * @brief Structure of RFCOMM received data.
 *
 * @remarks User can use standard linux functions for reading/writing
 * data from/to sockets.
 *
 * @see bt_socket_data_received_cb()
 */
typedef struct
{
	int socket_fd;	/**< The socket fd */
	int data_size;	/**< The length of the received data */
	char* data;	/**< The received data */
} bt_socket_received_data_s;

/**
 * @addtogroup CAPI_NETWORK_BLUETOOTH_MODULE
 * @{
 */

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Called when the Bluetooth adapter state changes. 
 * @param[in]   result  The result of the adapter state changing
 * @param[in]   adapter_state  The adapter state to be changed
 * @param[in]   user_data  The user data passed from the callback registration function
 * @pre Either bt_adapter_enable() or bt_adapter_disable() will invoke this callback if you register this callback using bt_adapter_set_state_changed_cb().
 * @see bt_adapter_enable()
 * @see bt_adapter_disable()
 * @see bt_adapter_set_state_changed_cb()
 * @see bt_adapter_unset_state_changed_cb() 
 */
typedef void (*bt_adapter_state_changed_cb)(int result, bt_adapter_state_e adapter_state, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Called when adapter name changes. 
 * @param[in]   device_name	The name of the Bluetooth device to be changed
 * @param[in]   user_data	The user data passed from the callback registration function
 * @pre This function will be invoked when the name of Bluetooth adapter changes
 * if you register this callback using bt_adapter_set_name_changed_cb().
 * @see bt_adapter_set_name()
 * @see bt_adapter_set_name_changed_cb()
 * @see bt_adapter_unset_name_changed_cb()
 */
typedef void (*bt_adapter_name_changed_cb)(char *device_name, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Called when the visibility mode changes. 
 * @param[in] result The result of the visibility mode changing
 * @param[in] visibility_mode The visibility mode to be changed
 * @param[in] user_data The user data passed from the callback registration function
 * 
 * @pre This function will be invoked when the visibility of Bluetooth adapter changes
 * if you register this callback using bt_adapter_set_visibility_mode_changed_cb().
 * 
 * @see bt_adapter_set_visibility()
 * @see bt_adapter_set_visibility_mode_changed_cb()
 * @see bt_adapter_unset_visibility_mode_changed_cb()
 */
typedef void (*bt_adapter_visibility_mode_changed_cb)
	(int result, bt_adapter_visibility_mode_e visibility_mode, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Called when the state of device discovery changes. 
 *
 * @remarks If \a discovery_state is #BT_ADAPTER_DEVICE_DISCOVERY_FOUND, 
 * then you can get some information, such as remote device address, remote device name, rssi, and bonding state.
 *
 * @param[in] result The result of the device discovery
 * @param[in] discovery_state The discovery state to be changed
 * @param[in] device_info The information of the discovered device \n
 * 					If \a discovery_state is #BT_ADAPTER_DEVICE_DISCOVERY_STARTED or 
 * #BT_ADAPTER_DEVICE_DISCOVERY_FINISHED, then \a device_info is NULL.
 * @param[in] user_data The user data passed from the callback registration function
 * 
 * @pre Either bt_adapter_start_device_discovery() or bt_adapter_stop_device_discovery() will invoke this function 
 * if you register this callback using bt_adapter_set_device_discovery_state_changed_cb().
 *
 * @see bt_adapter_start_device_discovery() 
 * @see bt_adapter_stop_device_discovery()
 * @see bt_adapter_set_device_discovery_state_changed_cb()
 * @see bt_adapter_unset_device_discovery_state_changed_cb()
 * 
 */
typedef void (*bt_adapter_device_discovery_state_changed_cb)
	(int result, bt_adapter_device_discovery_state_e discovery_state, bt_adapter_device_discovery_info_s *discovery_info, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Called when you get bonded devices repeatedly.
 *
 * @param[in] device_info The bonded device information
 * @param[in] user_data The user data passed from the foreach function
 * @return @c true to continue with the next iteration of the loop, 
 * \n @c false to break out of the loop.
 * @pre bt_adapter_foreach_bonded_device() will invoke this function.
 * 
 * @see bt_adapter_foreach_bonded_device()
 * 
 */
typedef bool (*bt_adapter_bonded_device_cb)(bt_device_info_s* device_info, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Called when the process of creating bond finishes.
 * @remarks If the remote user does not respond within 60 seconds, a time out will happen with #BT_ERROR_TIMED_OUT result code.\n
 * If bt_device_cancel_bonding() is called and it returns #BT_ERROR_NONE, then this callback function will be called 
 * with #BT_ERROR_CANCELLED result. \n
 * If creating a bond succeeds but service search fails, then this callback will be called with #BT_ERROR_SERVICE_SEARCH_FAILED.
 * In this case, you should try service search again by bt_device_start_service_search() to get the supported service list.
 *
 * @param[in] result The result of the bonding device
 * @param[in] device_info The device information which you creates bond with
 * @param[in] user_data The user data passed from the callback registration function
 * 
 * @pre Either bt_device_create_bond() will invoke this function 
 * if you register this callback using bt_device_set_bond_created_cb().
 *
 * @see bt_device_create_bond() 
 * @see bt_device_cancel_bonding()
 * @see bt_device_set_bond_created_cb()
 * @see bt_device_unset_bond_created_cb()
 */
typedef void (*bt_device_bond_created_cb)(int result, bt_device_info_s *device_info, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Called when the bond destroys. 
 * @param[in] result The result that a bond is destroyed
 * @param[in] remote_address The address of the remote Bluetooth device to destroy bond with
 * @param[in] user_data The user data passed from the callback registration function
 * @pre bt_device_destroy_bond() will invoke this function
 * if you register this callback using bt_device_set_bond_destroyed_cb().
 * 
 * @see bt_device_destroy_bond()
 * @see bt_device_set_bond_destroyed_cb()
 * @see bt_device_unset_bond_destroyed_cb()
 */
typedef void (*bt_device_bond_destroyed_cb)(int result, char *remote_address, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Called when the authorization of device changes. 
 * @param[in] authorization The authorization of device
 * @param[in] remote_address The address of the remote Bluetooth device which is (un)authorized
 * @param[in] user_data The user data passed from the callback registration function
 * @pre bt_device_set_authorization() will invoke this function if you register this callback using bt_device_set_authorization_changed_cb().
 *
 * @see bt_device_set_authorization()
 * @see #bt_device_set_authorization_changed_cb() 
 * @see #bt_device_unset_authorization_changed_cb()
 */
typedef void (*bt_device_authorization_changed_cb)
	(bt_device_authorization_e authorization, char *remote_address, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Called when the process of service search finishes. 
 * @remark If bt_device_cancel_service_search() is called and it returns #BT_ERROR_NONE, 
 * then this callback function will be called with #BT_ERROR_CANCELLED result.
 *
 * @param[in] result The result of the service searching
 * @param[in] sdp_info The structure of service lists found on a device
 * @param[in] user_data The user data passed from the callback registration function
 * @pre Either bt_device_start_service_search() will invoke this function 
 * if you register this callback using  bt_device_set_service_searched_cb().
 *
 * @see bt_device_start_service_search()
 * @see bt_device_cancel_service_search()
 * @see bt_device_set_service_searched_cb()
 * @see bt_device_unset_service_searched_cb()
 *
 */
typedef void (*bt_device_service_searched_cb)(int result, bt_device_sdp_info_s *sdp_info, void *user_data);

/** 
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Called when you receive data. 
 *
 * @param[in] data The received data from the remote device
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @pre When the connected remote Bluetooth device invokes bt_socket_send_data(),
 *		this function will be invoked if you register this function using bt_socket_set_data_received_cb(). 
 *
 * @see bt_socket_set_data_received_cb()
 * @see bt_socket_unset_data_received_cb()
 * @see bt_socket_send_data()
 */
typedef void (*bt_socket_data_received_cb)(bt_socket_received_data_s *data, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief  Called when the socket connection state changes.
 * @remarks  This function won't be invoked when you call bt_socket_disconnect_rfcomm(), which is synchronous function.
 *
 * @param[in] result The result of connection state changing
 * @param[in] connection_state The connection state
 * @param[in] connection The connection information which is established or disconnected
 * @param[in] user_data The user data passed from the callback registration function
 * @pre Either bt_socket_listen_and_accept_rfcomm() or bt_socket_connect_rfcomm() will invoke this function 
 * if you register this callback using bt_socket_set_connection_state_changed_cb(). \n
 * If the remote Bluetooth device is connected when bt_socket_destroy_rfcomm() is called, then bt_socket_connection_state_changed_cb() will be invoked.
 *
 * @see bt_socket_listen_and_accept_rfcomm()
 * @see bt_socket_connect_rfcomm()
 * @see bt_socket_set_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()
 */
typedef void (*bt_socket_connection_state_changed_cb)
	(int result, bt_socket_connection_state_e connection_state, bt_socket_connection_s *connection, void *user_data);


/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_MODULE
 * @brief Initializes the Bluetooth API.
 *
 * @remarks This function must be called before Bluetooth API starts. \n
 * You must free all resources of the Bluetooth service by calling bt_deinitialize() if Bluetooth service is no longer needed.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @see  bt_deinitialize()
 */
int bt_initialize(void);


/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_MODULE
 * @brief Releases all resources of the Bluetooth API.
 *
 * @remarks This function must be called if Bluetooth API is no longer needed. 
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre Bluetooth API must be initialized with bt_initialize().
 *
 * @see bt_initialize()
 */
int bt_deinitialize(void);


/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Enables the local Bluetooth adapter, asynchronously.
 *
 * @details This function enables Bluetooth protocol stack and hardware. 
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_ALREADY_DONE  Already enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation now in progress
 *
 * @pre Bluetooth service must be initialized with bt_initialize().
 * @post This function invokes bt_adapter_state_changed_cb().
 *
 * @see bt_initialize()
 * @see bt_adapter_get_state()
 * @see bt_adapter_disable()
 * @see bt_adapter_set_state_changed_cb()
 * @see bt_adapter_unset_state_changed_cb() 
 * @see bt_adapter_state_changed_cb()
 *
 */
int bt_adapter_enable(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Disables the local Bluetooth adapter, asynchronously. 
 *
 * @details This function disables Bluetooth protocol stack and hardware. 
 *
 * @remarks You should disable Bluetooth adapter to switch off Bluetooth chip, which is helpful for saving power.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation now in progress
 *
 * @pre Bluetooth API must be enabled with bt_adapter_enable().
 * @post This function invokes bt_adapter_state_changed_cb().
 *
 * @see bt_adapter_get_state()
 * @see bt_adapter_enable()
 * @see bt_adapter_state_changed_cb()
 * @see bt_adapter_set_state_changed_cb()
 * @see bt_adapter_unset_state_changed_cb ()
 *
 */
int bt_adapter_disable(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Gets the current state of local Bluetooth adapter.
 *
 * @param[out] adapter_state The current adapter state
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 *
 * @pre Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_initialize() 
 * @see bt_adapter_enable()
 * @see bt_adapter_disable()
 */
int bt_adapter_get_state(bt_adapter_state_e *adapter_state);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Gets the address of local Bluetooth adapter.
 *
 * @remarks The @a local_address must be released with free() by you.
 *
 * @param[out] local_address The device address of local Bluetooth adapter
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter 
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_OPERATION_FAILED Operation failed 
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable().
 * @see bt_adapter_enable()
 * @see bt_adapter_get_name()  
 */
int bt_adapter_get_address(char **local_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Gets the name of local Bluetooth adapter.
 *
 * @details Use this function to get the friendly name associated with Bluetooth 
 * device, retrieved by the remote Bluetooth devices.
 *
 * @remarks The @a local_name must be released with free() by you.
 *
 * @param[out] local_name  The local device name
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed 
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable().
 * 
 * @see bt_adapter_enable() 
 * @see bt_adapter_set_name() 
 */
int bt_adapter_get_name(char **local_name);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Sets the name of local Bluetooth adapter. 
 *
 * @param[in] local_name The name of the Bluetooth device. \n
 * 				The maximum length is 248 characters.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED Operation failed
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable().
 * @post bt_adapter_name_changed_cb() will be invoked if this function returns #BT_ERROR_NONE.
 * 
 * @see bt_adapter_enable()
 * @see bt_adapter_get_name()
 * @see bt_adapter_name_changed_cb()
 * @see bt_adapter_set_name_changed_cb()
 * @see bt_adapter_unset_name_changed_cb() 
 */
int bt_adapter_set_name(const char *local_name);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Gets the visibility mode of local Bluetooth adapter.
 *
 * @param[out] mode	The visibility mode of the Bluetooth device
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable(). 
 *
 * @see bt_adapter_enable() 
 * @see bt_adapter_set_visibility()
 */
int bt_adapter_get_visibility(bt_adapter_visibility_mode_e *mode);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Sets the visibility mode. 
 *
 * @remarks #BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE will change to #BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE 
 * after the given @a timeout_sec goes.
 *
 * @param[in] discoverable_mode The Bluetooth discoverable mode to set
 * @param[in] timeout_sec The discoverable time duration (in seconds)
 * 					@a timeout_sec is used only for #BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE mode.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable(). 
 * @post bt_adapter_visibility_mode_changed_cb() will be invoked if this function returns #BT_ERROR_NONE. 
 *
 * @see bt_adapter_enable()
 * @see bt_adapter_get_visibility()
 * @see bt_adapter_visibility_mode_changed_cb()
 * @see bt_adapter_set_visibility_mode_changed_cb()
 * @see bt_adapter_unset_visibility_mode_changed_cb() 
 */
int bt_adapter_set_visibility(bt_adapter_visibility_mode_e discoverable_mode, int timeout_sec);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Starts the device discovery, asynchronously. 
 *
 * @details If a device is discovered, bt_adapter_device_discovery_state_changed_cb() will be invoked 
 * with #BT_ADAPTER_DEVICE_DISCOVERY_FOUND, and then bt_adapter_device_discovery_state_changed_cb()
 * will be called with #BT_ADAPTER_DEVICE_DISCOVERY_FINISHED in case of the completion or cancellation of the discovery.
 *
 * @remarks To connect to peer Bluetooth device, you need to know its Bluetooth address. \n
 * The device discovery can be stopped by bt_adapter_stop_device_discovery().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation is now in progress 
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable(). 
 * @post This function invokes bt_adapter_device_discovery_state_changed_cb().
 *
 * @see bt_adapter_enable()
 * @see bt_adapter_is_discovering()
 * @see bt_adapter_stop_device_discovery()
 * @see bt_adapter_device_discovery_state_changed_cb()
 * @see bt_adapter_set_device_discovery_state_changed_cb()
 * @see bt_adapter_unset_device_discovery_state_changed_cb() 
 */
int bt_adapter_start_device_discovery(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Stops the device discovery, asynchronously. 
 * @remarks The device discovery process will take 10 ~ 20 seconds to get all the devices in vicinity. 
 * 
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOT_IN_PROGRESS  Operation is not in progress
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The device discovery must be in progress with bt_adapter_start_device_discovery(). 
 * @post This function invokes bt_adapter_device_discovery_state_changed_cb().
 *
 * @see bt_adapter_is_discovering() 
 * @see bt_adapter_start_device_discovery()
 * @see bt_adapter_set_device_discovery_state_changed_cb()
 * @see bt_adapter_unset_device_discovery_state_changed_cb()
 * @see bt_adapter_device_discovery_state_changed_cb()
 */
int bt_adapter_stop_device_discovery(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Checks for the device discovery is in progress or not.
 *
 * @remarks If Bluetooth discovery is in progress, other operations are not allowed and 
 * you have to either stop the discovery operation, or wait for it to be finished, 
 * before performing other operations.

 * @param[out] is_discovering The discovering status: (@c true = in progress , @c  false = not in progress )
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable(). 
 * 
 * @see bt_adapter_enable()
 * @see bt_adapter_start_device_discovery()
 * @see bt_adapter_stop_device_discovery()
 */
int bt_adapter_is_discovering(bool* is_discovering);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Retrieves the device information of all bonded devices. 
 * 
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data passed from the foreach function
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory 
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable(). 
 * @post This function invokes bt_adapter_bonded_device_cb().
 *
 * @see bt_adapter_bonded_device_cb()
 * @see bt_adapter_enable()
 */
int bt_adapter_foreach_bonded_device(bt_adapter_bonded_device_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Registers a callback function to be invoked when the Bluetooth adapter state changes.
 *
 * @param[in] callback	The callback function to invoke
 * @param[in] user_data	The user data to be passed to the callback function
 *
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 *
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @post bt_adapter_state_changed_cb() will be invoked.
 *
 * @see bt_initialize()
 * @see bt_adapter_state_changed_cb()
 * @see bt_adapter_set_state_changed_cb()
 * @see bt_adapter_unset_state_changed_cb()
 */
int bt_adapter_set_state_changed_cb(bt_adapter_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief	Unregisters the callback function.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 *
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 *
 * @see bt_initialize()
 * @see bt_adapter_set_state_changed_cb()
 */
int bt_adapter_unset_state_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Registers a callback function to be invoked when the name of Bluetooth adapter changes.
 *
 * @param[in] callback The callback function to invoke
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 *
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @post  bt_adapter_name_changed_cb() will be invoked.
 *
 * @see bt_initialize() 
 * @see bt_adapter_name_changed_cb()
 * @see bt_adapter_unset_name_changed_cb()
 */
int bt_adapter_set_name_changed_cb(bt_adapter_name_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief	Unregisters the callback function.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_initialize()
 * @see bt_adapter_set_name_changed_cb()
 */
int bt_adapter_unset_name_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Registers a callback function to be invoked when the visibility mode changes.
 *
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 *
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @post bt_adapter_visibility_mode_changed_cb() will be invoked.
 *
 * @see bt_initialize() 
 * @see bt_adapter_visibility_mode_changed_cb()
 * @see bt_adapter_unset_visibility_mode_changed_cb()
 */
int bt_adapter_set_visibility_mode_changed_cb(bt_adapter_visibility_mode_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief	Unregisters the callback function.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 *
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 *
 * @see bt_initialize() 
 * @see bt_adapter_set_visibility_mode_changed_cb()
 */
int bt_adapter_unset_visibility_mode_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Registers a callback function to be invoked when the device discovery state changes.
 *
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 *
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @post bt_adapter_device_discovery_state_changed_cb() will be invoked.
 *
 * @see bt_initialize() 
 * @see bt_adapter_device_discovery_state_changed_cb()
 * @see bt_adapter_set_device_discovery_state_changed_cb()
 * @see bt_adapter_unset_device_discovery_state_changed_cb() 
 */
int bt_adapter_set_device_discovery_state_changed_cb(bt_adapter_device_discovery_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief	Unregisters the callback function.
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_initialize() 
 * @see bt_adapter_set_device_discovery_state_changed_cb()  
 */
int bt_adapter_unset_device_discovery_state_changed_cb(void);


/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Creates a bond with a remote Bluetooth device, asynchronously. 
 *
 * @remarks A bond can be destroyed by bt_device_destroy_bond().\n
 * The bonding request can be cancelled by bt_device_cancel_bonding().
 *
 * @param[in] remote_address The address of the remote Bluetooth device with which the bond should be created
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_RESOURCE_BUSY  Device or resource busy
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable()
 * @pre The remote device must be discoverable with bt_adapter_start_device_discovery().
 * @post This function invokes bt_device_bond_created_cb().
 *
 * @see bt_adapter_enable()
 * @see bt_adapter_start_device_discovery()
 * @see bt_device_bond_created_cb()
 * @see bt_device_cancel_bonding()
 * @see bt_device_destroy_bond()
 * @see bt_device_set_bond_created_cb()
 * @see bt_device_unset_bond_created_cb() 
 */
int bt_device_create_bond(const char *remote_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Cancels the bonding process. 
 *
 * @remakrs Use this function when the remote Bluetooth device is not responding to the 
 * bond request or you wish to cancel the bonding request.
 * 
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOT_IN_PROGRESS  Operation not in progress
 * @pre The creating a bond must be in progress by bt_device_create_bond(). 
 *
 * @see bt_device_create_bond()
 * @see bt_device_bond_created_cb() 
 * @see bt_device_set_bond_created_cb()
 * @see bt_device_unset_bond_created_cb() 
 */
int bt_device_cancel_bonding(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Destroys the bond, asynchronously. 
 *
 * @param[in] remote_address The address of the remote Bluetooth device to remove bonding
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_RESOURCE_BUSY  Device or resource busy
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable().
 * @pre The bond with the remote device must be created with bt_device_create_bond(). 
 * @post This function invokes bt_device_bond_destroyed_cb().
 *
 * @see bt_adapter_enable()
 * @see bt_device_create_bond()
 * @see bt_device_bond_destroyed_cb()
 * @see bt_device_set_bond_destroyed_cb()
 * @see bt_device_unset_bond_destroyed_cb() 
 */
int bt_device_destroy_bond(const char *remote_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Sets an alias for the bonded device. 
 *
 * @param[in] remote_address The address of the remote Bluetooth device
 * @param[in] alias The alias of the remote Bluetooth device
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled 
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded 
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable().
 * @pre The bond with the remote device must be created with bt_device_create_bond(). 
 *
 * @see bt_adapter_enable()
 * @see bt_device_create_bond() 
 */
int bt_device_set_alias(const char *remote_address, const char *alias);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Sets the authorization of a bonded device, asynchronously. 
 *
 * @remarks Once a device is authorized, you don't need to receive a confirmation.
 * 
 * @param[in] remote_address The address of the remote Bluetooth device to authorize
 * @param[in] authorization The Bluetooth authorization state
 * 
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded 
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable().
 * @pre The bond with the remote device must be created with bt_device_create_bond(). 
 * @post bt_device_authorization_changed_cb() will be invoked.
 *
 * @see bt_adapter_enable()
 * @see bt_device_create_bond()  
 * @see bt_device_authorization_changed_cb()
 * @see bt_device_set_authorization_changed_cb()
 * @see bt_device_unset_authorization_changed_cb() 
 */
int bt_device_set_authorization(const char *remote_address, bt_device_authorization_e authorization_state);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Starts the search for services supported by the specified device, asynchronously.  
 *
 * @remarks If creating a bond succeeds, which means bt_device_bond_created_cb() is called with result #BT_ERROR_NONE,
 * then you don't need to run this function.\n
 * The service search takes a couple of seconds to complete normally. \n
 * The service search can be canceled by bt_device_cancel_service_search().
 *
 * @param[in] remote_address The address of the remote Bluetooth device whose services need to be checked
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded
 * @retval #BT_ERROR_SERVICE_SEARCH_FAILED  Service search failed
 * 
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable().
 * @pre The remote device must be discoverable with bt_adapter_start_device_discovery(). 
 * @pre The bond with the remote device must be created with bt_device_create_bond(). 
 * @post This function invokes bt_device_service_searched_cb().
 *
 * @see bt_adapter_enable()
 * @see bt_adapter_start_device_discovery()
 * @see bt_device_create_bond() 
 * @see bt_device_bond_created_cb()
 * @see bt_device_service_searched_cb()
 * @see bt_device_cancel_service_search()
 * @see bt_device_set_service_searched_cb()
 * @see bt_device_unset_service_searched_cb() 
 */
int bt_device_start_service_search(const char *remote_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Cancels service search process.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded 
 * @retval #BT_ERROR_NOT_IN_PROGRESS  Operation not in progress
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The service search must be in progress by bt_device_start_service_search(). 
 *
 * @see bt_device_start_service_search()
 * @see bt_device_service_searched_cb() 
 * @see bt_device_set_service_searched_cb()
 * @see bt_device_unset_service_searched_cb() 
 */
int bt_device_cancel_service_search(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Registers a callback function to be invoked when the bond creates.
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @post  bt_device_bond_created_cb() will be invoked. 
 * @see bt_initialize()
 * @see bt_device_bond_created_cb()
 * @see bt_device_unset_bond_created_cb()
 */
int bt_device_set_bond_created_cb(bt_device_bond_created_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief	Unregisters the callback function.
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @see bt_initialize() 
 * @see bt_device_set_bond_created_cb()
 */
int bt_device_unset_bond_created_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Registers a callback function to be invoked when the bond destroys.
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @post  bt_device_bond_destroyed_cb() will be invoked. 
 * @see bt_initialize() 
 * @see bt_device_bond_destroyed_cb()
 * @see bt_device_unset_bond_destroyed_cb()
 */
int bt_device_set_bond_destroyed_cb(bt_device_bond_destroyed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief	Unregisters the callback function.
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @see bt_initialize() 
 * @see bt_device_set_bond_destroyed_cb()
 */
int bt_device_unset_bond_destroyed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Registers a callback function to be invoked when the authorization of device changes.
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @post  bt_device_authorization_changed_cb() will be invoked. 
 * @see bt_initialize() 
 * @see bt_device_authorization_changed_cb()
 * @see bt_device_set_authorization_changed_cb() 
 * @see bt_device_unset_authorization_changed_cb()
 */
int bt_device_set_authorization_changed_cb(bt_device_authorization_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief	Unregisters the callback function.
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @see bt_initialize() 
 * @see bt_device_set_authorization_changed_cb()
 */
int bt_device_unset_authorization_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Registers a callback function to be invoked when the process of service search finishes.
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @post  bt_device_service_searched_cb() will be invoked. 
 * @see bt_initialize() 
 * @see bt_device_service_searched_cb()
 * @see bt_device_unset_service_searched_cb()
 */
int bt_device_set_service_searched_cb(bt_device_service_searched_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief	Unregisters the callback function.
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @see bt_initialize() 
 * @see bt_device_set_service_searched_cb()
 */
int bt_device_unset_service_searched_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Registers a rfcomm socket with a specific UUID. 
 *
 * @remarks A socket can be destroyed by bt_socket_destroy_rfcomm().
 *
 * @param[in] port_uuid The UUID of service to provide
 * @param[out] socket_fd A socket file descriptor to be used to communicate
 * @return 0 on success, otherwise a negative error value.
 *
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable(). 
 *
 * @see bt_adapter_enable() 
 * @see bt_socket_listen_and_accept_rfcomm()
 * @see bt_socket_destroy_rfcomm()
 */
int bt_socket_create_rfcomm(const char* port_uuid, int *socket_fd);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Removes the rfcomm socket with the given socket file descriptor.
 *
 * @param[in] socket_fd The socket file descriptor to destroy
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The socket must be created with bt_socket_create_rfcomm(). 
 * @post If callback function bt_socket_connection_state_changed_cb() is set and the remote Bluetooth device is connected,
 * then bt_socket_connection_state_changed_cb() will be called.
 *
 * @see bt_socket_create_rfcomm()
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()
 */
int bt_socket_destroy_rfcomm(int socket_fd);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Starts listening on passed rfcomm socket and accepts connection requests, asynchronously. 
 *
 * @param[in] socket_fd	The socket file descriptor on which start to listen
 * @param[in] max_pending_connections The maximum number of pending connections
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled 
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed 
 *
 * @pre The socket must be created with bt_socket_create_rfcomm(). 
 * @post This function invokes bt_socket_connection_state_changed_cb().
 *
 * @see bt_socket_create_rfcomm()
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb() 
 */
int bt_socket_listen_and_accept_rfcomm(int socket_fd, int max_pending_connections);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Connects to a specific RFCOMM based service on a remote Bluetooth device UUID, asynchronously.  
 *
 * @remarks A connection can be disconnected by bt_socket_disconnect_rfcomm(). 
 *
 * @param[in] remote_address The address of the remote Bluetooth device
 * @param[in] remote_port_uuid The UUID of service provided by the remote Bluetooth device
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED with bt_adapter_enable().
 * @pre The remote device must be discoverable with bt_adapter_start_device_discovery().
 * @pre The bond with the remote device must be created with bt_device_create_bond().  
 * @post This function invokes bt_socket_connection_state_changed_cb().
 * 
 * @see bt_adapter_enable()
 * @see bt_device_create_bond()
 * @see bt_adapter_start_device_discovery()
 * @see bt_device_start_service_search()
 * @see bt_socket_disconnect_rfcomm()
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()  
 */
int bt_socket_connect_rfcomm(const char *remote_address, const char* remote_port_uuid);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Disconnects the RFCOMM connection with the given socket file descriptor. 
 * @remarks Because this is a synchronous function, bt_socket_connection_state_changed_cb() won't be called
 * even though a connection is disconnected successfully. 
 *
 * @param[in] socket_fd The socket file descriptor to close
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled 
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 *
 * @pre The connection must be established with bt_socket_connect_rfcomm(). 
 * 
 * @see bt_socket_connect_rfcomm()
 */
int bt_socket_disconnect_rfcomm(int socket_fd);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Sends data to the connected device. 
 *
 * @param[in] socket_fd The connected socket 
 * @param[in] data The data to be sent
 * @param[in] length The length of data to be sent
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled 
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The connection must be established with either bt_socket_connect_rfcomm() or bt_socket_listen_and_accept_rfcomm(). 
 *
 * @see bt_socket_connect_rfcomm() 
 * @see bt_socket_listen_and_accept_rfcomm()
 */
int bt_socket_send_data(int socket_fd, const char* data, int length);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief  Register a callback function that will be invoked when you receive data.
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @post  bt_socket_data_received_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_socket_data_received_cb()
 * @see bt_socket_set_data_received_cb() 
 * @see bt_socket_unset_data_received_cb()
 */
int bt_socket_set_data_received_cb(bt_socket_data_received_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief	Unregisters the callback function.
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @see bt_initialize()
 * @see bt_socket_data_received_cb()
 * @see bt_socket_set_data_received_cb()
 */
int bt_socket_unset_data_received_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief  Register a callback function that will be invoked when the connection state changes.
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @post bt_socket_connection_state_changed_cb() will be invoked.
 * @see bt_initialize() 
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()
 */
int bt_socket_set_connection_state_changed_cb(bt_socket_connection_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief	Unregisters the callback function.
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @pre The Bluetooth service must be initialized with bt_initialize(). 
 * @see bt_initialize() 
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 */
int bt_socket_unset_connection_state_changed_cb(void);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __TIZEN_NETWORK_BLUETOOTH_H__
