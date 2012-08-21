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

#include <dlog.h>
#include <stdbool.h>
#include <bluetooth-api.h>
#include <string.h>
#include "bluetooth.h"
#include "bluetooth_private.h"
#include "bluetooth-audio-api.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "TIZEN_N_BLUETOOTH"

/*The below API is just to convert the error from Audio API's to CAPI error codes,
* this is temporary change and changes to proper error code will be done in
* subsequent check ins.*/
int _bt_convert_media_error_code(int error)
{
	switch(error) {
	case BLUETOOTH_AUDIO_ERROR_NONE:
		return BT_ERROR_NONE;
	case BLUETOOTH_AUDIO_ERROR_INTERNAL:
		return BT_ERROR_INVALID_PARAMETER;
	case BLUETOOTH_AUDIO_ERROR_INVALID_PARAM:
		return BT_ERROR_INVALID_PARAMETER;
	case BLUETOOTH_AG_ERROR_CONNECTION_ERROR:
		return BT_ERROR_OPERATION_FAILED;
	case BLUETOOTH_AV_ERROR_CONNECTION_ERROR:
		return BT_ERROR_OPERATION_FAILED;
	default:
		return BT_ERROR_NONE;
	}
}
int bt_audio_initialize(void)
{
	int error = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	error = bluetooth_audio_init(_bt_audio_event_proxy, NULL);
	error = _bt_convert_media_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__,
			_bt_convert_error_to_string(error), error);
	}
	return error;
}

int bt_audio_deinitialize(void)
{
	int error = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();

	error = bluetooth_audio_deinit();
	error = _bt_convert_media_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__,
			_bt_convert_error_to_string(error), error);
	}
	return error;
}

int bt_audio_connect(const char *remote_address, bt_audio_profile_type_e type)
{
	int error = BT_ERROR_NONE;
	bluetooth_device_address_t addr_hex = { {0,} };
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address);
	_bt_convert_address_to_hex(&addr_hex, remote_address);
	switch(type) {
	case BT_AUDIO_PROFILE_TYPE_HSP_HFP:
		error = bluetooth_ag_connect(&addr_hex);
		break;
	case BT_AUDIO_PROFILE_TYPE_A2DP:
		error = bluetooth_av_connect(&addr_hex);
		break;
	case BT_AUDIO_PROFILE_TYPE_ALL:
	default:
		error = bluetooth_audio_connect(&addr_hex);
		break;
	}
	error = _bt_convert_media_error_code(error);
	error = _bt_get_error_code(error);
	if (error != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__,
			_bt_convert_error_to_string(error), error);
	}
	return error;
}

int bt_audio_disconnect(const char *remote_address, bt_audio_profile_type_e type)
{
	int error = BT_ERROR_NONE;
	bluetooth_device_address_t addr_hex = { {0,} };
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address);
	_bt_convert_address_to_hex(&addr_hex, remote_address);
	switch(type) {
	case BT_AUDIO_PROFILE_TYPE_HSP_HFP:
		error = bluetooth_ag_disconnect(&addr_hex);
		break;
	case BT_AUDIO_PROFILE_TYPE_A2DP:
		error = bluetooth_av_disconnect(&addr_hex);
		break;
	case BT_AUDIO_PROFILE_TYPE_ALL:
	default:
		error = bluetooth_audio_disconnect(&addr_hex);
		break;
	}
	error = _bt_convert_media_error_code(error);
	error = _bt_get_error_code(error);
	if (error != BT_ERROR_NONE) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__,
			_bt_convert_error_to_string(error), error);
	}
	return error;
}

int bt_audio_set_connection_state_changed_cb(bt_audio_connection_state_changed_cb callback, void *user_data)
{
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_AUDIO_CONNECTION_STATUS, callback, user_data);
	return BT_ERROR_NONE;

}
int bt_audio_unset_connection_state_changed_cb(void)
{
	BT_CHECK_INIT_STATUS();
	if (_bt_check_cb(BT_EVENT_AUDIO_CONNECTION_STATUS) == true)
		_bt_unset_cb(BT_EVENT_AUDIO_CONNECTION_STATUS);
	return BT_ERROR_NONE;
}

int bt_ag_notify_speaker_gain(const char *remote_address, int gain)
{
	int error = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(remote_address);
	error = bluetooth_ag_set_speaker_gain((unsigned short)gain);
	error = _bt_convert_media_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__,
			_bt_convert_error_to_string(error), error);
	}
	return error;
}

int bt_ag_get_speaker_gain(const char *remote_address, int *gain)
{
	int error = BT_ERROR_NONE;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(gain);
	BT_CHECK_INPUT_PARAMETER(remote_address);
	error = bluetooth_ag_get_headset_volume((unsigned int *)gain);
	error = _bt_convert_media_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		LOGE("[%s] %s(0x%08x)", __FUNCTION__,
			_bt_convert_error_to_string(error), error);
	}
	return error;
}

int bt_ag_set_microphone_gain_changed_cb(bt_ag_microphone_gain_changed_cb callback, void *user_data)
{
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_AG_MICROPHONE_GAIN_CHANGE, callback, user_data);
	return BT_ERROR_NONE;

}

int bt_ag_unset_microphone_gain_changed_cb(void)
{
	BT_CHECK_INIT_STATUS();
	if (_bt_check_cb(BT_EVENT_AG_MICROPHONE_GAIN_CHANGE) == true)
		_bt_unset_cb(BT_EVENT_AG_MICROPHONE_GAIN_CHANGE);
	return BT_ERROR_NONE;
}

int bt_ag_set_speaker_gain_changed_cb(bt_ag_speaker_gain_changed_cb callback,
					void *user_data)
{
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_AG_SPEAKER_GAIN_CHANGE, callback, user_data);
	return BT_ERROR_NONE;
}

int bt_ag_unset_speaker_gain_changed_cb(void)
{
	BT_CHECK_INIT_STATUS();
	if (_bt_check_cb(BT_EVENT_AG_SPEAKER_GAIN_CHANGE) == true)
		_bt_unset_cb(BT_EVENT_AG_SPEAKER_GAIN_CHANGE);
	return BT_ERROR_NONE;
}
