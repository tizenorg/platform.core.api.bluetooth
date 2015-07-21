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
#include <bluetooth-telephony-api.h>
#include <bluetooth-media-control.h>
#include <bluetooth-hid-api.h>

#include "bluetooth.h"
#include "bluetooth_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

#undef LOG_TAG
#define LOG_TAG "CAPI_NETWORK_BLUETOOTH"

#define BT_INFO(fmt, args...) SLOGI(fmt, ##args)
#define BT_DBG(fmt, args...) SLOGD(fmt, ##args)
#define BT_ERR(fmt, args...) SLOGE(fmt, ##args)

#define OPP_UUID "00001105-0000-1000-8000-00805f9b34fb"

/**
 * @internal
 * @brief Bluetooth callback.
 */
typedef enum
{
	BT_EVENT_STATE_CHANGED = 0x00, /**< Adapter state is changed */
	BT_EVENT_LE_STATE_CHANGED, /**< Adapter le state is changed */
	BT_EVENT_NAME_CHANGED, /**< Adapter name is changed */
	BT_EVENT_VISIBILITY_MODE_CHANGED, /**< Adapter visibility mode is changed */
	BT_EVENT_VISIBILITY_DURATION_CHANGED, /**< Adapter visibility duration is changed */
	BT_EVENT_DEVICE_DISCOVERY_STATE_CHANGED, /**< Device discovery state is changed */
	BT_EVENT_LE_DEVICE_DISCOVERY_STATE_CHANGED, /**< LE Device discovery state is changed */
	BT_EVENT_LE_SCAN_RESULT_UPDATED, /**< LE Scan result is updated */
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
	BT_EVENT_HDP_DATA_RECEIVED, /**< HDP Data receive Callabck */
	BT_EVENT_AUDIO_CONNECTION_STATUS, /**< Audio Connection change callback */
	BT_EVENT_AG_SCO_CONNECTION_STATUS, /**< Audio - AG SCO Connection state change callback */
	BT_EVENT_AG_CALL_HANDLING_EVENT, /**< Audio - AG call event callback */
	BT_EVENT_AG_MULTI_CALL_HANDLING_EVENT, /**< Audio - AG 3-way call event callback */
	BT_EVENT_AG_DTMF_TRANSMITTED, /**< Audio - DTMF tone sending request */
	BT_EVENT_AG_MICROPHONE_GAIN_CHANGE, /**< Audio Microphone change callback */
	BT_EVENT_AG_SPEAKER_GAIN_CHANGE, /**< Audio Speaker gain change callback */
	BT_EVENT_AG_VENDOR_CMD, /**< Audio - XSAT Vendor cmd */
	BT_EVENT_AVRCP_CONNECTION_STATUS, /**< AVRCP connection change callback */
	BT_EVENT_AVRCP_EQUALIZER_STATE_CHANGED, /**< AVRCP equalizer state change callback */
	BT_EVENT_AVRCP_REPEAT_MODE_CHANGED, /**< AVRCP repeat mode change callback */
	BT_EVENT_AVRCP_SHUFFLE_MODE_CHANGED, /**< AVRCP equalizer mode change callback */
	BT_EVENT_AVRCP_SCAN_MODE_CHANGED, /**< AVRCP scan mode change callback */
	BT_EVENT_AVRCP_PLAY_STATUS_CHANGED, /**< AVRCP scan mode change callback */
	BT_EVENT_AVRCP_SONG_POSITION_CHANGED, /**< AVRCP scan mode change callback */
	BT_EVENT_AVRCP_TRACK_INFO_CHANGED, /**< AVRCP scan mode change callback */
	BT_EVENT_HID_CONNECTION_STATUS, /**< HID connection status callback */
	BT_EVENT_HID_DEVICE_CONNECTION_STATUS, /**< HID Device connection status callback */
	BT_EVENT_HID_DEVICE_DATA_RECEIVED, /**< HID Device Data received callback */
	BT_EVENT_DEVICE_CONNECTION_STATUS, /**< Device connection status callback */
	BT_EVENT_GATT_CONNECTION_STATUS, /** < GATT connection status callback */
	BT_EVENT_GATT_CLIENT_SERVICE_DISCOVERED, /** GATT services discovered callback */
	BT_EVENT_GATT_CLIENT_VALUE_CHANGED, /**< GATT characteristic value changed callback */
	BT_EVENT_GATT_CLIENT_READ_CHARACTERISTIC, /**< GATT characteristic value read callback */
	BT_EVENT_GATT_CLIENT_WRITE_CHARACTERISTIC, /**< GATT characteristic value write callback */
	BT_EVENT_GATT_CLIENT_READ_DESCRIPTOR, /**< GATT descriptor value read callback */
	BT_EVENT_GATT_CLIENT_WRITE_DESCRIPTOR, /**< GATT descriptor value write callback */
	BT_EVENT_GATT_SERVER_READ_REQUESTED, /**< GATT Characteristic/Descriptor Read Requested callback*/
#ifdef BT_ENABLE_LEGACY_GATT_CLIENT
	BT_EVENT_GATT_CLIENT_CHARACTERISTIC_DISCOVERED_LEGACY, /**< GATT characteristic discovered callback */
	BT_EVENT_GATT_CLIENT_CHARACTERISTIC_DESCRIPTOR_DISCOVERED_LEGACY, /**< GATT characteristic descriptor discovered callback */
	BT_EVENT_GATT_CLIENT_VALUE_CHANGED_LEGACY, /**< GATT characteristic value changed callback */
	BT_EVENT_GATT_CLIENT_READ_CHARACTERISTIC_LEGACY, /**< GATT characteristic value read callback */
	BT_EVENT_GATT_CLIENT_WRITE_CHARACTERISTIC_LEGACY, /**< GATT characteristic value write callback */
#endif
	BT_EVENT_ADVERTISING_STATE_CHANGED, /**< Advertising state changed callback */
	BT_EVENT_MANUFACTURER_DATA_CHANGED, /**< Manufacturer data changed callback */
	BT_EVENT_CONNECTABLE_CHANGED_EVENT, /**< Adapter connectable changed callback */
	BT_EVENT_RSSI_ENABLED_EVENT, /**< RSSI Enabled callback */
	BT_EVENT_RSSI_ALERT_EVENT, /**< RSSI Alert callback */
	BT_EVENT_GET_RSSI_EVENT, /**< Get RSSI Strength callback */
#ifdef TIZEN_WEARABLE
	BT_EVENT_PBAP_CONNECTION_STATUS, /**< PBAP connection status callback */
	BT_EVENT_PBAP_PHONEBOOK_SIZE, /**< PBAP Phonebook Size status callback */
	BT_EVENT_PBAP_PHONEBOOK_PULL, /**< PBAP Phonebook Pull status callback */
	BT_EVENT_PBAP_VCARD_LIST, /**< PBAP vCard List status callback */
	BT_EVENT_PBAP_VCARD_PULL, /**< PBAP vCard Pull status callback */
	BT_EVENT_PBAP_PHONEBOOK_SEARCH, /**< PBAP Phonebook Search status callback */
	BT_EVENT_HF_SCO_CONNECTION_STATUS, /**< Audio - HF SCO Connection state change callback */
	BT_EVENT_HF_SPEAKER_GAIN_CHANGE, /**< Audio - HF Speaker gain change callback */
	BT_EVENT_HF_CALL_HANDLING_EVENT, /**< Audio - HF call event callback */
	BT_EVENT_HF_VENDOR_DEP_CMD_EVENT, /**< Audio - HF Vendor Command callback */
	BT_EVENT_HF_MULTI_CALL_HANDLING_EVENT, /**< Audio - HF 3-way call event callback */
	BT_EVENT_HF_CALL_STATUS_UPDATED_EVENT, /**< Audio - HF call status updated callback */
#endif
	BT_EVENT_MAX
} bt_event_e;

