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
#include <arpa/inet.h>
#include <bluetooth-api.h>

#include "bluetooth.h"
#include "bluetooth_internal.h"
#include "bluetooth_private.h"

#ifdef TIZEN_LE_DISABLE
#define BT_CHECK_LE_SUPPORT() \
		{ \
			BT_CHECK_BT_SUPPORT(); \
			LOGE("[%s] NOT_SUPPORTED(0x%08x)", __FUNCTION__, BT_ERROR_NOT_SUPPORTED); \
			return BT_ERROR_NOT_SUPPORTED; \
		}
#else
#define BT_CHECK_LE_SUPPORT()
#endif

static GSList *advertiser_list = NULL;

//LCOV_EXCL_START
int bt_adapter_enable(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_enable_adapter());
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return error_code;
}

int bt_adapter_disable(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_disable_adapter());
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return error_code;
}

int bt_adapter_recover(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_recover_adapter());
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return error_code;
}

int bt_adapter_reset(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_reset_adapter());
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return error_code;
}
//LCOV_EXCL_STOP

int bt_adapter_get_state(bt_adapter_state_e *adapter_state)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(adapter_state);

	*adapter_state = bluetooth_check_adapter();
	return BT_ERROR_NONE;
}

//LCOV_EXCL_START
int bt_adapter_le_enable(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_enable_adapter_le());
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return error_code;
}

int bt_adapter_le_disable(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_get_error_code(bluetooth_disable_adapter_le());
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return error_code;
}

int bt_adapter_le_get_state(bt_adapter_le_state_e *adapter_le_state)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(adapter_le_state);

	*adapter_le_state = bluetooth_check_adapter_le();
	return BT_ERROR_NONE;
}
//LCOV_EXCL_STOP

int bt_adapter_get_address(char **address)
{
	bluetooth_device_address_t loc_address = { {0} };
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(address);

	error_code = _bt_get_error_code(bluetooth_get_local_address(&loc_address));
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
		return error_code; //LCOV_EXCL_LINE
	}

	error_code = _bt_convert_address_to_string(address, &loc_address);
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
		return error_code; //LCOV_EXCL_LINE
	}

	return BT_ERROR_NONE;
}

//LCOV_EXCL_START
int bt_adapter_get_version(char **version)
{
	int ret = BT_ERROR_NONE;
	bluetooth_version_t loc_ver = { { 0 } };

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(version);

	ret = _bt_get_error_code(bluetooth_get_local_version(&loc_ver));
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
		return ret; //LCOV_EXCL_LINE
	}

	*version = strdup(loc_ver.version);
	if (*version == NULL) {
		BT_ERR("OUT_OF_MEMORY(0x%08x)", BT_ERROR_OUT_OF_MEMORY);
		return BT_ERROR_OUT_OF_MEMORY;
	}

	return BT_ERROR_NONE;
}
//LCOV_EXCL_STOP

#define BT_ADAPTER_FIRMWARE_INFO_FILE_PATH "/var/lib/bluetooth/bcmtool_log"
#define BT_ADAPTER_STACK_INFO_FILE_PATH "/usr/etc/bluetooth/stack_info"
#define BT_ADAPTER_MAX_BUFFER_SIZE (32767 * 1000)

//LCOV_EXCL_START
int bt_adapter_get_local_info(char **chipset, char **firmware, char **stack_version, char **profiles)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	int ret = BT_ERROR_NONE;
	FILE *fp = NULL;
	char *buf = NULL;
	long lsize;
	size_t result;
	char *info_start = NULL;
	char *info_end = NULL;
	long info_size;
	char *local_chipset = NULL;
	char *local_firmware = NULL;
	char *local_stack_version = NULL;
	char *local_profiles = NULL;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(chipset);
	BT_CHECK_INPUT_PARAMETER(firmware);
	BT_CHECK_INPUT_PARAMETER(stack_version);
	BT_CHECK_INPUT_PARAMETER(profiles);

	if ((fp = fopen(BT_ADAPTER_FIRMWARE_INFO_FILE_PATH, "r")) == NULL) {
		BT_ERR("fopen() is failed(%s)", BT_ADAPTER_FIRMWARE_INFO_FILE_PATH);

		local_firmware = (char *)malloc(sizeof(char) * 1);
		if (local_firmware == NULL) {
			ret = BT_ERROR_OUT_OF_MEMORY;
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
			goto ERROR;
		}
		local_firmware[0] = '\0';
		local_chipset = (char *)malloc(sizeof(char) * 1);
		if (local_chipset == NULL) {
			ret = BT_ERROR_OUT_OF_MEMORY;
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
			goto ERROR;
		}
		local_chipset[0] = '\0';
	} else {
		fseek(fp, 0, SEEK_END);
		lsize = ftell(fp);
		if (lsize < 0) {
			BT_ERR("ftell() error(0x%x)", lsize);
			ret = BT_ERROR_OPERATION_FAILED;
			goto ERROR;
		}
		buf = (char *)malloc(sizeof(char) * (lsize + 1));
		if (buf == NULL) {
			ret = BT_ERROR_OUT_OF_MEMORY;
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
			goto ERROR;
		}
		fseek(fp, 0, SEEK_SET);
		result = fread(buf, 1, lsize, fp);
		buf[lsize] = '\0';

		if (result != lsize)
			BT_ERR("fread() error");

		info_start = strstr(buf, "bluetooth");
		if (info_start == NULL) {
			BT_ERR("strstr() error(0x%x)", info_start);
			ret = BT_ERROR_OPERATION_FAILED;
			goto ERROR;
		}
		info_start += 10;
		info_end = strstr(buf, "hcd");
		if (info_end == NULL) {
			BT_ERR("strstr() error(0x%x)", info_end);
			ret = BT_ERROR_OPERATION_FAILED;
			goto ERROR;
		}
		info_size = info_end - info_start - 1;

		local_firmware = (char *)malloc(sizeof(char) * (info_size + 1));
		if (local_firmware == NULL) {
			ret = BT_ERROR_OUT_OF_MEMORY;
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
			goto ERROR;
		}

		strncpy(local_firmware, info_start, info_size);
		local_firmware[info_size] = '\0';

		info_end = strchr(buf, '_');
		if (info_end == NULL) {
			BT_ERR("strchr() error(0x%x)", info_end);
			ret = BT_ERROR_OPERATION_FAILED;
			goto ERROR;
		}
		info_size = info_end - info_start;

		local_chipset = (char *)malloc(sizeof(char) * (info_size + 1));
		if (local_chipset == NULL) {
			ret = BT_ERROR_OUT_OF_MEMORY;
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
			goto ERROR;
		}

		strncpy(local_chipset, info_start, info_size);
		local_chipset[info_size] = '\0';

		if (buf)
			free(buf);
		buf = NULL;
		fclose(fp);
	}

	if ((fp = fopen(BT_ADAPTER_STACK_INFO_FILE_PATH, "r")) == NULL) {
		BT_ERR("fopen() error");
		ret = BT_ERROR_OPERATION_FAILED;
		goto ERROR;
	}

	fseek(fp, 0, SEEK_END);
	lsize = ftell(fp);
	if (lsize < 0) {
		BT_ERR("ftell() error(0x%x)", lsize);
		ret = BT_ERROR_OPERATION_FAILED;
		goto ERROR;
	}
	buf = (char *)malloc(sizeof(char) * (lsize + 1));
	if (buf == NULL) {
		ret = BT_ERROR_OUT_OF_MEMORY;
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
		goto ERROR;
	}
	fseek(fp, 0, SEEK_SET);
	result = fread(buf, 1, lsize, fp);
	buf[lsize] = '\0';

	if (result != lsize) {
		BT_ERR("fread() error(0x%x)", result);
		ret = BT_ERROR_OPERATION_FAILED;
		goto ERROR;
	}

	info_start = buf;
	info_end = strchr(buf, ',');
	if (info_end == NULL) {
		BT_ERR("strchr() error(0x%x)", info_end);
		ret = BT_ERROR_OPERATION_FAILED;
		goto ERROR;
	}
	info_size = info_end - info_start;

	if (info_size < 0 || info_size > BT_ADAPTER_MAX_BUFFER_SIZE) {
		BT_ERR("info size is incorrect: %ld", info_size);
		ret = BT_ERROR_OPERATION_FAILED;
		goto ERROR;
	}

	local_stack_version = (char *)malloc(sizeof(char) * (info_size + 1));
	if (local_stack_version == NULL) {
		ret = BT_ERROR_OUT_OF_MEMORY;
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
		goto ERROR;
	}

	strncpy(local_stack_version, info_start, info_size);
	local_stack_version[info_size] = '\0';

	info_start = info_end + 2;
	info_size = lsize - info_size - 3;

	if (info_size < 0 || info_size > BT_ADAPTER_MAX_BUFFER_SIZE) {
		BT_ERR("info size is incorrect: %ld", info_size);
		ret = BT_ERROR_OPERATION_FAILED;
		goto ERROR;
	}

	local_profiles = (char *)malloc(sizeof(char) * (info_size + 1));
	if (local_profiles == NULL) {
		ret = BT_ERROR_OUT_OF_MEMORY;
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
		goto ERROR;
	}

	strncpy(local_profiles, info_start, info_size);
	local_profiles[info_size] = '\0';

	if (buf)
		free(buf);
	fclose(fp);

	*chipset = local_chipset;
	*firmware = local_firmware;
	*stack_version = local_stack_version;
	*profiles = local_profiles;

	return BT_ERROR_NONE;

ERROR:
	if (local_chipset)
		free(local_chipset);
	if (local_firmware)
		free(local_firmware);
	if (local_stack_version)
		free(local_stack_version);
	if (buf)
		free(buf);
	if (fp)
		fclose(fp);
	return ret;
}
//LCOV_EXCL_STOP

int bt_adapter_get_name(char **name)
{
	int ret = BT_ERROR_NONE;
	bluetooth_device_name_t loc_name = { {0} };

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(name);

	ret = _bt_get_error_code(bluetooth_get_local_name(&loc_name));
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
		return ret; //LCOV_EXCL_LINE
	}

	*name = strdup(loc_name.name);
	if (*name == NULL) {
		BT_ERR("OUT_OF_MEMORY(0x%08x)", BT_ERROR_OUT_OF_MEMORY); //LCOV_EXCL_LINE
		return BT_ERROR_OUT_OF_MEMORY;
	}

	return BT_ERROR_NONE;
}

int bt_adapter_set_name(const char *name)
{
	bluetooth_device_name_t loc_name = { {0} };
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(name);

	strncpy(loc_name.name, name, BLUETOOTH_DEVICE_NAME_LENGTH_MAX);
	loc_name.name[BLUETOOTH_DEVICE_NAME_LENGTH_MAX] = '\0';

	ret = _bt_get_error_code(bluetooth_set_local_name(&loc_name));
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return ret;
}

//LCOV_EXCL_START
int bt_adapter_get_visibility(bt_adapter_visibility_mode_e *mode, int *duration)
{
	bluetooth_discoverable_mode_t discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_CONNECTABLE;
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(mode);

	ret = _bt_get_error_code(bluetooth_get_discoverable_mode(&discoverable_mode));
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
		return ret; //LCOV_EXCL_LINE
	}

	*mode = _bt_get_bt_visibility_mode_e(discoverable_mode);

	if (duration)
		*duration = 0;

	if (discoverable_mode == BLUETOOTH_DISCOVERABLE_MODE_TIME_LIMITED_DISCOVERABLE) {
		if (duration == NULL)
			return BT_ERROR_NONE;
		ret = bluetooth_get_timeout_value(duration);
		if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
		} //LCOV_EXCL_LINE
	}

	return BT_ERROR_NONE;
}

int bt_adapter_set_visibility(bt_adapter_visibility_mode_e visibility_mode, int timeout_sec)
{
	bluetooth_discoverable_mode_t discoverable_mode = BLUETOOTH_DISCOVERABLE_MODE_CONNECTABLE;
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
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
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return error_code;
}

