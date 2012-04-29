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

#include <glib.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dlog.h>
#include <stdio.h>
#include <stdbool.h>
#include <bluetooth.h>
#include <bluetooth-api.h>
#include <bluetooth_private.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "TIZEN_N_BLUETOOTH"

static bool is_initialized = false;
static bt_event_sig_event_slot_s bt_event_slot_container[] = {
	{BT_EVENT_STATE_CHANGED, NULL, NULL},
	{BT_EVENT_NAME_CHANGED, NULL, NULL},
	{BT_EVENT_VISIBILITY_MODE_CHANGED, NULL, NULL},
	{BT_EVENT_DEVICE_DISCOVERY_STATE_CHANGED, NULL, NULL},
	{BT_EVENT_BOND_CREATED, NULL, NULL},
	{BT_EVENT_BOND_DESTROYED, NULL, NULL},
	{BT_EVENT_AUTHORIZATION_CHANGED, NULL, NULL},
	{BT_EVENT_SERVICE_SEARCHED, NULL, NULL},
	{BT_EVENT_DATA_RECEIVED, NULL, NULL},
	{BT_EVENT_CONNECTION_STATE_CHANGED, NULL, NULL},
};

/*
 *  Internal Macros
 */
#define BT_CHECK_INIT_STATUS() \
	if( is_initialized != true ) \
	{ \
		LOGE("[%s] NOT_INITIALIZED(0x%08x)", __FUNCTION__, BT_ERROR_NOT_INITIALIZED); \
		return BT_ERROR_NOT_INITIALIZED; \
	}

#define BT_CHECK_INPUT_PARAMETER(arg) \
	if( arg == NULL ) \
	{ \
		LOGE("[%s] INVALID_PARAMETER(0x%08x)", __FUNCTION__, BT_ERROR_INVALID_PARAMETER); \
		return BT_ERROR_INVALID_PARAMETER; \
	}

/*
 *  Internal Functions
 */
static void __bt_event_proxy(int event, bluetooth_event_param_t *param, void *user_data);
static void __bt_set_cb(int events, void *callback, void *user_data);
static void __bt_unset_cb(int events);
static int __bt_get_cb_index(int event);
static void __bt_convert_lower_to_upper(char* origin);
static bt_adapter_visibility_mode_e __bt_get_bt_adapter_visibility_mode_e(bluetooth_discoverable_mode_t mode);
static int __bt_get_bt_device_sdp_info_s(bt_device_sdp_info_s **dest, bt_sdp_info_t *source);
static void __bt_free_bt_device_sdp_info_s(bt_device_sdp_info_s *sdp_info);
static int __bt_get_bt_adapter_device_discovery_info_s(bt_adapter_device_discovery_info_s **discovery_info, bluetooth_device_info_t *source_info);
static void __bt_free_bt_adapter_device_discovery_info_s(bt_adapter_device_discovery_info_s *discovery_info);

/*
 *  Public Functions
 */
int bt_initialize(void)
{
	if (is_initialized != true) {
		if (bluetooth_register_callback(&__bt_event_proxy, NULL) != BLUETOOTH_ERROR_NONE) {
			LOGE("[%s] OPERATION_FAILED(0x%08x)", __FUNCTION__, BT_ERROR_OPERATION_FAILED);
			return BT_ERROR_OPERATION_FAILED;
		}
		is_initialized = true;
	}

	return BT_ERROR_NONE;
}

int bt_deinitialize(void)
{
	BT_CHECK_INIT_STATUS();
	if (bluetooth_unregister_callback() != BLUETOOTH_ERROR_NONE) {
		LOGE("[%s] OPERATION_FAILED(0x%08x)", __FUNCTION__, BT_ERROR_OPERATION_FAILED);
		return BT_ERROR_OPERATION_FAILED;
	}
	is_initialized = false;

	return BT_ERROR_NONE;
}

int bt_adapter_enable(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code( bluetooth_enable_adapter() );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
}

int bt_adapter_disable(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code( bluetooth_disable_adapter() );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
}

int bt_adapter_get_state(bt_adapter_state_e *adapter_state)
{
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(adapter_state);

	*adapter_state = bluetooth_check_adapter();
	return BT_ERROR_NONE;
}

int bt_adapter_get_address(char **address)
{
	bluetooth_device_address_t loc_address = { {0} };
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(address);

	error_code = _bt_get_error_code( bluetooth_get_local_address(&loc_address) );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
		return error_code;
	}

	error_code = _bt_convert_address_to_string(address, &loc_address);
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
		return error_code;
	}

	return BT_ERROR_NONE;
}

int bt_adapter_get_name(char** name)
{
	int ret = BT_ERROR_NONE;
	bluetooth_device_name_t loc_name = { {0} };

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(name);

	ret = _bt_get_error_code( bluetooth_get_local_name(&loc_name) );
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
		return ret;
	}

	*name = strdup(loc_name.name);
	if (*name == NULL) {
		LOGE("[%s] OUT_OF_MEMORY(0x%08x)", __FUNCTION__, BT_ERROR_OUT_OF_MEMORY);
		return BT_ERROR_OUT_OF_MEMORY; 
	}

	return BT_ERROR_NONE;
}

