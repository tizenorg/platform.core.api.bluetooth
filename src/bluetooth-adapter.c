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
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <dlog.h>
#include <stdio.h>
#include <stdbool.h>
#ifdef NTB
#include "ntb-bluetooth.h"
#else
#include <bluetooth-api.h>
#endif

#include "bluetooth.h"
#include "bluetooth_private.h"

int bt_adapter_enable(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_enable();
        return error_code;
#else
	int error_code;

	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_enable_adapter());
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
#endif
}

int bt_adapter_disable(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_disable();
	return error_code;
#else
	int error_code;

	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_disable_adapter());
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
#endif
}

int bt_adapter_recover(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_recover();
	return error_code;
#else
	return BT_ERROR_NOT_SUPPORTED;
#endif
}

int bt_adapter_reset(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_reset();
	return error_code;
#else
	int error_code;

	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_reset_adapter());
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
#endif
}

int bt_adapter_get_state(bt_adapter_state_e *adapter_state)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_get_state(adapter_state);
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(adapter_state);

	*adapter_state = bluetooth_check_adapter();
	return BT_ERROR_NONE;
#endif
}

#ifndef NTB
int bt_adapter_le_enable(void)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_disable(void)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_get_state(bt_adapter_le_state_e *adapter_le_state)
{
	return BT_ERROR_NOT_SUPPORTED;
}
#endif

int bt_adapter_get_address(char **address)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_get_address(address);
	return error_code;
#else
	bluetooth_device_address_t loc_address = { {0} };
	int error_code;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(address);

	error_code = _bt_get_error_code(bluetooth_get_local_address(&loc_address));
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
		return error_code;
	}

	error_code = _bt_convert_address_to_string(address, &loc_address);
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
		return error_code;
	}

	return BT_ERROR_NONE;
#endif
}

int bt_adapter_get_version(char **version)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_get_version(version);
	return error_code;
#else
	return BT_ERROR_NOT_SUPPORTED;
#endif
}


int bt_adapter_get_local_info(char **chipset, char **firmware, char **stack_version, char **profiles)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_get_local_info(chipset, firmware, stack_version, profiles);
	return error_code;
#else
	return BT_ERROR_NOT_SUPPORTED;
#endif
}

int bt_adapter_get_name(char **name)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_get_name(name);
	return error_code;
#else
	int ret;
	bluetooth_device_name_t loc_name = { {0} };

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(name);

	ret = _bt_get_error_code(bluetooth_get_local_name(&loc_name));
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
		return ret;
	}

	*name = strdup(loc_name.name);
	if (*name == NULL) {
		BT_ERR("OUT_OF_MEMORY(0x%08x)", BT_ERROR_OUT_OF_MEMORY);
		return BT_ERROR_OUT_OF_MEMORY;
	}

	return BT_ERROR_NONE;
#endif
}

int bt_adapter_set_name(const char *name)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_set_name(name);
	return error_code;
#else
	bluetooth_device_name_t loc_name = { {0} };
	int ret;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(name);

	strncpy(loc_name.name, name, BLUETOOTH_DEVICE_NAME_LENGTH_MAX);
	loc_name.name[BLUETOOTH_DEVICE_NAME_LENGTH_MAX] = '\0';

	ret = _bt_get_error_code(bluetooth_set_local_name(&loc_name));
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
	}

	return ret;
#endif
}

int bt_adapter_get_visibility(bt_adapter_visibility_mode_e *mode, int *duration)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_get_visibility(mode, duration);
	return error_code;
#else
	bluetooth_discoverable_mode_t discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_CONNECTABLE;
	int ret;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(mode);

	ret = _bt_get_error_code(bluetooth_get_discoverable_mode(&discoverable_mode));
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
		return ret;
	}

	*mode = _bt_get_bt_visibility_mode_e(discoverable_mode);

	if (duration)
		*duration = 0;

	if (discoverable_mode == BLUETOOTH_DISCOVERABLE_MODE_TIME_LIMITED_DISCOVERABLE) {
		if (duration == NULL)
			return BT_ERROR_NONE;
		ret = bluetooth_get_timeout_value(duration);
		if (ret != BT_ERROR_NONE) {
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
		}
	}

	return BT_ERROR_NONE;