int bt_adapter_set_connectable_changed_cb(bt_adapter_connectable_changed_cb callback, void *user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_CONNECTABLE_CHANGED_EVENT, callback, user_data);
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return ret;
}

int bt_adapter_unset_connectable_changed_cb(void)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_CONNECTABLE_CHANGED_EVENT);
	return BT_ERROR_NONE;
}

int bt_adapter_get_connectable(bool *connectable)
{
	gboolean is_connectable = FALSE;
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(connectable);

	ret = _bt_get_error_code(bluetooth_is_connectable(&is_connectable));
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
		return ret;
	}

	*connectable = is_connectable ? true : false;

	return BT_ERROR_NONE;
}

int bt_adapter_set_connectable(bool connectable)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_get_error_code(bluetooth_set_connectable(connectable));
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return error_code;
}
//LCOV_EXCL_STOP

int bt_adapter_foreach_bonded_device(bt_adapter_bonded_device_cb foreach_cb, void *user_data)
{
	GPtrArray *dev_list = NULL;
	bt_device_info_s *dev_info = NULL;
	bluetooth_device_info_t *ptr = NULL;
	int ret = BT_ERROR_NONE;
	int i = 0;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(foreach_cb);

	dev_list = g_ptr_array_new();
	if (dev_list == NULL) {
		BT_ERR("OUT_OF_MEMORY(0x%08x)", BT_ERROR_OUT_OF_MEMORY); //LCOV_EXCL_LINE
		return BT_ERROR_OUT_OF_MEMORY;
	}

	ret = _bt_get_error_code(bluetooth_get_bonded_device_list(&dev_list));
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x) : Failed to get bonded device list", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
		return ret;
	}

	for (i = 0; i < dev_list->len; i++) { //LCOV_EXCL_LINE
		ptr = g_ptr_array_index(dev_list, i);
		if (ptr != NULL) {
			ret = _bt_get_bt_device_info_s(&dev_info, (bluetooth_device_info_t *)ptr);
			if (ret != BT_ERROR_NONE) {
				BT_ERR("%s(0x%08x) : Failed to get device info", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
				break;
			}

			if (!foreach_cb(dev_info, user_data)) {
				_bt_free_bt_device_info_s(dev_info);
				break;
			}
			_bt_free_bt_device_info_s(dev_info); //LCOV_EXCL_LINE
		} else {
			BT_ERR("OPERATION_FAILED(0x%08x)", BT_ERROR_OPERATION_FAILED); //LCOV_EXCL_LINE
			ret = BT_ERROR_OPERATION_FAILED;
			break;
		}
	}

	g_ptr_array_foreach(dev_list, (GFunc)g_free, NULL);
	g_ptr_array_free(dev_list, TRUE);

	return ret;
}

int bt_adapter_get_bonded_device_info(const char *remote_address, bt_device_info_s **device_info)
{
	int ret;
	bluetooth_device_address_t addr_hex = { {0,} };
	bluetooth_device_info_t *info;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address); //LCOV_EXCL_START

	info = (bluetooth_device_info_t *)malloc(sizeof(bluetooth_device_info_t));
	if (info == NULL)
		return BT_ERROR_OUT_OF_MEMORY;

	_bt_convert_address_to_hex(&addr_hex, remote_address);

	ret = _bt_get_error_code(bluetooth_get_bonded_device(&addr_hex, info));
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x) : Failed to run function",
					_bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} else {
		ret = _bt_get_bt_device_info_s(device_info, info);
		if (ret != BT_ERROR_NONE) {
			BT_ERR("%s(0x%08x) : Failed to get device info",
						_bt_convert_error_to_string(ret),
						ret); //LCOV_EXCL_LINE
		}
	}

	free(info);

	return ret; //LCOV_EXCL_STOP
}

int bt_adapter_free_device_info(bt_device_info_s *device_info)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(device_info);

	_bt_free_bt_device_info_s(device_info); //LCOV_EXCL_LINE

	return BT_ERROR_NONE; //LCOV_EXCL_LINE
}

int bt_adapter_is_service_used(const char *service_uuid, bool *used)
{
	int ret = BT_ERROR_NONE;
	gboolean is_used = FALSE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(service_uuid);
	BT_CHECK_INPUT_PARAMETER(used);

	if (strcmp(service_uuid, OPP_UUID) == 0) {
		*used = bluetooth_obex_server_is_activated();
	} else {
		ret = _bt_get_error_code(bluetooth_is_service_used(service_uuid, //LCOV_EXCL_LINE
							&is_used));
		*used = is_used ? true : false; //LCOV_EXCL_LINE
	}

	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x) : Failed to run function", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return ret;
}

int bt_adapter_set_state_changed_cb(bt_adapter_state_changed_cb callback, void *user_data)
{
	BT_DBG("");
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_STATE_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return ret;
}

//LCOV_EXCL_START
int bt_adapter_le_set_state_changed_cb(bt_adapter_le_state_changed_cb callback, void *user_data)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);

	_bt_le_adapter_init();
	_bt_set_cb(BT_EVENT_LE_STATE_CHANGED, callback, user_data);
	return BT_ERROR_NONE;
}
//LCOV_EXCL_STOP

int bt_adapter_set_name_changed_cb(bt_adapter_name_changed_cb callback, void *user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_NAME_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return ret;
}

int bt_adapter_set_visibility_mode_changed_cb(bt_adapter_visibility_mode_changed_cb callback, void *user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_VISIBILITY_MODE_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return ret;
}

int bt_adapter_set_device_discovery_state_changed_cb(bt_adapter_device_discovery_state_changed_cb callback, void *user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_DEVICE_DISCOVERY_STATE_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return ret;
}

#ifndef TIZEN_WEARABLE
int bt_adapter_le_set_device_discovery_state_changed_cb(bt_adapter_le_device_discovery_state_changed_cb callback, void *user_data)
{
	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);

	_bt_le_adapter_init();
	_bt_set_cb(BT_EVENT_LE_DEVICE_DISCOVERY_STATE_CHANGED, callback, user_data);
	return BT_ERROR_NONE;
}
#endif

int bt_adapter_unset_state_changed_cb(void)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_STATE_CHANGED);
	return BT_ERROR_NONE;
}

//LCOV_EXCL_START
int bt_adapter_le_unset_state_changed_cb(void)
{
	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_LE_STATE_CHANGED);
	_bt_le_adapter_deinit();
	return BT_ERROR_NONE;
}
//LCOV_EXCL_STOP

int bt_adapter_unset_name_changed_cb(void)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_NAME_CHANGED);
	return BT_ERROR_NONE;
}

int bt_adapter_unset_visibility_mode_changed_cb(void)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_VISIBILITY_MODE_CHANGED);
	return BT_ERROR_NONE;
}

int bt_adapter_set_visibility_duration_changed_cb(bt_adapter_visibility_duration_changed_cb callback, void *user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_VISIBILITY_DURATION_CHANGED, callback, user_data);
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return ret;
}

int bt_adapter_unset_visibility_duration_changed_cb(void)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_VISIBILITY_DURATION_CHANGED);
	return BT_ERROR_NONE;
}

int bt_adapter_unset_device_discovery_state_changed_cb(void)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_DEVICE_DISCOVERY_STATE_CHANGED);
	return BT_ERROR_NONE;
}

#ifndef TIZEN_WEARABLE
int bt_adapter_le_unset_device_discovery_state_changed_cb(void)
{
	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_LE_DEVICE_DISCOVERY_STATE_CHANGED);
	_bt_le_adapter_deinit();
	return BT_ERROR_NONE;
}
#endif

int bt_adapter_start_device_discovery(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_start_discovery(0, 0, BLUETOOTH_DEVICE_MAJOR_MASK_MISC));
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return error_code;
}

int bt_adapter_stop_device_discovery(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_cancel_discovery());
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return error_code;
}

int bt_adapter_is_discovering(bool *is_discovering)
{
	int ret = 0;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(is_discovering);

	ret = bluetooth_is_discovering();
	if (ret >= BLUETOOTH_ERROR_BASE) {
		*is_discovering = (ret == 1) ? true : false;
		return BT_ERROR_NONE;
	} else {
		ret = _bt_get_error_code(ret); //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
		return ret; //LCOV_EXCL_LINE
	}
}

#ifndef TIZEN_WEARABLE
int bt_adapter_le_start_device_discovery(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_start_le_discovery());
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return error_code;
}

int bt_adapter_le_stop_device_discovery(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_stop_le_discovery());
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code);
	}
	return error_code;
}

int bt_adapter_le_is_discovering(bool *is_discovering)
{
	int ret = 0;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(is_discovering);

	ret = bluetooth_is_le_discovering();
	if (ret >= BLUETOOTH_ERROR_BASE) {
		*is_discovering = (ret == 1) ? true : false;
		return BT_ERROR_NONE;
	} else {
		ret = _bt_get_error_code(ret); //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
		return ret; //LCOV_EXCL_LINE
	}
}
#endif

int bt_adapter_get_local_oob_data(unsigned char **hash, unsigned char **randomizer,
					int *hash_len, int *randomizer_len)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(hash);
	BT_CHECK_INPUT_PARAMETER(randomizer);
	BT_CHECK_INPUT_PARAMETER(hash_len);
	BT_CHECK_INPUT_PARAMETER(randomizer_len);

	bt_oob_data_t oob_data;

	ret = _bt_get_error_code(bluetooth_oob_read_local_data(&oob_data));
	if (BT_ERROR_NONE == ret) {
		*hash = g_memdup(oob_data.hash, BLUETOOTH_OOB_DATA_LENGTH);
		*randomizer = g_memdup(oob_data.randomizer,
						BLUETOOTH_OOB_DATA_LENGTH);
		*hash_len = BLUETOOTH_OOB_DATA_LENGTH;
		*randomizer_len = BLUETOOTH_OOB_DATA_LENGTH;
	} else {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	}
	return ret;
}

int bt_adapter_set_remote_oob_data(const char *remote_address,
				unsigned char *hash, unsigned char *randomizer,
				int hash_len, int randomizer_len)
{
	int ret = BT_ERROR_NONE;
	bluetooth_device_address_t addr_hex = { {0,} };
	bt_oob_data_t oob_data = { {0},};

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address); //LCOV_EXCL_START

	_bt_convert_address_to_hex(&addr_hex, remote_address);

	if (hash != NULL && randomizer != NULL) {
		memcpy(oob_data.hash, hash, hash_len);
		memcpy(oob_data.randomizer, randomizer, randomizer_len);
		oob_data.hash_len = hash_len;
		oob_data.randomizer_len = randomizer_len;
	}

	ret = _bt_get_error_code(bluetooth_oob_add_remote_data(&addr_hex, &oob_data)); //LCOV_EXCL_STOP
	if (BT_ERROR_NONE != ret) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return ret;
}

int bt_adapter_remove_remote_oob_data(const char *remote_address)
{
	int ret = BT_ERROR_NONE;
	bluetooth_device_address_t addr_hex = { {0,} };

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address);

	_bt_convert_address_to_hex(&addr_hex, remote_address); //LCOV_EXCL_LINE

	ret = _bt_get_error_code(bluetooth_oob_remove_remote_data(&addr_hex)); //LCOV_EXCL_LINE
	if (BT_ERROR_NONE != ret) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return ret; //LCOV_EXCL_LINE
}

//LCOV_EXCL_START
int bt_adapter_set_manufacturer_data(char *data, int len)
{

	int ret;
	bluetooth_manufacturer_data_t m_data = { 0 };

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(data);

	if (len + 2 > sizeof(m_data.data) || len < 0)
		return BT_ERROR_INVALID_PARAMETER;

	m_data.data_len = len;
	m_data.data[0] = len + 1;
	m_data.data[1] = 0xFF;

	memcpy(&m_data.data[2], data, len);

	ret = _bt_get_error_code(bluetooth_set_manufacturer_data(&m_data));
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return ret;
}

int bt_adapter_set_manufacturer_data_changed_cb(
		bt_adapter_manufacturer_data_changed_cb callback,
		void *user_data)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_MANUFACTURER_DATA_CHANGED,
			callback, user_data);
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return ret;
}