int bt_adapter_set_name(const char* name)
{
	bluetooth_device_name_t loc_name = { {0} };
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(name);

	strncpy(loc_name.name, name, BLUETOOTH_DEVICE_NAME_LENGTH_MAX);
	loc_name.name[BLUETOOTH_DEVICE_NAME_LENGTH_MAX] = '\0';

	ret = _bt_get_error_code( bluetooth_set_local_name(&loc_name) );
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_adapter_get_visibility(bt_adapter_visibility_mode_e *mode)
{
	bluetooth_discoverable_mode_t discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_CONNECTABLE;
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(mode);

	ret = _bt_get_error_code( bluetooth_get_discoverable_mode(&discoverable_mode) );
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
		return ret;
	}

	*mode = __bt_get_bt_adapter_visibility_mode_e(discoverable_mode);
	return BT_ERROR_NONE;
}

int bt_adapter_set_visibility(bt_adapter_visibility_mode_e visibility_mode, int timeout_sec)
{
	bluetooth_discoverable_mode_t discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_CONNECTABLE;
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	switch (visibility_mode) {
		case BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE :
			discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_TIME_LIMITED_DISCOVERABLE;
			break;
		case BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE :
			discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_CONNECTABLE;
			timeout_sec = 0;
			break;
		case BT_ADAPTER_VISIBILITY_MODE_GENERAL_DISCOVERABLE :
			discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_GENERAL_DISCOVERABLE;
			timeout_sec = 0;
			break;
		default:
			LOGE("[%s] INVALID_PARAMETER(0x%08x)", __FUNCTION__, BT_ERROR_INVALID_PARAMETER);
			return BT_ERROR_INVALID_PARAMETER;
	}

	error_code = _bt_get_error_code( bluetooth_set_discoverable_mode(discoverable_mode, timeout_sec) );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}

	return error_code;
}

int bt_device_create_bond(const char* device_address)
{
	bluetooth_device_address_t addr_hex = {{0,}};
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(device_address);

	_bt_convert_address_to_hex(&addr_hex, device_address);
	error_code = _bt_get_error_code( bluetooth_bond_device(&addr_hex) );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}

	return error_code;
}

int bt_device_cancel_bonding(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code( bluetooth_cancel_bonding() );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}

	return error_code;
}

int bt_device_destroy_bond(const char *device_address)
{
	bluetooth_device_address_t addr_hex = {{0,}};
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(device_address);

	_bt_convert_address_to_hex(&addr_hex, device_address);
	error_code = _bt_get_error_code( bluetooth_unbond_device(&addr_hex) );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}

	return error_code;
}

int bt_adapter_foreach_bonded_device(bt_adapter_bonded_device_cb foreach_cb, void *user_data)
{
	GPtrArray* dev_list = NULL;
	bt_device_info_s* dev_info = NULL;
	bluetooth_device_info_t* ptr = NULL;
	int ret = BT_ERROR_NONE;
	int i = 0;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(foreach_cb);

	dev_list = g_ptr_array_new();
	if (dev_list == NULL) {
		LOGE("[%s] OUT_OF_MEMORY(0x%08x)", __FUNCTION__, BT_ERROR_OUT_OF_MEMORY);
		return BT_ERROR_OUT_OF_MEMORY;
	}

	ret = _bt_get_error_code( bluetooth_get_bonded_device_list(&dev_list) );
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x) : Failed to get bonded device list", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
		return ret;
	}

	for (i = 0; i < dev_list->len; i++) {
		ptr = g_ptr_array_index(dev_list, i);
		if (ptr != NULL) {
			ret = _bt_get_bt_device_info_s(&dev_info, (bluetooth_device_info_t*)ptr);
			if (ret != BT_ERROR_NONE) {
				LOGE("[%s] %s(0x%08x) : Failed to get device info", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
				break;
			}

			if (!foreach_cb(dev_info, user_data)) {
				_bt_free_bt_device_info_s(dev_info);
				break;
			}
			_bt_free_bt_device_info_s(dev_info);
		} else {
			LOGE("[%s] OPERATION_FAILED(0x%08x)", __FUNCTION__, BT_ERROR_OPERATION_FAILED);
			ret = BT_ERROR_OPERATION_FAILED;
			break;
		}
	}

	if (dev_list != NULL) {
		g_ptr_array_free(dev_list, TRUE);
	}

	return ret;
}

int bt_device_set_alias(const char* device_address, const char* alias)
{
	bluetooth_device_address_t addr_hex = {{0,}};
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(device_address);
	BT_CHECK_INPUT_PARAMETER(alias);

	_bt_convert_address_to_hex(&addr_hex, device_address);
	error_code = _bt_get_error_code( bluetooth_set_alias(&addr_hex, alias) );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
}

int bt_device_set_authorization(const char *device_address, bt_device_authorization_e authorization)
{
	bluetooth_device_address_t addr_hex = {{0,}};
	gboolean trusted = FALSE;
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(device_address);

	_bt_convert_address_to_hex(&addr_hex, device_address);
	if( authorization == BT_DEVICE_AUTHORIZED )
		trusted = TRUE;

	error_code = _bt_get_error_code( bluetooth_authorize_device(&addr_hex, trusted) );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
}

int bt_device_start_service_search(const char * device_address)
{
	bluetooth_device_address_t addr_hex = {{0,}};
	int ret = 0;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(device_address);

	_bt_convert_address_to_hex(&addr_hex, device_address);
	ret = _bt_get_error_code( bluetooth_search_service(&addr_hex) );

	// In service search, BT_ERROR_SERVICE_SEARCH_FAILED is returned instead of BT_ERROR_OPERATION_FAILED.
	if( ret == BT_ERROR_OPERATION_FAILED )
		ret = BT_ERROR_SERVICE_SEARCH_FAILED;

	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}
	return ret;
}

