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
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <bluetooth-api.h>

#include "bluetooth.h"
#include "bluetooth_private.h"

#if 0
bluetooth_device_address_t addr_hex = { {0,} };
int error_code = BT_ERROR_NONE;

BT_CHECK_BT_SUPPORT();
BT_CHECK_INIT_STATUS();
BT_CHECK_INPUT_PARAMETER(device_address);

_bt_convert_address_to_hex(&addr_hex, device_address); /* LCOV_EXCL_START */
error_code = _bt_get_error_code(bluetooth_bond_device(&addr_hex));
if (error_code != BT_ERROR_NONE)
	BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

return error_code;
#endif

int bt_dpm_set_allow_bluetooth_mode(bt_dpm_allow_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_get_error_code(bluetooth_dpm_set_allow_bluetooth_mode(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);

	return error_code;
}

int bt_dpm_get_allow_bluetooth_mode(bt_dpm_allow_t *value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_allow_bluetooth_mode(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_activate_bluetooth_device_restriction(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_get_error_code(bluetooth_dpm_activate_bluetooth_device_restriction(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_is_bluetooth_device_restriction_active(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_get_error_code(bluetooth_dpm_is_bluetooth_device_restriction_active(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_activate_bluetoooth_uuid_restriction(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_get_error_code(bluetooth_dpm_activate_bluetoooth_uuid_restriction(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_is_bluetooth_uuid_restriction_active(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_get_error_code(bluetooth_dpm_is_bluetooth_uuid_restriction_active(value));
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
	error_code = _bt_get_error_code(bluetooth_dpm_add_bluetooth_devices_to_blacklist(&addr_hex));
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
	error_code = _bt_get_error_code(bluetooth_dpm_add_bluetooth_devices_to_whitelist(&addr_hex));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_add_bluetooth_uuids_to_blacklist(const char *service_uuid)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_add_bluetooth_uuids_to_blacklist(service_uuid));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_add_bluetooth_uuids_to_whitelist(const char *service_uuid)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_add_bluetooth_uuids_to_whitelist(service_uuid));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_clear_bluetooth_devices_from_blacklist(void)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_clear_bluetooth_devices_from_blacklist());
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_clear_bluetooth_devices_from_whitelist(void)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_clear_bluetooth_devices_from_whitelist());
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_clear_bluetooth_uuids_from_blacklist(void)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_clear_bluetooth_uuids_from_blacklist());
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_clear_bluetooth_uuids_from_whitelist(void)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_clear_bluetooth_uuids_from_whitelist());
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_get_bluetooth_devices_from_blacklist(bt_dpm_device_list_t *device_list)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_bluetooth_devices_from_blacklist(device_list));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_get_bluetooth_devices_from_whitelist(bt_dpm_device_list_t *device_list)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_bluetooth_devices_from_whitelist(device_list));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_get_bluetooth_uuids_from_blacklist(bt_dpm_uuids_list_t *uuid_list)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_bluetooth_uuids_from_blacklist(uuid_list));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_get_bluetooth_uuids_from_whitelist(bt_dpm_uuids_list_t *uuid_list)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_bluetooth_uuids_from_whitelist(uuid_list));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
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
	error_code = _bt_get_error_code(bluetooth_dpm_remove_bluetooth_device_from_whitelist(&addr_hex));
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
	error_code = _bt_get_error_code(bluetooth_dpm_remove_bluetooth_device_from_blacklist(&addr_hex));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_remove_bluetooth_uuid_from_whitelist(const char *service_uuid)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_remove_bluetooth_uuid_from_whitelist(service_uuid));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_remove_bluetooth_uuid_from_blacklist(const char *service_uuid)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_remove_bluetooth_uuid_from_blacklist(service_uuid));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_set_allow_bluetooth_outgoing_call(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_set_allow_bluetooth_outgoing_call(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_get_allow_bluetooth_outgoing_call(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_allow_bluetooth_outgoing_call(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_set_bluetooth_pairing_state(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_set_bluetooth_pairing_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_get_bluetooth_pairing_state(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_bluetooth_pairing_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_set_bluetooth_profile_state(bt_dpm_profile_t profile, bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_set_bluetooth_profile_state(profile, value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_get_bluetooth_profile_state(bt_dpm_profile_t profile, bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_bluetooth_profile_state(profile, value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_set_bluetooth_desktop_connectivity_state(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_set_bluetooth_desktop_connectivity_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_get_bluetooth_desktop_connectivity_state(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_bluetooth_desktop_connectivity_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_set_bluetooth_discoverable_state(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_set_bluetooth_discoverable_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_get_bluetooth_discoverable_state(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_bluetooth_discoverable_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

#if 0
 bt_dpm_result_t bluetooth_dpm_clear_bluetooth_devices_from_list(void);
 bt_dpm_result_t bluetooth_dpm_clear_bluetooth_uuids_from_list(void);
#endif

int bt_dpm_set_bluetooth_limited_discoverable_state(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_set_bluetooth_limited_discoverable_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_get_bluetooth_limited_discoverable_state(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_bluetooth_limited_discoverable_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_set_bluetooth_data_transfer_state(bt_dpm_status_t value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_set_bluetooth_data_transfer_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}

int bt_dpm_get_bluetooth_data_transfer_state(bt_dpm_status_t *value)
{
	int error_code = BT_ERROR_NONE;
	
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	
	error_code = _bt_get_error_code(bluetooth_dpm_get_bluetooth_data_transfer_state(value));
	if (error_code != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	
	return error_code;
}
