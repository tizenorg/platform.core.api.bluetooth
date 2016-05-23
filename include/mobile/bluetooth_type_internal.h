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


#ifndef __TIZEN_NETWORK_BLUETOOTH_TYPE_INTERNAL_H__
#define __TIZEN_NETWORK_BLUETOOTH_TYPE_INTERNAL_H__

 #ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @file bluetooth_type_internal.h
 */

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief  Enumerations of the Bluetooth adapter le state.
 * @since_tizen 2.3
 */
typedef enum {
	BT_ADAPTER_LE_DISABLED = 0x00, /**< Bluetooth le is disabled */
	BT_ADAPTER_LE_ENABLED, /**< Bluetooth le is enabled */
} bt_adapter_le_state_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief  Called when the Bluetooth adapter le state changes.
 * @since_tizen 2.3
 *
 * @param[in]   result  The result of the adapter state changing
 * @param[in]   adapter_le_state  The adapter le state to be changed
 * @param[in]   user_data  The user data passed from the callback registration function
 * @pre Either bt_adapter_le_enable() or bt_adapter_le_disable() will invoke this callback if you register this callback using bt_adapter_le_set_state_changed_cb().
 * @see bt_adapter_le_enable()
 * @see bt_adapter_le_disable()
 * @see bt_adapter_le_set_state_changed_cb()
 * @see bt_adapter_le_unset_state_changed_cb()
 */