int bt_device_cancel_service_search(void)
{
	int ret = 0;

	BT_CHECK_INIT_STATUS();
	ret = _bt_get_error_code( bluetooth_cancel_service_search() );
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_socket_create_rfcomm(const char* uuid, int *socket_fd)
{
	int ret = 0;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(uuid);
	BT_CHECK_INPUT_PARAMETER(socket_fd);

	ret = bluetooth_rfcomm_create_socket(uuid);
	if (ret < 0) {
		ret = _bt_get_error_code(ret);
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
		return ret;
	} else {
		*socket_fd = ret;
		return BT_ERROR_NONE;
	}
}

int bt_socket_destroy_rfcomm(int socket_fd)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code( bluetooth_rfcomm_remove_socket(socket_fd, 0) );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}

	return error_code;
}

int bt_socket_listen_and_accept_rfcomm(int socket_fd, int max_pending_connection)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	ret = _bt_get_error_code( bluetooth_rfcomm_listen_and_accept(socket_fd,max_pending_connection) );
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_socket_connect_rfcomm(const char* remote_address, const char* remote_port_uuid)
{
	bluetooth_device_address_t addr_hex = {{0,}};
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address);
	BT_CHECK_INPUT_PARAMETER(remote_port_uuid);

	_bt_convert_address_to_hex(&addr_hex, remote_address);

	error_code = _bt_get_error_code( bluetooth_rfcomm_connect(&addr_hex, remote_port_uuid) );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}

	return error_code;
}