typedef enum {
	BT_GATT_ROLE_SERVER = 0x01,
	BT_GATT_ROLE_CLIENT = 0x02,
} bt_gatt_role_e;

/**
 * @internal
 */
typedef enum {
	BT_ADAPTER_LE_ADVERTISING_DATA_INCOMP_LIST_16_BIT_SERVICE_CLASS_UUIDS = 0x02, /**<Incomplete list of 16 bit UUIDs */
	BT_ADAPTER_LE_ADVERTISING_DATA_COMP_LIST_16_BIT_SERVICE_CLASS_UUIDS = 0x03, /**< Complete list of 16 bit UUIDs */
	BT_ADAPTER_LE_ADVERTISING_DATA_INCOMP_LIST_128_BIT_SERVICE_CLASS_UUIDS = 0x06, /**< Incomplete list of 128 bit UUIDs */
	BT_ADAPTER_LE_ADVERTISING_DATA_COMP_LIST_128_BIT_SERVICE_CLASS_UUIDS = 0x07, /**< Complete list of 128 bit UUID */
	BT_ADAPTER_LE_ADVERTISING_DATA_SHORT_LOCAL_NAME = 0x08, /**<Shortened local name */
	BT_ADAPTER_LE_ADVERTISING_DATA_LOCAL_NAME = 0x09, /**<Complete local name */
	BT_ADAPTER_LE_ADVERTISING_DATA_TX_POWER_LEVEL = 0x0a, /**< TX-Power level*/
	BT_ADAPTER_LE_ADVERTISING_DATA_16_BIT_SERVICE_SOLICITATION_UUIDS = 0x14, /**< List of 16-bit Service Solicitation UUIDs*/
	BT_ADAPTER_LE_ADVERTISING_DATA_128_BIT_SERVICE_SOLICITATION_UUIDS = 0x15, /**< List of 128-bit Service Solicitation UUIDs*/
	BT_ADAPTER_LE_ADVERTISING_DATA_SERVICE_DATA = 0x16, /**< Service data */
	BT_ADAPTER_LE_ADVERTISING_DATA_APPEARANCE = 0x19, /**< Appearance*/
	BT_ADAPTER_LE_ADVERTISING_DATA_MANUFACTURER_SPECIFIC_DATA = 0xff, /**< Manufacturer data */
} bt_adapter_le_advertising_data_type_e;

