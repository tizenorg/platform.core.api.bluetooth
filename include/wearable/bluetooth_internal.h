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


#ifndef __TIZEN_NETWORK_BLUETOOTH_INTERNAL_H__
#define __TIZEN_NETWORK_BLUETOOTH_INTERNAL_H__

#include <glib.h>
#include "bluetooth_type.h"
#include "bluetooth_type_internal.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @file        bluetooth_internal.h
 */

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Enables the local Bluetooth adapter, asynchronously.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @details This function enables Bluetooth protocol stack and hardware.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_ALREADY_DONE  Already enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation now in progress
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre Bluetooth service must be initialized with bt_initialize().
 * @pre The state of local Bluetooth must be #BT_ADAPTER_DISABLED
 * @post This function invokes bt_adapter_state_changed_cb().
 *
 * @see bt_initialize()
 * @see bt_adapter_get_state()
 * @see bt_adapter_set_state_changed_cb()
 * @see bt_adapter_unset_state_changed_cb()
 * @see bt_adapter_state_changed_cb()
 *
 */
int bt_adapter_enable(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Disables the local Bluetooth adapter, asynchronously.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @details This function disables Bluetooth protocol stack and hardware.
 *
 * @remarks You should disable Bluetooth adapter, which is helpful for saving power.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation now in progress
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED
 * @post This function invokes bt_adapter_state_changed_cb().
 *
 * @see bt_adapter_get_state()
 * @see bt_adapter_state_changed_cb()
 * @see bt_adapter_set_state_changed_cb()
 * @see bt_adapter_unset_state_changed_cb ()
 *
 */
int bt_adapter_disable(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Recover the local Bluetooth adapter, asynchronously.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @details This function does recovery logic, disables Bluetooth protocol stack and hardware, then enables after a few seconds.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation now in progress
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED
 * @post This function invokes bt_adapter_state_changed_cb().
 *
 * @see bt_adapter_get_state()
 * @see bt_adapter_state_changed_cb()
 * @see bt_adapter_set_state_changed_cb()
 * @see bt_adapter_unset_state_changed_cb ()
 *
 */
int bt_adapter_recover(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Reset the local Bluetooth adapter, synchronously.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @details This function resets Bluetooth protocol and values.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OPERATION_FAILED Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre Bluetooth service must be initialized with bt_initialize().
 * @post bt_adapter_state_changed_cb() will be invoked if The state of local Bluetooth was #BT_ADAPTER_ENABLED.
 *
 * @see bt_initialize()
 * @see bt_adapter_get_state()
 * @see bt_adapter_set_state_changed_cb()
 * @see bt_adapter_unset_state_changed_cb()
 * @see bt_adapter_state_changed_cb()
 *
 */
int bt_adapter_reset(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Gets the version of local Bluetooth adapter.
 * @since_tizen 2.3.1
 * @remarks The @a local_version must be released with free() by you.
 *
 * @param[out] local_version The version of local Bluetooth adapter
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_OPERATION_FAILED Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 */
int bt_adapter_get_version(char **local_version);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Gets the information regarding local Bluetooth adapter.
 * @since_tizen 2.3.1
 * @remarks The @a all parameters must be released with free() by you.
 *
 * @param[out] chipset Chipset name of local Bluetooth adapter
 * @param[out] firmware Firmware info. of local Bluetooth adapter
 * @param[out] stack_version Bluetooth stack version
 * @param[out] profiles The profile list of local Bluetooth adapter
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_OPERATION_FAILED Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 */
int bt_adapter_get_local_info(char **chipset, char **firmware, char **stack_version, char **profiles);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Sets the visibility mode.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @remarks #BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE will change to #BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE
 * after the given @a duration goes.
 *
 * @param[in] discoverable_mode The Bluetooth visibility mode to set
 * @param[in] duration The duration until the visibility mode is changed to #BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE (in seconds).
 * @a duration is used only for #BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE mode.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @post bt_adapter_visibility_mode_changed_cb() will be invoked if this function returns #BT_ERROR_NONE.
 *
 * @see bt_adapter_get_visibility()
 * @see bt_adapter_visibility_mode_changed_cb()
 * @see bt_adapter_set_visibility_mode_changed_cb()
 * @see bt_adapter_unset_visibility_mode_changed_cb()
 */
int bt_adapter_set_visibility(bt_adapter_visibility_mode_e discoverable_mode, int duration);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Registers a callback function to be invoked when the connectable state changes.
 * @since_tizen 2.3.1
 *
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post bt_adapter_connectable_changed_cb() will be invoked.
 *
 * @see bt_initialize()
 * @see bt_adapter_connectable_changed_cb()
 * @see bt_adapter_unset_connectable_changed_cb()
 */
int bt_adapter_set_connectable_changed_cb(bt_adapter_connectable_changed_cb callback, void *user_data);

/**
 * @internal
 * @ingroup  CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Unregisters the callback function.
 * @since_tizen 2.3.1
 *
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The Bluetooth service must be initialized with bt_initialize().
 *
 * @see  bt_initialize()
 * @see  bt_adapter_set_connectable_changed_cb()
 */
int bt_adapter_unset_connectable_changed_cb(void);

/**
 * @internal
 * @ingroup  CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Gets the connectable state of local Bluetooth adapter.
 * @since_tizen 2.3.1
 *
 * @remarks When connectable state is false, no device can connect to this device and visibility mode cannot be changed.
 *
 * @param[out] connectable The connectable state of local Bluetooth adapter
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 *
 * @see bt_adapter_set_connectable()
 */
int bt_adapter_get_connectable(bool *connectable);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Sets the connectable state of local Bluetooth adapter.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @remarks When connectable state is false, no device can connect to this device and visibility mode cannot be changed.
 *
 * @param[in] connectable The connectable state to set
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @post bt_adapter_connectable_changed_cb() will be invoked if this function returns #BT_ERROR_NONE.
 *
 * @see bt_adapter_get_connectable()
 * @see bt_adapter_connectable_changed_cb()
 * @see bt_adapter_set_connectable_changed_cb()
 * @see bt_adapter_unset_connectable_changed_cb()
 */
int bt_adapter_set_connectable(bool connectable);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Sets the manufacturer data of local Bluetooth adapter.
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]   data	The manufacturer specific data of the Bluetooth device.
 * @param[in]   len	The length of @a data.Maximaum length is 240 bytes.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @post bt_adapter_manufacturer_data_changed_cb() will be invoked
 * if this function returns #BT_ERROR_NONE.
 *
 * @see bt_adapter_manufacturer_data_changed_cb
 * @see bt_adapter_set_manufacturer_data_changed_cb()
 * @see bt_adapter_unset_manufacturer_data_changed_cb()
 */
int bt_adapter_set_manufacturer_data(char *data, int len);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Registers a callback function to be invoked
 * when the manufacturer data of Bluetooth adapter changes.
 * @since_tizen 2.3
 *
 * @param[in]   callback	The callback function to invoke
 * @param[in]   user_data	The user data to be passed to the callback function
 *
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post  bt_adapter_manufacturer_data_changed_cb() will be invoked.
 *
 * @see bt_initialize()
 * @see bt_adapter_unset_manufacturer_data_changed_cb()
 */
int bt_adapter_set_manufacturer_data_changed_cb(
		bt_adapter_manufacturer_data_changed_cb callback,
		void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief	Unregisters the callback function.
 * @since_tizen 2.3
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_initialize()
 * @see bt_adapter_set_manufacturer_data_changed_cb()
 */
int bt_adapter_unset_manufacturer_data_changed_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Enables the local Bluetooth le adapter, asynchronously.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @details This function enables Bluetooth protocol stack and hardware.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_ALREADY_DONE  Already enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation now in progress
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre Bluetooth service must be initialized with bt_initialize().
 * @post This function invokes bt_adapter_le_state_changed_cb().
 *
 * @see bt_initialize()
 * @see bt_adapter_le_get_state()
 * @see bt_adapter_le_set_state_changed_cb()
 * @see bt_adapter_le_unset_state_changed_cb()
 * @see bt_adapter_le_state_changed_cb()
 *
 */
int bt_adapter_le_enable(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Disables the local Bluetooth le adapter, asynchronously.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @details This function disables Bluetooth le protocol stack and hardware.
 *
 * @remarks
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation now in progress
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_LE_ENABLED
 * @post This function invokes bt_adapter_le_state_changed_cb().
 *
 * @see bt_adapter_le_get_state()
 * @see bt_adapter_le_state_changed_cb()
 * @see bt_adapter_le_set_state_changed_cb()
 * @see bt_adapter_le_unset_state_changed_cb ()
 *
 */
int bt_adapter_le_disable(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Gets the current state of local Bluetooth adapter.
 * @since_tizen 2.3.1
 *
 * @param[out] adapter_le_state The current adapter le state
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_initialize()
 */
int bt_adapter_le_get_state(bt_adapter_le_state_e *adapter_le_state);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief  Registers a callback function to be invoked when the Bluetooth adapter le state changes.
 * @since_tizen 2.3.1
 *
 * @param[in] callback	The callback function to invoke
 * @param[in] user_data	The user data to be passed to the callback function
 *
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post bt_adapter_le_state_changed_cb() will be invoked.
 *
 * @see bt_initialize()
 * @see bt_adapter_le_state_changed_cb()
 * @see bt_adapter_le_unset_state_changed_cb()
 */
int bt_adapter_le_set_state_changed_cb(bt_adapter_le_state_changed_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief	Unregisters the callback function.
 * @since_tizen 2.3.1
 *
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_initialize()
 * @see bt_adapter_le_set_state_changed_cb()
 */
int bt_adapter_le_unset_state_changed_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief add address to whitelist for accepting scanning request.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @remarks If the adress is in the whitelist then other LE devices are able to
 * search this device. Before calling this API, make sure that the adapter is
 * enabled. There is no callback event for this API.

 * @param[in] address The other device's address
 * @param[in] address_type The other device's address type
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Adapter is not enabled
 * @retval #BT_ERROR_RESOURCE_BUSY  Device or resource busy
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 *
 * @see bt_adapter_le_start_advertising_new()
 * @see bt_adapter_le_stop_advertising()
 */
int bt_adapter_le_add_white_list(const char *address, bt_device_address_type_e address_type);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief remove address from the whitelist for not accepting scanning request.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @remarks If the adress is in the whitelist then other LE devices are able to
 * search this device. Before calling this API, make sure that the adapter is
 * enabled. There is no callback event for this API.
 *
 * @param[in] address The other device's address
 * @param[in] address_type The other device's address type
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Adapter is not enabled
 * @retval #BT_ERROR_RESOURCE_BUSY  Device or resource busy
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 *
 * @see bt_adapter_le_start_advertising_new()
 * @see bt_adapter_le_stop_advertising()
 */
int bt_adapter_le_remove_white_list(const char *address, bt_device_address_type_e address_type);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief  Sets the Privacy feature state of local Bluetooth adapter.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in] enable_privacy The privacy feature to set/unset.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The state of local Bluetooth must be #BT_ADAPTER_LE_ENABLED.
 *
 */
int bt_adapter_le_enable_privacy(bool enable_privacy);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Set Bluetooth LE scan mode
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in]  scan_mode  The scan mode
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE Successful
 * @retval #BT_ERROR_NOT_ENABLED Adapter is not enabled
 * @retval #BT_ERROR_INVALID_PARAM Parameter is invalid
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 */
int bt_adapter_le_set_scan_mode(bt_adapter_le_scan_mode_e scan_mode);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Creates scan filter to find only LE advertisement which has specific data.
 * @since_tizen 2.4
 *
 * @param[out] scan_filter The handle of scan filter
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_adapter_le_destroy_scan_filter()
 */
int bt_adapter_le_create_scan_filter(bt_scan_filter_h *scan_filter);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Destroys scan filter.
 * @since_tizen 2.4
 *
 * @param[in] scan_filter The handle of scan filter
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_adapter_le_create_scan_filter()
 */
int bt_adapter_le_destroy_scan_filter(bt_scan_filter_h scan_filter);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Adds the device address to filter advertisements
 * @since_tizen 2.4
 *
 * @param[in] scan_filter The handle of scan filter
 * @param[in] address The device address to filter advertisements
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_scan_filter_set_device_address(bt_scan_filter_h scan_filter, const char *address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Adds the device name to filter advertisements
 * @since_tizen 2.4
 *
 * @param[in] scan_filter The handle of scan filter
 * @param[in] name The device name to filter advertisements
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_scan_filter_set_device_name(bt_scan_filter_h scan_filter, const char *name);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Adds the service UUID to filter advertisements
 * @since_tizen 2.4
 *
 * @param[in] scan_filter The handle of scan filter
 * @param[in] uuid The service UUID to filter advertisements
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_scan_filter_set_service_uuid(bt_scan_filter_h scan_filter, const char *uuid);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Adds the service uuid and the mask to filter advertisements by partial data
 * @since_tizen 2.4
 *
 * @remarks the length of mask msut be the same with the length of service uuid.
 *
 * @param[in] scan_filter The handle of scan filter
 * @param[in] uuid The service UUID to filter advertisements
 * @param[in] mask The mask to filter advertisements
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_scan_filter_set_service_uuid_with_mask(bt_scan_filter_h scan_filter,
			const char *uuid, const char *mask);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Adds the service solicitation UUID to filter advertisements
 * @since_tizen 2.4
 *
 * @param[in] scan_filter The handle of scan filter
 * @param[in] uuid The service solicitation UUID to filter advertisements
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_scan_filter_set_service_solicitation_uuid(bt_scan_filter_h scan_filter, const char *uuid);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Adds the service solicitation uuid and the mask to filter advertisements by partial data
 * @since_tizen 2.4
 *
 * @remarks the length of mask msut be the same with the length of service solicitation uuid.
 *
 * @param[in] scan_filter The handle of scan filter
 * @param[in] uuid The service solicitation UUID to filter advertisements
 * @param[in] mask The mask to filter advertisements
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask(bt_scan_filter_h scan_filter,
			const char *uuid, const char *mask);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Adds the service data to filter advertisements
 * @since_tizen 2.4
 *
 * @param[in] scan_filter The handle of scan filter
 * @param[in] uuid The service UUID to filter advertisements
 * @param[in] data The service data to filter advertisements
 * @param[in] data_len The length of the service data
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_scan_filter_set_service_data(bt_scan_filter_h scan_filter,
			const char *uuid, const char *data, unsigned int data_len);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Adds the service data and the mask to filter advertisements by partial data
 * @since_tizen 2.4
 *
 * @remarks the length of mask msut be the same with the length of service data.
 *
 * @param[in] scan_filter The handle of scan filter
 * @param[in] uuid The service UUID to filter advertisements
 * @param[in] data The service data to filter advertisements
 * @param[in] data_len The length of the service data
 * @param[in] mask The mask to filter advertisements
 * @param[in] mask_len The length of the mask to be set.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_scan_filter_set_service_data_with_mask(bt_scan_filter_h scan_filter,
			const char *uuid, const char *data, unsigned int data_len, const char *mask, unsigned int mask_len);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Adds the manufacturer data to filter advertisements
 * @since_tizen 2.4
 *
 * @param[in] scan_filter The handle of scan filter
 * @param[in] manufacturer_id The manufacturer ID (0x0000 ~ 0xFFFF)
 * @param[in] data The manufacturer data (byte array)
 * @param[in] data_len The length of manufacturer data
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_scan_filter_set_manufacturer_data(bt_scan_filter_h scan_filter,
			int manufacturer_id, const char *data, unsigned int data_len);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Adds the manufacturer data and the mask to filter advertisements by partial data
 * @since_tizen 2.4
 *
 * @remarks the length of mask msut be the same with the length of service uuid.
 *
 * @param[in] scan_filter The handle of scan filter
 * @param[in] manufacturer_id The manufacturer ID (0x0000 ~ 0xFFFF)
 * @param[in] data The manufacturer data (byte array)
 * @param[in] data_len The length of manufacturer data
 * @param[in] mask The mask to filter advertisements
 * @param[in] mask_len The length of the mask to be set.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_scan_filter_set_manufacturer_data_with_mask(bt_scan_filter_h scan_filter,
			int manufacturer_id, const char *data, unsigned int data_len, const char *mask, unsigned int mask_len);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Registers the scan filter to use for scanning
 * @since_tizen 2.4
 *
 * @remarks Several scan filters can be registered. And the specific advertisements, satisfy the one of scan filters, will be found.
 *
 * @param[in] scan_filter The handle of scan filter
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Scan is in progress
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_register_scan_filter(bt_scan_filter_h scan_filter);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Unregisters the scan filter to be registered
 * @since_tizen 2.4
 *
 * @param[in] scan_filter The handle of scan filter
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Scan is in progress
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_unregister_scan_filter(bt_scan_filter_h scan_filter);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Unregisters all scan filters to be registered
 * @since_tizen 2.4
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Scan is in progress
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 */
int bt_adapter_le_unregister_all_scan_filters(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Set advertising filter policy to use white list
 * @since_tizen 2.4
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @param[in] advertiser The handle of advertiser
 * @param[in] filter_policy The filter policy of advertising
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation is now in progress
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_adapter_le_start_advertising_new()
 */
int bt_adapter_le_set_advertising_filter_policy(bt_advertiser_h advertiser, bt_adapter_le_advertising_filter_policy_e filter_policy);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Creates a bond with a remote Bluetooth device, asynchronously.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @remarks A bond can be destroyed by bt_device_destroy_bond().\n
 * The bonding request can be cancelled by bt_device_cancel_bonding().
 *
 * @param[in] remote_address The address of the remote Bluetooth device with which the bond should be created
 * @param[in] conn_type The connection type(LE or BREDR) to create bond with remote device
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_RESOURCE_BUSY     Device or resource busy
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The remote device must be discoverable with bt_adapter_start_device_discovery().
 * @post This function invokes bt_device_bond_created_cb().
 *
 * @see bt_adapter_start_device_discovery()
 * @see bt_device_create_bond()
 * @see bt_device_bond_created_cb()
 * @see bt_device_cancel_bonding()
 * @see bt_device_destroy_bond()
 * @see bt_device_set_bond_created_cb()
 * @see bt_device_unset_bond_created_cb()
 */
int bt_device_create_bond_by_type(const char *remote_address,
				  bt_device_connection_link_type_e conn_type);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Cancels service search process.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded
 * @retval #BT_ERROR_NOT_IN_PROGRESS  Operation not in progress
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The service search must be in progress by bt_device_start_service_search().
 *
 * @see bt_device_start_service_search()
 * @see bt_device_service_searched_cb()
 * @see bt_device_set_service_searched_cb()
 * @see bt_device_unset_service_searched_cb()
 */
int bt_device_cancel_service_search(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Gets a connection state
 * @since_tizen 2.4
 *
 * @param[in] remote_address The address of the remote Bluetooth device
 * @param[in] link_type The link type to get a connection state
 * @param[out] connected The connection state
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED   Operation failed
 */
int bt_device_get_connection_state(const char *remote_address, bt_device_connection_link_type_e link_type, bool *connected);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Registers a rfcomm server socket with a specific UUID. Activation by dbus is possible when the profile is connected.
 * @since_tizen 2.4
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @remarks A socket can be destroyed by bt_socket_destroy_rfcomm_ex().
 * Application should call this API to receive a connection event when launched again by dbus.
 *
 * @param[in] uuid The UUID of service to provide
 * @param[in] bus_name bus_name of the application which is provided in service file.
 * @param[in] object_path dbus of the application
 * @return 0 on success, otherwise a negative error value.
 *
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Already registered
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 *
 * @see bt_socket_listen_and_accept_rfcomm_ex()
 * @see bt_socket_destroy_rfcomm_ex()
 */
int bt_socket_create_rfcomm_ex(const char *uuid, const char *bus_name, const char *object_path);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Removes the rfcomm server socket which was created using bt_socket_create_rfcomm_ex().
 * @since_tizen 2.4
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @remarks If callback function bt_socket_connection_state_changed_cb() is set and the remote Bluetooth device is connected,
 * then bt_socket_connection_state_changed_cb() will be called when this function is finished successfully.
 *
 * @param[in] uuid The UUID (which was created using bt_socket_create_rfcomm()) to destroy
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The socket must be created with bt_socket_create_rfcomm_ex().
 * @post If callback function bt_socket_connection_state_changed_cb() is set and the remote Bluetooth device is connected,
 * then bt_socket_connection_state_changed_cb() will be called.
 * @see bt_socket_create_rfcomm_ex()
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()
 */
int bt_socket_destroy_rfcomm_ex(const char *uuid);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Starts listening on passed rfcomm socket and accepts connection requests. Activation by dbus is possible when the profile is connected.
 * @since_tizen 2.4
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @details Pop-up is shown automatically when a RFCOMM connection is requested.
 * bt_socket_connection_state_changed_cb() will be called with
 * #BT_SOCKET_CONNECTED if you click "yes" and connection is finished successfully.
 * @param[in] uuid The UUID of service to provide
 * @param[in] max_pending_connections The maximum number of pending connections
 * @param[in] bus_name bus_name of the application which is provided in service file.
 * @param[in] object_path dbus of the application
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The socket must be created with bt_socket_create_rfcomm_ex().
 * @post If callback function bt_socket_connection_state_changed_cb() is set,
 * then bt_socket_connection_state_changed_cb() will be called when the remote Bluetooth device is connected.
 * @see bt_socket_create_rfcomm_ex()
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()
 */
int bt_socket_listen_and_accept_rfcomm_ex(const char *uuid, int max_pending_connections, const char* bus_name, const char *object_path);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Starts listening on passed rfcomm socket.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @details bt_socket_connection_requested_cb() will be called when a RFCOMM connection is requested.
 *
 * @param[in] socket_fd  The file descriptor socket on which start to listen
 * @param[in] max_pending_connections  The number of pending connections
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The socket must be created with bt_socket_create_rfcomm().
 * @post This function invokes bt_socket_connection_state_changed_cb().
 *
 * @see bt_socket_create_rfcomm()
 * @see bt_socket_set_connection_requested_cb()
 * @see bt_socket_unset_connection_requested_cb()
 * @see bt_socket_connection_requested_cb()
 */
int bt_socket_listen(int socket_fd, int max_pending_connections);

/**
 * @internal
 * @ingroup  CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief  Accepts a connection request.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] requested_socket_fd  The file descriptor of socket on which a connection is requested
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The connection is requested by bt_socket_connection_requested_cb().
 * @see bt_socket_create_rfcomm()
 * @see bt_socket_connection_requested_cb()
 * @see bt_socket_listen()
 * @see bt_socket_reject()
*/
int bt_socket_accept(int requested_socket_fd);

/**
 * @internal
 * @ingroup  CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief  Rejects a connection request.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] socket_fd  The file descriptor of socket on which a connection is requested
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The connection is requested by bt_socket_connection_requested_cb().
 * @see bt_socket_create_rfcomm()
 * @see bt_socket_connection_requested_cb()
 * @see bt_socket_listen()
 * @see bt_socket_accept()
 */
int bt_socket_reject(int socket_fd);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_SERVER_MODULE
 * @brief Initializes the Bluetooth OPP server requested by bt_opp_server_push_requested_cb().
 * @since_tizen 2.3.1
 * @details The popup appears when an OPP connection is requested from a remote device.
 * If you accept the request, then connection will be established and bt_opp_server_push_requested_cb() will be called.
 * At that time, you can call either bt_opp_server_accept() or bt_opp_server_reject().
 * @remarks This function must be called to start Bluetooth OPP server. You must free all resources of the Bluetooth service
 * by calling bt_opp_server_deinitialize() if Bluetooth OPP service is no longer needed.
 * @param[in] destination  The destination path
 * @param[in] push_requested_cb  The callback called when a push is requested
 * @param[in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_RESOURCE_BUSY  Device or resource busy
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @see  bt_opp_server_push_requested_cb()
 * @see  bt_opp_server_deinitialize()
 * @see  bt_opp_server_accept()
 * @see  bt_opp_server_reject()
 */
int bt_opp_server_initialize(const char *destination, bt_opp_server_push_requested_cb push_requested_cb, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief Notifies the call event to the remote bluetooth device.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @remarks Before notifying #BT_AG_CALL_EVENT_ANSWERED or #BT_AG_CALL_EVENT_DIALING, you should open SCO(Synchronous Connection Oriented link)
 * if Bluetooth Hands-Free need SCO connection.
 * @param[in] event  The call event
 * @param[in] call_id  The call ID
 * @param[in] phone_number  The phone number. You must set this value in case of #BT_AG_CALL_EVENT_DIALING and #BT_AG_CALL_EVENT_INCOMING.
 * In other cases, this value can be NULL.
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio device must be connected with bt_audio_connect().
 * @see bt_audio_connect()
 */
int bt_ag_notify_call_event(bt_ag_call_event_e event, unsigned int call_id, const char *phone_number);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief Notifies the call list to the remote bluetooth device.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] list  The call list
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio device must be connected with bt_audio_connect().
 * @see bt_audio_connect()
 */
int bt_ag_notify_call_list(bt_call_list_h list);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief Notifies the state of voice recognition.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] state  The state of voice recognition: (@c true = enabled, @c  false = disabled)
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio device must be connected with bt_audio_connect().
 * @see bt_audio_connect()
 */
int bt_ag_notify_voice_recognition_state(bool state);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Registers a callback function that will be invoked when a call handling event happened from Hands-Free.
 * @since_tizen 2.3.1
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_call_handling_event_cb()
 * @see bt_ag_unset_call_handling_event_cb()
 */
int bt_ag_set_call_handling_event_cb(bt_ag_call_handling_event_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Unregisters a callback function that will be invoked when a call handling event happened from Hands-Free.
 * @since_tizen 2.3.1
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_call_handling_event_cb()
 * @see bt_ag_set_call_handling_event_cb()
 */
int bt_ag_unset_call_handling_event_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Registers a callback function that will be invoked when a multi call handling event happened from Hands-Free.
 * @since_tizen 2.3.1
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_multi_call_handling_event_cb()
 * @see bt_ag_unset_multi_call_handling_event_cb()
 */
int bt_ag_set_multi_call_handling_event_cb(bt_ag_multi_call_handling_event_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Unregisters a callback function that will be invoked when a multi call handling event happened from Hands-Free.
 * @since_tizen 2.3.1
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_multi_call_handling_event_cb()
 * @see bt_ag_set_multi_call_handling_event_cb()
 */
int bt_ag_unset_multi_call_handling_event_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Registers a callback function that will be invoked when a DTMF(Dual Tone Multi Frequency) is transmitted from Hands-Free.
 * @since_tizen 2.3.1
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_dtmf_transmitted_cb()
 * @see bt_ag_unset_dtmf_transmitted_cb()
 */
int bt_ag_set_dtmf_transmitted_cb(bt_ag_dtmf_transmitted_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Unregisters a callback function that will be invoked when a DTMF(Dual Tone Multi Frequency) is transmitted from Hands-Free.
 * @since_tizen 2.3.1
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_dtmf_transmitted_cb()
 * @see bt_ag_set_dtmf_transmitted_cb()
 */
int bt_ag_unset_dtmf_transmitted_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Notifies the speaker gain to the remote device.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @details This function sends a signal to the remote device. This signal has the gain value.
 * @a gain is represented on a scale from 0 to 15. This value is absolute value relating to a particular volume level.
 * When the speaker gain of remote device is changed to the requested gain, bt_audio_speaker_gain_changed_cb() will be called.
 * @param[in] gain The gain of speaker (0 ~ 15)
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The remote device is connected by bt_audio_connect() with #BT_AUDIO_PROFILE_TYPE_HSP_HFP service.
 * @see bt_ag_get_speaker_gain()
 * @see bt_ag_set_speaker_gain_changed_cb()
 * @see bt_ag_unset_speaker_gain_changed_cb()
 */
int bt_ag_notify_speaker_gain(int gain);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Gets the current speaker gain of the remote device.
 * @since_tizen 2.3.1
 * @details This function gets the value of speaker gain of the remote device.
 * @a gain is represented on a scale from 0 to 15. This value is absolute value relating to a particular volume level.
 * @param[out] gain The gain of speaker (0 ~ 15)
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The remote device is connected by bt_audio_connect() with #BT_AUDIO_PROFILE_TYPE_HSP_HFP service.
 * @see bt_ag_notify_speaker_gain()
 * @see bt_ag_set_speaker_gain_changed_cb()
 * @see bt_ag_unset_speaker_gain_changed_cb()
 */
int bt_ag_get_speaker_gain(int *gain);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief Checks whether the remoted device enables NREC(Noise Reduction and Echo Canceling) or not.
 * @since_tizen 2.3.1
 * @param[out] enabled The NREC status: (@c true = enabled, @c  false = not enabled)
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The remote device is connected by bt_audio_connect() with #BT_AUDIO_PROFILE_TYPE_HSP_HFP service.
 * @see bt_audio_connect()
 */
int bt_ag_is_nrec_enabled(bool *enabled);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Registers a callback function that will be invoked when the speaker gain of the remote device is changed.
 * @since_tizen 2.3.1
 * @details This function let you know the change of the speaker gain of the remote device.
 * @a gain is represented on a scale from 0 to 15. This value is absolute value relating to a particular volume level.
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_unset_speaker_gain_changed_cb()
 */
int bt_ag_set_speaker_gain_changed_cb(bt_ag_speaker_gain_changed_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Unregisters a callback function that will be invoked when the speaker gain of the remote device is changed.
 * @since_tizen 2.3.1
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_set_speaker_gain_changed_cb()
 */
int bt_ag_unset_speaker_gain_changed_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Registers a callback function that will be invoked when the microphone gain of the remote device is changed.
 * @since_tizen 2.3.1
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_unset_microphone_gain_changed_cb()
 */
int bt_ag_set_microphone_gain_changed_cb(bt_ag_microphone_gain_changed_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief  Unregisters a callback function that will be invoked when the microphone gain of the remote device is changed.
 * @since_tizen 2.3.1
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_set_microphone_gain_changed_cb()
 */
int bt_ag_unset_microphone_gain_changed_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_CALL_MODULE
 * @brief Creates a handle of call list.
 * @since_tizen 2.3.1
 * @param[out] list  The handle of call list
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_call_list_destroy()
 */
int bt_call_list_create(bt_call_list_h *list);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_CALL_MODULE
 * @brief Destroys the handle of call list.
 * @since_tizen 2.3.1
 * @param[in] list  The handle of call list
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_call_list_create()
 */
int bt_call_list_destroy(bt_call_list_h list);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_CALL_MODULE
 * @brief Resets the handle of call list.
 * @since_tizen 2.3.1
 * @param[in] list  The handle of call list
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_call_list_create()
 */
int bt_call_list_reset(bt_call_list_h list);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_CALL_MODULE
 * @brief Adds a call to the handle of call list.
 * @since_tizen 2.3.1
 * @param[in] list  The handle of call list
 * @param[in] call_id  The call ID
 * @param[in] state  The state of audio gate call
 * @param[in] phone_number The phone number. You must set this value in case of #BT_AG_CALL_EVENT_DIALING and      #BT_AG_CALL_EVENT_INCOMING.
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_call_list_create()
 */
int bt_call_list_add(bt_call_list_h list, unsigned int call_id, bt_ag_call_state_e state, const char *phone_number);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief Checks whether the remoted device is wbs (Wide Band Speech) mode or not.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[out] wbs_mode The wbs status: (@c true = wide band speech, @c  false = narrow band speech)
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The remote device is connected by bt_audio_connect() with #BT_AUDIO_PROFILE_TYPE_HSP_HFP service.
 * @see bt_audio_connect()
 */
int bt_ag_is_wbs_mode(bool *wbs_mode);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_AG_MODULE
 * @brief Gets the HF(Hands-Free) profile connected status for AG role.
 * @since_tizen 2.4
 * @param[out] connected the connected status: (@c true = connected , @c  false = not connected )
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED	Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 */
int bt_ag_is_connected(bool *connected);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief  Registers a callback function that will be invoked when the SCO(Synchronous Connection Oriented link) state is changed.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_sco_state_changed_cb()
 * @see bt_ag_unset_sco_state_changed_cb()
 */
int bt_hf_set_sco_state_changed_cb(bt_hf_sco_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief  Unregisters a callback function that will be invoked when the SCO(Synchronous Connection Oriented link) state is changed.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_sco_state_changed_cb()
 * @see bt_ag_set_sco_state_changed_cb()
 */
int bt_hf_unset_sco_state_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief  Registers a callback function that will be invoked when a call handling event happened from Hands-Free.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_call_handling_event_cb()
 * @see bt_ag_unset_call_handling_event_cb()
 */
int bt_hf_set_call_handling_event_cb(bt_hf_call_handling_event_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief  Unregisters a callback function that will be invoked when a call handling event happened from Hands-Free.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_call_handling_event_cb()
 * @see bt_ag_set_call_handling_event_cb()
 */
int bt_hf_unset_call_handling_event_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief  Registers a callback function that will be invoked when a multi call handling event happened from Hands-Free.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_multi_call_handling_event_cb()
 * @see bt_ag_unset_multi_call_handling_event_cb()
 */
int bt_hf_set_multi_call_handling_event_cb(bt_hf_multi_call_handling_event_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief  Unregisters a callback function that will be invoked when a multi call handling event happened from Hands-Free.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_ag_multi_call_handling_event_cb()
 * @see bt_ag_set_multi_call_handling_event_cb()
 */
int bt_hf_unset_multi_call_handling_event_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief Initializes the Bluetooth HF profile related with audio.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @remarks This function must be called before Bluetooth profiles related with audio starts.
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_hf_deinitialize()
 */
int bt_hf_initialize(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief Deinitializes the Bluetooth HF profile related with audio.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 */
int bt_hf_deinitialize(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief Notifies the call event to the remote bluetooth device.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @privlevel platform
 * @privilege http://tizen.org/privilege/bluetooth.admin
 * @remarks Before notifying #BT_HF_CALL_EVENT_ANSWERED or #BT_HF_CALL_EVENT_DIALING, you should open SCO(Synchronous Connection Oriented link)
 * if Bluetooth Hands-Free need SCO connection.
 * @param[in] event  The call event
 * @param[in] call_id  The call ID
 * @param[in] phone_number  The phone number. You must set this value in case of #BT_HF_CALL_EVENT_DIALING and #BT_HF_CALL_EVENT_INCOMING.
 * In other cases, this value can be NULL.
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio device must be connected with bt_audio_connect().
 * @see bt_audio_connect()
 */
int bt_hf_notify_call_event(bt_hf_call_event_e event, char *phone_number);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief  Notifies the speaker gain to the remote device.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @privlevel platform
 * @privilege http://tizen.org/privilege/bluetooth.admin
 * @details This function sends a signal to the remote device. This signal has the gain value.
 * @a gain is represented on a scale from 0 to 15. This value is absolute value relating to a particular volume level.
 * When the speaker gain of remote device is changed to the requested gain, bt_audio_speaker_gain_changed_cb() will be called.
 * @param[in] gain The gain of speaker (0 ~ 15)
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The remote device is connected by bt_audio_connect() with #BT_AUDIO_PROFILE_TYPE_HSP_HFP service.
 * @see bt_hf_get_speaker_gain()
 * @see bt_hf_set_speaker_gain_changed_cb()
 * @see bt_hf_unset_speaker_gain_changed_cb()
 */
int bt_hf_notify_speaker_gain(int gain);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief  Registers a callback function that will be invoked when the speaker gain of the remote device is changed.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @details This function let you know the change of the speaker gain of the remote device.
 * @a gain is represented on a scale from 0 to 15. This value is absolute value relating to a particular volume level.
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_hf_unset_speaker_gain_changed_cb()
 */
int bt_hf_set_speaker_gain_changed_cb(bt_hf_speaker_gain_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief  Unregisters a callback function that will be invoked when the speaker gain of the remote device is changed.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_hf_set_speaker_gain_changed_cb()
 */
int bt_hf_unset_speaker_gain_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief Notifies the state of voice recognition.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @privlevel platform
 * @privilege http://tizen.org/privilege/bluetooth.admin
 * @param[in] state  The state of voice recognition: (@c true = enabled, @c  false = disabled)
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio device must be connected with bt_audio_connect().
 * @see bt_audio_connect()
 */
int bt_hf_notify_voice_recognition_state(bool state);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief  Registers a callback function that will be invoked when a call status event happened from Hands-Free.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_hf_unset_call_status_updated_event_cb()
 */
int bt_hf_set_call_status_updated_event_cb(bt_hf_call_status_updated_event_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief  Unregisters a callback function that will be invoked when a call status event happened from Hands-Free.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_hf_set_call_status_updated_event_cb()
 */
int bt_hf_unset_call_status_updated_event_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief Closes an opened SCO(Synchronous Connection Oriented link), synchronously.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @privlevel platform
 * @privilege http://tizen.org/privilege/bluetooth.admin
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 */
int bt_hf_close_sco(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief Sends the DTMF(Dual Tone Multi Frequency).
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @privlevel platform
 * @privilege http://tizen.org/privilege/bluetooth.admin
 * @param[in] dtmf  The DTMF to send
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The Bluetooth audio device must be connected with bt_audio_connect().
 * @see bt_audio_connect()
 */
int bt_hf_send_dtmf(char *dtmf);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief Gets the HF(Hands-Free) profile connected status for HF role.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @param[out] connected the connected status: (@c true = connected , @c  false = not connected )
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED	Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 */
int bt_hf_is_connected(bool *connected);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief Checks whether an opened SCO(Synchronous Connection Oriented link) exists or not.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 *
 * @param[out] opened The SCO status: (@c true = opened, @c  false = not opened)
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio device must be connected with bt_audio_connect().
 * @see bt_audio_connect()
 */
int bt_hf_is_sco_opened(bool *opened);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief Gets the codec ID.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @remarks The @a codec_id must be released with free() by you.
 *
 * @param[out] codec_id The codec ID
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio device must be connected with bt_audio_connect().
 * @see bt_audio_connect()
 */
int bt_hf_get_codec_id(unsigned int *codec_id);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief Gets the call status information list.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 * @remarks The @a call_list must be released with bt_hf_free_call_status_info_list() by you.
 * @remarks call_info_list has elements which consist of bt_hf_call_status_info_s
 *
 * @param[out] call_list The call status information list
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio device must be connected with bt_audio_connect().
 * @see bt_hf_call_status_info_s
 * @see bt_audio_connect()
 */
int bt_hf_get_call_status_info_list(GSList **call_list);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_HF_MODULE
 * @brief Frees the call status information list.
 * @since_tizen @if MOBILE @elseif WEARABLE 2.3.1 @endif
 *
 * @param[in] call_list The call status information list
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_hf_get_call_status_info_list()
 */
int bt_hf_free_call_status_info_list(GSList *call_list);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief Gets the specification name from the UUID
 * @since_tizen 2.4
 *
 * @remarks @a name must be released with free() by you.
 *
 * @param[in] uuid The UUID
 * @param[out] name The specification name which defined from www.bluetooth.org
 * @return  0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_gatt_get_uuid()
 */
int bt_gatt_get_uuid_specification_name(const char *uuid, char **name);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_GATT_SERVER_MODULE
 * @brief  Updates the permissions which a characteristic or descriptor's GATT handle has.
 * @since_tizen 3.0
 *
 * @param[in] gatt_handle The handle of a characteristic or descriptor
 * @param[in] permissions The permissions to be updated
 * @return  0 on success, otherwise a negative error value
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_gatt_characteristic_create()
 * @see bt_gatt_descriptor_create()
 * @see bt_gatt_permission_e
 */
int bt_gatt_set_permissions(bt_gatt_h gatt_handle, int permissions);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief Destroys the GATT handle
 * @since_tizen 2.4
 *
 * @param[in] gatt_handle The handle of service, characteristic or descriptor
 * @return  0 on success, otherwise a negative error value
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_gatt_service_create()
 * @see bt_gatt_characteristic_create()
 * @see bt_gatt_descriptor_create()
 */
int bt_gatt_destroy(bt_gatt_h gatt_handle);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_MODULE
 * @brief  Registers a callback function that will be invoked when the A2DP Source connection state is changed.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_audio_connection_state_changed_cb()
 */
int bt_a2dp_source_audio_set_connection_state_changed_cb(bt_audio_connection_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_MODULE
 * @brief  Unregisters a callback function that will be invoked when the A2DP Source connection state is changed.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 * @see bt_audio_connection_state_changed_cb()
 * @see bt_audio_set_connection_state_changed_cb()
 */
int bt_a2dp_source_audio_unset_connection_state_changed_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_PAN_NAP_MODULE
 * @brief Activates the NAP(Network Access Point).
 * @since_tizen 2.3.1
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_ALREADY_DONE  Operation is already done
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED
 * @see bt_nap_deactivate()
 */
int bt_nap_activate(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_PAN_NAP_MODULE
 * @brief Deactivates the NAP(Network Access Point).
 * @since_tizen 2.3.1
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_ALREADY_DONE  Operation is already done
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth NAP service must be activated with bt_nap_activate().
 * @see bt_nap_activate()
 */
int bt_nap_deactivate(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_PAN_NAP_MODULE
 * @brief Disconnects the all PANUs(Personal Area Networking User) which are connected to you.
 * @since_tizen 2.3.1
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth NAP service must be activated with bt_nap_activate().
 * @see bt_nap_activate()
 */
int bt_nap_disconnect_all(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_PAN_NAP_MODULE
 * @brief Disconnects the specified PANU(Personal Area Networking User) which is connected to you.
 * @since_tizen 2.3.1
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] remote_address  The remote address
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth NAP service must be activated with bt_nap_activate().
 * @see bt_nap_activate()
 */
int bt_nap_disconnect(const char *remote_address);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_PAN_NAP_MODULE
 * @brief  Registers a callback function that will be invoked when the connection state changes.
 * @since_tizen 2.3.1
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post bt_nap_connection_state_changed_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_nap_connection_state_changed_cb()
 * @see bt_nap_unset_connection_state_changed_cb()
 */
int bt_nap_set_connection_state_changed_cb(bt_nap_connection_state_changed_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_PAN_NAP_MODULE
 * @brief  Unregisters a callback function that will be invoked when the connection state changes.
 * @since_tizen 2.3.1
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post bt_nap_connection_state_changed_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_nap_connection_state_changed_cb()
 * @see bt_nap_set_connection_state_changed_cb()
 */
int bt_nap_unset_connection_state_changed_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_PAN_PANU_MODULE
 * @brief  Registers a callback function that will be invoked when the connection state changes.
 * @since_tizen 2.3.1
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post bt_nap_connection_state_changed_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_panu_connection_state_changed_cb()
 * @see bt_panu_unset_connection_state_changed_cb()
 */
int bt_panu_set_connection_state_changed_cb(bt_panu_connection_state_changed_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_PAN_PANU_MODULE
 * @brief  Unregisters a callback function that will be invoked when the connection state changes.
 * @since_tizen 2.3.1
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post bt_nap_connection_state_changed_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_panu_connection_state_changed_cb()
 * @see bt_panu_set_connection_state_changed_cb()
 */
int bt_panu_unset_connection_state_changed_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_PAN_PANU_MODULE
 * @brief Connects the remote device with the PAN(Personal Area Networking) service, asynchronously.
 * @since_tizen 2.3.1
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] remote_address  The remote address
 * @param[in] type  The type of PAN service
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The local device must be bonded with the remote device by bt_device_create_bond().
 * @post bt_panu_connection_state_changed_cb() will be invoked.
 * @see bt_panu_disconnect()
 * @see bt_panu_connection_state_changed_cb()
 */
int bt_panu_connect(const char *remote_address, bt_panu_service_type_e type);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_PAN_PANU_MODULE
 * @brief Disconnects the remote device with the PAN(Personal Area Networking) service, asynchronously.
 * @since_tizen 2.3.1
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] remote_address  The remote address
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The remote device must be connected by bt_panu_connect().
 * @post bt_panu_connection_state_changed_cb() will be invoked.
 * @see bt_panu_connect()
 * @see bt_panu_connection_state_changed_cb()
 */
int bt_panu_disconnect(const char *remote_address);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief   update LE connection.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @pre The remote device must be connected with bt_gatt_connect().
 */
int bt_device_le_conn_update(const char *device_address,
			     const bt_le_conn_update_s *parameters);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Registers the method for HID Device role
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @remarks This function must be called to register HID UUID
 * then only remote device could be able identify this one as HID device
 *
 * @param[in] callback  The callback called when the connection state is changed
 * @param[in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Already activated
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_hid_device_deactivate()
 */
int bt_hid_device_activate(bt_hid_device_connection_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Unregisters the method for HID Device role
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @remarks This function must be called to deregister HID UUID
 *
 * @param[in] socket_fd on which uuid need to be deregistered.
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOT_IN_PROGRESS  Not activated
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_hid_device_activate()
 */
int bt_hid_device_deactivate(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Initiates HID device Connection with device role
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @remarks This function must be called to Initiate Hid device role connection
 *
 * @param[in] remote_address device address of remote device.
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOT_IN_PROGRESS  Not activated
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_ALREADY_DONE   Already connected
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_hid_device_activate()
 */
int bt_hid_device_connect(const char *remote_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Disconnects the connection with HID Host device.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in] remote_address device address of remote device.
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_hid_device_connection_state_changed_cb()
 */
int bt_hid_device_disconnect(const char *remote_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Sends the mouse event data.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in] remote_address device address of remote device.
 * @param[in] mouse_data mouse data that need to be passed to remote device
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 *
 * @pre The HID connection must be established.
 * @see bt_hid_device_connection_state_changed_cb()
 */
int bt_hid_device_send_mouse_event(const char *remote_address,
			const bt_hid_mouse_data_s *mouse_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Sends the keyboard event data.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in] remote_address device address of remote device.
 * @param[in] key_data  key data the need to be passed to remote device
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 *
 * @pre The HID connection must be established.
 * @see bt_hid_device_connection_state_changed_cb()
 */
int bt_hid_device_send_key_event(const char *remote_address,
			const bt_hid_key_data_s *key_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Sets the callback when device gets some data from HID Host.
 * @since_tizen 2.3.1
 *
 * @param[in] callback  callback function to be set when data is received.
 * @param[in] user_data data from application which will be provided in callback.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 *
 * @see bt_hid_device_connection_state_changed_cb()
 */
int bt_hid_device_set_data_received_cb(bt_hid_device_data_received_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Unsets the callback when device gets some data from HID Host.
 * @since_tizen 2.3.1
 *
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 *
 * @see bt_hid_device_connection_state_changed_cb()
 */
int bt_hid_device_unset_data_received_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Responds to the reports from HID Host.
 * @since_tizen 2.3.1
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in] remote_address device address of remote device.
 * @param[in] htype Header type to be there in response
 * @param[in] ptype Parameter type to be there in response.
 * @param[in] data Data to be present in data payload of response.
 * @param[in] data_len The length of the response data
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 *
 * @pre The HID connection must be established.
 * @see bt_hid_device_connection_state_changed_cb()
 */
int bt_hid_device_reply_to_report(const char *remote_address,
		bluetooth_hid_header_type_t htype, bluetooth_hid_param_type_t ptype,
		const char *data, unsigned int data_len);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Sets Restriction for BT mode(BT allowed or not).
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	value - BT Allow value.
 *		BT_DPM_ERROR	 = -1,	 < bluetooth allowance error
 *		BT_DPM_BT_ALLOWED,		 < bluetooth allowance allowed
 *		BT_DPM_HANDSFREE_ONLY,  < bluetooth allowance handsfree only
 *		BT_DPM_BT_RESTRICTED,  < bluetooth allowance restricted
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre none.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_set_allow_bluetooth_mode(bt_dpm_allow_e value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads Restriction for BT mode(BT allowed or not).
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in] none
 * @param[out]	value - BT Allow value.
 *		BT_DPM_ERROR	 = -1,	 < bluetooth allowance error
 *		BT_DPM_BT_ALLOWED,		 < bluetooth allowance allowed
 *		BT_DPM_HANDSFREE_ONLY,	< bluetooth allowance handsfree only
 *		BT_DPM_BT_RESTRICTED,  < bluetooth allowance restricted
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre none.
 * @see bt_dpm_set_allow_bluetooth_mode()
 */
int bt_dpm_get_allow_bluetooth_mode(bt_dpm_allow_e *value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Sets the Restriction for device.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_activate_device_restriction(bt_dpm_status_e value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the Restriction for device.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_is_device_restriction_active(bt_dpm_status_e *value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Sets the Restriction for uuid.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_activate_uuid_restriction(bt_dpm_status_e value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the Restriction for uuid.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_is_uuid_restriction_active(bt_dpm_status_e *value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Adds the device to blacklist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	device_address - Device address
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_add_devices_to_blacklist(const char *device_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Adds the device to whitelist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	device_address - Device address
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_add_devices_to_whitelist(const char *device_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Adds the uuids to blacklist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	service_uuids - profile or custom service uuids
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_add_uuids_to_blacklist(const char *service_uuid);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Adds the uuid to whitelist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	service_uuids - profile or custom service uuids
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_add_uuids_to_whitelist(const char *service_uuid);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Clears the device from blacklist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	none
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_clear_devices_from_blacklist(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Clears the device from whitelist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	none
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_clear_devices_from_whitelist(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Clears the uuids from blacklist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	none
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_clear_uuids_from_blacklist(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Clears the uuids from whitelist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	none
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_clear_uuids_from_whitelist(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the devices from blacklist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out] device_list - list of devices
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_get_devices_from_blacklist(bt_dpm_device_list_s **device_list);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the devices from whitelist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out] device_list - list of devices
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_get_devices_from_whitelist(bt_dpm_device_list_s **device_list);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the uuids from blacklist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out] uuid_list - list of uuids
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_get_uuids_from_blacklist(bt_dpm_uuids_list_s **uuid_list);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the uuids from whitelist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out] uuid_list - list of uuids
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_get_uuids_from_whitelist(bt_dpm_uuids_list_s **uuid_list);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Removes the devices from whitelist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	device_address - Device address
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_remove_device_from_whitelist(const char *device_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Removes the devices from blacklist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	device_address - Device address
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_remove_device_from_blacklist(const char *device_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Removes the uuids from whitelist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	service_uuids - profile or custom service uuids
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_remove_uuid_from_whitelist(const char *service_uuid);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Removes the uuids from blacklist.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	service_uuids - profile or custom service uuids
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_remove_uuid_from_blacklist(const char *service_uuid);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Sets the Restriction for  outgoing call.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_set_allow_outgoing_call(bt_dpm_status_e value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the Restriction for  outgoing call.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_get_allow_outgoing_call(bt_dpm_status_e *value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Sets the Restriction for pairing.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_set_pairing_state(bt_dpm_status_e value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the Restriction for pairing.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_get_pairing_state(bt_dpm_status_e *value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Sets the Restriction for profiles.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]profile - Profile.
 *		BT_DPM_POLICY_A2DP_PROFILE_STATE,
 *		BT_DPM_POLICY_AVRCP_PROFILE_STATE,
 *		BT_DPM_POLICY_BPP_PROFILE_STATE,
 *		BT_DPM_POLICY_DUN_PROFILE_STATE,
 *		BT_DPM_POLICY_FTP_PROFILE_STATE,
 *		BT_DPM_POLICY_HFP_PROFILE_STATE,
 *		BT_DPM_POLICY_HSP_PROFILE_STATE,
 *		BT_DPM_POLICY_PBAP_PROFILE_STATE,
 *		BT_DPM_POLICY_SAP_PROFILE_STATE,
 *		BT_DPM_POLICY_SPP_PROFILE_STATE,
 *		BT_DPM_PROFILE_NONE
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_set_profile_state(bt_dpm_profile_e profile, bt_dpm_status_e value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the Restriction for profiles.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]profile - Profile.
 *		BT_DPM_POLICY_A2DP_PROFILE_STATE,
 *		BT_DPM_POLICY_AVRCP_PROFILE_STATE,
 *		BT_DPM_POLICY_BPP_PROFILE_STATE,
 *		BT_DPM_POLICY_DUN_PROFILE_STATE,
 *		BT_DPM_POLICY_FTP_PROFILE_STATE,
 *		BT_DPM_POLICY_HFP_PROFILE_STATE,
 *		BT_DPM_POLICY_HSP_PROFILE_STATE,
 *		BT_DPM_POLICY_PBAP_PROFILE_STATE,
 *		BT_DPM_POLICY_SAP_PROFILE_STATE,
 *		BT_DPM_POLICY_SPP_PROFILE_STATE,
 *		BT_DPM_PROFILE_NONE
 * @param[out]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_get_profile_state(bt_dpm_profile_e profile, bt_dpm_status_e *value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Sets the Restriction for desktop connectivity.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_set_desktop_connectivity_state(bt_dpm_status_e value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the Restriction for desktop connectivity.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_get_desktop_connectivity_state(bt_dpm_status_e *value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Sets the Restriction for discoverable mode.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_set_discoverable_state(bt_dpm_status_e value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the Restriction for discoverable mode.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_get_discoverable_state(bt_dpm_status_e *value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Sets the Restriction for limited discoverable mode.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */

int bt_dpm_set_limited_discoverable_state(bt_dpm_status_e value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the Restriction for limited discoverable mode.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_get_limited_discoverable_state(bt_dpm_status_e *value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Sets the Restriction for Data transfer.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[in]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_set_data_transfer_state(bt_dpm_status_e value);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DPM_MODULE
 * @brief Reads the Restriction for Data transfer.
 * @since_tizen 3.0
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 *
 * @param[out]	value - State value.
 *		BT_DPM_ALLOWED		= 0,	< DPM Policy status allowed.
 *		BT_DPM_RESTRICTED		= 1,	< DPM Policy status restricted.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER	invalid paramter
 * @retval #BT_ERROR_NOT_SUPPORTED	Not suported
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED operation failed
 *
 * @pre bt_dpm_set_allow_bluetooth_mode must be allowed.
 * @see bt_dpm_get_allow_bluetooth_mode()
 */
int bt_dpm_get_data_transfer_state(bt_dpm_status_e *value);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_NETWORK_BLUETOOTH_INTERNAL_H__ */
