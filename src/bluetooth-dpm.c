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
#include <dlog.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <bluetooth-api.h>

#include "bluetooth.h"
#include "bluetooth_private.h"

static int _bt_dpm_get_error_code(int origin_error)
{
	switch (origin_error) {
	case BLUETOOTH_DPM_RESULT_SUCCESS:
		return BT_ERROR_NONE;
	case BLUETOOTH_DPM_RESULT_INVALID_PARAM:
		return BT_ERROR_INVALID_PARAMETER;
	case BLUETOOTH_DPM_RESULT_NOT_SUPPORTED:
		return BT_ERROR_NOT_SUPPORTED;
	case BLUETOOTH_DPM_RESULT_SERVICE_NOT_ENABLED:
		return BT_ERROR_NOT_ENABLED;
	case BLUETOOTH_DPM_RESULT_FAIL:
	case BLUETOOTH_DPM_RESULT_ACCESS_DENIED:
	default:
		return BT_ERROR_OPERATION_FAILED;
	}

}

int bt_dpm_set_allow_bluetooth_mode(bt_dpm_allow_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_set_allow_bluetooth_mode(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_get_allow_bluetooth_mode(bt_dpm_allow_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_allow_bluetooth_mode(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_activate_bluetooth_device_restriction(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_activate_bluetooth_device_restriction(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_is_bluetooth_device_restriction_active(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_is_bluetooth_device_restriction_active(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_activate_bluetoooth_uuid_restriction(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_activate_bluetoooth_uuid_restriction(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_is_bluetooth_uuid_restriction_active(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_is_bluetooth_uuid_restriction_active(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_add_bluetooth_devices_to_blacklist(const char *device_address)
{
	bluetooth_device_address_t addr_hex = { {0,} };
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(device_address);

	_bt_convert_address_to_hex(&addr_hex, device_address);
	error_code = _bt_dpm_get_error_code(bluetooth_dpm_add_bluetooth_devices_to_blacklist(&addr_hex));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_add_bluetooth_devices_to_whitelist(const char *device_address)
{
	bluetooth_device_address_t addr_hex = { {0,} };
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(device_address);

	_bt_convert_address_to_hex(&addr_hex, device_address);
	error_code = _bt_dpm_get_error_code(bluetooth_dpm_add_bluetooth_devices_to_whitelist(&addr_hex));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_add_bluetooth_uuids_to_blacklist(const char *service_uuid)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_add_bluetooth_uuids_to_blacklist(service_uuid));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_add_bluetooth_uuids_to_whitelist(const char *service_uuid)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_add_bluetooth_uuids_to_whitelist(service_uuid));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_clear_bluetooth_devices_from_blacklist(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_clear_bluetooth_devices_from_blacklist());
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_clear_bluetooth_devices_from_whitelist(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_clear_bluetooth_devices_from_whitelist());
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_clear_bluetooth_uuids_from_blacklist(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_clear_bluetooth_uuids_from_blacklist());
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_clear_bluetooth_uuids_from_whitelist(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_clear_bluetooth_uuids_from_whitelist());
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

static int __bt_get_bt_dpm_device_list_info_s(bt_dpm_device_list_s **device_info, bt_dpm_device_list_t *source_info)
{
	int i;

	BT_CHECK_INPUT_PARAMETER(source_info);

	*device_info = (bt_dpm_device_list_s *)malloc(sizeof(device_info));
	if (*device_info == NULL)
		return BT_ERROR_OUT_OF_MEMORY;

	(*device_info)->count = source_info->count;
	if (source_info->count > 0) {
		(*device_info)->devices = (char **)malloc(sizeof(char *) *source_info->count);
		if ((*device_info)->devices)
			for (i = 0; i < (*device_info)->count; i++) {
				_bt_convert_address_to_string(&((*device_info)->devices[i]), &(source_info->addresses[i]));
				BT_INFO("Devices: %s", (*device_info)->devices[i]);
			}
	} else
		(*device_info)->devices = NULL;

	return BT_ERROR_NONE;
}

int bt_dpm_get_bluetooth_devices_from_blacklist(bt_dpm_device_list_s *device_list)
{
	int error_code = BT_ERROR_NONE;
	bt_dpm_device_list_t dev_list;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_bluetooth_devices_from_blacklist(&dev_list));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	else {
		error_code = __bt_get_bt_dpm_device_list_info_s(&device_list, &dev_list);
	}

	return error_code;
}

int bt_dpm_get_bluetooth_devices_from_whitelist(bt_dpm_device_list_s *device_list)
{
	int error_code = BT_ERROR_NONE;
	bt_dpm_device_list_t dev_list;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_bluetooth_devices_from_whitelist(&dev_list));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	else {
		error_code = __bt_get_bt_dpm_device_list_info_s(&device_list, &dev_list);
	}

	return error_code;
}

static int __bt_get_bt_dpm_uuid_list_info_s(bt_dpm_uuids_list_s **uuid_list, bt_dpm_uuids_list_t *source_info)
{
	int i;

	BT_CHECK_INPUT_PARAMETER(source_info);

	*uuid_list = (bt_dpm_uuids_list_s *)malloc(sizeof(uuid_list));
	if (*uuid_list == NULL)
		return BT_ERROR_OUT_OF_MEMORY;

	(*uuid_list)->count = source_info->count;

	if (source_info->count > 0) {
		(*uuid_list)->uuids = (char **)malloc(sizeof(char *) *source_info->count);
		if ((*uuid_list)->uuids != NULL) {
			for (i = 0; i < source_info->count; i++) {
				(*uuid_list)->uuids[i] = strdup(source_info->uuids[i]);
				if ((*uuid_list)->uuids[i] != NULL)
					BT_INFO("UUID: %s", (*uuid_list)->uuids[i]);
			}
		}
	} else
		(*uuid_list)->uuids = NULL;

	return BT_ERROR_NONE;
}

int bt_dpm_get_bluetooth_uuids_from_blacklist(bt_dpm_uuids_list_s *uuid_list)
{
	int error_code = BT_ERROR_NONE;
	bt_dpm_uuids_list_t uuids;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_bluetooth_uuids_from_blacklist(&uuids));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	else {
		__bt_get_bt_dpm_uuid_list_info_s(&uuid_list, &uuids);
	}

	return error_code;
}

int bt_dpm_get_bluetooth_uuids_from_whitelist(bt_dpm_uuids_list_s *uuid_list)
{
	int error_code = BT_ERROR_NONE;
	bt_dpm_uuids_list_t uuids;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_bluetooth_uuids_from_whitelist(&uuids));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	else {
		__bt_get_bt_dpm_uuid_list_info_s(&uuid_list, &uuids);
	}

	return error_code;
}

int bt_dpm_remove_bluetooth_device_from_whitelist(const char *device_address)
{
	bluetooth_device_address_t addr_hex = { {0,} };
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(device_address);

	_bt_convert_address_to_hex(&addr_hex, device_address);
	error_code = _bt_dpm_get_error_code(bluetooth_dpm_remove_bluetooth_device_from_whitelist(&addr_hex));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_remove_bluetooth_device_from_blacklist(const char *device_address)
{
	bluetooth_device_address_t addr_hex = { {0,} };
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(device_address);

	_bt_convert_address_to_hex(&addr_hex, device_address);
	error_code = _bt_dpm_get_error_code(bluetooth_dpm_remove_bluetooth_device_from_blacklist(&addr_hex));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_remove_bluetooth_uuid_from_whitelist(const char *service_uuid)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_remove_bluetooth_uuid_from_whitelist(service_uuid));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_remove_bluetooth_uuid_from_blacklist(const char *service_uuid)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_dpm_get_error_code(bluetooth_dpm_remove_bluetooth_uuid_from_blacklist(service_uuid));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_set_allow_bluetooth_outgoing_call(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_set_allow_bluetooth_outgoing_call(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_get_allow_bluetooth_outgoing_call(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_allow_bluetooth_outgoing_call(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_set_bluetooth_pairing_state(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_set_bluetooth_pairing_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_get_bluetooth_pairing_state(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_bluetooth_pairing_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_set_bluetooth_profile_state(bt_dpm_profile_t profile, bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_set_bluetooth_profile_state(profile, value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_get_bluetooth_profile_state(bt_dpm_profile_t profile, bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_bluetooth_profile_state(profile, value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_set_bluetooth_desktop_connectivity_state(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_set_bluetooth_desktop_connectivity_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_get_bluetooth_desktop_connectivity_state(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_bluetooth_desktop_connectivity_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_set_bluetooth_discoverable_state(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_set_bluetooth_discoverable_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_get_bluetooth_discoverable_state(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_bluetooth_discoverable_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_set_bluetooth_limited_discoverable_state(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_set_bluetooth_limited_discoverable_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_get_bluetooth_limited_discoverable_state(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_bluetooth_limited_discoverable_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_set_bluetooth_data_transfer_state(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_set_bluetooth_data_transfer_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_get_bluetooth_data_transfer_state(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_dpm_get_error_code(bluetooth_dpm_get_bluetooth_data_transfer_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}
