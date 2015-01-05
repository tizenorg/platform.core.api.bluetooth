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
#include <stdbool.h>
#include <dlog.h>
#ifdef NTB
#include "ntb-bluetooth.h"
#else
#include <bluetooth-api.h>
#endif

#include "bluetooth.h"
#include "bluetooth_private.h"

int bt_gatt_foreach_primary_services(const char *remote_address,
				bt_gatt_primary_service_cb callback,
				void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_gatt_foreach_primary_services(remote_address, callback, user_data);
	return error_code;
#else
	int i;
	int ret;
	bool foreach_call = true;
	bluetooth_device_address_t addr_hex = { {0,} };
	bt_gatt_handle_info_t *prim_svc;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address);
	BT_CHECK_INPUT_PARAMETER(callback);

	prim_svc = g_new0(bt_gatt_handle_info_t, 1);

	_bt_convert_address_to_hex(&addr_hex, remote_address);

	ret = _bt_get_error_code(bluetooth_gatt_get_primary_services(&addr_hex,
								prim_svc));
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x) : Failed to run function",
					_bt_convert_error_to_string(ret), ret);
		g_free(prim_svc);
		return ret;
	}

	for (i = 0; i < prim_svc->count; i++) {
		if (prim_svc->handle[i] == NULL)
			continue;

		BT_INFO("handle: %s", prim_svc->handle[i]);

		if (foreach_call == true &&
		    !callback((bt_gatt_attribute_h)prim_svc->handle[i], user_data)) {
			foreach_call = false;
		}

		/* Application should clone the handle using API in callback */
		/* bt_gatt_clone_attribute_handle */
		g_free(prim_svc->handle[i]);
	}

	g_free(prim_svc->handle);
	g_free(prim_svc);

	return ret;
#endif
}

int bt_gatt_discover_characteristics(bt_gatt_attribute_h service,
				bt_gatt_characteristics_discovered_cb callback,
				void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_gatt_discover_characteristics(service, callback, user_data);
	return error_code;
#else
	int ret;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(service);
	BT_CHECK_INPUT_PARAMETER(callback);

	ret = _bt_get_error_code(bluetooth_gatt_discover_service_characteristics((const char *)service));

	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
	} else {
		_bt_set_cb(BT_EVENT_GATT_CHARACTERISTIC_DISCOVERED, callback, user_data);
	}

	return ret;
#endif
}

int bt_gatt_get_service_uuid(bt_gatt_attribute_h service, char **uuid)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_gatt_get_service_uuid(service, uuid);
	return error_code;
#else
	int i;
	int ret;
	bt_gatt_service_property_t property;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(service);

	memset(&property, 0x00, sizeof(bt_gatt_service_property_t));

	ret = _bt_get_error_code(bluetooth_gatt_get_service_property((const char *)service, &property));

	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
	} else {
		*uuid = g_strdup(property.uuid);

		if (property.handle_info.count != 0 && property.handle_info.handle) {
			for (i = 0; i < property.handle_info.count; i++) {
				g_free(property.handle_info.handle[i]);
			}
			g_free(property.handle_info.handle);
		}
	}

	return ret;
#endif
}

int bt_gatt_foreach_included_services(bt_gatt_attribute_h service,
				bt_gatt_included_service_cb callback,
				void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_gatt_foreach_included_services(service, callback, user_data);
	return error_code;
#else
	int i;
	int ret;
	bool foreach_call = true;
	bt_gatt_service_property_t property;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(service);
	BT_CHECK_INPUT_PARAMETER(callback);

	memset(&property, 0x00, sizeof(bt_gatt_service_property_t));

	ret = _bt_get_error_code(bluetooth_gatt_get_service_property((const char *)service, &property));

	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
	} else {
		if (property.handle_info.count == 0 ||
		     property.handle_info.handle == NULL) {
			return ret;
		}

		for (i = 0; i < property.handle_info.count; i++) {
			if (property.handle_info.handle[i] == NULL)
				continue;

			if (foreach_call == true &&
			    !callback((bt_gatt_attribute_h)property.handle_info.handle[i],
					user_data)) {
				foreach_call = false;
			}

			g_free(property.handle_info.handle[i]);
		}
		g_free(property.handle_info.handle);
	}
	return ret;