/**
 * @internal
 */
 typedef struct {
	bt_adapter_le_advertising_mode_e mode;
	bt_adapter_le_advertising_filter_policy_e filter_policy;
	bt_adapter_le_advertising_type_e type;
} bt_adapter_le_advertising_parameters_s;

typedef struct {
	int handle;

	bt_adapter_le_advertising_state_changed_cb cb;
	void *user_data;

	bt_adapter_le_advertising_parameters_s adv_params;

	unsigned int adv_data_len;
	char *adv_data;
	unsigned int adv_system_data_len;

	unsigned int scan_rsp_data_len;
	char *scan_rsp_data;
	unsigned int scan_rsp_system_data_len;
} bt_advertiser_s;

typedef struct {
	int slot_id;
	char *device_address;
	char *device_name;
	char *service_uuid;
	char *service_uuid_mask;
	char *service_solicitation_uuid;
	char *service_solicitation_uuid_mask;
	char *service_data_uuid;
	char *service_data;
	unsigned int service_data_len;
	char *service_data_mask;
	int manufacturer_id;
	char *manufacturer_data;
	unsigned int manufacturer_data_len;
	char *manufacturer_data_mask;
} bt_le_scan_filter_s;

/**
 * @internal
 */
typedef struct bt_event_sig_event_slot_s
{
    const void *callback;
    void *user_data;
} bt_event_sig_event_slot_s;

typedef struct {
	GSList *services;
} bt_gatt_server_s;

typedef struct {
	GSList *services;
	char *remote_address;
	bool services_discovered;
} bt_gatt_client_s;

typedef struct {
	bt_gatt_type_e type;
	bt_gatt_role_e role;
	void *parent;
	char *path;
	char *uuid;
} bt_gatt_common_s;

typedef struct {
	bt_gatt_type_e type;
	bt_gatt_role_e role;
	void *parent;
	char *path;
	char *uuid;

	bool is_included_service;

	bt_gatt_service_type_e service_type;

	GSList *included_services;
	GSList *characteristics;
} bt_gatt_service_s;

typedef struct {
	bt_gatt_type_e type;
	bt_gatt_role_e role;
	void *parent;
	char *path;
	char *uuid;

	int permissions;
	int properties;
	bt_gatt_write_type_e write_type;

	GSList *descriptors;

	bt_gatt_client_characteristic_value_changed_cb value_changed_cb;
	void *value_changed_user_data;

	bt_gatt_server_value_changed_cb server_value_changed_cb;
	void *server_value_changed_user_data;

	bt_gatt_server_read_value_requested_cb read_requested_cb;
	void *read_requested_user_data;

	int value_length;
	char *value;
} bt_gatt_characteristic_s;

typedef struct {
	bt_gatt_type_e type;
	bt_gatt_role_e role;
	void *parent;
	char *path;
	char *uuid;

	int permissions;

	int value_length;
	char *value;
} bt_gatt_descriptor_s;

