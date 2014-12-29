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

int bt_hdp_register_sink_app(unsigned short data_type, char **app_id)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_hdp_register_sink_app(data_type, app_id);
	return error_code;
#else
	int error = BT_ERROR_NONE;
	char *app_handle = NULL;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(app_id);
	error = bluetooth_hdp_activate(data_type, HDP_ROLE_SINK, HDP_QOS_ANY, &app_handle);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
		return error;
	}

	*app_id = strdup(app_handle);
	if (*app_id == NULL) {
		return BT_ERROR_OUT_OF_MEMORY;
	}

	return BT_ERROR_NONE;
#endif
}

int bt_hdp_unregister_sink_app(const char *app_id)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_hdp_unregister_sink_app(app_id);
	return error_code;
#else
	int error = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(app_id);
	error = bluetooth_hdp_deactivate(app_id);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_hdp_send_data(unsigned int channel, const char *data, unsigned int size)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_hdp_send_data(channel, data, size);
	return error_code;
#else
	int error = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	if (NULL == data) {
		BT_ERR("%s", _bt_convert_error_to_string(BT_ERROR_INVALID_PARAMETER));
	}
	error = bluetooth_hdp_send_data(channel, data, size);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_hdp_connect_to_source(const char *remote_address, const char *app_id)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_hdp_connect_to_source(remote_address, app_id);
	return error_code;
#else
	int error = BT_ERROR_NONE;
	bluetooth_device_address_t addr_hex = { {0,} };
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(app_id);
	BT_CHECK_INPUT_PARAMETER(remote_address);
	_bt_convert_address_to_hex(&addr_hex, remote_address);
	error = bluetooth_hdp_connect(app_id, HDP_QOS_ANY, &addr_hex);
	error = _bt_get_error_code(error);
	if (error != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_hdp_disconnect(const char *remote_address, unsigned int channel)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_hdp_disconnect(remote_address, channel);
	return error_code;
#else
	int error = BT_ERROR_NONE;
	bluetooth_device_address_t addr_hex = { {0,} };
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address);
	_bt_convert_address_to_hex(&addr_hex, remote_address);

	error = bluetooth_hdp_disconnect(channel, &addr_hex);
	error = _bt_get_error_code(error);
	if (error != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_hdp_set_connection_state_changed_cb(bt_hdp_connected_cb connected_cb,
		bt_hdp_disconnected_cb disconnected_cb, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_hdp_set_connection_state_changed_cb(connected_cb, disconnected_cb, user_data);
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(connected_cb);
	BT_CHECK_INPUT_PARAMETER(disconnected_cb);
	_bt_set_cb(BT_EVENT_HDP_CONNECTED, connected_cb, user_data);
	_bt_set_cb(BT_EVENT_HDP_DISCONNECTED, disconnected_cb, user_data);
	return BT_ERROR_NONE;
#endif
}

int bt_hdp_unset_connection_state_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_hdp_unset_connection_state_changed_cb();
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	if ( _bt_check_cb(BT_EVENT_HDP_CONNECTED) == true)
		_bt_unset_cb(BT_EVENT_HDP_CONNECTED);
	if ( _bt_check_cb(BT_EVENT_HDP_DISCONNECTED) == true)
		_bt_unset_cb(BT_EVENT_HDP_DISCONNECTED);

	return BT_ERROR_NONE;
#endif
}

int bt_hdp_set_data_received_cb(bt_hdp_data_received_cb callback,
				void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_hdp_set_data_received_cb(callback, user_data);
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_HDP_DATA_RECEIVED, callback, user_data);
	return BT_ERROR_NONE;
#endif
}

int bt_hdp_unset_data_received_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_hdp_unset_data_received_cb();
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	if ( _bt_check_cb(BT_EVENT_HDP_DATA_RECEIVED) == true)
		_bt_unset_cb(BT_EVENT_HDP_DATA_RECEIVED);
	return BT_ERROR_NONE;
#endif
}