int bt_adapter_unset_manufacturer_data_changed_cb(void)
{
	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_MANUFACTURER_DATA_CHANGED);
	return BT_ERROR_NONE;
}

int bt_adapter_le_add_white_list(const char *address, bt_device_address_type_e address_type)
{
	int error_code = BT_ERROR_NONE;
	bluetooth_device_address_t addr_hex = { {0,} };

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(address);
	_bt_convert_address_to_hex(&addr_hex, address);

	error_code = _bt_get_error_code(bluetooth_add_white_list(&addr_hex, address_type));
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return error_code;
}

int bt_adapter_le_remove_white_list(const char *address, bt_device_address_type_e address_type)
{
	int error_code = BT_ERROR_NONE;
	bluetooth_device_address_t addr_hex = { {0,} };

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(address);
	_bt_convert_address_to_hex(&addr_hex, address);

	error_code = _bt_get_error_code(bluetooth_remove_white_list(&addr_hex, address_type));
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return error_code;
}

int bt_adapter_le_clear_white_list(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_get_error_code(bluetooth_clear_white_list());
	if (error_code != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE

	return error_code;
}

int bt_adapter_le_set_scan_mode(bt_adapter_le_scan_mode_e scan_mode)
{
	int ret = BT_ERROR_NONE;
	bluetooth_le_scan_params_t scan_params;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();

	scan_params.type = BT_ADAPTER_LE_ACTIVE_SCAN;

	if (scan_mode == BT_ADAPTER_LE_SCAN_MODE_BALANCED) {
		scan_params.interval = 5000;
		scan_params.window = 2000;
	} else if (scan_mode == BT_ADAPTER_LE_SCAN_MODE_LOW_LATENCY) {
		scan_params.interval = 5000;
		scan_params.window = 5000;
	} else if (scan_mode == BT_ADAPTER_LE_SCAN_MODE_LOW_ENERGY) {
		scan_params.interval = 5000;
		scan_params.window = 500;
	} else
		return BT_ERROR_INVALID_PARAMETER;

	ret = _bt_get_error_code(bluetooth_set_scan_parameters(&scan_params));
	if (ret != BT_ERROR_NONE) { //LCOV_EXCL_LINE
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	} //LCOV_EXCL_LINE
	return ret;
}
//LCOV_EXCL_STOP

int bt_adapter_le_create_advertiser(bt_advertiser_h *advertiser)
{
	bt_advertiser_s *__adv = NULL;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	__adv = (bt_advertiser_s*)g_malloc0(sizeof(bt_advertiser_s));
	if (__adv == NULL) {
		BT_ERR("OUT_OF_MEMORY(0x%08x)", BT_ERROR_OUT_OF_MEMORY); //LCOV_EXCL_LINE
		return BT_ERROR_OUT_OF_MEMORY; //LCOV_EXCL_LINE
	}
	__adv->handle = GPOINTER_TO_INT(__adv);

	*advertiser = (bt_advertiser_h)__adv;

	advertiser_list = g_slist_append(advertiser_list, __adv);

	return BT_ERROR_NONE;
}

int bt_adapter_le_destroy_advertiser(bt_advertiser_h advertiser)
{
	int ret = BT_ERROR_NONE;
	int error_code;
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	_bt_unset_cb(BT_EVENT_ADVERTISING_STATE_CHANGED);

	error_code = bluetooth_set_advertising(__adv->handle, FALSE);
	ret = _bt_get_error_code(error_code);
	if (ret != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE

	advertiser_list = g_slist_remove(advertiser_list, __adv);

	/* Free advertising data */
	g_free(__adv->adv_data);
	g_free(__adv->scan_rsp_data);
	g_free(__adv);

	return BT_ERROR_NONE;
}

static int __bt_remove_ad_data_by_type(char *in_data, unsigned int in_len,
		char in_type, char **data, unsigned int *data_len)
{
	if (in_data == NULL || data == NULL || data_len == NULL)
		return BT_ERROR_OPERATION_FAILED;

	int i;
	int len = 0;
	int type = 0;
	char *p;

	for (i = 0; i < in_len; i++) { //LCOV_EXCL_LINE
		len = in_data[i];
		if (len <= 0 || i + 1 >= in_len) {
			BT_ERR("Invalid advertising data"); //LCOV_EXCL_LINE
			return BT_ERROR_OPERATION_FAILED; //LCOV_EXCL_LINE
		}

		type = in_data[i + 1];
		if (type == in_type) {
			i = i + 2;
			len--;
			break;
		}

		i += len; //LCOV_EXCL_LINE
		len = 0; //LCOV_EXCL_LINE
	}

	if (i + len > in_len) {
		BT_ERR("Invalid advertising data"); //LCOV_EXCL_LINE
		return BT_ERROR_OPERATION_FAILED; //LCOV_EXCL_LINE
	} else if (len == 0 &&
			in_type != BT_ADAPTER_LE_ADVERTISING_DATA_LOCAL_NAME &&
			in_type != BT_ADAPTER_LE_ADVERTISING_DATA_TX_POWER_LEVEL) {
		BT_INFO("AD Type 0x%02x data is not set", in_type); //LCOV_EXCL_LINE
		return BT_ERROR_OPERATION_FAILED; //LCOV_EXCL_LINE
	}

	p = (char *)malloc(sizeof(char) * (in_len - len));
	if (p == NULL) {
		return BT_ERROR_OUT_OF_MEMORY;
	}

	memcpy(p, in_data, sizeof(char) * i);
	memcpy(p + i, in_data + i + len, sizeof(char) * (in_len - len - i));

	*data = p;
	*data_len = in_len - len;

	return BT_ERROR_NONE;
}

int bt_adapter_le_add_advertising_data(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, bt_adapter_le_packet_data_type_e data_type,
		void *data, unsigned int data_size)
{
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;
	char **p;
	unsigned int *len;
	unsigned int *system_data_len;
	char *new_p;
	bt_adapter_le_advertising_data_type_e adv_type;
	int adv_flag_len = 0;
	int adv_ext_len = 0;

	adv_type = (bt_adapter_le_advertising_data_type_e)data_type;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	if ((data == NULL || data_size == 0) &&
		(adv_type != BT_ADAPTER_LE_ADVERTISING_DATA_LOCAL_NAME &&
		adv_type != BT_ADAPTER_LE_ADVERTISING_DATA_TX_POWER_LEVEL)) {
		BT_ERR("empty data for packet type %d", pkt_type); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER; //LCOV_EXCL_LINE
	}

	BT_CHECK_INPUT_PARAMETER(advertiser);

	if (pkt_type == BT_ADAPTER_LE_PACKET_ADVERTISING) {
		p = &__adv->adv_data;
		len = &__adv->adv_data_len;
		system_data_len = &__adv->adv_system_data_len;
		adv_flag_len = 3;
	} else if (pkt_type == BT_ADAPTER_LE_PACKET_SCAN_RESPONSE) {
		p = &__adv->scan_rsp_data;
		len = &__adv->scan_rsp_data_len;
		system_data_len = &__adv->scan_rsp_system_data_len;
	} else
		return BT_ERROR_INVALID_PARAMETER;

	if (adv_type == BT_ADAPTER_LE_ADVERTISING_DATA_LOCAL_NAME ||
		adv_type == BT_ADAPTER_LE_ADVERTISING_DATA_TX_POWER_LEVEL)
		adv_ext_len = *system_data_len + 1;

	/* 2 bytes are required for Length and AD Type */
	if (adv_flag_len + *len + adv_ext_len + data_size + 2 > 31) {
		BT_ERR("Quota exceeded"); //LCOV_EXCL_LINE
		return BT_ERROR_QUOTA_EXCEEDED; //LCOV_EXCL_LINE
	}

	if (*len == 0)
		*p = NULL;

	new_p = realloc(*p, sizeof(char) * (*len + data_size + 2));
	if (new_p == NULL) {
		return BT_ERROR_OUT_OF_MEMORY;
	}

	new_p[*len] = data_size + 1;
	new_p[*len + 1] = adv_type;
	if ((data != NULL) && (data_size != 0))
		memcpy(new_p + (*len + 2), data, data_size);

	*p = new_p;
	*len += data_size + 2;

	if (adv_type == BT_ADAPTER_LE_ADVERTISING_DATA_LOCAL_NAME ||
		adv_type == BT_ADAPTER_LE_ADVERTISING_DATA_TX_POWER_LEVEL)
		*system_data_len += 1;

	return BT_ERROR_NONE;
}

int bt_adapter_le_remove_advertising_data(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, bt_adapter_le_packet_data_type_e data_type)
{
	int ret = BT_ERROR_NONE;
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;
	char **p;
	unsigned int *len;
	unsigned int *system_data_len;
	char *new_p = NULL;
	unsigned int new_len = 0;
	bt_adapter_le_advertising_data_type_e adv_type;

	adv_type = (bt_adapter_le_advertising_data_type_e)data_type;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	switch (pkt_type) {
	case BT_ADAPTER_LE_PACKET_ADVERTISING:
		p = &__adv->adv_data;
		len = &__adv->adv_data_len;
		system_data_len = &__adv->adv_system_data_len;
		break;

	case BT_ADAPTER_LE_PACKET_SCAN_RESPONSE:
		p = &__adv->scan_rsp_data; //LCOV_EXCL_LINE
		len = &__adv->scan_rsp_data_len; //LCOV_EXCL_LINE
		system_data_len = &__adv->scan_rsp_system_data_len; //LCOV_EXCL_LINE
		break; //LCOV_EXCL_LINE

	default:
		BT_ERR("Unknown LE packet type : %d", pkt_type); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER; //LCOV_EXCL_LINE
	}

	ret = __bt_remove_ad_data_by_type(*p, *len, adv_type, &new_p, &new_len);
	if (ret != BT_ERROR_NONE) {
		return ret;
	}

	free(*p);
	*p = new_p;
	*len = new_len;

	if (adv_type == BT_ADAPTER_LE_ADVERTISING_DATA_LOCAL_NAME ||
		adv_type == BT_ADAPTER_LE_ADVERTISING_DATA_TX_POWER_LEVEL)
		*system_data_len -= 1; //LCOV_EXCL_LINE

	return ret;
}

static int __bt_convert_string_to_uuid(const char *string, char **uuid, int *bit)
{
	char *data;

	if (strlen(string) == 4)  { // 16 bit uuid
		unsigned short val;
		char *stop;
		data = g_malloc0(sizeof(char) * 2);
		if (data == NULL)
			return BT_ERROR_OUT_OF_MEMORY; //LCOV_EXCL_LINE

		val = strtol(string, &stop, 16);
		val = htons(val);
		memcpy(data, &val, 2);
		*uuid = data;
		*bit = 16; //LCOV_EXCL_START
	} else if (strlen(string) == 36)  { // 128 bit uuid
		if (string[8] != '-' || string[13] != '-' ||
			string[18] != '-' || string[23] != '-') {
			BT_ERR("Invalid UUID"); //LCOV_EXCL_LINE
			return BT_ERROR_INVALID_PARAMETER; //LCOV_EXCL_LINE
		}

		int ret;
		unsigned int val0, val4;
		unsigned short val1, val2, val3, val5;
		data = g_malloc0(sizeof(char) * 16);
		/* Fix : NULL_RETURNS */
		if (data == NULL)
			return BT_ERROR_OUT_OF_MEMORY;

		ret = sscanf(string, "%08x-%04hx-%04hx-%04hx-%08x%04hx",
					&val0, &val1, &val2, &val3, &val4, &val5);
		if (ret != 6)
		{
			g_free(data);
			return BT_ERROR_OPERATION_FAILED;
		}

		val0 = htonl(val0);
		val1 = htons(val1);
		val2 = htons(val2);
		val3 = htons(val3);
		val4 = htonl(val4);
		val5 = htons(val5);

		memcpy(data, &val0, 4);
		memcpy(data + 4, &val1, 2);
		memcpy(data + 6, &val2, 2);
		memcpy(data + 8, &val3, 2);
		memcpy(data + 10, &val4, 4);
		memcpy(data + 14, &val5, 2);

		*uuid = data;
		*bit = 128;
	} else {
		BT_ERR("Invalid UUID"); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER; //LCOV_EXCL_LINE
	}

	return BT_ERROR_NONE; //LCOV_EXCL_STOP
}

static int __bt_convert_byte_ordering(char *data, int data_len, char **converted_data)
{
	char *swp;
	int i, j;

	/* Convert to little endian */
	swp = g_malloc0(data_len);
	/* Fix : NULL_RETURNS */
	if (swp == NULL)
		return BT_ERROR_OUT_OF_MEMORY;
	for (i = 0, j = data_len - 1; i < data_len; i++, j--)
		swp[i] = data[j];

	*converted_data = swp;

	return BT_ERROR_NONE;
}

static int __bt_find_adv_data_type(bt_advertiser_h advertiser,
			bt_adapter_le_packet_type_e pkt_type, bt_adapter_le_advertising_data_type_e data_type,
			char **data_ptr, int *data_len)
{
	int type;
	int len;
	int i;
	char *adv_data = NULL;
	int adv_len = 0;
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;

	if (pkt_type == BT_ADAPTER_LE_PACKET_ADVERTISING) {
		adv_data = __adv->adv_data;
		adv_len = __adv->adv_data_len;
	} else if (pkt_type == BT_ADAPTER_LE_PACKET_SCAN_RESPONSE) {
		adv_data = __adv->scan_rsp_data;
		adv_len = __adv->scan_rsp_data_len;
	} else
		return BT_ERROR_INVALID_PARAMETER;

	if (!adv_data)
		return BT_ERROR_OPERATION_FAILED;

	for (i = 0; i <adv_len ; i++) { //LCOV_EXCL_START
		len = adv_data[i];
		type = adv_data[i + 1];

		if (type == data_type) {
			*data_ptr = &adv_data[i];
			*data_len = len;
			return BT_ERROR_NONE;
		} else {
			i = i + adv_data[i]; //LCOV_EXCL_STOP
		}
	}

	return BT_ERROR_NONE;
}

//LCOV_EXCL_START
static int __bt_append_adv_type_data(bt_advertiser_h advertiser,
			bt_adapter_le_packet_type_e pkt_type,
			char *new_data, int new_data_len,
			bt_adapter_le_advertising_data_type_e data_type, char *data_ptr, int data_len)
{
	int type;
	int len;
	int dest_type;
	int i;
	char *new_adv = NULL;
	char *adv_data = NULL;
	int adv_len = 0;
	int adv_flag_len = 0;
	int system_data_len = 0;
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;

	if (pkt_type == BT_ADAPTER_LE_PACKET_ADVERTISING) {
		adv_data = __adv->adv_data;
		adv_len = __adv->adv_data_len;
		system_data_len = __adv->adv_system_data_len;
		adv_flag_len = 3;
	} else if (pkt_type == BT_ADAPTER_LE_PACKET_SCAN_RESPONSE) {
		adv_data = __adv->scan_rsp_data;
		adv_len = __adv->scan_rsp_data_len;
		system_data_len = __adv->scan_rsp_system_data_len;
	} else
		return BT_ERROR_INVALID_PARAMETER;

	if (!adv_data)
		return BT_ERROR_OPERATION_FAILED;

	dest_type = data_ptr[1];

	if (data_type != dest_type) {
		BT_ERR("Invalid data type"); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER; //LCOV_EXCL_LINE
	}

	if (adv_flag_len + adv_len + system_data_len + new_data_len > 31) {
		BT_ERR("Quota exceeded"); //LCOV_EXCL_LINE
		return BT_ERROR_QUOTA_EXCEEDED; //LCOV_EXCL_LINE
	}

	new_adv = g_malloc0(adv_len + new_data_len);
	if (!new_adv)
		return BT_ERROR_OUT_OF_MEMORY;

	for (i = 0; i < adv_len; i++) {
		len = adv_data[i];
		type = adv_data[i + 1];

		if (type == dest_type) {
			int rest_data_len;

			memcpy(new_adv + i, &adv_data[i], len + 1);
			memcpy(new_adv + i + len + 1, new_data, new_data_len);
			new_adv[i] += new_data_len;

			rest_data_len = adv_len - (i  + len + 1);
			if (rest_data_len > 0)
				memcpy(new_adv + i + len + 1 + new_data_len,
						&adv_data[i + len + 1], rest_data_len);

			break;
		} else {
			memcpy(new_adv + i, &adv_data[i], len + 1);
			i = i + len;
		}
	}

	if (pkt_type == BT_ADAPTER_LE_PACKET_ADVERTISING) {
		g_free(__adv->adv_data);
		__adv->adv_data = new_adv;
		__adv->adv_data_len += new_data_len;
	} else if (pkt_type == BT_ADAPTER_LE_PACKET_SCAN_RESPONSE) {
		g_free(__adv->scan_rsp_data);
		__adv->scan_rsp_data = new_adv;
		__adv->scan_rsp_data_len += new_data_len;
	}

	return BT_ERROR_NONE;
}
//LCOV_EXCL_STOP

int bt_adapter_le_add_advertising_service_uuid(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, const char *uuid)
{
	int ret = BT_ERROR_NONE;
	bt_adapter_le_advertising_data_type_e data_type = 0;
	int byte_len = 0;
	int uuid_bit = 0;
	char *uuid_ptr = NULL;
	char *data_ptr = NULL;
	char *converted_uuid = NULL;
	int data_len = 0;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);
	BT_CHECK_INPUT_PARAMETER(uuid);

	ret = __bt_convert_string_to_uuid(uuid, &uuid_ptr, &uuid_bit);
	if (ret != BT_ERROR_NONE)
		return ret;

	if (uuid_bit == 16) {
		byte_len = 2;
		data_type = BT_ADAPTER_LE_ADVERTISING_DATA_INCOMP_LIST_16_BIT_SERVICE_CLASS_UUIDS;
	} else if (uuid_bit == 128) { //LCOV_EXCL_LINE
		byte_len = 16; //LCOV_EXCL_LINE
		data_type = BT_ADAPTER_LE_ADVERTISING_DATA_INCOMP_LIST_128_BIT_SERVICE_CLASS_UUIDS; //LCOV_EXCL_LINE
	}

	__bt_convert_byte_ordering(uuid_ptr, byte_len, &converted_uuid);
	g_free(uuid_ptr);

	__bt_find_adv_data_type(advertiser, pkt_type, data_type, &data_ptr, &data_len);
	if (data_ptr) {
		ret = __bt_append_adv_type_data(advertiser, pkt_type, converted_uuid, byte_len, data_type, data_ptr, data_len); //LCOV_EXCL_LINE
	} else {
		ret = bt_adapter_le_add_advertising_data(advertiser, pkt_type, data_type, converted_uuid, byte_len);
	}
	g_free(converted_uuid);

	return ret;
}

int bt_adapter_le_add_advertising_service_solicitation_uuid(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, const char *uuid)
{
	int ret = BT_ERROR_NONE;
	bt_adapter_le_advertising_data_type_e data_type = 0;
	int byte_len = 0;
	int uuid_bit = 0;
	char *uuid_ptr = NULL;
	char *data_ptr = NULL;
	char *converted_uuid = NULL;
	int data_len = 0;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);
	BT_CHECK_INPUT_PARAMETER(uuid);

	ret = __bt_convert_string_to_uuid(uuid, &uuid_ptr, &uuid_bit);
	if (ret != BT_ERROR_NONE)
		return ret;

	if (uuid_bit == 16) {
		byte_len = 2;
		data_type = BT_ADAPTER_LE_ADVERTISING_DATA_16_BIT_SERVICE_SOLICITATION_UUIDS;
	} else if (uuid_bit == 128) { //LCOV_EXCL_LINE
		byte_len = 16; //LCOV_EXCL_LINE
		data_type = BT_ADAPTER_LE_ADVERTISING_DATA_128_BIT_SERVICE_SOLICITATION_UUIDS; //LCOV_EXCL_LINE
	}

	__bt_convert_byte_ordering(uuid_ptr, byte_len, &converted_uuid);
	g_free(uuid_ptr);

	__bt_find_adv_data_type(advertiser, pkt_type, data_type, &data_ptr, &data_len);
	if (data_ptr) {
		ret = __bt_append_adv_type_data(advertiser, pkt_type, converted_uuid, byte_len, data_type, data_ptr, data_len); //LCOV_EXCL_LINE
	} else {
		ret = bt_adapter_le_add_advertising_data(advertiser, pkt_type, data_type, converted_uuid, byte_len);
	}
	g_free(converted_uuid);

	return ret;
}