#endif
}

#ifndef NTB
int bt_gatt_set_characteristic_changed_cb(bt_gatt_characteristic_changed_cb callback,
				void *user_data)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_gatt_unset_characteristic_changed_cb(void)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_gatt_watch_characteristic_changes(bt_gatt_attribute_h service)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_gatt_unwatch_characteristic_changes(bt_gatt_attribute_h service)
{
	return BT_ERROR_NOT_SUPPORTED;
}
#endif

int bt_gatt_get_characteristic_declaration(bt_gatt_attribute_h characteristic,
				char **uuid, unsigned char **value,
				int *value_length)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_gatt_get_characteristic_declaration(characteristic, uuid, value, value_length);
	return error_code;
#else
	int ret;
	bt_gatt_char_property_t property;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(characteristic);

	memset(&property, 0x00, sizeof(bt_gatt_char_property_t));

	ret = _bt_get_error_code(bluetooth_gatt_get_characteristics_property((const char *)characteristic, &property));

	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
	} else {
		if (property.uuid) {
			*uuid = g_strdup(property.uuid);
			g_free(property.uuid);
		}

		if (property.val && property.val_len != 0) {
			*value = g_memdup(property.val, property.val_len);
			*value_length = property.val_len;
			g_free(property.val);
		}

		g_free(property.name);

	}

	return ret;
#endif
}

#ifndef NTB
int bt_gatt_set_characteristic_value(bt_gatt_attribute_h characteristic,
				const unsigned char *value,
				int value_length)
{
	int ret;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(characteristic);
	BT_CHECK_INPUT_PARAMETER(value);

	if (value_length <= 0)
		return BT_ERROR_INVALID_PARAMETER;

	ret = _bt_get_error_code(bluetooth_gatt_set_characteristics_value((const char *)characteristic,
							(const guint8 *)value, value_length));

	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
	}

	return ret;
}

int bt_gatt_set_characteristic_value_request(bt_gatt_attribute_h characteristic,
				const unsigned char *value, int value_length,
				bt_gatt_characteristic_write_cb callback)
{
	return BT_ERROR_NOT_SUPPORTED;
}
#endif

int bt_gatt_clone_attribute_handle(bt_gatt_attribute_h *clone,
				bt_gatt_attribute_h origin)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_gatt_clone_attribute_handle(clone, origin);
	return error_code;
#else
	int error = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(origin);

	*clone = g_strdup((char *)origin);

	return error;
#endif
}

int bt_gatt_destroy_attribute_handle(bt_gatt_attribute_h handle)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_gatt_destroy_attribute_handle(handle);
	return error_code;
#else
	int error = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(handle);

	g_free(handle);

	return error;
#endif
}

int bt_gatt_read_characteristic_value(bt_gatt_attribute_h characteristic,
		bt_gatt_characteristic_read_cb callback)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_gatt_read_characteristic_value(characteristic, callback);
	return error_code;
#else
	return BT_ERROR_NOT_SUPPORTED;
#endif
}

#ifndef NTB
int bt_gatt_discover_characteristic_descriptor(bt_gatt_attribute_h characteristic_handle,
				bt_gatt_characteristic_descriptor_discovered_cb callback,
				void *user_data)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_gatt_connect(const char *address, bool auto_connect)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_gatt_disconnect(const char *address)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_gatt_set_connection_state_changed_cb(bt_gatt_connection_state_changed_cb callback, void *user_data)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_gatt_unset_connection_state_changed_cb(void)
{
	return BT_ERROR_NOT_SUPPORTED;
}
#endif