#endif
}

int bt_adapter_set_visibility(bt_adapter_visibility_mode_e visibility_mode, int timeout_sec)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_set_visibility(visibility_mode, timeout_sec);
	return error_code;
#else
	bluetooth_discoverable_mode_t discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_CONNECTABLE;
	int error_code = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	switch (visibility_mode) {
	case BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE:
		discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_TIME_LIMITED_DISCOVERABLE;
		break;
	case BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE:
		discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_CONNECTABLE;
		timeout_sec = 0;
		break;
	case BT_ADAPTER_VISIBILITY_MODE_GENERAL_DISCOVERABLE:
		discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_GENERAL_DISCOVERABLE;
		timeout_sec = 0;
		break;
	default:
		BT_ERR("INVALID_PARAMETER(0x%08x)", BT_ERROR_INVALID_PARAMETER);
		return BT_ERROR_INVALID_PARAMETER;
	}

	error_code = _bt_get_error_code(bluetooth_set_discoverable_mode(discoverable_mode, timeout_sec));
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	}

	return error_code;
#endif
}

int bt_adapter_set_connectable_changed_cb(bt_adapter_connectable_changed_cb callback, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_set_connectable_changed_cb(callback, user_data);
	return error_code;
#else
	return BT_ERROR_NOT_SUPPORTED;
#endif
}

int bt_adapter_unset_connectable_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_unset_connectable_changed_cb();
	return error_code;
#else
	return BT_ERROR_NOT_SUPPORTED;
#endif
}

int bt_adapter_get_connectable(bool *connectable)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_get_connectable(connectable);
	return error_code;
#else
	return BT_ERROR_NOT_SUPPORTED;
#endif
}

int bt_adapter_set_connectable(bool connectable)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_set_connectable(connectable);
	return error_code;
#else
	return BT_ERROR_NOT_SUPPORTED;
#endif
}

int bt_adapter_foreach_bonded_device(bt_adapter_bonded_device_cb foreach_cb, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_foreach_bonded_device(foreach_cb, user_data);
	return error_code;
#else
	GPtrArray *dev_list = NULL;
	bt_device_info_s *dev_info = NULL;
	bluetooth_device_info_t *ptr = NULL;
	int ret = BT_ERROR_NONE;
	int i = 0;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(foreach_cb);

	dev_list = g_ptr_array_new();
	if (dev_list == NULL) {
		BT_ERR("OUT_OF_MEMORY(0x%08x)", BT_ERROR_OUT_OF_MEMORY);
		return BT_ERROR_OUT_OF_MEMORY;
	}

	ret = _bt_get_error_code(bluetooth_get_bonded_device_list(&dev_list));
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x) : Failed to get bonded device list", _bt_convert_error_to_string(ret), ret);
		return ret;
	}

	for (i = 0; i < dev_list->len; i++) {
		ptr = g_ptr_array_index(dev_list, i);
		if (ptr != NULL) {
			ret = _bt_get_bt_device_info_s(&dev_info, (bluetooth_device_info_t *)ptr);
			if (ret != BT_ERROR_NONE) {
				BT_ERR("%s(0x%08x) : Failed to get device info", _bt_convert_error_to_string(ret), ret);
				break;
			}

			if (!foreach_cb(dev_info, user_data)) {
				_bt_free_bt_device_info_s(dev_info);
				break;
			}
			_bt_free_bt_device_info_s(dev_info);
		} else {
			BT_ERR("OPERATION_FAILED(0x%08x)", BT_ERROR_OPERATION_FAILED);
			ret = BT_ERROR_OPERATION_FAILED;
			break;
		}
	}

	if (dev_list != NULL) {
		g_ptr_array_free(dev_list, TRUE);
	}

	return ret;
#endif
}

int bt_adapter_get_bonded_device_info(const char *remote_address, bt_device_info_s **device_info)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_get_bonded_device_info(remote_address, device_info);
	return error_code;