int bt_adapter_le_add_advertising_service_data(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, const char *uuid,
		const char *service_data, int service_data_len)
{
	int ret = BT_ERROR_NONE;
	char *data_ptr = NULL;
	int data_len;
	char *adv_data = NULL;
	int uuid_bit;
	char *uuid_ptr;
	int byte_len;
	char *converted_uuid = NULL;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);
	BT_CHECK_INPUT_PARAMETER(service_data);

	__bt_find_adv_data_type(advertiser, pkt_type,
				BT_ADAPTER_LE_ADVERTISING_DATA_SERVICE_DATA,
				&data_ptr, &data_len);
	if (data_ptr) {
		BT_ERR("Aleady existed"); //LCOV_EXCL_LINE
		return BT_ERROR_ALREADY_DONE; //LCOV_EXCL_LINE
	}

	ret = __bt_convert_string_to_uuid(uuid, &uuid_ptr, &uuid_bit);
	if (ret != BT_ERROR_NONE)
		return ret;

	if (uuid_bit == 16) {
		byte_len = 2;
	} else if (uuid_bit == 128) { //LCOV_EXCL_LINE
		BT_ERR("128 bit UUID is not supported"); //LCOV_EXCL_LINE
		g_free(uuid_ptr); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER; //LCOV_EXCL_LINE
	}

	__bt_convert_byte_ordering(uuid_ptr, byte_len, &converted_uuid);
	g_free(uuid_ptr);

	adv_data = g_malloc0(sizeof(char) * (service_data_len + 2));
	if (!adv_data) {
		g_free(converted_uuid); //LCOV_EXCL_LINE
		return BT_ERROR_OUT_OF_MEMORY;
	}

	memcpy(adv_data, converted_uuid, 2);
	memcpy(adv_data + 2, service_data, service_data_len);

	ret = bt_adapter_le_add_advertising_data(advertiser,
		pkt_type, BT_ADAPTER_LE_ADVERTISING_DATA_SERVICE_DATA,
		adv_data, service_data_len + 2);

	g_free(adv_data);
	g_free(converted_uuid);

	return ret;
}

int bt_adapter_le_set_advertising_appearance(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, int appearance)
{
	int ret = BT_ERROR_NONE;
	char *data_ptr = NULL;
	int data_len;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	__bt_find_adv_data_type(advertiser, pkt_type, BT_ADAPTER_LE_ADVERTISING_DATA_APPEARANCE,
				&data_ptr, &data_len);
	if (data_ptr) {
		BT_ERR("Aleady existed"); //LCOV_EXCL_LINE
		return BT_ERROR_ALREADY_DONE; //LCOV_EXCL_LINE
	}

	ret = bt_adapter_le_add_advertising_data(advertiser,
		pkt_type, BT_ADAPTER_LE_ADVERTISING_DATA_APPEARANCE, &appearance, 2);

	return ret;
}

