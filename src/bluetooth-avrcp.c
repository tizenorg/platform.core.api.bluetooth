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
#include <stdbool.h>
#include "bluetooth.h"
#include "bluetooth_private.h"
#ifdef NTB
#include "ntb-bluetooth.h"
#else
#include <bluetooth-api.h>
#include "bluetooth-audio-api.h"
#include "bluetooth-media-control.h"
#endif

#ifndef NTB
/*The below API is just to conver the error from Audio API's to CAPI error codes,
* this is temporary change and changes to proper error code will be done in
* subsequent check ins.*/
int _bt_convert_avrcp_error_code(int error)
{
	switch(error) {
	case BT_MEDIA_ERROR_NONE:
		return BT_ERROR_NONE;
	case BT_MEDIA_ERROR_INTERNAL:
		return BT_ERROR_INVALID_PARAMETER;
	case BT_MEDIA_ERROR_ALREADY_INITIALIZED:
		return BT_ERROR_OPERATION_FAILED;
	default:
		return BT_ERROR_NONE;
	}
}
#endif

int bt_avrcp_target_initialize(bt_avrcp_target_connection_state_changed_cb callback, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_target_initialize(callback, user_data);
	return error_code;
#else
	int error;

	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_AVRCP_CONNECTION_STATUS, callback, user_data);
	error = bluetooth_media_player_init(_bt_avrcp_event_proxy, NULL);
	error = _bt_convert_avrcp_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_avrcp_target_deinitialize(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_target_deinitialize();
	return error_code;
#else
	int error;

	BT_CHECK_INIT_STATUS();
	if (_bt_check_cb(BT_EVENT_AVRCP_CONNECTION_STATUS) == true)
		_bt_unset_cb(BT_EVENT_AVRCP_CONNECTION_STATUS);

	error = bluetooth_media_player_deinit();
	error = _bt_convert_avrcp_error_code(error);

	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_avrcp_target_notify_equalizer_state(bt_avrcp_equalizer_state_e state)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_target_notify_equalizer_state(state);
	return error_code;
#else
	int error;
	BT_CHECK_INIT_STATUS();
	error = bluetooth_media_player_change_property(EQUALIZER, state);
	error = _bt_convert_avrcp_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_avrcp_target_notify_repeat_mode(bt_avrcp_repeat_mode_e mode)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_target_notify_repeat_mode(mode);
	return error_code;
#else
	int error;
	BT_CHECK_INIT_STATUS();
	error = bluetooth_media_player_change_property(REPEAT, mode);
	error = _bt_convert_avrcp_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_avrcp_target_notify_shuffle_mode(bt_avrcp_shuffle_mode_e mode)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_target_notify_shuffle_mode(mode);
	return error_code;
#else
	int error;
	BT_CHECK_INIT_STATUS();
	error = bluetooth_media_player_change_property(SHUFFLE, mode);
	error = _bt_convert_avrcp_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_avrcp_target_notify_scan_mode(bt_avrcp_scan_mode_e mode)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_target_notify_scan_mode(mode);
	return error_code;
#else
	int error;
	BT_CHECK_INIT_STATUS();
	error = bluetooth_media_player_change_property(SCAN, mode);
	error = _bt_convert_avrcp_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_avrcp_target_notify_player_state(bt_avrcp_player_state_e state)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_target_notify_player_state(state);
	return error_code;
#else
	int error;
	BT_CHECK_INIT_STATUS();
	error = bluetooth_media_player_change_property(STATUS, state);
	error = _bt_convert_avrcp_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_avrcp_target_notify_position(unsigned int position)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_target_notify_position(position);
	return error_code;
#else
	int error;
	BT_CHECK_INIT_STATUS();
	error = bluetooth_media_player_change_property(POSITION, position);
	error = _bt_convert_avrcp_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_avrcp_target_notify_track(const char *title, const char *artist, const char *album,
		const char *genre, unsigned int track_num, unsigned int total_tracks, unsigned int duration)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_target_notify_track(title, artist, album, genre, track_num, total_tracks, duration);
	return error_code;
#else
	int error;
	BT_CHECK_INIT_STATUS();
	media_metadata_attributes_t metadata;
	metadata.title = title;
	metadata.artist = artist;
	metadata.duration = duration;
	metadata.genre = genre;
	metadata.number = track_num;
	metadata.album = album;
	metadata.total_tracks = total_tracks;
	error = bluetooth_media_player_change_track(&metadata);
	error = _bt_convert_avrcp_error_code(error);
	error = _bt_get_error_code(error);
	if (BT_ERROR_NONE != error) {
		BT_ERR("%s(0x%08x)", _bt_convert_error_to_string(error), error);
	}
	return error;
#endif
}

int bt_avrcp_set_equalizer_state_changed_cb(bt_avrcp_equalizer_state_changed_cb callback, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_set_equalizer_state_changed_cb(callback, user_data);
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_AVRCP_EQUALIZER_STATE_CHANGED, callback, user_data);
	return BT_ERROR_NONE;
#endif
}

int bt_avrcp_unset_equalizer_state_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_unset_equalizer_state_changed_cb();
	return error_code;
#else
	_bt_unset_cb(BT_EVENT_AVRCP_EQUALIZER_STATE_CHANGED);
	return BT_ERROR_NONE;
#endif
}

int bt_avrcp_set_repeat_mode_changed_cb(bt_avrcp_repeat_mode_changed_cb callback, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_set_repeat_mode_changed_cb(callback, user_data);
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_AVRCP_REPEAT_MODE_CHANGED, callback, user_data);
	return BT_ERROR_NONE;
#endif
}

int bt_avrcp_unset_repeat_mode_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_unset_repeat_mode_changed_cb();
	return error_code;
#else
	_bt_unset_cb(BT_EVENT_AVRCP_REPEAT_MODE_CHANGED);
	return BT_ERROR_NONE;
#endif
}

int bt_avrcp_set_shuffle_mode_changed_cb(bt_avrcp_shuffle_mode_changed_cb callback, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_set_shuffle_mode_changed_cb(callback, user_data);
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_AVRCP_SHUFFLE_MODE_CHANGED, callback, user_data);
	return BT_ERROR_NONE;
#endif
}

int bt_avrcp_unset_shuffle_mode_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_unset_shuffle_mode_changed_cb();
	return error_code;
#else
	_bt_unset_cb(BT_EVENT_AVRCP_SHUFFLE_MODE_CHANGED);
	return BT_ERROR_NONE;
#endif
}

int bt_avrcp_set_scan_mode_changed_cb(bt_avrcp_scan_mode_changed_cb callback, void *user_data)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_set_scan_mode_changed_cb(callback, user_data);
	return error_code;
#else
	BT_CHECK_INIT_STATUS();
	BT_CHECK_INPUT_PARAMETER(callback);
	_bt_set_cb(BT_EVENT_AVRCP_SCAN_MODE_CHANGED, callback, user_data);
	return BT_ERROR_NONE;
#endif
}

int bt_avrcp_unset_scan_mode_changed_cb(void)
{
#ifdef NTB
	int error_code = BT_ERROR_NONE;
	error_code = ntb_bt_avrcp_unset_scan_mode_changed_cb();
	return error_code;
#else
	_bt_unset_cb(BT_EVENT_AVRCP_SCAN_MODE_CHANGED);
	return BT_ERROR_NONE;
#endif
}

