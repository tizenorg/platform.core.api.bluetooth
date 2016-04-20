/*
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __TIZEN_NETWORK_BLUETOOTH_UNIT_TEST_H__
#define __TIZEN_NETWORK_BLUETOOTH_UNIT_TEST_H__


#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_LEN 49
#define MAX_SERVICES 10
#define PRT(format, args...) printf("%s:%d() "format, __FUNCTION__, __LINE__, ##args)
#define TC_PRT(format, args...) PRT(format"\n", ##args)

typedef enum {
	BT_UNIT_TEST_TABLE_MAIN = 1,
	BT_UNIT_TEST_TABLE_SET_ADDRESS,
	BT_UNIT_TEST_TABLE_ADAPTER,
	BT_UNIT_TEST_TABLE_ADAPTER_LE,
	BT_UNIT_TEST_TABLE_DEVICE,
	BT_UNIT_TEST_TABLE_SOCKET,
	BT_UNIT_TEST_TABLE_OPP,
	BT_UNIT_TEST_TABLE_AUDIO,
	BT_UNIT_TEST_TABLE_PAN,
	BT_UNIT_TEST_TABLE_GATT,
	BT_UNIT_TEST_TABLE_HPS,
	BT_UNIT_TEST_TABLE_AVRCP,
	BT_UNIT_TEST_TABLE_HID,
	BT_UNIT_TEST_TABLE_IPSP,
	BT_UNIT_TEST_TABLE_HDP,
	BT_UNIT_TEST_TABLE_DPM,
#ifdef TIZEN_WEARABLE
	BT_UNIT_TEST_TABLE_HF,
	BT_UNIT_TEST_TABLE_PBAP_CLIENT,
#endif
	BT_UNIT_TEST_TABLE_AUTOMATED_TEST,
	BT_UNIT_TEST_FUNCTION_INITIALIZE_ALL,
	BT_UNIT_TEST_TABLE_FINISH = 0xFF,
} bt_unit_test_table_e;

typedef enum {
	BT_UNIT_TEST_FUNCTION_BACK = 0,
	BT_UNIT_TEST_FUNCTION_SET_ADDRESS = 0,
	BT_UNIT_TEST_FUNCTION_INITIALIZE = 1,
	BT_UNIT_TEST_FUNCTION_DEINITIALIZE,
	BT_UNIT_TEST_FUNCTION_ADAPTER_GET_STATE = 1,
	BT_UNIT_TEST_FUNCTION_ADAPTER_ENABLE,
	BT_UNIT_TEST_FUNCTION_ADAPTER_DISABLE,
	BT_UNIT_TEST_FUNCTION_ADAPTER_RECOVER,
	BT_UNIT_TEST_FUNCTION_ADAPTER_START_DEVICE_DISCOVERY,
	BT_UNIT_TEST_FUNCTION_ADAPTER_STOP_DEVICE_DISCOVERY,
	BT_UNIT_TEST_FUNCTION_ADAPTER_IS_DISCOVERING,
	BT_UNIT_TEST_FUNCTION_ADAPTER_FOREACH_BONDED_DEVICE,
	BT_UNIT_TEST_FUNCTION_ADAPTER_GET_BONDED_DEVICE_INFO,
	BT_UNIT_TEST_FUNCTION_ADAPTER_IS_SERVICE_USED,
	BT_UNIT_TEST_FUNCTION_ADAPTER_GET_VISIBILITY,
	BT_UNIT_TEST_FUNCTION_ADAPTER_SET_DEVICE_DISCOVERY_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_UNSET_DEVICE_DISCOVERY_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_GET_LOCAL_OOB_DATA,
	BT_UNIT_TEST_FUNCTION_ADAPTER_SET_LOCAL_OOB_DATA,
	BT_UNIT_TEST_FUNCTION_ADAPTER_REMOVE_REMOTE_OOB_DATA,
	BT_UNIT_TEST_FUNCTION_ADAPTER_SET_VISIBILITY_MODE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_UNSET_VISIBILITY_MODE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_SET_VISIBILITY_DURATION_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_UNSET_VISIBILITY_DURATION_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_SET_CONNECTABLE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_UNSET_CONNECTABLE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_GET_CONNECTABLE,
	BT_UNIT_TEST_FUNCTION_ADAPTER_SET_CONNECTABLE,
	BT_UNIT_TEST_FUNCTION_ADAPTER_GET_VERSION,
	BT_UNIT_TEST_FUNCTION_ADAPTER_GET_LOCAL_INFO,
	BT_UNIT_TEST_FUNCTION_ADAPTER_SET_MANUFACTURER_DATA_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_UNSET_MANUFACTURER_DATA_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_SET_MANUFACTURER_DATA,
	BT_UNIT_TEST_FUNCTION_ADAPTER_SET_AUTHENTICATION_REQUSET_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_UNSET_AUTHENTICATION_REQUSET_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_PASSKEY_REPLY_ACCEPT,
	BT_UNIT_TEST_FUNCTION_ADAPTER_PASSKEY_REPLY_CANCEL,
	BT_UNIT_TEST_FUNCTION_ADAPTER_PASSKEY_CONFIRMATION_REPLY_ACCEPT,
	BT_UNIT_TEST_FUNCTION_ADAPTER_PASSKEY_CONFIRMATION_REPLY_REJECT,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_GET_STATE = 1,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_ENABLE,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_DISABLE,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_SET_SCAN_MODE,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_START_SCAN,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_STOP_SCAN,
#ifndef TIZEN_WEARABLE
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_START_DEVICE_DISCOVERY,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_STOP_DEVICE_DISCOVERY,
#endif
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_ADD_ADVERTISING_DATA,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_SET_ADVERTISING_MODE,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_SET_ADVERTISING_FILTER_POLICY,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_SET_ADVERTISING_CONNECTABLE,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_START_ADVERTISING_NEW,
#ifndef TIZEN_WEARABLE
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_START_ADVERTISING,
#endif
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_STOP_ADVERTISING,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_ADD_WHITE_LIST,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_REMOVE_WHITE_LIST,
#ifndef TIZEN_WEARABLE
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_CLEAR_WHITE_LIST,
#endif
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_ENABLE_PRIVACY,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_REGISTER_SCAN_FILTER_DEVICE_ADDRESS,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_REGISTER_SCAN_FILTER_SERVICE_UUID,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_REGISTER_SCAN_FILTER_SERVICE_SOLICITATION_UUID,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_UNREGISTER_ALL_SCAN_FILTERS,
#ifndef TIZEN_WEARABLE
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_SET_DEVICE_DISCOVERY_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_UNSET_DEVICE_DISCOVERY_STATE_CHANGED_CB,
#endif
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_READ_MAXIMUM_DATA_LENGTH,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_WRITE_HOST_SUGGESTED_DEFAULT_DATA_LENGTH,
	BT_UNIT_TEST_FUNCTION_ADAPTER_LE_READ_HOST_SUGGESTED_DEFAULT_DATA_LENGTH,
	BT_UNIT_TEST_FUNCTION_LE_DEVICE_SET_DATA_LENGTH,
	BT_UNIT_TEST_FUNCTION_LE_DEVICE_DATA_LENGTH_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_DEVICE_SET_AUTHORIZATION_TRUE = 1,
	BT_UNIT_TEST_FUNCTION_DEVICE_SET_AUTHORIZATION_FALSE,
	BT_UNIT_TEST_FUNCTION_DEVICE_SET_AUTHORIZATION_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_DEVICE_UNSET_AUTHORIZATION_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_DEVICE_SET_CONNECTION_STAET_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_DEVICE_UNSET_CONNECTION_STAET_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_DEVICE_FOREACH_CONNECTED_PROFILES,
	BT_UNIT_TEST_FUNCTION_DEVICE_IS_PROFILE_CONNECTED,
	BT_UNIT_TEST_FUNCTION_DEVICE_SET_BOND_CREATED_CB,
	BT_UNIT_TEST_FUNCTION_DEVICE_SET_BOND_DESTROYED_CB,
	BT_UNIT_TEST_FUNCTION_DEVICE_CREATE_BOND,
	BT_UNIT_TEST_FUNCTION_DEVICE_CREATE_BOND_BY_TYPE,
	BT_UNIT_TEST_FUNCTION_DEVICE_DESTROY_BOND,
	BT_UNIT_TEST_FUNCTION_DEVICE_ENABLE_RSSI_MONITOR,
	BT_UNIT_TEST_FUNCTION_DEVICE_DISABLE_RSSI_MONITOR,
	BT_UNIT_TEST_FUNCTION_DEVICE_GET_RSSI_STRENGTH,
	BT_UNIT_TEST_FUNCTION_DEVICE_GET_CONNECTION_STATE,
	BT_UNIT_TEST_FUNCTION_SOCKET_CREATE_RFCOMM = 1,
	BT_UNIT_TEST_FUNCTION_SOCKET_DESTROY_RFCOMM,
	BT_UNIT_TEST_FUNCTION_SOCKET_LISTEN_AND_ACCEPT_RFCOMM,
	BT_UNIT_TEST_FUNCTION_SOCKET_LISTEN,
	BT_UNIT_TEST_FUNCTION_SOCKET_ACCEPT,
	BT_UNIT_TEST_FUNCTION_SOCKET_REJECT,
	BT_UNIT_TEST_FUNCTION_SOCKET_CONNECT_RFCOMM,
	BT_UNIT_TEST_FUNCTION_SOCKET_DISCONNECT_RFCOMM,
	BT_UNIT_TEST_FUNCTION_SOCKET_SEND_DATA,
	BT_UNIT_TEST_FUNCTION_SOCKET_CREATE_RFCOMM_CUSTOM_UUID,
	BT_UNIT_TEST_FUNCTION_SOCKET_DESTROY_RFCOMM_CUSTOM_UUID,
	BT_UNIT_TEST_FUNCTION_SOCKET_LISTEN_AND_ACCEPT_RFCOMM_CUSTOM_UUID,
	BT_UNIT_TEST_FUNCTION_SOCKET_CONNECT_RFCOMM_CUSTOM_UUID,
	BT_UNIT_TEST_FUNCTION_SOCKET_DISCONNECT_RFCOMM_CUSTOM_UUID,
	BT_UNIT_TEST_FUNCTION_SOCKET_SEND_DATA_CUSTOM_UUID,
	BT_UNIT_TEST_FUNCTION_SOCKET_SET_DATA_RECEIVED_CB,
	BT_UNIT_TEST_FUNCTION_SOCKET_UNSET_DATA_RECEIVED_CB,
	BT_UNIT_TEST_FUNCTION_SOCKET_SET_CONNECTION_REQUESTED_CB,
	BT_UNIT_TEST_FUNCTION_SOCKET_UNSET_CONNECTION_REQUESTED_CB,
	BT_UNIT_TEST_FUNCTION_SOCKET_SET_CONNECTION_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_SOCKET_UNSET_CONNECTION_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_OPP_CLIENT_INITIALIZE = 1,
	BT_UNIT_TEST_FUNCTION_OPP_CLIENT_DEINITIALIZE,
	BT_UNIT_TEST_FUNCTION_OPP_CLIENT_ADD_FILE,
	BT_UNIT_TEST_FUNCTION_OPP_CLIENT_CLEAR_FILES,
	BT_UNIT_TEST_FUNCTION_OPP_CLIENT_PUSH_FILES,
	BT_UNIT_TEST_FUNCTION_OPP_CLIENT_CANCEL_PUSH,
	BT_UNIT_TEST_FUNCTION_AUDIO_INITIALIZE = 1,
	BT_UNIT_TEST_FUNCTION_AUDIO_DEINITIALIZE,
	BT_UNIT_TEST_FUNCTION_AUDIO_CONNECT,
	BT_UNIT_TEST_FUNCTION_AUDIO_DISCONNECT,
	BT_UNIT_TEST_FUNCTION_AUDIO_SINK_CONNECT,
	BT_UNIT_TEST_FUNCTION_AUDIO_SINK_DISCONNECT,
	BT_UNIT_TEST_FUNCTION_AUDIO_SET_CONNECTION_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AUDIO_UNSET_CONNECTION_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AG_OPEN_SCO,
	BT_UNIT_TEST_FUNCTION_AG_CLOSE_SCO,
	BT_UNIT_TEST_FUNCTION_AG_IS_SCO_OPENED,
	BT_UNIT_TEST_FUNCTION_AG_SET_SCO_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AG_UNSET_SCO_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AG_IS_CONNECTED,
	BT_UNIT_TEST_FUNCTION_AG_CALL_EVENT_IDLE,
	BT_UNIT_TEST_FUNCTION_AG_CALL_EVENT_ANSWERED,
	BT_UNIT_TEST_FUNCTION_AG_CALL_EVENT_DIALING,
	BT_UNIT_TEST_FUNCTION_AG_CALL_EVENT_ALERTING,
	BT_UNIT_TEST_FUNCTION_AG_CALL_EVENT_INCOMING,
	BT_UNIT_TEST_FUNCTION_CALL_LIST_CREATE,
	BT_UNIT_TEST_FUNCTION_CALL_LIST_DESTROY,
	BT_UNIT_TEST_FUNCTION_CALL_LIST_RESET,
	BT_UNIT_TEST_FUNCTION_CALL_LIST_ADD,
	BT_UNIT_TEST_FUNCTION_AG_NOTIFY_CALL_LIST,
	BT_UNIT_TEST_FUNCTION_AG_SET_CALL_HANDLING_EVENT_CB,
	BT_UNIT_TEST_FUNCTION_AG_IS_NREC_ENABLED,
	BT_UNIT_TEST_FUNCTION_AG_IS_WBS_MODE,
	BT_UNIT_TEST_FUNCTION_AG_SET_VENDOR_CMD_CB,
	BT_UNIT_TEST_FUNCTION_AG_UNSET_VENDOR_CMD_CB,
	BT_UNIT_TEST_FUNCTION_AG_NOTIFY_VENDOR_CMD,
	BT_UNIT_TEST_FUNCTION_A2DP_SET_CONTENT_PROTECTION_ENABLE,
	BT_UNIT_TEST_FUNCTION_A2DP_SET_CONTENT_PROTECTION_DISABLE,
	BT_UNIT_TEST_FUNCTION_NAP_ACTIVATE = 1,
	BT_UNIT_TEST_FUNCTION_NAP_DEACTIVATE,
	BT_UNIT_TEST_FUNCTION_NAP_DISCONNECT_ALL,
	BT_UNIT_TEST_FUNCTION_NAP_DISCONNECT,
	BT_UNIT_TEST_FUNCTION_PANU_SET_CONNECTION_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_PANU_CONNECT,
	BT_UNIT_TEST_FUNCTION_GATT_CONNECT = 1,
	BT_UNIT_TEST_FUNCTION_GATT_DISCONNECT,
	BT_UNIT_TEST_FUNCTION_SET_GATT_CONNECTION_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_UNSET_GATT_CONNECTION_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_GATT_CLIENT_CREATE,
	BT_UNIT_TEST_FUNCTION_GATT_CLIENT_DESTROY,
	BT_UNIT_TEST_FUNCTION_GATT_CLIENT_GET_REMOTE_ADDRESS,
	BT_UNIT_TEST_FUNCTION_GATT_CLIENT_PRINT_ALL,
	BT_UNIT_TEST_FUNCTION_GATT_CLIENT_READ_VALUE,
	BT_UNIT_TEST_FUNCTION_GATT_CLIENT_WRITE_VALUE,
	BT_UNIT_TEST_FUNCTION_GATT_CLIENT_SET_CHAR_VALUE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_GATT_CLIENT_UNSET_CHAR_VALUE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_GATT_CLIENT_FOREACH_SERVICES,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_INITIALIZE,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_DEINITIALIZE,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_UNREGISTER_ALL_SERVICES,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_FOREACH_SERVICES,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_REGISTER_BATTERY_SVC,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_CHANGE_BATTERY_LEVEL,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_REGISTER_HEART_RATE_SVC,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_NOTIFY_HEART_RATE_MEASUREMENT,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_REGISTER_THERMOMETER_SVC,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_CHANGE_THERMOMETER_MEASUREMENT,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_REGISTER_DEVICE_INFORMATION_SVC,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_REGISTER_LINK_LOSS_SVC,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_REGISTER_CUSTOM_SVC,
	BT_UNIT_TEST_FUNCTION_GATT_SERVER_CHANGE_CUSTOM_VAL,
	BT_UNIT_TEST_FUNCTION_GATT_START_SERVER,
	BT_UNIT_TEST_FUNCTION_ANCS_PAIR,
	BT_UNIT_TEST_FUNCTION_ANCS_WATCH,
	BT_UNIT_TEST_FUNCTION_ANCS_POSITIVE_ACTION,
	BT_UNIT_TEST_FUNCTION_ANCS_NEGATIVE_ACTION,
	BT_UNIT_TEST_FUNCTION_ANCS_GET_NOTI_ATTR,
#ifdef BT_ENABLE_LEGACY_GATT_CLIENT
	BT_UNIT_TEST_FUNCTION_GATT_FOREACH_PRIMARY_SERVICES,
	BT_UNIT_TEST_FUNCTION_GATT_DISCOVER_CHARACTERISTICS,
	BT_UNIT_TEST_FUNCTION_GATT_DISCOVER_CHARACTERISTIC_DESCRIPTORS,
	BT_UNIT_TEST_FUNCTION_GATT_GET_SERVICE_UUID,
	BT_UNIT_TEST_FUNCTION_GATT_FOREACH_INCLUDED_SERVICES,
	BT_UNIT_TEST_FUNCTION_GATT_SET_CHARACTERISTIC_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_GATT_UNSET_CHARACTERISTIC_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_GATT_GET_CHARACTERISTIC_DECLARATION,
	BT_UNIT_TEST_FUNCTION_GATT_SET_CHARACTERISTIC_VALUE,
	BT_UNIT_TEST_FUNCTION_GATT_SET_CHARACTERISTIC_VALUE_REQUEST,
	BT_UNIT_TEST_FUNCTION_GATT_READ_CHARACTERISTIC_VALUE,
	BT_UNIT_TEST_FUNCTION_GATT_WATCH_CHARACTERISTIC_CHANGES,
	BT_UNIT_TEST_FUNCTION_GATT_UNWATCH_CHARACTERISTIC_CHANGES,
#endif
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_CREATE = 1,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_DESTROY,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_PRINT_ALL,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_READ_VALUE,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_SET_URI,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_SET_HDR,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_SET_ENTITY,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_SET_CP,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_GET_URI,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_GET_HDR,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_GET_ENTITY,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_GET_SECURITY,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_SET_STATUS_NOTIFICATION,
	BT_UNIT_TEST_FUNCTION_HPS_CLIENT_UNSET_STATUS_NOTIFICATION,
	BT_UNIT_TEST_FUNCTION_AVRCP_TARGET_INITIALIZE = 1,
	BT_UNIT_TEST_FUNCTION_AVRCP_TARGET_DEINITIALIZE,
	BT_UNIT_TEST_FUNCTION_AVRCP_SET_EQUALIZER_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_SET_REPEAT_MODE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_SET_SHUFFLE_MODE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_SET_SCAN_MODE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_UNSET_EQUALIZER_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_UNSET_REPEAT_MODE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_UNSET_SHUFFLE_MODE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_UNSET_SCAN_MODE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_INITIALIZE,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_DEINITIALIZE,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_CONNECT,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_DISCONNECT,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_PLAY,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_STOP,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_PAUSE,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_FF,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_RW,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_NEXT,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_PREV,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_GET_REPEAT,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_SET_REPEAT,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_GET_SHUFFLE,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_SET_SHUFFLE,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_GET_POSITION,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_GET_PLAY_STATUS,
	BT_UNIT_TEST_FUNCTION_AVRCP_CONTROL_GET_TRACK_INFO,
	BT_UNIT_TEST_FUNCTION_AVRCP_SET_SONG_POSITION_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_SET_PLAY_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_SET_TRACK_INFO_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_UNSET_SONG_POSITION_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_UNSET_PLAY_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_AVRCP_UNSET_TRACK_INFO_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_HID_HOST_INITIALIZE = 1,
	BT_UNIT_TEST_FUNCTION_HID_HOST_DEINITIALIZE,
	BT_UNIT_TEST_FUNCTION_HID_HOST_CONNECT,
	BT_UNIT_TEST_FUNCTION_HID_HOST_DISCONNECT,
	BT_UNIT_TEST_FUNCTION_HID_DEVICE_ACTIVATE,
	BT_UNIT_TEST_FUNCTION_HID_DEVICE_CONNECT,
	BT_UNIT_TEST_FUNCTION_HID_DEVICE_DISCONNECT,
	BT_UNIT_TEST_FUCNTION_HID_DEVICE_DEACTIVATE,
	BT_UNIT_TEST_FUNCTION_HID_DEVICE_SEND_MOUSE_EVENT,
	BT_UNIT_TEST_FUNCTION_HID_DEVICE_SEND_KEY_EVENT,
	BT_UNIT_TEST_FUNCTION_HID_DEVICE_SET_DATA_RECEIVED_CB,
	BT_UNIT_TEST_FUNCTION_HID_DEVICE_UNSET_DATA_RECEIVED_CB,
	BT_UNIT_TEST_FUNCTION_IPSP_REGISTER = 1,
	BT_UNIT_TEST_FUNCTION_IPSP_UNREGISTER,
	BT_UNIT_TEST_FUNCTION_IPSP_INITIALIZE,
	BT_UNIT_TEST_FUNCTION_IPSP_DEINITIALIZE,
	BT_UNIT_TEST_FUNCTION_IPSP_CONNECT,
	BT_UNIT_TEST_FUNCTION_IPSP_DISCONNECT,
	BT_UNIT_TEST_FUNCTION_IPSP_START_ADVERTISING,
	BT_UNIT_TEST_FUNCTION_IPSP_SET_CONNECTION_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_IPSP_UNSET_CONNECTION_STATE_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_HDP_REGISTER_SINK_APP = 1,
	BT_UNIT_TEST_FUNCTION_HDP_UNREGISTER_SINK_APP,
	BT_UNIT_TEST_FUNCTION_HDP_CONNECT_TO_SOURCE,
	BT_UNIT_TEST_FUNCTION_HDP_DISCONNECT,
	BT_UNIT_TEST_FUNCTION_HDP_SEND_DATA,
	BT_UNIT_TEST_FUNCTION_HDP_SET_CONNECTION_CB,
	BT_UNIT_TEST_FUNCTION_HDP_UNSET_CONNECTION_CB,
	BT_UNIT_TEST_FUNCTION_HDP_SET_DATA_RECEIVED_CB,
	BT_UNIT_TEST_FUNCTION_HDP_UNSET_DATA_RECEIVED_CB,
	BT_UNIT_TEST_FUNCTION_DPM_SET_DEFAULT_POLICIES = 1,
	BT_UNIT_TEST_FUNCTION_DPM_SET_ALLOW_BLUETOOTH_MODE,
	BT_UNIT_TEST_FUNCTION_DPM_GET_ALLOW_BLUETOOTH_MODE,
	BT_UNIT_TEST_FUNCTION_DPM_ACTIVATE_DEVICE_RESTRICTION,
	BT_UNIT_TEST_FUNCTION_DPM_IS_DEVICE_RESTRICTIO_ACTIVATE,
	BT_UNIT_TEST_FUNCTION_DPM_ACTIVATE_UUID_RESTRICTION,
	BT_UNIT_TEST_FUNCTION_DPM_IS_UUID_RESTRICTIO_ACTIVATE,
	BT_UNIT_TEST_FUNCTION_DPM_ADD_DEVICES_TO_BLACKLIST,
	BT_UNIT_TEST_FUNCTION_DPM_ADD_DEVICES_TO_WHITELIST,
	BT_UNIT_TEST_FUNCTION_DPM_ADD_UUIDS_TO_BLACKLIST,
	BT_UNIT_TEST_FUNCTION_DPM_ADD_UUIDS_TO_WHITELIST,
	BT_UNIT_TEST_FUNCTION_DPM_GET_DEVICES_FROM_BLACKLIST,
	BT_UNIT_TEST_FUNCTION_DPM_GET_DEVICES_FROM_WHITELIST,
	BT_UNIT_TEST_FUNCTION_DPM_GET_UUIDS_FROM_BLACKLIST,
	BT_UNIT_TEST_FUNCTION_DPM_GET_UUIDS_FROM_WHITELIST,
	BT_UNIT_TEST_FUNCTION_DPM_CLEAR_DEVICES_FROM_BLACKLIST,
	BT_UNIT_TEST_FUNCTION_DPM_CLEAR_DEVICES_FROM_WHITELIST,
	BT_UNIT_TEST_FUNCTION_DPM_CLEAR_UUIDS_FROM_BLACKLIST,
	BT_UNIT_TEST_FUNCTION_DPM_CLEAR_UUIDS_FROM_WHITELIST,
	BT_UNIT_TEST_FUNCTION_DPM_REMOVE_DEVICE_FROM_BLACKLIST,
	BT_UNIT_TEST_FUNCTION_DPM_REMOVE_DEVICE_FROM_WHITELIST,
	BT_UNIT_TEST_FUNCTION_DPM_REMOVE_UUIDS_FROM_BLACKLIST,
	BT_UNIT_TEST_FUNCTION_DPM_REMOVE_UUIDS_FROM_WHITELIST,
	BT_UNIT_TEST_FUNCTION_DPM_SET_ALLOW_OUTGOING_CALL,
	BT_UNIT_TEST_FUNCTION_DPM_GET_ALLOW_OUTGOING_CALL,
	BT_UNIT_TEST_FUNCTION_DPM_SET_PAIRING_STATE,
	BT_UNIT_TEST_FUNCTION_DPM_GET_PAIRING_STATE,
	BT_UNIT_TEST_FUNCTION_DPM_SET_PROFILE_STATE,
	BT_UNIT_TEST_FUNCTION_DPM_GET_PROFILE_STATE,
	BT_UNIT_TEST_FUNCTION_DPM_SET_DESKTOP_CONNECTIVITY_STATE,
	BT_UNIT_TEST_FUNCTION_DPM_GET_DESKTOP_CONNECTIVITY_STATE,
	BT_UNIT_TEST_FUNCTION_DPM_SET_DISCOVERABLE_STATE,
	BT_UNIT_TEST_FUNCTION_DPM_GET_DISCOVERABLE_STATE,
	BT_UNIT_TEST_FUNCTION_DPM_SET_LIMITED_DISCOVERABLE_STATE,
	BT_UNIT_TEST_FUNCTION_DPM_GET_LIMITED_DISCOVERABLE_STATE,
	BT_UNIT_TEST_FUNCTION_DPM_SET_DATA_TRANSFER_STATE,
	BT_UNIT_TEST_FUNCTION_DPM_GET_DATA_TRANSFER_STATE,
#ifdef TIZEN_WEARABLE
	BT_UNIT_TEST_FUNCTION_HF_INITIALIZE = 1,
	BT_UNIT_TEST_FUNCTION_HF_DEINITIALIZE,
	BT_UNIT_TEST_FUNCTION_HF_NOTIFY_CALL_ANSWER,
	BT_UNIT_TEST_FUNCTION_HF_NOTIFY_CALL_INIT,
	BT_UNIT_TEST_FUNCTION_HF_NOTIFY_CALL_TERM,
	BT_UNIT_TEST_FUNCTION_HF_GET_CALL_STATUS_INFO_LIST,
	BT_UNIT_TEST_FUNCTION_HF_SET_CALL_EVENT_CB,
	BT_UNIT_TEST_FUNCTION_HF_UNSET_CALL_EVENT_CB,
	BT_UNIT_TEST_FUNCTION_HF_SET_CALL_STATUS_UPDATED_EVENT_CB,
	BT_UNIT_TEST_FUNCTION_HF_UNSET_CALL_STATUS_UPDATED_EVENT_CB,
	BT_UNIT_TEST_FUNCTION_HF_NOTIFY_SPEAKER_GAIN,
	BT_UNIT_TEST_FUNCTION_HF_SET_SPEAKER_GAIN_CB,
	BT_UNIT_TEST_FUNCTION_HF_UNSET_SPEAKER_GAIN_CB,
	BT_UNIT_TEST_FUNCTION_HF_NOTIFY_VOICE_REC_TRUE,
	BT_UNIT_TEST_FUNCTION_HF_NOTIFY_VOICE_REC_FALSE,
	BT_UNIT_TEST_FUNCTION_HF_IS_SCO_OPENED,
	BT_UNIT_TEST_FUNCTION_HF_GET_CODEC_ID,
	BT_UNIT_TEST_FUNCTION_HF_SET_SCO_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_HF_UNSET_SCO_CHANGED_CB,
	BT_UNIT_TEST_FUNCTION_HF_NOTIFY_VENDOR_CMD,
	BT_UNIT_TEST_FUNCTION_HF_SET_VENDOR_CMD_EVENT_CB,
	BT_UNIT_TEST_FUNCTION_HF_UNSET_VENDOR_CMD_EVENT_CB,
	BT_UNIT_TEST_FUNCTION_PBAP_CLIENT_INITIALIZE = 1,
	BT_UNIT_TEST_FUNCTION_PBAP_CLIENT_DEINITIALIZE,
	BT_UNIT_TEST_FUNCTION_PBAP_CLIENT_CONNECT,
	BT_UNIT_TEST_FUNCTION_PBAP_CLIENT_DISCONNECT,
	BT_UNIT_TEST_FUNCTION_PBAP_CLIENT_GETSIZE,
	BT_UNIT_TEST_FUNCTION_PBAP_CLIENT_PHONEBOOKPULL,
	BT_UNIT_TEST_FUNCTION_PBAP_CLIENT_VCARDLIST,
	BT_UNIT_TEST_FUNCTION_PBAP_CLIENT_VCARDPULL,
	BT_UNIT_TEST_FUNCTION_PBAP_CLIENT_PHONEBOOKSEARCH,
	BT_UNIT_TEST_FUNCTION_PBAP_CLIENT_VCARDLIST_MAXLIST_ZERO,
#endif
	BT_UNIT_TEST_FUNCTION_ON_OFF_REPEAT_TEST = 1,
	BT_UNIT_TEST_FUNCTION_ON_OFF_REPEAT_TEST_1_SEC_DELAY,
	BT_UNIT_TEST_FUNCTION_ON_OFF_REPEAT_TEST_N_SEC_DELAY,

	BT_UNIT_TEST_FUNCTION_ACTIVATE_FLAG_TO_SET_PARAMETERS = 0XFF,
} bt_unit_test_function_e;

typedef struct {
	const char *tc_name;
	int tc_code;
} tc_table_t;

typedef struct {
	int param_count;
	char **params;
} tc_params_t;

#define BT_UNIT_TEST_PARAM_TYPE_BOOL		"bool(true, false)"
#define BT_UNIT_TEST_PARAM_TYPE_INT		"int(1, 2, 10, 777...)"
#define BT_UNIT_TEST_PARAM_TYPE_FLOAT		"float(1.5, 0.625...)"
#define BT_UNIT_TEST_PARAM_TYPE_STRING		"string(abc, HAHA..)"
#define BT_UNIT_TEST_PARAM_TYPE_BYTE_ARRAY	"byte array(03FF0102, 0015836CF7B2...)"

int test_input_callback(void *data);

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_NETWORK_BLUETOOTH_UNIT_TEST_H__ */
