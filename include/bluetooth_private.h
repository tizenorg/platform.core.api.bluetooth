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

#ifdef __cplusplus
extern "C" {
#endif

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
} bt_event_e;

/**
 * @internal
 */
struct bt_event_sig_event_slot_s
{
    int event_type;
    const void* callback;
    void* user_data;
};

/**
 * @internal
 * @brief Proxy of platform events.
 */
void _bt_event_proxy(int event, bluetooth_event_param_t *param, void *user_data);

/**
 * @internal
 * @brief Registers a new callback.
 */
void _bt_set_cb(int events, void *callback, void *user_data);

/**
 * @internal
 * @brief Removes callback function form callback registry.
 */
void _bt_unset_cb(int events);

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
void _bt_convert_address_to_hex(bluetooth_device_address_t* addr_hex, const char* addr_str);


/**
 * @internal
 * @brief Convert Bluetooth F/W bt_sdp_info_t to capi bt_device_sdp_info_s.
 */
int _bt_get_bt_device_sdp_info_s(bt_device_sdp_info_s **dest, bt_sdp_info_t *source);


/**
 * @internal
 * @brief Free bt_device_sdp_info_s.
 */
void _bt_free_bt_device_sdp_info_s(bt_device_sdp_info_s *sdp_info);

/**
 * @internal
 * @brief Convert bluetooth_discoverable_mode_t into bt_adapter_visibility_mode_e.
 */
bt_adapter_visibility_mode_e _bt_get_bt_adapter_visibility_mode_e(bluetooth_discoverable_mode_t mode);

/**
 * @internal
 * @brief Convert Bluetooth F/W bluetooth_device_info_t to capi bt_adapter_device_discovery_info_s.
 */
int _bt_get_bt_adapter_device_discovery_info_s
	(bt_adapter_device_discovery_info_s **discovery_info, bluetooth_device_info_t *source_info);

/**
 * @internal
 * @brief Free bt_adapter_device_discovery_info_s.
 */
void _bt_free_bt_adapter_device_discovery_info_s(bt_adapter_device_discovery_info_s *discovery_info);

/**
 * @internal
 * @brief Get index of callback.
 */
int _bt_get_cb_index(int event);

/**
 * @internal
 * @brief Copy service list.
 */
int _bt_copy_service_list(bt_device_info_s *bonded_device_info, bt_device_sdp_info_s *sdp_info);

/**
 * @internal
 * @brief Convert error code to string.
 */
char* _bt_convert_error_to_string(int error);

/**
 * @internal
 * @brief Convert lower case to upper case in origin.
 */
void _bt_convert_lower_to_upper(char* origin);

	
#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_NETWORK_BLUETOOTH_PRIVATE_H__ */