#else
	int ret;
	bluetooth_device_address_t addr_hex = { {0,} };
	bluetooth_device_info_t *info;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address);

	info = (bluetooth_device_info_t *)malloc(sizeof(bluetooth_device_info_t));
	if (info == NULL)
		return BT_ERROR_OUT_OF_MEMORY;

	_bt_convert_address_to_hex(&addr_hex, remote_address);

	ret = _bt_get_error_code(bluetooth_get_bonded_device(&addr_hex, info));
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x) : Failed to run function",
					_bt_convert_error_to_string(ret), ret);
	} else {
		ret = _bt_get_bt_device_info_s(device_info, info);
		if (ret != BT_ERROR_NONE) {
			BT_ERR("%s(0x%08x) : Failed to get device info",
						_bt_convert_error_to_string(ret),
						ret);
		}
	}

	free(info);

	return ret;
#endif
}

int bt_adapter_free_device_info(bt_device_info_s *device_info)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_free_device_info(device_info);
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(device_info);

	_bt_free_bt_device_info_s(device_info);

	return BT_ERROR_NONE;
#endif
}

int bt_adapter_is_service_used(const char *service_uuid, bool *used)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_is_service_used(service_uuid, used);
	return error_code;
#else
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(service_uuid);
	BT_CHECK_INPUT_PARAMETER(used);

	if (strcmp(service_uuid, OPP_UUID) == 0) {
		*used = bluetooth_obex_server_is_activated();
	} else {
		ret = _bt_get_error_code(bluetooth_is_service_used(service_uuid,
							(gboolean *)used));
	}

	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x) : Failed to run function", _bt_convert_error_to_string(ret), ret);
	}

	return ret;
#endif
}

int bt_adapter_set_state_changed_cb(bt_adapter_state_changed_cb callback, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_set_state_changed_cb(callback, user_data);
	return error_code;
#else

	BT_DBG("");
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_STATE_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
	}

	return ret;
#endif
}

#ifndef NTB
int bt_adapter_le_set_state_changed_cb(bt_adapter_le_state_changed_cb callback, void *user_data)
{
	return BT_ERROR_NOT_SUPPORTED;
}
#endif

int bt_adapter_set_name_changed_cb(bt_adapter_name_changed_cb callback, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_set_name_changed_cb(callback, user_data);
	return error_code;
#else
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_NAME_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
	}

	return ret;
#endif
}

int bt_adapter_set_visibility_mode_changed_cb(bt_adapter_visibility_mode_changed_cb callback, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_set_visibility_mode_changed_cb(callback, user_data);
	return error_code;
#else
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_VISIBILITY_MODE_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
	}

	return ret;
#endif
}

int bt_adapter_set_device_discovery_state_changed_cb(bt_adapter_device_discovery_state_changed_cb callback, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_set_device_discovery_state_changed_cb(callback, user_data);
	return error_code;
#else
	int ret = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_DEVICE_DISCOVERY_STATE_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
	}

	return ret;
#endif
}

#ifndef NTB
int bt_adapter_le_set_device_discovery_state_changed_cb(bt_adapter_le_device_discovery_state_changed_cb callback, void *user_data)
{
	return BT_ERROR_NOT_SUPPORTED;
}
#endif

int bt_adapter_unset_state_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_unset_state_changed_cb();
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_STATE_CHANGED);
	return BT_ERROR_NONE;
#endif
}

#ifndef NTB
int bt_adapter_le_unset_state_changed_cb(void)
{
	return BT_ERROR_NOT_SUPPORTED;
}
#endif

int bt_adapter_unset_name_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_unset_name_changed_cb();
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_NAME_CHANGED);
	return BT_ERROR_NONE;
#endif
}

int bt_adapter_unset_visibility_mode_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_unset_visibility_mode_changed_cb();
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_VISIBILITY_MODE_CHANGED);
	return BT_ERROR_NONE;
#endif
}

int bt_adapter_set_visibility_duration_changed_cb(bt_adapter_visibility_duration_changed_cb callback, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_set_visibility_duration_changed_cb(callback, user_data);
	return error_code;
#else
	return BT_ERROR_NOT_SUPPORTED;
#endif
}