typedef void (*bt_adapter_le_state_changed_cb)(int result, bt_adapter_le_state_e adapter_le_state, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Enumerations for the call state
 * @since_tizen 2.3
 */
typedef enum {
	BT_AG_CALL_EVENT_IDLE = 0x00,  /**< Idle */
	BT_AG_CALL_EVENT_ANSWERED,  /**< Answered */
	BT_AG_CALL_EVENT_HELD,  /**< Held */
	BT_AG_CALL_EVENT_RETRIEVED,  /**< Retrieved */
	BT_AG_CALL_EVENT_DIALING,  /**< Dialing */
	BT_AG_CALL_EVENT_ALERTING,  /**< Alerting */
	BT_AG_CALL_EVENT_INCOMING,  /**< Incoming */
} bt_ag_call_event_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Enumerations for the call state
 * @since_tizen 2.3
 */
typedef enum {
	BT_AG_CALL_STATE_IDLE = 0x00,  /**< Idle state */
	BT_AG_CALL_STATE_ACTIVE,  /**< Active state */
	BT_AG_CALL_STATE_HELD,  /**< Held state */
	BT_AG_CALL_STATE_DIALING,  /**< Dialing state */
	BT_AG_CALL_STATE_ALERTING,  /**< Alerting state */
	BT_AG_CALL_STATE_INCOMING,  /**< Incoming state */
	BT_AG_CALL_STATE_WAITING,  /**< Waiting for connected indication event after answering an incoming call*/
} bt_ag_call_state_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Called when the connectable state changes.
 * @since_tizen 2.3
 *
 * @param[in] result The result of the connectable state changing
 * @param[in] connectable The connectable to be changed
 * @param[in] user_data The user data passed from the callback registration function
 *
 * @pre This function will be invoked when the connectable state of local Bluetooth adapter changes
 * if you register this callback using bt_adapter_set_connectable_changed_cb().
 *
 * @see bt_adapter_set_connectable()
 * @see bt_adapter_set_connectable_changed_cb()
 * @see bt_adapter_unset_connectable_changed_cb()
 */
typedef void (*bt_adapter_connectable_changed_cb)
	(int result, bool connectable, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_SERVER_MODULE
 * @brief  Called when the push is requested.
 * @since_tizen 2.3
 *
 * @details You must call bt_opp_server_accept() if you want to accept.
 * Otherwise, you must call bt_opp_server_reject().
 * @param[in] file  The path of file to be pushed
 * @param[in] size The file size (bytes)
 * @param[in] user_data The user data passed from the callback registration function
 * @see bt_opp_server_initialize()
 */
typedef void (*bt_opp_server_push_requested_cb)(const char *file, int size, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief  Enumerations of the Bluetooth adapter le scan type.
 * @since_tizen 2.3
 */
typedef enum {
	BT_ADAPTER_LE_PASSIVE_SCAN = 0x00,
	BT_ADAPTER_LE_ACTIVE_SCAN
} bt_adapter_le_scan_type_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief  Enumerations of the Bluetooth le scan mode.
 * @since_tizen 2.3
 */
typedef enum {
	BT_ADAPTER_LE_SCAN_MODE_BALANCED,
	BT_ADAPTER_LE_SCAN_MODE_LOW_LATENCY,
	BT_ADAPTER_LE_SCAN_MODE_LOW_ENERGY
} bt_adapter_le_scan_mode_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Called when the manufacturer dat changes.
 * @since_tizen 2.3
 *
 * @param[in]   data		The manufacurer data of the Bluetooth device to be changed
 * @param[in]   len			The length of @a data
 * @param[in]   user_data	The user data passed from the callback registration function
 * @pre This function will be invoked when the manufacturer data of Bluetooth adapter changes
 * if callback is registered using bt_adapter_set_manufacturer_data_changed_cb().
 * @see bt_adapter_set_manufacturer_data()
 * @see bt_adapter_set_manufacturer_data_changed_cb()
 * @see bt_adapter_unset_manufacturer_data_changed_cb()
 */
typedef void (*bt_adapter_manufacturer_data_changed_cb) (char *data,
		int len, void *user_data);

/**
* @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
* @brief DPM BT allowance state
* @since_tizen 3.0
*/
typedef enum {
	BT_DPM_ERROR	  = -1,   /**< bluetooth allowance error */
	BT_DPM_BT_ALLOWED,	  /**< bluetooth allowance allowed */
	BT_DPM_HANDSFREE_ONLY, /**< bluetooth allowance handsfree only */
	BT_DPM_BT_RESTRICTED,  /**< bluetooth allowance restricted */
} bt_dpm_allow_e;

/**
* @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
* @brief DPM Policy status
* @since_tizen 3.0
*/
typedef enum {
	BT_DPM_STATUS_ERROR = -1,

	BT_DPM_ALLOWED	 = 0,	 /**< DPM Policy status allowed. */
	BT_DPM_RESTRICTED		 = 1,	 /**< DPM Policy status restricted. */

	BT_DPM_ENABLE			 = 1,	 /**< DPM Policy status enabled. */
	BT_DPM_DISABLE	= 0,	 /**< DPM Policy status disabled. */

	BT_DPM_FALSE		 = 0,	 /**< DPM Policy status false. */
	BT_DPM_TRUE 	 = 1,	 /**< DPM Policy status true. */
} bt_dpm_status_e;

/**
* @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
* @brief DPM Profile states
* @since_tizen 3.0
*/
typedef enum {
	BT_DPM_POLICY_A2DP_PROFILE_STATE,
	BT_DPM_POLICY_AVRCP_PROFILE_STATE,
	BT_DPM_POLICY_BPP_PROFILE_STATE,
	BT_DPM_POLICY_DUN_PROFILE_STATE,
	BT_DPM_POLICY_FTP_PROFILE_STATE,
	BT_DPM_POLICY_HFP_PROFILE_STATE,
	BT_DPM_POLICY_HSP_PROFILE_STATE,
	BT_DPM_POLICY_PBAP_PROFILE_STATE,
	BT_DPM_POLICY_SAP_PROFILE_STATE,
	BT_DPM_POLICY_SPP_PROFILE_STATE,
	BT_DPM_PROFILE_NONE,
} bt_dpm_profile_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief The handle to control Bluetooth LE scan filter
 * @since_tizen 2.4
 */
typedef void *bt_scan_filter_h;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Enumerations for the player control command
 * @since_tizen 2.3
 */
typedef enum {
	BT_AVRCP_CONTROL_PLAY = 0x01,   /**< Play */
	BT_AVRCP_CONTROL_PAUSE,   /**< Pause */
	BT_AVRCP_CONTROL_STOP,   /**< Stop */
	BT_AVRCP_CONTROL_NEXT,   /**< Next Track*/
	BT_AVRCP_CONTROL_PREVIOUS,   /**< Previous track */
	BT_AVRCP_CONTROL_FAST_FORWARD,   /**< Fast Forward */
	BT_AVRCP_CONTROL_REWIND   /**< Rewind */
} bt_avrcp_player_command_e;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief Structure of Track metadata information.
 * @since_tizen 2.3
 *
 * @see #bt_class_s
 */
typedef struct {
	const char *title;
	const char *artist;
	const char *album;
	const char *genre;
	unsigned int total_tracks;
	unsigned int number;
	unsigned int duration;
} bt_avrcp_metadata_attributes_info_s;

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Called when the connection state is changed.
 * @since_tizen 2.3
 * @param[in] connected  The state to be changed. @a true means connected state, Otherwise, @a false.
 * @param[in] remote_address  The remote address
 * @param[in] user_data The user data passed from the callback registration function
 * @see bt_avrcp_control_initialize()
 * @see bt_avrcp_control_deinitialize()
 */
typedef void (*bt_avrcp_control_connection_state_changed_cb) (bool connected, const char *remote_address, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Called when the Song position mode is changed by the remote target device.
 * @since_tizen 2.3
 *
 * @param[in] position The song position
 * @param[in] user_data The user data passed from the callback registration function
 * @see bt_avrcp_set_song_position_changed_cb()
 * @see bt_avrcp_unset_song_position_changed_cb()
 */
typedef void (*bt_avrcp_song_position_changed_cb) (unsigned int position, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Called when the Song metadata information is changed by the remote target device.
 * @since_tizen 2.3
 *
 * @param[in] position The song metadata information
 * @param[in] user_data The user data passed from the callback registration function
 * @see bt_avrcp_set_track_info_changed_cb()
 * @see bt_avrcp_unset_track_info_changed_cb()
 */
typedef void (*bt_avrcp_track_info_changed_cb) (bt_avrcp_metadata_attributes_info_s *track, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Called when the Song Play status mode is changed by the remote target device.
 * @since_tizen 2.3
 *
 * @param[in] play_state The song play status
 * @param[in] user_data The user data passed from the callback registration function
 * @see bt_avrcp_set_play_status_changed_cb()
 * @see bt_avrcp_unset_play_status_changed_cb()
 */
typedef void (*bt_avrcp_play_status_changed_cb) (bt_avrcp_player_state_e play_state, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Device LE connection update structure.
 * @since_tizen 2.3
 */
typedef struct {
	unsigned int interval_min;   /**< Minimum value for the connection event interval (msec) */
	unsigned int interval_max;   /**< Maximum value for the connection event interval (msec) */
	unsigned int latency;   /**< Slave latency (msec) */
	unsigned int time_out;   /**< Supervision timeout (msec) */
} bt_le_conn_update_s;


/**
 * Structure to DPM device list
 */
typedef struct {
	int count;
	char **devices;
} bt_dpm_device_list_s;

/**
 * Structure to DPM uuid list
 */
typedef struct {
	int count;
	char **uuids;
} bt_dpm_uuids_list_s;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_NETWORK_BLUETOOTH_TYPE_INTERNAL_H__ */