int bt_adapter_le_add_advertising_manufacturer_data(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, int manufacturer_id,
		const char *manufacturer_data, int manufacturer_data_len)
{
	int ret = BT_ERROR_NONE;
	char *data_ptr = NULL;
	int data_len;
	char *adv_data = NULL;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);
	BT_CHECK_INPUT_PARAMETER(manufacturer_data);

	__bt_find_adv_data_type(advertiser, pkt_type,
				BT_ADAPTER_LE_ADVERTISING_DATA_MANUFACTURER_SPECIFIC_DATA,
				&data_ptr, &data_len);
	if (data_ptr) {
		BT_ERR("Aleady existed"); //LCOV_EXCL_LINE
		return BT_ERROR_ALREADY_DONE; //LCOV_EXCL_LINE
	}

	adv_data = g_malloc0(sizeof(char) * (manufacturer_data_len + 2));
	if (!adv_data)
		return BT_ERROR_OUT_OF_MEMORY;

	adv_data[0] = manufacturer_id & 0xffffffff;
	adv_data[1] = (manufacturer_id & 0xff00) >> 8;
	memcpy(adv_data + 2, manufacturer_data, manufacturer_data_len);

	ret = bt_adapter_le_add_advertising_data(advertiser,
		pkt_type, BT_ADAPTER_LE_ADVERTISING_DATA_MANUFACTURER_SPECIFIC_DATA,
		adv_data, manufacturer_data_len + 2);

	g_free(adv_data);

	return ret;
}

int bt_adapter_le_set_advertising_device_name(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, bool include_name)
{
	int ret = BT_ERROR_NONE;
	char *data_ptr = NULL;
	int data_len;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	if (!include_name) {
		ret = bt_adapter_le_remove_advertising_data(advertiser, pkt_type, //LCOV_EXCL_LINE
			BT_ADAPTER_LE_ADVERTISING_DATA_LOCAL_NAME);
		return ret;
	}

	__bt_find_adv_data_type(advertiser, pkt_type,
				BT_ADAPTER_LE_ADVERTISING_DATA_LOCAL_NAME,
				&data_ptr, &data_len);
	if (data_ptr) {
		BT_ERR("Aleady existed"); //LCOV_EXCL_LINE
		return BT_ERROR_ALREADY_DONE; //LCOV_EXCL_LINE
	}

	ret = bt_adapter_le_add_advertising_data(advertiser,
		pkt_type, BT_ADAPTER_LE_ADVERTISING_DATA_LOCAL_NAME,
		NULL, 0);

	return ret;
}

int bt_adapter_le_set_advertising_tx_power_level(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, bool include_tx_power)
{
	int ret = BT_ERROR_NONE;
	char *data_ptr = NULL;
	int data_len;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	if (!include_tx_power) {
		ret = bt_adapter_le_remove_advertising_data(advertiser, pkt_type, //LCOV_EXCL_LINE
			BT_ADAPTER_LE_ADVERTISING_DATA_TX_POWER_LEVEL);
		return ret;
	}

	__bt_find_adv_data_type(advertiser, pkt_type,
				BT_ADAPTER_LE_ADVERTISING_DATA_TX_POWER_LEVEL,
				&data_ptr, &data_len);
	if (data_ptr) {
		BT_ERR("Aleady existed"); //LCOV_EXCL_LINE
		return BT_ERROR_ALREADY_DONE; //LCOV_EXCL_LINE
	}

	ret = bt_adapter_le_add_advertising_data(advertiser,
		pkt_type, BT_ADAPTER_LE_ADVERTISING_DATA_TX_POWER_LEVEL,
		NULL, 0);

	return ret;
}

int bt_adapter_le_clear_advertising_data(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type)
{
	int ret = BT_ERROR_NONE;
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;
	char **p;
	unsigned int *len;
	unsigned int *system_data_len;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	switch (pkt_type) {
	case BT_ADAPTER_LE_PACKET_ADVERTISING:
		p = &__adv->adv_data;
		len = &__adv->adv_data_len;
		system_data_len = &__adv->adv_system_data_len;
		break;

	case BT_ADAPTER_LE_PACKET_SCAN_RESPONSE:
		p = &__adv->scan_rsp_data;
		len = &__adv->scan_rsp_data_len;
		system_data_len = &__adv->scan_rsp_system_data_len;
		break;

	default:
		BT_ERR("Unknown LE packet type : %d", pkt_type); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER; //LCOV_EXCL_LINE
	}

	if (*p) {
		free(*p);
		*p = NULL;
	}
	*len = 0;
	*system_data_len = 0;

	return ret;
}

#ifndef TIZEN_WEARABLE
int bt_adapter_le_start_advertising(bt_advertiser_h advertiser,
		bt_adapter_le_advertising_params_s *adv_params,
		bt_adapter_le_advertising_state_changed_cb cb, void *user_data)
{
	int ret = BT_ERROR_NONE;
	int error_code;
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;
	bluetooth_advertising_data_t adv = { {0} };
	bluetooth_scan_resp_data_t resp = { {0} };
	bluetooth_advertising_params_t param;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	if (__adv->adv_data_len > 0 && __adv->adv_data) { //LCOV_EXCL_START
		memcpy(adv.data, __adv->adv_data, __adv->adv_data_len);
		error_code = bluetooth_set_advertising_data(__adv->handle, &adv, __adv->adv_data_len);
		ret = _bt_get_error_code(error_code);
		if (ret != BT_ERROR_NONE) {
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
			return ret; //LCOV_EXCL_STOP
		}
	}

	if (__adv->scan_rsp_data_len > 0 && __adv->scan_rsp_data) { //LCOV_EXCL_START
		memcpy(resp.data, __adv->scan_rsp_data, __adv->scan_rsp_data_len);
		error_code = bluetooth_set_scan_response_data(__adv->handle, &resp, __adv->scan_rsp_data_len);
		ret = _bt_get_error_code(error_code);
		if (ret != BT_ERROR_NONE) {
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret);
			return ret; //LCOV_EXCL_STOP
		}
	}

	if (adv_params == NULL) {
		error_code = bluetooth_set_advertising(__adv->handle, TRUE); //LCOV_EXCL_LINE
	} else {
		param.interval_min = adv_params->interval_min;
		param.interval_max = adv_params->interval_max;
		param.filter_policy = BT_ADAPTER_LE_ADVERTISING_FILTER_DEFAULT;
		param.type = BT_ADAPTER_LE_ADVERTISING_CONNECTABLE;
		error_code = bluetooth_set_custom_advertising(__adv->handle, TRUE, &param);
	}

	ret = _bt_get_error_code(error_code);
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
		return ret;
	}

	_bt_set_cb(BT_EVENT_ADVERTISING_STATE_CHANGED, cb, user_data);

	return ret;
}
#endif

int bt_adapter_le_stop_advertising(bt_advertiser_h advertiser)
{
	int ret = BT_ERROR_NONE;
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	ret = _bt_get_error_code(bluetooth_set_advertising(__adv->handle, FALSE));
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
	}

	return ret;
}

int bt_adapter_le_start_advertising_new(bt_advertiser_h advertiser,
		bt_adapter_le_advertising_state_changed_cb cb, void *user_data)
{
	int ret = BT_ERROR_NONE;
	int error_code;
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;
	bluetooth_advertising_data_t adv = { {0} };
	bluetooth_scan_resp_data_t resp = { {0} };
	bluetooth_advertising_params_t param;
	float interval = 500;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	if (__adv->adv_data_len > 0 && __adv->adv_data) { //LCOV_EXCL_START
		memcpy(adv.data, __adv->adv_data, __adv->adv_data_len);
		error_code = bluetooth_set_advertising_data(__adv->handle, &adv, __adv->adv_data_len);
		ret = _bt_get_error_code(error_code);
		if (ret != BT_ERROR_NONE) {
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_STOP
			return ret;
		}
	}

	if (__adv->scan_rsp_data_len > 0 && __adv->scan_rsp_data) { //LCOV_EXCL_START
		memcpy(resp.data, __adv->scan_rsp_data, __adv->scan_rsp_data_len);
		error_code = bluetooth_set_scan_response_data(__adv->handle, &resp, __adv->scan_rsp_data_len);
		ret = _bt_get_error_code(error_code);
		if (ret != BT_ERROR_NONE) {
			BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_STOP
			return ret;
		}
	}

	if (__adv->adv_params.mode == BT_ADAPTER_LE_ADVERTISING_MODE_BALANCED)
		interval = 500;
	else if (__adv->adv_params.mode == BT_ADAPTER_LE_ADVERTISING_MODE_LOW_LATENCY)
		interval = 150;
	else if (__adv->adv_params.mode == BT_ADAPTER_LE_ADVERTISING_MODE_LOW_ENERGY)
		interval = 1000;

	param.interval_min = interval;
	param.interval_max = interval;
	param.filter_policy = __adv->adv_params.filter_policy;
	param.type = __adv->adv_params.type;
	error_code = bluetooth_set_custom_advertising(__adv->handle, TRUE, &param);

	ret = _bt_get_error_code(error_code);
	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
		return ret;
	}

	__adv->cb = cb;
	__adv->user_data = user_data;

	return ret;
}

void _bt_adapter_le_invoke_advertising_state_cb(int handle, int result, bt_adapter_le_advertising_state_e adv_state)
{
	const GSList *l = NULL;

	for (l = advertiser_list; l; l = g_slist_next(l)) {
		bt_advertiser_s *__adv = (bt_advertiser_s *)l->data;
		if (__adv->handle == handle) {
			if (__adv->cb == NULL) {
				BT_ERR("advertiser cb is NULL"); //LCOV_EXCL_LINE
				return; //LCOV_EXCL_LINE
			}

			__adv->cb(result, (bt_advertiser_h)__adv, adv_state, __adv->user_data);
			return;
		}
	}

	BT_ERR("No available advertiser"); //LCOV_EXCL_LINE
}

int bt_adapter_le_set_advertising_mode(bt_advertiser_h advertiser,
		bt_adapter_le_advertising_mode_e mode)
{
	int error_code = BT_ERROR_NONE;
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	if (mode < BT_ADAPTER_LE_ADVERTISING_MODE_BALANCED ||
		mode > BT_ADAPTER_LE_ADVERTISING_MODE_LOW_ENERGY)
		return BT_ERROR_INVALID_PARAMETER;

	error_code = _bt_get_error_code(bluetooth_check_privilege_advertising_parameter());
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
		return BT_ERROR_PERMISSION_DENIED; //LCOV_EXCL_LINE
	}

	// TODO : Before set the mode, check the inprogress status
	__adv->adv_params.mode = mode;

	return error_code;
}

//LCOV_EXCL_START
int bt_adapter_le_set_advertising_filter_policy(bt_advertiser_h advertiser,
		bt_adapter_le_advertising_filter_policy_e filter_policy)
{
	int error_code = BT_ERROR_NONE;
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	if (filter_policy < BT_ADAPTER_LE_ADVERTISING_FILTER_DEFAULT ||
		filter_policy > BT_ADAPTER_LE_ADVERTISING_FILTER_ALLOW_SCAN_CONN_WL)
		return BT_ERROR_INVALID_PARAMETER;

	error_code = _bt_get_error_code(bluetooth_check_privilege_advertising_parameter());
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
		return BT_ERROR_PERMISSION_DENIED;
	}

	// TODO : Before set the filter policy, check the inprogress status
	__adv->adv_params.filter_policy = filter_policy;

	return error_code;
}
//LCOV_EXCL_STOP

int bt_adapter_le_set_advertising_connectable(bt_advertiser_h advertiser, bool connectable)
{
	int error_code = BT_ERROR_NONE;
	bt_advertiser_s *__adv = (bt_advertiser_s *)advertiser;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(advertiser);

	error_code = _bt_get_error_code(bluetooth_check_privilege_advertising_parameter());
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
		return BT_ERROR_PERMISSION_DENIED; //LCOV_EXCL_LINE
	}

	if (connectable)
		__adv->adv_params.type = BT_ADAPTER_LE_ADVERTISING_CONNECTABLE; //LCOV_EXCL_LINE
	else
		__adv->adv_params.type = BT_ADAPTER_LE_ADVERTISING_SCANNABLE;

	// TODO : Before set the type, check the inprogress status

	return error_code;
}

//LCOV_EXCL_START
int bt_adapter_le_enable_privacy(bool enable_privacy)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();

	error_code = _bt_get_error_code(bluetooth_enable_le_privacy(enable_privacy));

	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	}
	return error_code;
}