int bt_adapter_unset_visibility_duration_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_unset_visibility_duration_changed_cb();
	return error_code;
#else
	return BT_ERROR_NOT_SUPPORTED;
#endif
}

int bt_adapter_unset_device_discovery_state_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_unset_device_discovery_state_changed_cb();
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_DEVICE_DISCOVERY_STATE_CHANGED);
	return BT_ERROR_NONE;
#endif
}

#ifndef NTB
int bt_adapter_le_unset_device_discovery_state_changed_cb(void)
{
	return BT_ERROR_NOT_SUPPORTED;
}
#endif

int bt_adapter_start_device_discovery(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_start_device_discovery();
	return error_code;
#else
	int error_code;

	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_start_discovery(0, 0, BLUETOOTH_DEVICE_MAJOR_MASK_MISC));
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
#endif
}

int bt_adapter_stop_device_discovery(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_stop_device_discovery();
	return error_code;
#else
	int error_code;

	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_cancel_discovery());
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
#endif
}

int bt_adapter_is_discovering(bool *is_discovering)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_adapter_is_discovering(is_discovering);
	return error_code;
#else
	int ret = 0;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(is_discovering);

	ret = bluetooth_is_discovering();
	if (ret >= BLUETOOTH_ERROR_BASE) {
		*is_discovering = (ret == 1) ? true : false;
		return BT_ERROR_NONE;
	} else {
		ret = _bt_get_error_code(ret);
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
		return ret;
	}
#endif
}

#ifndef NTB
int bt_adapter_le_start_device_discovery(void)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_stop_device_discovery(void)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_is_discovering(bool *is_discovering)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_get_local_oob_data(unsigned char **hash, unsigned char **randomizer,
					int *hash_len, int *randomizer_len)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_set_remote_oob_data(const char *remote_address,
				unsigned char *hash, unsigned char *randomizer,
				int hash_len, int randomizer_len)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_remove_remote_oob_data(const char *remote_address)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_add_white_list(const char *address, bt_device_address_type_e address_type)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_remove_white_list(const char *address, bt_device_address_type_e address_type)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_clear_white_list(void)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_create_advertiser(bt_advertiser_h *advertiser)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_destroy_advertiser(bt_advertiser_h advertiser)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_add_advertising_data(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, bt_adapter_le_packet_data_type_e data_type,
		void *data, unsigned int data_size)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_remove_advertising_data(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, bt_adapter_le_packet_data_type_e data_type)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_clear_advertising_data(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_start_advertising(bt_advertiser_h advertiser,
		bt_adapter_le_advertising_params_s *adv_params,
		bt_adapter_le_advertising_state_changed_cb cb, void *user_data)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_stop_advertising(bt_advertiser_h advertiser)
{
	return BT_ERROR_NOT_SUPPORTED;
}

int bt_adapter_le_enable_privacy(bool enable_privacy)
{
	return BT_ERROR_NOT_SUPPORTED;
}
#endif

#ifdef NTB
int bt_agent_register(bt_agent *agent)
{
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_agent_register(agent);
	return error_code;
}

int bt_agent_unregister(void)
{
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_agent_unregister();
	return error_code;
}

void bt_agent_confirm_accept(bt_req_t *requestion)
{
	ntb_bt_agent_confirm_accept(requestion);
}

void bt_agent_confirm_reject(bt_req_t *requestion)
{
	ntb_bt_agent_confirm_reject(requestion);
}

void bt_agent_pincode_reply(const char *pin_code, bt_req_t *requestion)
{
	ntb_bt_agent_pincode_reply(pin_code, requestion);
}

void bt_agent_pincode_cancel(bt_req_t *requestion)
{
	ntb_bt_agent_pincode_cancel(requestion);
}

#ifdef TIZEN_3
int bt_agent_register_sync(void)
{
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_agent_register_sync();
	return error_code;
}

void bt_agent_reply_sync(bt_agent_accept_type_t reply)
{
	ntb_bt_agent_reply_sync(reply);
}
#endif
#endif
