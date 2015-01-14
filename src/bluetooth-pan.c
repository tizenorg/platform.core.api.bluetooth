/*
 * Copyright (c) 2012-2013 Samsung Electronics Co., Ltd.
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
#include <dlog.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#ifdef NTB
#include "ntb-bluetooth.h"
#else
#include <bluetooth-api.h>
#endif

#include "bluetooth.h"
#include "bluetooth_private.h"

GList *sending_files;

int bt_nap_activate(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_nap_activate();
	return error_code;
#else
	int error = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	error = bluetooth_network_activate_server();
	error = _bt_get_error_code(error);
	if (error != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_nap_deactivate(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_nap_deactivate();
	return error_code;
#else
	int error = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	error = bluetooth_network_deactivate_server();
	error = _bt_get_error_code(error);
	if (error != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

/* bluez don't support the disconnect API about NAP server */
/* So we implement this, deactivate the server and re-activate the server */
int bt_nap_disconnect_all(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_nap_disconnect_all();
	return error_code;
#else
	int error = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	error = bluetooth_network_deactivate_server();
	error = _bt_get_error_code(error);
	if (error != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	} else {
		return bt_nap_activate();
	}

	return error;
#endif
}

int bt_nap_disconnect(const char *remote_address)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_nap_disconnect(remote_address);
	return error_code;
#else
	return BT_ERROR_NOT_SUPPORTED;
#endif
}

int bt_nap_set_connection_state_changed_cb(
				bt_nap_connection_state_changed_cb callback,
				void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_nap_set_connection_state_changed_cb(callback,
								user_data);
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_NAP_CONNECTION_STATE_CHANGED, callback, user_data);
	return BT_ERROR_NONE;
#endif
}

int bt_nap_unset_connection_state_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_nap_unset_connection_state_changed_cb();
	return error_code;
#else
	_bt_unset_cb(BT_EVENT_NAP_CONNECTION_STATE_CHANGED);
	return BT_ERROR_NONE;
#endif
}

int bt_panu_set_connection_state_changed_cb(
				bt_panu_connection_state_changed_cb callback,
				void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_panu_set_connection_state_changed_cb(callback,
								user_data);
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_PAN_CONNECTION_STATE_CHANGED, callback, user_data);
	return BT_ERROR_NONE;
#endif
}

int bt_panu_unset_connection_state_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_panu_unset_connection_state_changed_cb();
	return error_code;
#else
	_bt_unset_cb(BT_EVENT_PAN_CONNECTION_STATE_CHANGED);
	return BT_ERROR_NONE;
#endif
}

int bt_panu_connect(const char *remote_address, bt_panu_service_type_e type)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_panu_connect(remote_address, type);
	return error_code;
#else
	int error = BT_ERROR_INVALID_PARAMETER;
	bluetooth_device_address_t addr_hex = { {0,} };

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address);
	_bt_convert_address_to_hex(&addr_hex, remote_address);
	if (BT_PANU_SERVICE_TYPE_NAP == type) {
		error = bluetooth_network_connect(&addr_hex,
					BLUETOOTH_NETWORK_NAP_ROLE, NULL);
		error = _bt_get_error_code(error);
		if (error != BT_ERROR_NONE) {
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error),
					error);
		}
	}
	return error;
#endif
}

int bt_panu_disconnect(const char *remote_address)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_panu_disconnect(remote_address);
	return error_code;
#else
	int error = BT_ERROR_INVALID_PARAMETER;
	bluetooth_device_address_t addr_hex = { {0,} };

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address);
	_bt_convert_address_to_hex(&addr_hex, remote_address);
	error = bluetooth_network_disconnect(&addr_hex);
	error = _bt_get_error_code(error);
	if (error != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error),
				error);
	}
	return error;
#endif
}