static void __bt_adapter_le_convert_scan_filter(bluetooth_le_scan_filter_t *dest, bt_le_scan_filter_s *src)
{
	int bit;
	char *data;

	memset(dest, 0x00, sizeof(bluetooth_le_scan_filter_t));

	if (src->device_address) {
		dest->added_features |= BLUETOOTH_LE_SCAN_FILTER_FEATURE_DEVICE_ADDRESS;
		_bt_convert_address_to_hex(&dest->device_address, src->device_address);
	}

	if (src->device_name) {
		dest->added_features |= BLUETOOTH_LE_SCAN_FILTER_FEATURE_DEVICE_NAME;
		strncpy(dest->device_name, src->device_name, BLUETOOTH_ADVERTISING_DATA_LENGTH_MAX);
		dest->device_name[BLUETOOTH_ADVERTISING_DATA_LENGTH_MAX - 1] = '\0';
	}

	if (src->service_uuid) {
		if (__bt_convert_string_to_uuid(src->service_uuid, &data, &bit) == BT_ERROR_NONE) {
			dest->added_features |= BLUETOOTH_LE_SCAN_FILTER_FEATURE_SERVICE_UUID;
			if (bit == 16)
				dest->service_uuid.data_len = 2;
			else
				dest->service_uuid.data_len = 16;
			memcpy(dest->service_uuid.data.data, data, dest->service_uuid.data_len);
			g_free(data);

			dest->service_uuid_mask.data_len = dest->service_uuid.data_len;
			if (src->service_uuid_mask) {
				__bt_convert_string_to_uuid(src->service_uuid_mask, &data, &bit);
				memcpy(dest->service_uuid_mask.data.data, data, dest->service_uuid_mask.data_len);
				g_free(data);
			} else {
				memset(dest->service_uuid_mask.data.data, 0xFF, dest->service_uuid_mask.data_len);
			}
		}
	}

	if (src->service_solicitation_uuid) {
		if (__bt_convert_string_to_uuid(src->service_solicitation_uuid, &data, &bit) == BT_ERROR_NONE) {
			dest->added_features |= BLUETOOTH_LE_SCAN_FILTER_FEATURE_SERVICE_SOLICITATION_UUID;

			if (bit == 16)
				dest->service_solicitation_uuid.data_len = 2;
			else
				dest->service_solicitation_uuid.data_len = 16;
			memcpy(dest->service_solicitation_uuid.data.data, data, dest->service_solicitation_uuid.data_len);
			g_free(data);

			dest->service_solicitation_uuid_mask.data_len = dest->service_solicitation_uuid.data_len;
			if (src->service_solicitation_uuid_mask) {
				__bt_convert_string_to_uuid(src->service_solicitation_uuid_mask, &data, &bit);
				memcpy(dest->service_solicitation_uuid_mask.data.data, data, dest->service_solicitation_uuid_mask.data_len);
				g_free(data);
			} else {
				memset(dest->service_solicitation_uuid_mask.data.data, 0xFF, dest->service_solicitation_uuid_mask.data_len);
			}
		}
	}

	if (src->service_data_uuid) {
		char *service_uuid;
		int uuid_len;
		if (__bt_convert_string_to_uuid(src->service_data_uuid, &service_uuid, &bit) == BT_ERROR_NONE) {
			dest->added_features |= BLUETOOTH_LE_SCAN_FILTER_FEATURE_SERVICE_DATA;
			if (bit == 16)
				uuid_len = 2;
			else
				uuid_len = 16;

			memcpy(dest->service_data.data.data, service_uuid, uuid_len);
			g_free(service_uuid);
			memcpy(dest->service_data.data.data + uuid_len, src->service_data, src->service_data_len);
			dest->service_data.data_len = uuid_len + src->service_data_len;

			dest->service_data_mask.data_len = uuid_len + src->service_data_len;
			memset(dest->service_data_mask.data.data, 0xFF, uuid_len);
			if (src->service_data_mask)
				memcpy(dest->service_data_mask.data.data + uuid_len, src->service_data_mask, src->service_data_len);
			else
				memset(dest->service_data_mask.data.data + uuid_len, 0xFF, src->service_data_len);
		}
	}

	if (src->manufacturer_id > -1) {
		dest->added_features |= BLUETOOTH_LE_SCAN_FILTER_FEATURE_MANUFACTURER_DATA;
		dest->manufacturer_id = src->manufacturer_id;

		if (src->manufacturer_data) {
			memcpy(dest->manufacturer_data.data.data, src->manufacturer_data, src->manufacturer_data_len);
			dest->manufacturer_data.data_len = src->manufacturer_data_len;

			dest->manufacturer_data_mask.data_len = src->manufacturer_data_len;
			if (src->manufacturer_data_mask)
				memcpy(dest->manufacturer_data_mask.data.data, src->manufacturer_data_mask, src->manufacturer_data_len);
			else
				memset(dest->manufacturer_data_mask.data.data, 0xFF, src->manufacturer_data_len);
		}
	}
}
//LCOV_EXCL_STOP

int bt_adapter_le_start_scan(bt_adapter_le_scan_result_cb cb, void *user_data)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(cb);

	_bt_le_adapter_init();
	_bt_set_cb(BT_EVENT_LE_SCAN_RESULT_UPDATED, cb, user_data);

	error_code = _bt_get_error_code(bluetooth_start_le_discovery());
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	}
	return error_code;
}

int bt_adapter_le_stop_scan(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	error_code = _bt_get_error_code(bluetooth_stop_le_discovery());
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	}
	return error_code;
}

int bt_adapter_le_get_scan_result_service_uuids(const bt_adapter_le_device_scan_result_info_s *info,
			bt_adapter_le_packet_type_e pkt_type, char ***uuids, int *count)
{
	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(info);
	BT_CHECK_INPUT_PARAMETER(uuids); //LCOV_EXCL_START
	BT_CHECK_INPUT_PARAMETER(count);

	int adv_length = 0;
	char *adv_data = NULL;
	char *remain_data = NULL;
	int remain_len = 0;
	int field_len = 0;
	int uuid_size = 0;
	int uuid_count = 0;
	int uuid_index = 0;
	int i;

	if (pkt_type == BT_ADAPTER_LE_PACKET_ADVERTISING) {
		adv_data = info->adv_data;
		adv_length = info->adv_data_len;
	} else if (pkt_type == BT_ADAPTER_LE_PACKET_SCAN_RESPONSE) {
		adv_data = info->scan_data;
		adv_length = info->scan_data_len;
	} else
		return BT_ERROR_INVALID_PARAMETER;

	if (!adv_data || adv_length < 3)
		return BT_ERROR_NO_DATA;

	remain_data = adv_data;
	remain_len = adv_length;
	field_len = 0;
	while (remain_len > 0) {
		field_len = remain_data[0];
		if (remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_INCOMP_LIST_16_BIT_SERVICE_CLASS_UUIDS ||
			remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_COMP_LIST_16_BIT_SERVICE_CLASS_UUIDS)
			uuid_count += (field_len - 1) / 2;
		else if (remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_INCOMP_LIST_128_BIT_SERVICE_CLASS_UUIDS ||
			remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_COMP_LIST_128_BIT_SERVICE_CLASS_UUIDS)
			uuid_count += (field_len - 1) / 16;

		remain_len = remain_len - field_len - 1;
		remain_data += field_len + 1;
	}

	if (uuid_count == 0)
		return BT_ERROR_NO_DATA;

	*uuids = g_malloc0(sizeof(char*) * uuid_count);
	/* Fix : NULL_RETURNS */
	if (*uuids == NULL)
		return BT_ERROR_OUT_OF_MEMORY;

	*count = uuid_count;

	remain_data = adv_data;
	remain_len = adv_length;
	field_len = 0;
	while (remain_len) {
		field_len = remain_data[0];
		if (remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_INCOMP_LIST_16_BIT_SERVICE_CLASS_UUIDS ||
			remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_COMP_LIST_16_BIT_SERVICE_CLASS_UUIDS)
			uuid_size = 2;
		else if (remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_INCOMP_LIST_128_BIT_SERVICE_CLASS_UUIDS ||
			remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_COMP_LIST_128_BIT_SERVICE_CLASS_UUIDS)
			uuid_size = 16;
		else
			uuid_size = 0;

		if (uuid_size != 0) {
			for (i = 0; i < (field_len - 1); i += uuid_size) {
				if (uuid_size == 2) {
					(*uuids)[uuid_index] = g_malloc0(sizeof(char) * 4 + 1);
					/* Fix : NULL_RETURNS */
					if ((*uuids)[uuid_index] == NULL)
						return BT_ERROR_OUT_OF_MEMORY;
					snprintf((*uuids)[uuid_index], 5, "%2.2X%2.2X", remain_data[i+3], remain_data[i+2]);
				} else {
					(*uuids)[uuid_index] = g_malloc0(sizeof(char) * 36 + 1);
					/* Fix : NULL_RETURNS */
					if ((*uuids)[uuid_index] == NULL)
						return BT_ERROR_OUT_OF_MEMORY;
					snprintf((*uuids)[uuid_index], 37, "%2.2X%2.2X%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X",
						remain_data[i+17], remain_data[i+16], remain_data[i+15], remain_data[i+14],
						remain_data[i+13], remain_data[i+12], remain_data[i+11], remain_data[i+10], remain_data[i+9], remain_data[i+8],
						remain_data[i+7], remain_data[i+6], remain_data[i+5], remain_data[i+4], remain_data[i+3], remain_data[i+2]);
				}
				uuid_index++;
			}
		}

		remain_len = remain_len - field_len - 1;
		remain_data += field_len + 1;
	}

	return BT_ERROR_NONE;
} //LCOV_EXCL_STOP

int bt_adapter_le_get_scan_result_device_name(const bt_adapter_le_device_scan_result_info_s *info,
			bt_adapter_le_packet_type_e pkt_type, char **name)
{
	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(info); //LCOV_EXCL_START
	BT_CHECK_INPUT_PARAMETER(name);

	int adv_length = 0;
	char *adv_data = NULL;
	int field_len = 0;

	if (pkt_type == BT_ADAPTER_LE_PACKET_ADVERTISING) {
		adv_data = info->adv_data;
		adv_length = info->adv_data_len;
	} else if (pkt_type == BT_ADAPTER_LE_PACKET_SCAN_RESPONSE) {
		adv_data = info->scan_data;
		adv_length = info->scan_data_len;
	} else
		return BT_ERROR_INVALID_PARAMETER;

	if (!adv_data || adv_length < 3)
		return BT_ERROR_NO_DATA;

	while (adv_length > 0) {
		field_len = adv_data[0];
		if (adv_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_LOCAL_NAME ||
			adv_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_SHORT_LOCAL_NAME) {
			*name = g_malloc0(sizeof(char) * field_len);
			/* Fix : NULL_RETURNS */
			if (*name == NULL)
				return BT_ERROR_OUT_OF_MEMORY;
			memcpy(*name, &adv_data[2], field_len - 1);

			return BT_ERROR_NONE;
		}

		adv_length = adv_length - field_len - 1;
		adv_data += field_len + 1;
	}

	return BT_ERROR_NO_DATA; //LCOV_EXCL_STOP
}

int bt_adapter_le_get_scan_result_tx_power_level(const bt_adapter_le_device_scan_result_info_s *info,
			bt_adapter_le_packet_type_e pkt_type, int *power_level)
{
	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(info); //LCOV_EXCL_START
	BT_CHECK_INPUT_PARAMETER(power_level);

	int adv_length = 0;
	char *adv_data = NULL;
	int field_len = 0;

	if (pkt_type == BT_ADAPTER_LE_PACKET_ADVERTISING) {
		adv_data = info->adv_data;
		adv_length = info->adv_data_len;
	} else if (pkt_type == BT_ADAPTER_LE_PACKET_SCAN_RESPONSE) {
		adv_data = info->scan_data;
		adv_length = info->scan_data_len;
	} else
		return BT_ERROR_INVALID_PARAMETER;

	if (!adv_data || adv_length < 3)
		return BT_ERROR_NO_DATA;

	while (adv_length > 0) {
		field_len = adv_data[0];
		if (adv_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_TX_POWER_LEVEL) {
			if (adv_data[2] & 0x80)
				*power_level = 0xffffff00 | adv_data[2];
			else
				*power_level = (int)adv_data[2];

			return BT_ERROR_NONE;
		}

		adv_length = adv_length - field_len - 1;
		adv_data += field_len + 1;
	}

	return BT_ERROR_NO_DATA; //LCOV_EXCL_STOP
}