int bt_socket_disconnect_rfcomm(int socket_fd)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();

	ret = _bt_get_error_code( bluetooth_rfcomm_disconnect(socket_fd) );
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_socket_send_data(int socket_fd, const char* data, int length)
{
	int ret = 0;

	BT_CHECK_INIT_STATUS();
	ret = bluetooth_rfcomm_write(socket_fd, data, length);
	if (ret == BLUETOOTH_ERROR_NOT_IN_OPERATION) {
		LOGE("[%s] OPERATION_FAILED(0x%08x)", __FUNCTION__, BT_ERROR_OPERATION_FAILED);
		return BT_ERROR_OPERATION_FAILED;
	}

	ret = _bt_get_error_code(ret);
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_adapter_set_state_changed_cb(bt_adapter_state_changed_cb callback, void* user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	__bt_set_cb(BT_EVENT_STATE_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_adapter_set_name_changed_cb(bt_adapter_name_changed_cb callback, void* user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	__bt_set_cb(BT_EVENT_NAME_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_adapter_set_visibility_mode_changed_cb(bt_adapter_visibility_mode_changed_cb callback, void* user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	__bt_set_cb(BT_EVENT_VISIBILITY_MODE_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_adapter_set_device_discovery_state_changed_cb(bt_adapter_device_discovery_state_changed_cb callback, void* user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	__bt_set_cb(BT_EVENT_DEVICE_DISCOVERY_STATE_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_device_set_bond_created_cb(bt_device_bond_created_cb callback, void* user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	__bt_set_cb(BT_EVENT_BOND_CREATED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_device_set_bond_destroyed_cb(bt_device_bond_destroyed_cb callback, void* user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	__bt_set_cb(BT_EVENT_BOND_DESTROYED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_device_set_authorization_changed_cb(bt_device_authorization_changed_cb callback, void* user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	__bt_set_cb(BT_EVENT_AUTHORIZATION_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_device_set_service_searched_cb(bt_device_service_searched_cb callback, void* user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	__bt_set_cb(BT_EVENT_SERVICE_SEARCHED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_socket_set_data_received_cb(bt_socket_data_received_cb callback, void* user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	__bt_set_cb(BT_EVENT_DATA_RECEIVED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_socket_set_connection_state_changed_cb(bt_socket_connection_state_changed_cb callback, void* user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	__bt_set_cb(BT_EVENT_CONNECTION_STATE_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_adapter_unset_state_changed_cb(void)
{
	BT_CHECK_INIT_STATUS();
	__bt_unset_cb(BT_EVENT_STATE_CHANGED);
	return BT_ERROR_NONE;
}

int bt_adapter_unset_name_changed_cb(void)
{
	BT_CHECK_INIT_STATUS();
	__bt_unset_cb(BT_EVENT_NAME_CHANGED);
	return BT_ERROR_NONE;
}

int bt_adapter_unset_visibility_mode_changed_cb(void)
{
	BT_CHECK_INIT_STATUS();
	__bt_unset_cb(BT_EVENT_VISIBILITY_MODE_CHANGED);
	return BT_ERROR_NONE;
}

int bt_adapter_unset_device_discovery_state_changed_cb(void)
{
	BT_CHECK_INIT_STATUS();
	__bt_unset_cb(BT_EVENT_DEVICE_DISCOVERY_STATE_CHANGED);
	return BT_ERROR_NONE;
}

int bt_device_unset_bond_created_cb(void)
{
	BT_CHECK_INIT_STATUS();
	__bt_unset_cb(BT_EVENT_BOND_CREATED);
	return BT_ERROR_NONE;
}

int bt_device_unset_bond_destroyed_cb(void)
{
	BT_CHECK_INIT_STATUS();
	__bt_unset_cb(BT_EVENT_BOND_DESTROYED);
	return BT_ERROR_NONE;
}

int bt_device_unset_authorization_changed_cb(void)
{
	BT_CHECK_INIT_STATUS();
	__bt_unset_cb(BT_EVENT_AUTHORIZATION_CHANGED);
	return BT_ERROR_NONE;
}

int bt_device_unset_service_searched_cb(void)
{
	BT_CHECK_INIT_STATUS();
	__bt_unset_cb(BT_EVENT_SERVICE_SEARCHED);
	return BT_ERROR_NONE;
}

int bt_socket_unset_data_received_cb(void)
{
	BT_CHECK_INIT_STATUS();
	__bt_unset_cb(BT_EVENT_DATA_RECEIVED);
	return BT_ERROR_NONE;
}

int bt_socket_unset_connection_state_changed_cb(void)
{
	BT_CHECK_INIT_STATUS();
	__bt_unset_cb(BT_EVENT_CONNECTION_STATE_CHANGED);
	return BT_ERROR_NONE;
}

int bt_adapter_start_device_discovery(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code( bluetooth_start_discovery(0, 0, BLUETOOTH_DEVICE_MAJOR_MASK_MISC) );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
}

int bt_adapter_stop_device_discovery(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code( bluetooth_cancel_discovery() );
	if (error_code != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
}

int bt_adapter_is_discovering(bool* is_discovering)
{
	int ret = 0;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(is_discovering);

	ret = bluetooth_is_discovering();
	if (ret >= BLUETOOTH_ERROR_BASE) {
		*is_discovering = (ret == 1)?true:false;
		return BT_ERROR_NONE;
	} else {
		ret = _bt_get_error_code(ret);
		LOGE("[%s] %s(0x%08x)", __FUNCTION__, _bt_convert_error_to_string(ret), ret);
		return ret;
	}
}

/*
 *  Internal Functions
 */
static void __bt_set_cb(int events, void* callback, void* user_data)
{
	bt_event_slot_container[events].callback = callback;
	bt_event_slot_container[events].user_data = user_data;
}

static void __bt_unset_cb(int events)
{
	if (bt_event_slot_container[events].callback != NULL) {
		bt_event_slot_container[events].callback = NULL;
		bt_event_slot_container[events].user_data = NULL;
	}
}

int _bt_get_error_code(int origin_error)
{
	switch (origin_error) {
		case BLUETOOTH_ERROR_NONE:
			return BT_ERROR_NONE;
		case BLUETOOTH_ERROR_INVALID_DATA:
		case BLUETOOTH_ERROR_INVALID_PARAM:
		case BLUETOOTH_ERROR_NOT_CONNECTED:
		case BLUETOOTH_ERROR_NOT_SUPPORT:
			return BT_ERROR_INVALID_PARAMETER;
		case BLUETOOTH_ERROR_MEMORY_ALLOCATION:
		case BLUETOOTH_ERROR_OUT_OF_MEMORY:
			return BT_ERROR_OUT_OF_MEMORY;
		case BLUETOOTH_ERROR_TIMEOUT:
			return BT_ERROR_TIMED_OUT;
		case BLUETOOTH_ERROR_DEVICE_NOT_ENABLED:
			return BT_ERROR_NOT_ENABLED;
		case BLUETOOTH_ERROR_DEVICE_ALREADY_ENABLED:
			return BT_ERROR_ALREADY_DONE;
		case BLUETOOTH_ERROR_NOT_PAIRED:
			return BT_ERROR_REMOTE_DEVICE_NOT_BONDED;
		case BLUETOOTH_ERROR_NOT_IN_OPERATION:
			return BT_ERROR_NOT_IN_PROGRESS;
		case BLUETOOTH_ERROR_IN_PROGRESS:
			return BT_ERROR_NOW_IN_PROGRESS;
		case BLUETOOTH_ERROR_DEVICE_BUSY:
			return BT_ERROR_RESOURCE_BUSY;
		case BLUETOOTH_ERROR_CANCEL:
		case BLUETOOTH_ERROR_CANCEL_BY_USER:
			return BT_ERROR_CANCELLED;
		case BLUETOOTH_ERROR_AUTHENTICATION_FAILED:
			return BT_ERROR_AUTH_FAILED;
		case BLUETOOTH_ERROR_HOST_DOWN:
			return BT_ERROR_REMOTE_DEVICE_NOT_FOUND;
		case BLUETOOTH_ERROR_SERVICE_SEARCH_ERROR:
			return BT_ERROR_SERVICE_SEARCH_FAILED;
		case BLUETOOTH_ERROR_SERVICE_NOT_FOUND:
		case BLUETOOTH_ERROR_PARING_FAILED:
		case BLUETOOTH_ERROR_MAX_CONNECTION:
		case BLUETOOTH_ERROR_ALREADY_CONNECT:
		case BLUETOOTH_ERROR_NO_RESOURCES:
		case BLUETOOTH_ERROR_REGISTRATION_FAILED:
		case BLUETOOTH_ERROR_CONNECTION_BUSY:
		case BLUETOOTH_ERROR_MAX_CLIENT:
		case BLUETOOTH_ERROR_INVALID_CALLBACK:
		case BLUETOOTH_ERROR_NOT_FOUND:
		case BLUETOOTH_ERROR_INTERNAL:
		case BLUETOOTH_ERROR_CONNECTION_ERROR:
		case BLUETOOTH_ERROR_ACCESS_DENIED:
		default:
			return BT_ERROR_OPERATION_FAILED;
	}

}

int _bt_get_bt_device_info_s(bt_device_info_s** dest_dev, bluetooth_device_info_t* source_dev)
{
	int i = 0;

	BT_CHECK_INPUT_PARAMETER(source_dev);

	*dest_dev = (bt_device_info_s *)malloc(sizeof(bt_device_info_s));
	if (*dest_dev == NULL) {
		return BT_ERROR_OUT_OF_MEMORY;
	}

	if (strlen(source_dev->device_name.name) > 0) {
		(*dest_dev)->remote_name = strdup(source_dev->device_name.name);
	} else {
		(*dest_dev)->remote_name = NULL;
	}

	_bt_convert_address_to_string(&((*dest_dev)->remote_address), &(source_dev->device_address));

	(*dest_dev)->bt_class.major_device_class = source_dev->device_class.major_class;
	(*dest_dev)->bt_class.minor_device_class = source_dev->device_class.minor_class;
	(*dest_dev)->bt_class.major_service_class_mask = source_dev->device_class.service_class;
	if (source_dev->service_index > 0) {
		(*dest_dev)->service_uuid = (char**)malloc(sizeof(char*) * source_dev->service_index);
		if ((*dest_dev)->service_uuid != NULL) {
			for (i = 0; i < source_dev->service_index; i++) {
				(*dest_dev)->service_uuid[i] = strdup(source_dev->uuids[i]);
				if ((*dest_dev)->service_uuid[i] != NULL) {
					__bt_convert_lower_to_upper((*dest_dev)->service_uuid[i]);
				}
			}
		}
	} else {
		(*dest_dev)->service_uuid = NULL;
	}
	(*dest_dev)->service_count = source_dev->service_index;
	(*dest_dev)->is_bonded = (bool)source_dev->paired;
	(*dest_dev)->is_connected = (bool)source_dev->connected;
	(*dest_dev)->is_authorized = (bool)source_dev->trust;

	return BT_ERROR_NONE;
}

void _bt_free_bt_device_info_s(bt_device_info_s* device_info)
{
	int i = 0;

	if(device_info == NULL)
		return;

	if(device_info->remote_name != NULL)
		free(device_info->remote_name);

	if(device_info->remote_address != NULL)
		free(device_info->remote_address);

	if (device_info->service_uuid != NULL) {
		for (i = 0; i < device_info->service_count; i++) {
			if( device_info->service_uuid[i] != NULL )
				free(device_info->service_uuid[i]);
		}
		free(device_info->service_uuid);
	}

	free(device_info);
	device_info = NULL;
}

int _bt_convert_address_to_string(char** addr_str, bluetooth_device_address_t* addr_hex)
{
	char address[18] = {0,};

	snprintf(address, 18, "%2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X", addr_hex->addr[0], addr_hex->addr[1], addr_hex->addr[2], addr_hex->addr[3], addr_hex->addr[4], addr_hex->addr[5]);
	*addr_str = strdup(address);

	if (*addr_str != NULL) {
		return BT_ERROR_NONE;
	} else {
		return BT_ERROR_OUT_OF_MEMORY;
	}
}

void _bt_convert_address_to_hex(bluetooth_device_address_t* addr_hex, const char* addr_str)
{
	int i = 0;
	unsigned int addr[BLUETOOTH_ADDRESS_LENGTH] = {0,};

	i = sscanf(addr_str, "%X:%X:%X:%X:%X:%X", &addr[0], &addr[1], &addr[2], &addr[3], &addr[4], &addr[5]);
	if (i != BLUETOOTH_ADDRESS_LENGTH) {
		LOGI("[%s] Invalid format string - %s", __FUNCTION__, addr_str);
	}

	for (i = 0; i < BLUETOOTH_ADDRESS_LENGTH; i++) {
		addr_hex->addr[i] = (unsigned char)addr[i];
	}
}

static int __bt_get_bt_device_sdp_info_s(bt_device_sdp_info_s** dest, bt_sdp_info_t* source)
{
	int i = 0;

	*dest = (bt_device_sdp_info_s *)malloc(sizeof(bt_device_sdp_info_s));
	if (*dest == NULL) {
		return BT_ERROR_OUT_OF_MEMORY;
	}

	if (_bt_convert_address_to_string(&((*dest)->remote_address), &(source->device_addr)) != BT_ERROR_NONE) {
		__bt_free_bt_device_sdp_info_s(*dest);
		return BT_ERROR_OUT_OF_MEMORY;
	}

	if (source->service_index > 0) {
		(*dest)->service_uuid = (char**)malloc(sizeof(char*) * source->service_index);
		if ((*dest)->service_uuid == NULL) {
			__bt_free_bt_device_sdp_info_s(*dest);
			return BT_ERROR_OUT_OF_MEMORY;
		}

		for (i = 0; i < source->service_index; i++) {
			(*dest)->service_uuid[i] = strdup(source->uuids[i]);
			if ((*dest)->service_uuid[i] == NULL) {
				__bt_free_bt_device_sdp_info_s(*dest);
				return BT_ERROR_OUT_OF_MEMORY;
			}
			__bt_convert_lower_to_upper((*dest)->service_uuid[i]);
		}
	} else {
		(*dest)->service_uuid = NULL;
	}
	(*dest)->service_count = source->service_index;

	return BT_ERROR_NONE;
}

static void __bt_free_bt_device_sdp_info_s(bt_device_sdp_info_s* sdp_info)
{
	int i = 0;

	if(sdp_info == NULL)
		return;

	if(sdp_info->remote_address != NULL)
		free(sdp_info->remote_address);

	if (sdp_info->service_uuid != NULL) {
		for (i = 0; i < sdp_info->service_count; i++) {
			if( sdp_info->service_uuid[i] != NULL )
				free( sdp_info->service_uuid[i] );
		}
		free( sdp_info->service_uuid );
	}

	free(sdp_info);
	sdp_info = NULL;
}

static bt_adapter_visibility_mode_e __bt_get_bt_adapter_visibility_mode_e(bluetooth_discoverable_mode_t mode)
{
	switch (mode) {
		case BLUETOOTH_DISCOVERABLE_MODE_TIME_LIMITED_DISCOVERABLE:
			return BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE;
		case BLUETOOTH_DISCOVERABLE_MODE_GENERAL_DISCOVERABLE:
			return BT_ADAPTER_VISIBILITY_MODE_GENERAL_DISCOVERABLE;
		default:
			return BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE;
	}
}

static void __bt_event_proxy(int event, bluetooth_event_param_t *param, void* user_data)
{
	bluetooth_rfcomm_connection_t* connection_ind = NULL;
	bluetooth_rfcomm_disconnection_t* disconnection_ind = NULL;
	bt_socket_connection_s rfcomm_connection;
	bt_device_sdp_info_s* sdp_info = NULL;
	bt_adapter_device_discovery_info_s* discovery_info = NULL;
	bt_device_info_s *bonded_device = NULL;
	char* device_addr = NULL;
	int error_code = BT_ERROR_NONE;
	int event_index = -1;

	event_index = __bt_get_cb_index(event);
	if (event_index == -1 || bt_event_slot_container[event_index].callback == NULL) {
		return;
	}

	switch (event) {
		case BLUETOOTH_EVENT_ENABLED:
			LOGI("[%s] bt_adapter_state_changed_cb() will be called with BT_ADAPTER_ENABLED", __FUNCTION__);
			((bt_adapter_state_changed_cb)bt_event_slot_container[event_index].callback)
		    (_bt_get_error_code(param->result), BT_ADAPTER_ENABLED, bt_event_slot_container[event_index].user_data);
			break;
		case BLUETOOTH_EVENT_DISABLED:
			LOGI("[%s] bt_adapter_state_changed_cb() will be called with BT_ADAPTER_DISABLED", __FUNCTION__);
			((bt_adapter_state_changed_cb)bt_event_slot_container[event_index].callback)
		    (_bt_get_error_code(param->result), BT_ADAPTER_DISABLED, bt_event_slot_container[event_index].user_data);
			break;
		case BLUETOOTH_EVENT_LOCAL_NAME_CHANGED:
			LOGI("[%s] bt_adapter_name_changed_cb() will be called", __FUNCTION__);
			((bt_adapter_name_changed_cb)bt_event_slot_container[event_index].callback)
				((char*)(param->param_data), bt_event_slot_container[event_index].user_data);
			break;
		case BLUETOOTH_EVENT_DISCOVERABLE_MODE_CHANGED:
			LOGI("[%s] bt_adapter_visibility_mode_changed_cb() will be called", __FUNCTION__);
			((bt_adapter_visibility_mode_changed_cb)bt_event_slot_container[event_index].callback)
		    (_bt_get_error_code(param->result), __bt_get_bt_adapter_visibility_mode_e(*(bt_adapter_visibility_mode_e *)(param->param_data)), bt_event_slot_container[event_index].user_data);
			break;
		case BLUETOOTH_EVENT_DISCOVERY_STARTED:
			LOGI("[%s] bt_adapter_device_discovery_state_changed_cb() will be called with BT_ADAPTER_DEVICE_DISCOVERY_STARTED", __FUNCTION__);
			((bt_adapter_device_discovery_state_changed_cb)bt_event_slot_container[event_index].callback)
		    (_bt_get_error_code(param->result), BT_ADAPTER_DEVICE_DISCOVERY_STARTED, NULL, bt_event_slot_container[event_index].user_data);
			break;
		case BLUETOOTH_EVENT_DISCOVERY_FINISHED:
			LOGI("[%s] bt_adapter_device_discovery_state_changed_cb() will be called with BT_ADAPTER_DEVICE_DISCOVERY_FINISHED", __FUNCTION__);
			((bt_adapter_device_discovery_state_changed_cb)bt_event_slot_container[event_index].callback)
		    (_bt_get_error_code(param->result), BT_ADAPTER_DEVICE_DISCOVERY_FINISHED, NULL, bt_event_slot_container[event_index].user_data);
			break;
		case BLUETOOTH_EVENT_REMOTE_DEVICE_NAME_UPDATED:
			LOGI("[%s] bt_adapter_device_discovery_state_changed_cb() will be called with BT_ADAPTER_DEVICE_DISCOVERY_FOUND", __FUNCTION__);
			if( __bt_get_bt_adapter_device_discovery_info_s(&discovery_info, (bluetooth_device_info_t *)(param->param_data)) == BT_ERROR_NONE ) {
				((bt_adapter_device_discovery_state_changed_cb)bt_event_slot_container[event_index].callback)
					(_bt_get_error_code(param->result), BT_ADAPTER_DEVICE_DISCOVERY_FOUND, discovery_info, bt_event_slot_container[event_index].user_data);
				__bt_free_bt_adapter_device_discovery_info_s(discovery_info);
			} else {
				((bt_adapter_device_discovery_state_changed_cb)bt_event_slot_container[event_index].callback)
					(_bt_get_error_code(param->result), BT_ADAPTER_DEVICE_DISCOVERY_FOUND, NULL, bt_event_slot_container[event_index].user_data);
			}
			break;
		case BLUETOOTH_EVENT_BONDING_FINISHED:
			LOGI("[%s] bt_device_bond_created_cb() will be called", __FUNCTION__);
			_bt_get_bt_device_info_s(&bonded_device, (bluetooth_device_info_t *)(param->param_data));

			((bt_device_bond_created_cb)bt_event_slot_container[event_index].callback)
			  (_bt_get_error_code(param->result), bonded_device, bt_event_slot_container[event_index].user_data);
			_bt_free_bt_device_info_s(bonded_device);
			bonded_device = NULL;
			break;
		case BLUETOOTH_EVENT_BONDED_DEVICE_REMOVED:
			LOGI("[%s] bt_device_bond_destroyed_cb() will be called", __FUNCTION__);
			_bt_convert_address_to_string(&device_addr, (bluetooth_device_address_t *)(param->param_data));
			((bt_device_bond_destroyed_cb)bt_event_slot_container[event_index].callback)
			  (_bt_get_error_code(param->result), device_addr, bt_event_slot_container[event_index].user_data);
			if(device_addr != NULL)
				free(device_addr);
			device_addr = NULL;
			break;
		case BLUETOOTH_EVENT_DEVICE_AUTHORIZED:
			LOGI("[%s] bt_device_authorization_changed_cb() will be called with BT_DEVICE_AUTHORIZED", __FUNCTION__);
			_bt_convert_address_to_string(&device_addr, (bluetooth_device_address_t *)(param->param_data));
			((bt_device_authorization_changed_cb)bt_event_slot_container[event_index].callback)
				(BT_DEVICE_AUTHORIZED, device_addr, bt_event_slot_container[event_index].user_data);
			if(device_addr != NULL)
				free(device_addr);
			device_addr = NULL;
			break;
		case BLUETOOTH_EVENT_DEVICE_UNAUTHORIZED:
			LOGI("[%s] bt_device_authorization_changed_cb() will be called with BT_DEVICE_UNAUTHORIZED", __FUNCTION__);
			_bt_convert_address_to_string(&device_addr, (bluetooth_device_address_t *)(param->param_data));
			((bt_device_authorization_changed_cb)bt_event_slot_container[event_index].callback)
				(BT_DEVICE_UNAUTHORIZED, device_addr, bt_event_slot_container[event_index].user_data);
			if(device_addr != NULL)
				free(device_addr);
			device_addr = NULL;
			break;
		case BLUETOOTH_EVENT_SERVICE_SEARCHED:
			LOGI("[%s] bt_device_service_searched_cb() will be called", __FUNCTION__);
			__bt_get_bt_device_sdp_info_s(&sdp_info, (bt_sdp_info_t*)(param->param_data));
			error_code = _bt_get_error_code(param->result);
			// In service search, BT_ERROR_SERVICE_SEARCH_FAILED is returned instead of BT_ERROR_OPERATION_FAILED.
			if( error_code == BT_ERROR_OPERATION_FAILED )
				error_code = BT_ERROR_SERVICE_SEARCH_FAILED;
			((bt_device_service_searched_cb)bt_event_slot_container[event_index].callback)
				(error_code, sdp_info, bt_event_slot_container[event_index].user_data);
			__bt_free_bt_device_sdp_info_s(sdp_info);
			break;
		case BLUETOOTH_EVENT_RFCOMM_DATA_RECEIVED:
			LOGI("[%s] bt_socket_data_received_cb() will be called", __FUNCTION__);
			((bt_socket_data_received_cb)bt_event_slot_container[event_index].callback)
				((bt_socket_received_data_s*)(param->param_data), bt_event_slot_container[event_index].user_data);
			break;
		case BLUETOOTH_EVENT_RFCOMM_CONNECTED:
			LOGI("[%s] bt_socket_connection_state_changed_cb() will be called with BT_SOCKET_CONNECTED", __FUNCTION__);
			// In other case, BLUETOOTH_ERROR_INVALID_PARAM will be changed to BT_ERROR_INVALID_PARAM
			if(param->result == BLUETOOTH_ERROR_INVALID_PARAM)
				error_code = BT_ERROR_OPERATION_FAILED;
			else
				error_code = _bt_get_error_code(param->result);

			connection_ind = (bluetooth_rfcomm_connection_t*)(param->param_data);
			rfcomm_connection.socket_fd = connection_ind->socket_fd;
			rfcomm_connection.local_role = connection_ind->device_role;
			_bt_convert_address_to_string(&(rfcomm_connection.remote_address), &(connection_ind->device_addr));

			((bt_socket_connection_state_changed_cb)bt_event_slot_container[event_index].callback)
				(error_code, BT_SOCKET_CONNECTED, &rfcomm_connection, bt_event_slot_container[event_index].user_data);

			if( rfcomm_connection.remote_address != NULL ) {
				free(rfcomm_connection.remote_address);
				rfcomm_connection.remote_address = NULL;
			}

			break;
		case BLUETOOTH_EVENT_RFCOMM_DISCONNECTED:
			LOGI("[%s] bt_socket_connection_state_changed_cb() will be called with BT_SOCKET_DISCONNECTED", __FUNCTION__);
			disconnection_ind = (bluetooth_rfcomm_disconnection_t*)(param->param_data);
			rfcomm_connection.socket_fd = disconnection_ind->socket_fd;
			rfcomm_connection.local_role = BT_SOCKET_UNKNOWN;
			_bt_convert_address_to_string(&(rfcomm_connection.remote_address), &(disconnection_ind->device_addr));
			((bt_socket_connection_state_changed_cb)bt_event_slot_container[event_index].callback)
				(_bt_get_error_code(param->result), BT_SOCKET_DISCONNECTED, &rfcomm_connection, bt_event_slot_container[event_index].user_data);

			if( rfcomm_connection.remote_address != NULL ) {
				free(rfcomm_connection.remote_address);
				rfcomm_connection.remote_address = NULL;
			}
			break;
	}
}

static int __bt_get_bt_adapter_device_discovery_info_s(bt_adapter_device_discovery_info_s **discovery_info, bluetooth_device_info_t *source_info) {
	BT_CHECK_INPUT_PARAMETER(source_info);

	*discovery_info = (bt_adapter_device_discovery_info_s *)malloc(sizeof(bt_adapter_device_discovery_info_s));
	if (*discovery_info == NULL) {
		return BT_ERROR_OUT_OF_MEMORY;
	}

	if (strlen(source_info->device_name.name) > 0) {
		(*discovery_info)->remote_name = strdup(source_info->device_name.name);
	} else {
		(*discovery_info)->remote_name = NULL;
	}

	_bt_convert_address_to_string(&((*discovery_info)->remote_address), &(source_info->device_address));

	(*discovery_info)->bt_class.major_device_class = source_info->device_class.major_class;
	(*discovery_info)->bt_class.minor_device_class = source_info->device_class.minor_class;
	(*discovery_info)->bt_class.major_service_class_mask = source_info->device_class.service_class;

	(*discovery_info)->rssi = (bool)source_info->rssi;
	(*discovery_info)->is_bonded = (bool)source_info->paired;

	return BT_ERROR_NONE;
}

static void __bt_free_bt_adapter_device_discovery_info_s(bt_adapter_device_discovery_info_s* discovery_info)
{
	if(discovery_info == NULL)
		return;

	if(discovery_info->remote_name != NULL)
		free(discovery_info->remote_name);

	if(discovery_info->remote_address != NULL)
		free(discovery_info->remote_address);

	free(discovery_info);
	discovery_info = NULL;
}

static int __bt_get_cb_index(int event)
{
	switch (event) {
		case BLUETOOTH_EVENT_ENABLED:
		case BLUETOOTH_EVENT_DISABLED:
			return BT_EVENT_STATE_CHANGED;
		case BLUETOOTH_EVENT_LOCAL_NAME_CHANGED:
			return BT_EVENT_NAME_CHANGED;
		case BLUETOOTH_EVENT_DISCOVERABLE_MODE_CHANGED:
			return BT_EVENT_VISIBILITY_MODE_CHANGED;
		case BLUETOOTH_EVENT_DISCOVERY_STARTED:
		case BLUETOOTH_EVENT_DISCOVERY_FINISHED:
		case BLUETOOTH_EVENT_REMOTE_DEVICE_NAME_UPDATED:
			return BT_EVENT_DEVICE_DISCOVERY_STATE_CHANGED;
		case BLUETOOTH_EVENT_BONDING_FINISHED:
			return BT_EVENT_BOND_CREATED;
		case BLUETOOTH_EVENT_BONDED_DEVICE_REMOVED:
			return BT_EVENT_BOND_DESTROYED;
		case BLUETOOTH_EVENT_DEVICE_AUTHORIZED:
		case BLUETOOTH_EVENT_DEVICE_UNAUTHORIZED:
			return BT_EVENT_AUTHORIZATION_CHANGED;
		case BLUETOOTH_EVENT_SERVICE_SEARCHED:
			return BT_EVENT_SERVICE_SEARCHED;
		case BLUETOOTH_EVENT_RFCOMM_DATA_RECEIVED:
			return BT_EVENT_DATA_RECEIVED;
		case BLUETOOTH_EVENT_RFCOMM_CONNECTED:
		case BLUETOOTH_EVENT_RFCOMM_DISCONNECTED:
			return BT_EVENT_CONNECTION_STATE_CHANGED;
		default:
			return -1;
	}
}

char* _bt_convert_error_to_string(int error)
{
	switch (error) {
		case BT_ERROR_CANCELLED:
			return "CANCELLED";
		case BT_ERROR_INVALID_PARAMETER:
			return "INVALID_PARAMETER";
		case BT_ERROR_OUT_OF_MEMORY:
			return "OUT_OF_MEMORY";
		case BT_ERROR_RESOURCE_BUSY:
			return "RESOURCE_BUSY";
		case BT_ERROR_TIMED_OUT:
			return "TIMED_OUT";
		case BT_ERROR_NOW_IN_PROGRESS:
			return "NOW_IN_PROGRESS";
		case BT_ERROR_NOT_INITIALIZED:
			return "NOT_INITIALIZED";
		case BT_ERROR_NOT_ENABLED:
			return "DEVICE_NOT_ENABLED";
		case BT_ERROR_ALREADY_DONE:
			return "ALREADY_DONE";
		case BT_ERROR_OPERATION_FAILED:
			return "OPERATION_FAILED";
		case BT_ERROR_NOT_IN_PROGRESS:
			return "NOT_IN_PROGRESS";
		case BT_ERROR_REMOTE_DEVICE_NOT_BONDED:
			return "REMOTE_DEVICE_NOT_BONDED";
		case BT_ERROR_AUTH_REJECTED:
			return "AUTH_REJECTED";
		case BT_ERROR_AUTH_FAILED:
			return "AUTH_FAILED";
		case BT_ERROR_REMOTE_DEVICE_NOT_FOUND:
			return "REMOTE_DEVICE_NOT_FOUND";
		case BT_ERROR_SERVICE_SEARCH_FAILED:
			return "SERVICE_SEARCH_FAILED";
		default:
			return "UNKNOWN";
	}
}

static void __bt_convert_lower_to_upper(char* origin)
{
	int length = strlen(origin);
	int i = 0;

	for (i = 0; i < length; i++) {
		if (islower(origin[i])) {
			origin[i] = toupper(origin[i]);
		}
	}
}
