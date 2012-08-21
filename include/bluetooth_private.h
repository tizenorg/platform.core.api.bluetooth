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


#ifndef __TIZEN_NETWORK_BLUETOOTH_PRIVATE_H__
#define __TIZEN_NETWORK_BLUETOOTH_PRIVATE_H__

#include <dlog.h>
#include <stdbool.h>
#include <bluetooth-api.h>
#include <bluetooth-audio-api.h>
#include <bluetooth-media-control.h>
#include <bluetooth-hid-api.h>

#include "bluetooth.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OPP_UUID "00001105-0000-1000-8000-00805f9b34fb"

/**
 * @internal
 * @brief Bluetooth callback.
 */
typedef enum
{
	BT_EVENT_STATE_CHANGED = 0x00, /**< Adapter state is changed */
	BT_EVENT_NAME_CHANGED, /**< Adapter name is changed */
	BT_EVENT_VISIBILITY_MODE_CHANGED, /**< Adapter visibility mode is changed */
	BT_EVENT_DEVICE_DISCOVERY_STATE_CHANGED, /**< Device discovery state is changed */
	BT_EVENT_BOND_CREATED, /**< A bond is created */
	BT_EVENT_BOND_DESTROYED, /**< A bond is destroyed */
	BT_EVENT_AUTHORIZATION_CHANGED, /**< Authorization is changed */
	BT_EVENT_SERVICE_SEARCHED, /**< Service search finish */
	BT_EVENT_DATA_RECEIVED, /**< Data is received */
	BT_EVENT_CONNECTION_STATE_CHANGED, /**< Connection state is changed */
	BT_EVENT_RFCOMM_CONNECTION_REQUESTED, /**< RFCOMM connection is requested */
	BT_EVENT_OPP_CONNECTION_REQUESTED, /**< OPP connection is requested */
	BT_EVENT_OPP_PUSH_REQUESTED, /**< OPP push is requested */
	BT_EVENT_OPP_SERVER_TRANSFER_PROGRESS, /**< OPP transfer progress */
	BT_EVENT_OPP_SERVER_TRANSFER_FINISHED, /**< OPP transfer is completed */
	BT_EVENT_OPP_CLIENT_PUSH_RESPONSED, /**< OPP client connection is reponsed */
	BT_EVENT_OPP_CLIENT_PUSH_PROGRESS, /**< OPP client push progress */
	BT_EVENT_OPP_CLIENT_PUSH_FINISHED, /**< OPP client push is finished */
	BT_EVENT_PAN_CONNECTION_STATE_CHANGED, /**< PAN connection change */
	BT_EVENT_NAP_CONNECTION_STATE_CHANGED, /**< NAP connection change */
	BT_EVENT_HDP_CONNECTED, /**< HDP connection change */
	BT_EVENT_HDP_DISCONNECTED, /**< HDP disconnection change */
	BT_EVENT_HDP_DATA_RECIEVED, /**< HDP Data recieve Callabck */
	BT_EVENT_AUDIO_CONNECTION_STATUS, /**< Audio Connection change callback */
	BT_EVENT_AG_MICROPHONE_GAIN_CHANGE, /**< Audio Microphone change callback */
	BT_EVENT_AG_SPEAKER_GAIN_CHANGE, /**< Audio Speaker gain change callback */
	BT_EVENT_AVRCP_CONNECTION_STATUS, /**< AVRCP connection change callback */
	BT_EVENT_HID_CONNECTION_STATUS /**< HID connection status callback */
} bt_event_e;

/**
 * @internal
 */
typedef struct bt_event_sig_event_slot_s
{
    int event_type;
    const void *callback;
    void *user_data;
} bt_event_sig_event_slot_s;


#define BT_CHECK_INPUT_PARAMETER(arg) \
	if (arg == NULL) \
	{ \
		LOGE("[%s] INVALID_PARAMETER(0x%08x)", __FUNCTION__, BT_ERROR_INVALID_PARAMETER); \
		return BT_ERROR_INVALID_PARAMETER; \
	}

/**
 * @internal
 * @brief Check the initialzating status
 */
int _bt_check_init_status(void);

#define BT_CHECK_INIT_STATUS() \
	if (_bt_check_init_status() == BT_ERROR_NOT_INITIALIZED) \
	{ \
		LOGE("[%s] NOT_INITIALIZED(0x%08x)", __FUNCTION__, BT_ERROR_NOT_INITIALIZED); \
		return BT_ERROR_NOT_INITIALIZED; \
	}

/**
 * @internal
 * @brief Set the event callback.
 */
void _bt_set_cb(int events, void *callback, void *user_data);

/**
 * @internal
 * @brief Unset the event callback.
 */
void _bt_unset_cb(int events);

/**
 * @internal
 * @brief Check if the event callback exist or not.
 */
bool _bt_check_cb(int events);

/**
 * @internal
 * @brief Convert Bluetooth F/W error codes to capi Bluetooth error codes.
 */
int _bt_get_error_code(int origin_error);


/**
 * @internal
 * @brief Convert Bluetooth F/W bluetooth_device_info_t to capi bt_device_info_s.
 */
int _bt_get_bt_device_info_s(bt_device_info_s **dest_dev, bluetooth_device_info_t *source_dev);


/**
 * @internal
 * @brief Free bt_device_info_s.
 */
void _bt_free_bt_device_info_s(bt_device_info_s *device_info);

/**
 * @internal
 * @brief Convert Bluetooth F/W bluetooth_device_address_t to string.
 */
int _bt_convert_address_to_string(char **addr_str, bluetooth_device_address_t *addr_hex);


/**
 * @internal
 * @brief Convert string to Bluetooth F/W bluetooth_device_address_t.
 */
void _bt_convert_address_to_hex(bluetooth_device_address_t *addr_hex, const char *addr_str);


/**
 * @internal
 * @brief Convert error code to string.
 */
char* _bt_convert_error_to_string(int error);

/**
 * @internal
 * @brief Convert the visibility mode
 */
bt_adapter_visibility_mode_e _bt_get_bt_visibility_mode_e(bluetooth_discoverable_mode_t mode);

/**
 * @internal
 * @brief Since the Audio call back and event proxy call backs have different prototype it is wrapper function.
 */
void _bt_audio_event_proxy(int event, bt_audio_event_param_t *param, void *user_data);

/**
 * @internal
 * @brief Since the AVRCP call back and event proxy call backs have different prototype it is wrapper function.
 */
void _bt_avrcp_event_proxy(int event, media_event_param_t *param, void *user_data);

/**
 * @internal
 * @brief Since the HID call back and event proxy call backs have different prototype it is wrapper function.
 */
void _bt_hid_event_proxy(int event, hid_event_param_t *param, void *user_data);


#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_NETWORK_BLUETOOTH_PRIVATE_H__ */