int bt_adapter_le_get_scan_result_service_solicitation_uuids(const bt_adapter_le_device_scan_result_info_s *info,
			bt_adapter_le_packet_type_e pkt_type, char ***uuids, int *count)
{
	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(info); //LCOV_EXCL_START
	BT_CHECK_INPUT_PARAMETER(uuids);
	BT_CHECK_INPUT_PARAMETER(count);

	int adv_length = 0;
	char *adv_data = NULL;
	char *remain_data = NULL;
	int remain_len = 0;
	int field_len = 0;
	int uuid_size = 0;
	int uuid_count = 0;
	int uuid_index = 0;
	int i;

	if (pkt_type == BT_ADAPTER_LE_PACKET_ADVERTISING) {
		adv_data = info->adv_data;
		adv_length = info->adv_data_len;
	} else if (pkt_type == BT_ADAPTER_LE_PACKET_SCAN_RESPONSE) {
		adv_data = info->scan_data;
		adv_length = info->scan_data_len;
	} else
		return BT_ERROR_INVALID_PARAMETER;

	if (!adv_data || adv_length < 3)
		return BT_ERROR_NO_DATA;

	remain_data = adv_data;
	remain_len = adv_length;
	field_len = 0;
	while (remain_len > 0) {
		field_len = remain_data[0];
		if (remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_16_BIT_SERVICE_SOLICITATION_UUIDS)
			uuid_count += (field_len - 1) / 2;
		else if (remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_128_BIT_SERVICE_SOLICITATION_UUIDS)
			uuid_count += (field_len - 1) / 16;

		remain_len = remain_len - field_len - 1;
		remain_data += field_len + 1;
	}

	if (uuid_count == 0)
		return BT_ERROR_NO_DATA;

	*uuids = g_malloc0(sizeof(char*) * uuid_count);
	/* Fix : NULL_RETURNS */
	if (*uuids == NULL)
		return BT_ERROR_OUT_OF_MEMORY;
	*count = uuid_count;

	remain_data = adv_data;
	remain_len = adv_length;
	field_len = 0;
	while (remain_len > 0) {
		field_len = remain_data[0];
		if (remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_16_BIT_SERVICE_SOLICITATION_UUIDS)
			uuid_size = 2;
		else if (remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_128_BIT_SERVICE_SOLICITATION_UUIDS)
			uuid_size = 16;
		else
			uuid_size = 0;

		if (uuid_size != 0) {
			for (i = 0; i < (field_len - 1); i += uuid_size) {
				if (uuid_size == 2) {
					(*uuids)[uuid_index] = g_malloc0(sizeof(char) * 4 + 1);
					/* Fix : NULL_RETURNS */
					if ((*uuids)[uuid_index] == NULL)
						return BT_ERROR_OUT_OF_MEMORY;
					snprintf((*uuids)[uuid_index], 5, "%2.2X%2.2X", remain_data[i+3], remain_data[i+2]);
				} else {
					(*uuids)[uuid_index] = g_malloc0(sizeof(char) * 36 + 1);
					/* Fix : NULL_RETURNS */
					if ((*uuids)[uuid_index] == NULL)
						return BT_ERROR_OUT_OF_MEMORY;
					snprintf((*uuids)[uuid_index], 37, "%2.2X%2.2X%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X-%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X",
						remain_data[i+17], remain_data[i+16], remain_data[i+15], remain_data[i+14],
						remain_data[i+13], remain_data[i+12], remain_data[i+11], remain_data[i+10], remain_data[i+9], remain_data[i+8],
						remain_data[i+7], remain_data[i+6], remain_data[i+5], remain_data[i+4], remain_data[i+3], remain_data[i+2]);
				}
				uuid_index++;
			}
		}

		remain_len = remain_len - field_len - 1;
		remain_data += field_len + 1;
	}

	return BT_ERROR_NONE; //LCOV_EXCL_STOP
}

int bt_adapter_le_get_scan_result_service_data_list(const bt_adapter_le_device_scan_result_info_s *info,
			bt_adapter_le_packet_type_e pkt_type, bt_adapter_le_service_data_s **data_list, int *count)
{
	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(info); //LCOV_EXCL_START
	BT_CHECK_INPUT_PARAMETER(count);

	int adv_length = 0;
	char *adv_data = NULL;
	char *remain_data = NULL;
	int remain_len = 0;
	int field_len = 0;
	int data_count = 0;
	int data_index = 0;

	if (pkt_type == BT_ADAPTER_LE_PACKET_ADVERTISING) {
		adv_data = info->adv_data;
		adv_length = info->adv_data_len;
	} else if (pkt_type == BT_ADAPTER_LE_PACKET_SCAN_RESPONSE) {
		adv_data = info->scan_data;
		adv_length = info->scan_data_len;
	} else
		return BT_ERROR_INVALID_PARAMETER;

	if (!adv_data || adv_length < 3)
		return BT_ERROR_NO_DATA;

	remain_data = adv_data;
	remain_len = adv_length;
	field_len = 0;
	while (remain_len > 0) {
		field_len = remain_data[0];
		if (remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_SERVICE_DATA)
			data_count++;

		remain_len = remain_len - field_len - 1;
		remain_data += field_len + 1;
	}

	if (data_count == 0)
		return BT_ERROR_NO_DATA;

	*data_list = g_malloc0(sizeof(bt_adapter_le_service_data_s) * data_count);
	/* Fix : NULL_RETURNS */
	if (*data_list == NULL)
		return BT_ERROR_OUT_OF_MEMORY;
	*count = data_count;

	remain_data = adv_data;
	remain_len = adv_length;
	field_len = 0;
	while (remain_len > 0) {
		field_len = remain_data[0];
		if (remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_SERVICE_DATA) {
			(*data_list)[data_index].service_uuid = g_malloc0(sizeof(char) * 4 + 1);
			snprintf((*data_list)[data_index].service_uuid, 5, "%2.2X%2.2X", remain_data[3], remain_data[2]);

			(*data_list)[data_index].service_data = g_memdup(&remain_data[4], field_len - 3);
			(*data_list)[data_index].service_data_len = field_len - 3;

			data_index++;
		}

		remain_len = remain_len - field_len - 1;
		remain_data += field_len + 1;
	}

	return BT_ERROR_NONE; //LCOV_EXCL_STOP
}

int bt_adapter_le_free_service_data_list(bt_adapter_le_service_data_s *data_list, int count)
{
	int i;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(data_list); //LCOV_EXCL_START

	for (i = 0; i < count; i++) {
		g_free(data_list[i].service_uuid);
		g_free(data_list[i].service_data);
	}
	g_free(data_list);

	return BT_ERROR_NONE; //LCOV_EXCL_STOP
}

int bt_adapter_le_get_scan_result_appearance(const bt_adapter_le_device_scan_result_info_s *info,
			bt_adapter_le_packet_type_e pkt_type, int *appearance)
{
	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(info); //LCOV_EXCL_START
	BT_CHECK_INPUT_PARAMETER(appearance);

	int adv_length = 0;
	char *adv_data = NULL;
	int field_len = 0;

	if (pkt_type == BT_ADAPTER_LE_PACKET_ADVERTISING) {
		adv_data = info->adv_data;
		adv_length = info->adv_data_len;
	} else if (pkt_type == BT_ADAPTER_LE_PACKET_SCAN_RESPONSE) {
		adv_data = info->scan_data;
		adv_length = info->scan_data_len;
	} else
		return BT_ERROR_INVALID_PARAMETER;

	if (!adv_data || adv_length < 3)
		return BT_ERROR_NO_DATA;

	while (adv_length > 0) {
		field_len = adv_data[0];
		if (adv_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_APPEARANCE) {
			*appearance = adv_data[3] << 8;
			*appearance += adv_data[2];


			return BT_ERROR_NONE;
		}

		adv_length = adv_length - field_len - 1;
		adv_data += field_len + 1;
	}

	return BT_ERROR_NO_DATA; //LCOV_EXCL_STOP
}


int bt_adapter_le_get_scan_result_manufacturer_data(const bt_adapter_le_device_scan_result_info_s *info,
			bt_adapter_le_packet_type_e pkt_type, int *manufacturer_id, char **manufacturer_data, int *manufacturer_data_len)
{
	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(info);
	BT_CHECK_INPUT_PARAMETER(manufacturer_id); //LCOV_EXCL_START
	BT_CHECK_INPUT_PARAMETER(manufacturer_data);
	BT_CHECK_INPUT_PARAMETER(manufacturer_data_len);

	int adv_length = 0;
	char *adv_data = NULL;
	char *remain_data = NULL;
	int remain_len = 0;
	int field_len = 0;

	if (pkt_type == BT_ADAPTER_LE_PACKET_ADVERTISING) {
		adv_data = info->adv_data;
		adv_length = info->adv_data_len;
	} else if (pkt_type == BT_ADAPTER_LE_PACKET_SCAN_RESPONSE) {
		adv_data = info->scan_data;
		adv_length = info->scan_data_len;
	} else
		return BT_ERROR_INVALID_PARAMETER;

	if (!adv_data || adv_length < 3)
		return BT_ERROR_NO_DATA;

	remain_data = adv_data;
	remain_len = adv_length;
	field_len = 0;
	while (remain_len > 0) {
		field_len = remain_data[0];
		if (remain_data[1] == BT_ADAPTER_LE_ADVERTISING_DATA_MANUFACTURER_SPECIFIC_DATA) {
			*manufacturer_id = remain_data[3] << 8;
			*manufacturer_id += remain_data[2];

			*manufacturer_data = g_memdup(&adv_data[4], field_len - 3);
			*manufacturer_data_len = field_len - 3;

			return BT_ERROR_NONE;
		}

		remain_len = remain_len - field_len - 1;
		remain_data += field_len + 1;
	}

	return BT_ERROR_NO_DATA; //LCOV_EXCL_STOP
}

//LCOV_EXCL_START
int bt_adapter_le_create_scan_filter(bt_scan_filter_h *scan_filter)
{
	bt_le_scan_filter_s *__filter = NULL;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);

	__filter = (bt_le_scan_filter_s*)g_malloc0(sizeof(bt_le_scan_filter_s));
	if (__filter == NULL) {
		BT_ERR("OUT_OF_MEMORY(0x%08x)", BT_ERROR_OUT_OF_MEMORY); //LCOV_EXCL_LINE
		return BT_ERROR_OUT_OF_MEMORY;
	}

	__filter->manufacturer_id = -1;
	*scan_filter = (bt_scan_filter_h)__filter;

	return BT_ERROR_NONE;
}

int bt_adapter_le_destroy_scan_filter(bt_scan_filter_h scan_filter)
{
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s *)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);

	g_free(__filter->device_address);
	g_free(__filter->device_name);
	g_free(__filter->service_uuid);
	g_free(__filter->service_uuid_mask);
	g_free(__filter->service_solicitation_uuid);
	g_free(__filter->service_solicitation_uuid_mask);
	g_free(__filter->service_data_uuid);
	g_free(__filter->service_data);
	g_free(__filter->service_data_mask);
	g_free(__filter->manufacturer_data);
	g_free(__filter->manufacturer_data_mask);
	g_free(__filter);

	return BT_ERROR_NONE;
}

int bt_adapter_le_scan_filter_set_device_address(bt_scan_filter_h scan_filter, const char *address)
{
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s *)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);
	BT_CHECK_INPUT_PARAMETER(address);

	g_free(__filter->device_address);

	__filter->device_address = strdup(address);

	return BT_ERROR_NONE;
}