typedef struct {
	bt_gatt_client_h client;
	bt_gatt_h gatt_handle;
	void *user_data;

	/*
	 * Temp callback. Once bluez's discover service issue is fixed,
	 * it will be removed
	 */
	bt_gatt_client_request_completed_cb cb;
} bt_gatt_client_cb_data_s;

typedef void (*_bt_gatt_client_value_changed_cb)(char *char_path,
		unsigned char *value, int value_length, void *user_data);

#define BT_CHECK_INPUT_PARAMETER(arg) \
	if (arg == NULL) \
	{ \
		LOGE("[%s] INVALID_PARAMETER(0x%08x)", __FUNCTION__, BT_ERROR_INVALID_PARAMETER); \
		return BT_ERROR_INVALID_PARAMETER; \
	}

#ifdef TIZEN_BT_DISABLE
#define BT_CHECK_BT_SUPPORT() \
        { \
                LOGE("[%s] NOT_SUPPORTED(0x%08x)", __FUNCTION__, BT_ERROR_NOT_SUPPORTED); \
                return BT_ERROR_NOT_SUPPORTED; \
        }
#else
#define BT_CHECK_BT_SUPPORT()
#endif

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

#define BT_CHECK_ADAPTER_STATUS() \
	if (bluetooth_check_adapter() == BLUETOOTH_ADAPTER_DISABLED) \
	{ \
		LOGE("[%s] BT_ERROR_NOT_ENABLED(0x%08x)", __FUNCTION__, BT_ERROR_NOT_ENABLED); \
		return BT_ERROR_NOT_ENABLED; \
	}

/**
 * @internal
 * @brief Initialize Bluetooth LE adapter
 */
int _bt_le_adapter_init(void);

/**
 * @internal
 * @brief Deinitialize Bluetooth LE adapter
 */
int _bt_le_adapter_deinit(void);

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

#ifdef TIZEN_WEARABLE
/**
 * @internal
 * @brief Since the HF call back and event proxy call backs have different prototype it is wrapper function.
 */
void _bt_hf_event_proxy(int event, bt_hf_event_param_t *param, void *user_data);
#endif

/**
 * @internal
 * @brief Since the Telephony call back and event proxy call backs have different prototype it is wrapper function.
 */
void _bt_telephony_event_proxy(int event, telephony_event_param_t *param, void *user_data);

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

void _bt_adapter_le_invoke_advertising_state_cb(int handle, int result, bt_adapter_le_advertising_state_e adv_state);

#ifdef BT_ENABLE_LEGACY_GATT_CLIENT
bool _bt_gatt_is_legacy_client_mode(void);
#endif

const GSList* _bt_gatt_get_client_list(void);

const GSList* _bt_gatt_get_server_list(void);

int _bt_gatt_client_update_all(bt_gatt_client_h client);

/* HID device related type */
typedef struct
{
        unsigned char btcode;
        unsigned char rep_id;
        unsigned char button;
        signed char axis_x;
        signed char axis_y;
        signed char axis_z;
} bt_hid_mouse_data_s;

typedef struct
{
        unsigned char btcode;
        unsigned char rep_id;
        unsigned char modify;
        unsigned char key[8];
} bt_hid_key_data_s;

typedef enum {
        BT_HID_HEADER_HANDSHAKE,
        BT_HID_HEADER_HID_CONTROL,
        BT_HID_HEADER_GET_REPORT,
        BT_HID_HEADER_SET_REPORT,
        BT_HID_HEADER_GET_PROTOCOL,
        BT_HID_HEADER_SET_PROTOCOL,
        BT_HID_HEADER_DATA,
        BT_HID_HEADER_UNKNOWN
} bluetooth_hid_header_type_t;

typedef enum {
        BT_HID_PARAM_DATA_RTYPE_INPUT,
        BT_HID_PARAM_DATA_RTYPE_OUTPUT
} bluetooth_hid_param_type_t;

typedef struct
{
        const char *address;
        bluetooth_hid_header_type_t type;
        bluetooth_hid_param_type_t param;
        int data_size;  /**< The length of the received data */
        const char *data;     /**< The received data */
} bt_hid_device_received_data_s;

typedef void (*bt_hid_device_connection_state_changed_cb) (int result,
                bool connected, const char *remote_address, void *user_data);

typedef void (*bt_hid_device_data_received_cb)(const bt_hid_device_received_data_s *data, void *user_data);
/* HID device related type */

#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_NETWORK_BLUETOOTH_PRIVATE_H__ */