int bt_adapter_le_scan_filter_set_device_name(bt_scan_filter_h scan_filter, const char *name)
{
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s *)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);
	BT_CHECK_INPUT_PARAMETER(name);

	if (strlen(name) > 29) {
		BT_ERR("INVALID_PARAMETER(0x%08x)", BT_ERROR_INVALID_PARAMETER); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER;
	}

	g_free(__filter->device_name);

	__filter->device_name = strdup(name);

	return BT_ERROR_NONE;
}

int bt_adapter_le_scan_filter_set_service_uuid(bt_scan_filter_h scan_filter, const char *uuid)
{
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s *)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);
	BT_CHECK_INPUT_PARAMETER(uuid);

	g_free(__filter->service_uuid);
	g_free(__filter->service_uuid_mask);

	__filter->service_uuid = strdup(uuid);
	__filter->service_uuid_mask = NULL;

	return BT_ERROR_NONE;
}

int bt_adapter_le_scan_filter_set_service_uuid_with_mask(bt_scan_filter_h scan_filter,
			const char *uuid, const char *mask)
{
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s *)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);
	BT_CHECK_INPUT_PARAMETER(uuid);
	BT_CHECK_INPUT_PARAMETER(mask);

	if (strlen(uuid) != strlen(mask)) {
		BT_ERR("INVALID_PARAMETER(0x%08x)", BT_ERROR_INVALID_PARAMETER); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER;
	}

	g_free(__filter->service_uuid);
	g_free(__filter->service_uuid_mask);

	__filter->service_uuid = strdup(uuid);
	__filter->service_uuid_mask = strdup(mask);

	return BT_ERROR_NONE;
}

int bt_adapter_le_scan_filter_set_service_solicitation_uuid(bt_scan_filter_h scan_filter, const char *uuid)
{
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s *)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);
	BT_CHECK_INPUT_PARAMETER(uuid);

	g_free(__filter->service_solicitation_uuid);
	g_free(__filter->service_solicitation_uuid_mask);

	__filter->service_solicitation_uuid = strdup(uuid);
	__filter->service_solicitation_uuid_mask = NULL;

	return BT_ERROR_NONE;
}

int bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask(bt_scan_filter_h scan_filter,
			const char *uuid, const char *mask)
{
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s *)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);
	BT_CHECK_INPUT_PARAMETER(uuid);
	BT_CHECK_INPUT_PARAMETER(mask);

	if (strlen(uuid) != strlen(mask)) {
		BT_ERR("INVALID_PARAMETER(0x%08x)", BT_ERROR_INVALID_PARAMETER); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER;
	}

	g_free(__filter->service_solicitation_uuid);
	g_free(__filter->service_solicitation_uuid_mask);

	__filter->service_solicitation_uuid = strdup(uuid);
	__filter->service_solicitation_uuid_mask = strdup(mask);

	return BT_ERROR_NONE;
}

int bt_adapter_le_scan_filter_set_service_data(bt_scan_filter_h scan_filter,
			const char *uuid, const char *data, unsigned int data_len)
{
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s *)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);
	BT_CHECK_INPUT_PARAMETER(uuid);
	BT_CHECK_INPUT_PARAMETER(data);

	if (data_len > 27) {
		BT_ERR("INVALID_PARAMETER(0x%08x)", BT_ERROR_INVALID_PARAMETER); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER;
	}

	g_free(__filter->service_data_uuid);
	g_free(__filter->service_data);
	g_free(__filter->service_data_mask);

	__filter->service_data_uuid = strdup(uuid);
	__filter->service_data = g_memdup(data, data_len);
	__filter->service_data_len = data_len;
	__filter->service_data_mask = NULL;

	return BT_ERROR_NONE;
}

int bt_adapter_le_scan_filter_set_service_data_with_mask(bt_scan_filter_h scan_filter,
			const char *uuid, const char *data, unsigned int data_len, const char *mask, unsigned int mask_len)
{
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s *)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);
	BT_CHECK_INPUT_PARAMETER(uuid);
	BT_CHECK_INPUT_PARAMETER(data);
	BT_CHECK_INPUT_PARAMETER(mask);

	if (data_len != mask_len || data_len > 27) {
		BT_ERR("INVALID_PARAMETER(0x%08x)", BT_ERROR_INVALID_PARAMETER); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER;
	}

	g_free(__filter->service_data_uuid);
	g_free(__filter->service_data);
	g_free(__filter->service_data_mask);

	__filter->service_data_uuid = strdup(uuid);
	__filter->service_data = g_memdup(data, data_len);
	__filter->service_data_len = data_len;
	__filter->service_data_mask = g_memdup(mask, data_len);

	return BT_ERROR_NONE;
}

int bt_adapter_le_scan_filter_set_manufacturer_data(bt_scan_filter_h scan_filter,
			int manufacturer_id, const char *data, unsigned int data_len)
{
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s *)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);

	if (manufacturer_id < 0 || manufacturer_id > 0xFFFF) {
		BT_ERR("manufacturer_id is %.8x(0x%08x)", manufacturer_id, BT_ERROR_INVALID_PARAMETER); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER;
	}

	if (data_len > 27) {
		BT_ERR("INVALID_PARAMETER(0x%08x)", BT_ERROR_INVALID_PARAMETER); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER;
	}

	g_free(__filter->manufacturer_data);
	g_free(__filter->manufacturer_data_mask);

	__filter->manufacturer_id = manufacturer_id;
	if (data != NULL) {
		__filter->manufacturer_data = g_memdup(data, data_len);
		__filter->manufacturer_data_len = data_len;
	} else {
		__filter->manufacturer_data = NULL;
		__filter->manufacturer_data_len = 0;
	}
	__filter->manufacturer_data_mask = NULL;

	return BT_ERROR_NONE;
}

int bt_adapter_le_scan_filter_set_manufacturer_data_with_mask(bt_scan_filter_h scan_filter,
			int manufacturer_id, const char *data, unsigned int data_len, const char *mask, unsigned int mask_len)
{
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s *)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);
	BT_CHECK_INPUT_PARAMETER(data);
	BT_CHECK_INPUT_PARAMETER(mask);

	if (manufacturer_id < 0 || manufacturer_id > 0xFFFF) {
		BT_ERR("manufacturer_id is %.8x(0x%08x)", manufacturer_id, BT_ERROR_INVALID_PARAMETER); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER;
	}

	if (data_len != mask_len || data_len > 27) {
		BT_ERR("INVALID_PARAMETER(0x%08x)", BT_ERROR_INVALID_PARAMETER); //LCOV_EXCL_LINE
		return BT_ERROR_INVALID_PARAMETER;
	}

	g_free(__filter->manufacturer_data);
	g_free(__filter->manufacturer_data_mask);

	__filter->manufacturer_id = manufacturer_id;
	__filter->manufacturer_data = g_memdup(data, data_len);
	__filter->manufacturer_data_len = data_len;
	__filter->manufacturer_data_mask = g_memdup(mask, data_len);

	return BT_ERROR_NONE;
}

int bt_adapter_le_register_scan_filter(bt_scan_filter_h scan_filter)
{
	int error_code = BT_ERROR_NONE;
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s*)scan_filter;
	bluetooth_le_scan_filter_t filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);
	if (bluetooth_is_le_scanning() == TRUE) {
		BT_ERR("NOW_IN_PROGRESS(0x%08x)", BT_ERROR_NOW_IN_PROGRESS); //LCOV_EXCL_LINE
		return BT_ERROR_NOW_IN_PROGRESS;
	}

	__bt_adapter_le_convert_scan_filter(&filter, __filter);

	error_code = _bt_get_error_code(bluetooth_register_scan_filter(&filter, &__filter->slot_id));
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	}

	return error_code;
}

int bt_adapter_le_unregister_scan_filter(bt_scan_filter_h scan_filter)
{
	int error_code = BT_ERROR_NONE;
	bt_le_scan_filter_s *__filter = (bt_le_scan_filter_s*)scan_filter;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(scan_filter);
	if (bluetooth_is_le_scanning() == TRUE) {
		BT_ERR("NOW_IN_PROGRESS(0x%08x)", BT_ERROR_NOW_IN_PROGRESS); //LCOV_EXCL_LINE
		return BT_ERROR_NOW_IN_PROGRESS;
	}

	error_code = _bt_get_error_code(bluetooth_unregister_scan_filter(__filter->slot_id));
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	}

	return BT_ERROR_NONE;
}

int bt_adapter_le_unregister_all_scan_filters(void)
{
	int error_code = BT_ERROR_NONE;

	BT_CHECK_LE_SUPPORT();
	BT_CHECK_INIT_STATUS();
	if (bluetooth_is_le_scanning() == TRUE) {
		BT_ERR("NOW_IN_PROGRESS(0x%08x)", BT_ERROR_NOW_IN_PROGRESS); //LCOV_EXCL_LINE
		return BT_ERROR_NOW_IN_PROGRESS;
	}

	error_code = _bt_get_error_code(bluetooth_unregister_all_scan_filters());
	if (error_code != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error_code), error_code); //LCOV_EXCL_LINE
	}

	return BT_ERROR_NONE;
}

int bt_adapter_le_read_maximum_data_length(
		int *max_tx_octets, int *max_tx_time,
		int *max_rx_octets, int *max_rx_time)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	bluetooth_le_read_maximum_data_length_t max_le_datalength;

	ret = _bt_get_error_code(
		bluetooth_le_read_maximum_data_length(&max_le_datalength));

	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
		return ret;
	}

	*max_tx_octets = max_le_datalength.max_tx_octets;
	*max_tx_time = max_le_datalength.max_tx_time;
	*max_rx_octets = max_le_datalength.max_rx_octets;
	*max_rx_time = max_le_datalength.max_rx_time;

	return ret;
}

int bt_adapter_le_write_host_suggested_default_data_length(
	const unsigned int def_tx_Octets, const unsigned int def_tx_Time)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	/*Range for host suggested txtime is 0x001B-0x00FB  and
	txocets is 0x0148- 0x0848 as per BT 4.2 spec*/
	if (((def_tx_Octets < 27 || def_tx_Octets > 251) ||
		(def_tx_Time < 328 || def_tx_Time > 2120)) ||
		((def_tx_Octets < 0x001B || def_tx_Octets > 0x00FB) ||
		(def_tx_Time < 0x0148 || def_tx_Time > 0x0848))) {
		return BT_ERROR_INVALID_PARAMETER;
	}

	ret = _bt_get_error_code(
		bluetooth_le_write_host_suggested_default_data_length(
					def_tx_Octets, def_tx_Time));

	if (ret != BT_ERROR_NONE)
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE

	return ret;
}

int bt_adapter_le_read_suggested_default_data_length(
	unsigned int *def_tx_Octets,  unsigned int *def_tx_Time)
{
	int ret = BT_ERROR_NONE;

	BT_CHECK_BT_SUPPORT();
	BT_CHECK_INIT_STATUS();

	bluetooth_le_read_host_suggested_data_length_t data_values;

	ret = _bt_get_error_code(
		bluetooth_le_read_suggested_default_data_length(&data_values));

	if (ret != BT_ERROR_NONE) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(ret), ret); //LCOV_EXCL_LINE
		return ret;
	}

	*def_tx_Octets = data_values.def_tx_octets;
	*def_tx_Time = data_values.def_tx_time;

	return ret;
}

int bt_adapter_set_authentication_req_cb(bt_adapter_authentication_req_cb callback, void *user_data)
{
	BT_CHECK_INIT_STATUS();
	_bt_set_cb(BT_EVENT_AUTHENTICATION_REQUEST, callback, user_data);
	return BT_ERROR_NONE;
}

int bt_adapter_unset_authentication_req_cb(void)
{
	BT_CHECK_INIT_STATUS();
	_bt_unset_cb(BT_EVENT_AUTHENTICATION_REQUEST);
	return BT_ERROR_NONE;
}
//LCOV_EXCL_STOP
