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


#ifndef __TIZEN_NETWORK_BLUETOOTH_H__
#define __TIZEN_NETWORK_BLUETOOTH_H__

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <tizen_error.h>

#include "bluetooth_type.h"
#include "bluetooth_internal.h"
#include "bluetooth_extention.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @file        bluetooth.h
 * @brief       API to control the Bluetooth adapter and devices and communications.
 * @ingroup     CAPI_NETWORK_BLUETOOTH_MODULE
 */


/**
 * @addtogroup CAPI_NETWORK_BLUETOOTH_MODULE
 * @{
 */


/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_MODULE
 * @brief Initializes the Bluetooth API.
 * @since_tizen 2.3
 *
 * @remarks This function must be called before Bluetooth API starts. \n
 * You must free all resources of the Bluetooth service by calling bt_deinitialize() if Bluetooth service is no longer needed.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see  bt_deinitialize()
 */
int bt_initialize(void);


/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_MODULE
 * @brief Releases all resources of the Bluetooth API.
 * @since_tizen 2.3
 *
 * @remarks This function must be called if Bluetooth API is no longer needed.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre Bluetooth API must be initialized with bt_initialize().
 *
 * @see bt_initialize()
 */
int bt_deinitialize(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Gets the current state of local Bluetooth adapter.
 * @since_tizen 2.3
 *
 * @param[out] adapter_state The current adapter state
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
int bt_adapter_get_state(bt_adapter_state_e *adapter_state);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Gets the address of local Bluetooth adapter.
 * @since_tizen 2.3
 *
 * @remarks The @a local_address must be released with free() by you.
 *
 * @param[out] local_address The device address of local Bluetooth adapter
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
 * @see bt_adapter_get_name()
 */
int bt_adapter_get_address(char **local_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Gets the name of local Bluetooth adapter.
 * @since_tizen 2.3
 *
 * @details Use this function to get the friendly name associated with Bluetooth
 * device, retrieved by the remote Bluetooth devices.
 *
 * @remarks The @a local_name must be released with free() by you.
 *
 * @param[out] local_name  The local device name
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 *
 * @see bt_adapter_set_name()
 */
int bt_adapter_get_name(char **local_name);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Sets the name of local Bluetooth adapter.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @param[in] local_name The name of the Bluetooth device. \n
 *				The maximum length is 248 characters.
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
 * @post bt_adapter_name_changed_cb() will be invoked if this function returns #BT_ERROR_NONE.
 *
 * @see bt_adapter_get_name()
 * @see bt_adapter_name_changed_cb()
 * @see bt_adapter_set_name_changed_cb()
 * @see bt_adapter_unset_name_changed_cb()
 */
int bt_adapter_set_name(const char *local_name);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Gets the visibility mode of local Bluetooth adapter.
 * @since_tizen 2.3
 * @param[out] mode  The visibility mode of the Bluetooth device
 * @param[out] duration  The duration until the visibility mode is changed to #BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE (in seconds).
 * @a duration is valid only if @a mode is #BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE. This value can be NULL.
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 */
int bt_adapter_get_visibility(bt_adapter_visibility_mode_e *mode, int *duration);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Starts the device discovery, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @details If a device is discovered, bt_adapter_device_discovery_state_changed_cb() will be invoked
 * with #BT_ADAPTER_DEVICE_DISCOVERY_FOUND, and then bt_adapter_device_discovery_state_changed_cb()
 * will be called with #BT_ADAPTER_DEVICE_DISCOVERY_FINISHED in case of the completion or cancellation of the discovery.
 *
 * @remarks To connect to peer Bluetooth device, you need to know its Bluetooth address. \n
 * The device discovery can be stopped by bt_adapter_stop_device_discovery().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation is now in progress
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @post This function invokes bt_adapter_device_discovery_state_changed_cb().
 *
 * @see bt_adapter_is_discovering()
 * @see bt_adapter_stop_device_discovery()
 * @see bt_adapter_device_discovery_state_changed_cb()
 * @see bt_adapter_set_device_discovery_state_changed_cb()
 * @see bt_adapter_unset_device_discovery_state_changed_cb()
 */
int bt_adapter_start_device_discovery(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Stops the device discovery, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @remarks The device discovery process will take 10 ~ 20 seconds to get all the devices in vicinity.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOT_IN_PROGRESS  Operation is not in progress
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The device discovery must be in progress with bt_adapter_start_device_discovery().
 * @post This function invokes bt_adapter_device_discovery_state_changed_cb().
 *
 * @see bt_adapter_is_discovering()
 * @see bt_adapter_start_device_discovery()
 * @see bt_adapter_set_device_discovery_state_changed_cb()
 * @see bt_adapter_unset_device_discovery_state_changed_cb()
 * @see bt_adapter_device_discovery_state_changed_cb()
 */
int bt_adapter_stop_device_discovery(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Checks for the device discovery is in progress or not.
 * @since_tizen 2.3
 *
 * @remarks If Bluetooth discovery is in progress, other operations are not allowed and
 * you have to either stop the discovery operation, or wait for it to be finished,
 * before performing other operations.

 * @param[out] is_discovering The discovering status: (@c true = in progress , @c  false = not in progress )
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
 * @see bt_adapter_start_device_discovery()
 * @see bt_adapter_stop_device_discovery()
 */
int bt_adapter_is_discovering(bool *is_discovering);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Get the service mask from the uuid list.
 * @since_tizen 2.3
 *
 * @param[in] uuids The UUID list of the device.
 * @param[in] no_of_service The number of the UUID list count.
 * @param[out] service_mask_list Service mask list converted from the given UUID list.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_service_class_t
 */
int bt_device_get_service_mask_from_uuid_list(char **uuids,
				      int no_of_service,
				      bt_service_class_t *service_mask_list);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Retrieves the device information of all bonded devices.
 * @since_tizen 2.3
 *
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data passed from the foreach function
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @post This function invokes bt_adapter_bonded_device_cb().
 *
 * @see bt_adapter_bonded_device_cb()
 */
int bt_adapter_foreach_bonded_device(bt_adapter_bonded_device_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Gets the device information of a bonded device.
 * @since_tizen 2.3
 * @remarks The @a device_info must be released with bt_adapter_free_device_info() by you .
 *
 * @param [in] remote_address The address of remote device
 * @param [out] device_info The bonded device information
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @post This function invokes bt_adapter_bonded_device_cb().
 *
 * @see bt_adapter_bonded_device_cb()
 */
int bt_adapter_get_bonded_device_info(const char *remote_address, bt_device_info_s **device_info);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Frees device info.
 * @since_tizen 2.3
 *
 * @param [in] device_info The bonded device information
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_adapter_get_bonded_device_info()
 */
int bt_adapter_free_device_info(bt_device_info_s *device_info);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Checks whether the UUID of service is used or not
 * @since_tizen 2.3
 * @param[in] service_uuid The UUID of service
 * @param[out] used Indicates whether the service is used or not
 * @return true on success, otherwise false.
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 */
int bt_adapter_is_service_used(const char *service_uuid, bool *used);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Registers a callback function to be invoked when the Bluetooth adapter state changes.
 * @since_tizen 2.3
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
 * @post bt_adapter_state_changed_cb() will be invoked.
 *
 * @see bt_initialize()
 * @see bt_adapter_state_changed_cb()
 * @see bt_adapter_set_state_changed_cb()
 * @see bt_adapter_unset_state_changed_cb()
 */
int bt_adapter_set_state_changed_cb(bt_adapter_state_changed_cb callback, void *user_data);

/**
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
 * @see bt_adapter_set_state_changed_cb()
 */
int bt_adapter_unset_state_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Registers a callback function to be invoked when the name of Bluetooth adapter changes.
 * @since_tizen 2.3
 *
 * @param[in] callback The callback function to invoke
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post  bt_adapter_name_changed_cb() will be invoked.
 *
 * @see bt_initialize()
 * @see bt_adapter_name_changed_cb()
 * @see bt_adapter_unset_name_changed_cb()
 */
int bt_adapter_set_name_changed_cb(bt_adapter_name_changed_cb callback, void *user_data);

/**
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
 * @see bt_adapter_set_name_changed_cb()
 */
int bt_adapter_unset_name_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Registers a callback function to be invoked when the visibility mode changes.
 * @since_tizen 2.3
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
 * @post bt_adapter_visibility_mode_changed_cb() will be invoked.
 *
 * @see bt_initialize()
 * @see bt_adapter_visibility_mode_changed_cb()
 * @see bt_adapter_unset_visibility_mode_changed_cb()
 */
int bt_adapter_set_visibility_mode_changed_cb(bt_adapter_visibility_mode_changed_cb callback, void *user_data);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Unregisters the callback function.
 * @since_tizen 2.3
 *
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The Bluetooth service must be initialized with bt_initialize().
 *
 * @see  bt_initialize()
 * @see  bt_adapter_set_visibility_mode_changed_cb()
 */
int bt_adapter_unset_visibility_mode_changed_cb(void);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Registers a callback function to be invoked every second
 * @since_tizen 2.3
 * until the visibility mode is changed from #BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE
 * to #BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE.
 * @details  When you set visibility mode as #BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE,
 * @a callback will be called every second until visibility mode is changed to #BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE.
 * @param[in]  callback  The callback function to register
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The Bluetooth service must be initialized by bt_initialize().
 * @post  bt_adapter_visibility_duration_changed_cb() will be invoked.
 * @see  bt_initialize()
 * @see  bt_adapter_visibility_duration_changed_cb()
 * @see  bt_adapter_unset_visibility_duration_changed_cb()
 */
int bt_adapter_set_visibility_duration_changed_cb(bt_adapter_visibility_duration_changed_cb callback, void *user_data);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief	 Unregisters the callback function.
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The Bluetooth service must be initialized with bt_initialize().
 * @see  bt_initialize()
 * @see  bt_adapter_set_visibility_duration_changed_cb()
 */
int bt_adapter_unset_visibility_duration_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief  Registers a callback function to be invoked when the device discovery state changes.
 * @since_tizen 2.3
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
 * @post bt_adapter_device_discovery_state_changed_cb() will be invoked.
 *
 * @see bt_initialize()
 * @see bt_adapter_device_discovery_state_changed_cb()
 * @see bt_adapter_set_device_discovery_state_changed_cb()
 * @see bt_adapter_unset_device_discovery_state_changed_cb()
 */
int bt_adapter_set_device_discovery_state_changed_cb(bt_adapter_device_discovery_state_changed_cb callback, void *user_data);

/**
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
 * @see bt_adapter_set_device_discovery_state_changed_cb()
 */
int bt_adapter_unset_device_discovery_state_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Get the Hash and Randmoizer value, synchronously.
 * @since_tizen 2.3
 *
 * @param[out] hash The hash value recieved from the controller
 * @param[out] randomizer The hash value recieved from the controller
 * @param[out] hash_len The length of the hash value
 * @param[out] randomizer_len The length of the randomizer value
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 */
int bt_adapter_get_local_oob_data(unsigned char **hash, unsigned char **randomizer,
					int *hash_len, int *randomizer_len);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Sets the Hash and Randmoizer value, synchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @param[in] remote_address Remote device address
 * @param[in] hash The hash value recieved from the controller
 * @param[in] randomizer The hash value recieved from the controller
 * @param[in] hash_len The length of the hash value. Allowed value is 16
 * @param[in] randomizer_len The length of the randomizer value. Allowed value is 16
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 */
int bt_adapter_set_remote_oob_data(const char *remote_address,
				unsigned char *hash, unsigned char *randomizer,
				int hash_len, int randomizer_len);
/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_MODULE
 * @brief Deletes the Hash and Randomizer value, synchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @param[in] remote_address Remote device address
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 */
int bt_adapter_remove_remote_oob_data(const char *remote_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Starts the LE device discovery for a BT_ADAPTER_DEVICE_DISCOVERY_LE type.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @details If a LE device is discovered, bt_adapter_le_device_discovery_state_changed_cb()
*  will be invoked with #BT_ADAPTER_LE_DEVICE_DISCOVERY_FOUND, and then bt_adapter_le_device_discovery_state_changed_cb()
 * will be called with #BT_ADAPTER_LE_DEVICE_DISCOVERY_FINISHED in case of the completion or cancellation of the discovery.
 *
 * @remarks To connect to peer Bluetooth device, you need to know its Bluetooth address. \n
 * The device discovery can be stopped by bt_adapter_le_stop_device_discovery().
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation is now in progress
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * or must be #BT_ADAPTER_LE_ENABLED.
 * @post This function invokes bt_adapter_le_device_discovery_state_changed_cb().
 *
 * @see bt_adapter_le_is_discovering()
 * @see bt_adapter_le_device_discovery_state_changed_cb()
 * @see bt_adapter_le_set_device_discovery_state_changed_cb()
 * @see bt_adapter_le_unset_device_discovery_state_changed_cb()
 */
int bt_adapter_le_start_device_discovery(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Stops the LE device discovery, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOT_IN_PROGRESS  Operation is not in progress
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The device discovery must be in progress with bt_adapter_le_start_device_discovery().
 * @post This function invokes bt_adapter_le_device_discovery_state_changed_cb().
 *
 * @see bt_adapter_le_is_discovering()
 * @see bt_adapter_le_start_device_discovery()
 * @see bt_adapter_le_set_device_discovery_state_changed_cb()
 * @see bt_adapter_le_unset_device_discovery_state_changed_cb()
 * @see bt_adapter_le_device_discovery_state_changed_cb()
 */
int bt_adapter_le_stop_device_discovery(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Checks for the LE device discovery is in progress or not.
 * @since_tizen 2.3
 *
 * @remarks If Bluetooth LE discovery is in progress, other operations are not allowed and
 * you have to either stop the LE discovery operation, or wait for it to be finished,
 * before performing other operations.

 * @param[out] is_discovering The discovering status: (@c true = in progress , @c  false = not in progress )
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
 * or must be #BT_ADAPTER_LE_ENABLED.
 *
 * @see bt_adapter_le_start_device_discovery()
 * @see bt_adapter_le_stop_device_discovery()
 */
int bt_adapter_le_is_discovering(bool *is_discovering);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief  Registers a callback function to be invoked when the LE device discovery state changes.
 * @since_tizen 2.3
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
 * @post bt_adapter_le_device_discovery_state_changed_cb() will be invoked.
 *
 * @see bt_initialize()
 * @see bt_adapter_le_device_discovery_state_changed_cb()
 * @see bt_adapter_le_unset_device_discovery_state_changed_cb()
 */
int bt_adapter_le_set_device_discovery_state_changed_cb(bt_adapter_le_device_discovery_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
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
 * @see bt_adapter_le_set_device_discovery_state_changed_cb()
 */
int bt_adapter_le_unset_device_discovery_state_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Create advertiser to advertise device's existence or respond to LE scanning reqeust.
 * @since_tizen 2.3
 *
 * @param[out] advertiser The handle of advertiser
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
 * @see bt_adapter_le_destroy_advertiser()
 */
int bt_adapter_le_create_advertiser(bt_advertiser_h *advertiser);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Destroy advertiser.
 * @since_tizen 2.3
 *
 * @param[out] advertiser The handle of advertiser
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_adapter_le_create_advertiser()
 */
int bt_adapter_le_destroy_advertiser(bt_advertiser_h advertiser);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Set the data to be advertised or responded to scan request from LE scanning device.
 *        The maximum advertised or responded data size is 31 bytes
 *        including data type and system wide data.
 * @since_tizen 2.3
 *
 * @param[in] advertiser The handle of advertiser
 * @param[in] pkt_type The packet type
 * @param[in] data_type The data type that is included in packet
 * @param[in] data The data to be advertised or be responded to scan request from LE scanning device
 * @param[in] data_size The size of data to be set.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_QUOTA_EXCEEDED  Quota exceeded
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_adapter_le_remove_advertising_data()
 * @see bt_adapter_le_clear_advertising_data()
 */
int bt_adapter_le_add_advertising_data(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, bt_adapter_le_packet_data_type_e data_type,
		void *data, unsigned int data_size);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Unset the data to be advertised or responded to scan request from LE scanning device.
 * @since_tizen 2.3
 *
 * @param[in] advertiser The handle of advertiser
 * @param[in] pkt_type The packet type
 * @param[in] data_type The data type to be removed from selected packet
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_adapter_le_add_advertising_data()
 * @see bt_adapter_le_clear_advertising_data()
 */
int bt_adapter_le_remove_advertising_data(bt_advertiser_h advertiser,
		bt_adapter_le_packet_type_e pkt_type, bt_adapter_le_packet_data_type_e data_type);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Clear all data to be advertised or responded to scan request from LE scanning device.
 * @since_tizen 2.3
 *
 * @param[in] advertiser The handle of advertiser
 * @param[in] pkt_type The packet type to be cleared
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 *
 * @see bt_adapter_le_add_advertising_data()
 * @see bt_adapter_le_remove_advertising_data()
 */
int bt_adapter_le_clear_advertising_data(bt_advertiser_h advertiser, bt_adapter_le_packet_type_e pkt_type);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Start advertising with passed advertiser and advertising parameters.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @details Once Bluetooth advertising is started, nearby Bluetooth LE(Low Energy) supported
 * devices can know this device's existence. And one of them can make a connection reqeust,
 * if it is allowed.
 *
 * @param[in] advertiser The handle of advertiser
 * @param[in] adv_params The parameters of advertising \n
 * If NULL is passed, default values which are defined in driver / controller are used.
 * @param[in] cb The callback to report the result of this function
 * @param[in] user_data The user data to be passed when callback is called
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation is now in progress
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post This function invokes bt_adapter_le_advertising_state_changed_cb().
 *
 * @see bt_adapter_le_stop_advertising()
 * @see bt_adapter_le_advertising_state_changed_cb()
 */
int bt_adapter_le_start_advertising(bt_advertiser_h advertiser, bt_adapter_le_advertising_params_s *adv_params,
		bt_adapter_le_advertising_state_changed_cb cb, void *user_data);
/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_ADAPTER_LE_MODULE
 * @brief Stops the advertising.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @param[in] advertiser The handle of advertiser
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOT_IN_PROGRESS  Operation is not in progress
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The advertising must be going on with bt_adapter_le_start_advertising().
 * @post This function invokes bt_adapter_le_advertising_state_changed_cb().
 *
 * @see bt_adapter_le_start_advertising()
 * @see bt_adapter_le_advertising_state_changed_cb()
 */
int bt_adapter_le_stop_advertising(bt_advertiser_h advertiser);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Creates a bond with a remote Bluetooth device, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @remarks A bond can be destroyed by bt_device_destroy_bond().\n
 * The bonding request can be cancelled by bt_device_cancel_bonding().
 *
 * @param[in] remote_address The address of the remote Bluetooth device with which the bond should be created
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_RESOURCE_BUSY  Device or resource busy
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The remote device must be discoverable with bt_adapter_start_device_discovery().
 * @post This function invokes bt_device_bond_created_cb().
 *
 * @see bt_adapter_start_device_discovery()
 * @see bt_device_bond_created_cb()
 * @see bt_device_cancel_bonding()
 * @see bt_device_destroy_bond()
 * @see bt_device_set_bond_created_cb()
 * @see bt_device_unset_bond_created_cb()
 */
int bt_device_create_bond(const char *remote_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Cancels the bonding process.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @remarks Use this function when the remote Bluetooth device is not responding to the
 * bond request or you wish to cancel the bonding request.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOT_IN_PROGRESS  Operation not in progress
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The creating a bond must be in progress by bt_device_create_bond().
 *
 * @see bt_device_create_bond()
 * @see bt_device_bond_created_cb()
 * @see bt_device_set_bond_created_cb()
 * @see bt_device_unset_bond_created_cb()
 */
int bt_device_cancel_bonding(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Destroys the bond, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @param[in] remote_address The address of the remote Bluetooth device to remove bonding
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_RESOURCE_BUSY  Device or resource busy
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The bond with the remote device must be created with bt_device_create_bond().
 * @post This function invokes bt_device_bond_destroyed_cb().
 *
 * @see bt_device_create_bond()
 * @see bt_device_bond_destroyed_cb()
 * @see bt_device_set_bond_destroyed_cb()
 * @see bt_device_unset_bond_destroyed_cb()
 */
int bt_device_destroy_bond(const char *remote_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Sets an alias for the bonded device.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @param[in] remote_address The address of the remote Bluetooth device
 * @param[in] alias The alias of the remote Bluetooth device
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The bond with the remote device must be created with bt_device_create_bond().
 *
 * @see bt_device_create_bond()
 */
int bt_device_set_alias(const char *remote_address, const char *alias);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Sets the authorization of a bonded device, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @remarks Once a device is authorized, you don't need to receive a confirmation.
 *
 * @param[in] remote_address The address of the remote Bluetooth device to authorize
 * @param[in] authorization_state The Bluetooth authorization state
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The bond with the remote device must be created with bt_device_create_bond().
 * @post bt_device_authorization_changed_cb() will be invoked.
 *
 * @see bt_device_create_bond()
 * @see bt_device_authorization_changed_cb()
 * @see bt_device_set_authorization_changed_cb()
 * @see bt_device_unset_authorization_changed_cb()
 */
int bt_device_set_authorization(const char *remote_address, bt_device_authorization_e authorization_state);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Starts the search for services supported by the specified device, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @remarks If creating a bond succeeds, which means bt_device_bond_created_cb() is called with result #BT_ERROR_NONE,
 * then you don't need to run this function.\n
 * The service search takes a couple of seconds to complete normally. \n
 *
 * @param[in] remote_address The address of the remote Bluetooth device whose services need to be checked
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded
 * @retval #BT_ERROR_SERVICE_SEARCH_FAILED  Service search failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The remote device must be discoverable with bt_adapter_start_device_discovery().
 * @pre The bond with the remote device must be created with bt_device_create_bond().
 * @post This function invokes bt_device_service_searched_cb().
 *
 * @see bt_adapter_start_device_discovery()
 * @see bt_device_create_bond()
 * @see bt_device_bond_created_cb()
 * @see bt_device_service_searched_cb()
 * @see bt_device_set_service_searched_cb()
 * @see bt_device_unset_service_searched_cb()
 */
int bt_device_start_service_search(const char *remote_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Gets the connected profiles.
 * @since_tizen 2.3
 * @param[in] remote_address The address of the remote device
 * @param[in] callback The callback function to invoke
 * @param[in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @post bt_device_connected_profile() will be invoked.
 * @see bt_device_connected_profile()
 */
int bt_device_foreach_connected_profiles(const char *remote_address, bt_device_connected_profile callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief Gets the profile connected status.
 * @since_tizen 2.3
 * @param[in] remote_address The address of the remote device
 * @param[in] bt_profile wish to know bt_profile
 * @param[out] connected_status the connected status
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED	Remote device not bonded
 * @retval #BT_ERROR_OPERATION_FAILED	Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 */
int bt_device_is_profile_connected(const char *remote_address, bt_profile_e bt_profile,
					bool *connected_status);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Registers a callback function to be invoked when the bond creates.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post  bt_device_bond_created_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_device_bond_created_cb()
 * @see bt_device_unset_bond_created_cb()
 */
int bt_device_set_bond_created_cb(bt_device_bond_created_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief	Unregisters the callback function.
 * @since_tizen 2.3
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_device_set_bond_created_cb()
 */
int bt_device_unset_bond_created_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Registers a callback function to be invoked when the bond destroys.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post  bt_device_bond_destroyed_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_device_bond_destroyed_cb()
 * @see bt_device_unset_bond_destroyed_cb()
 */
int bt_device_set_bond_destroyed_cb(bt_device_bond_destroyed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief	Unregisters the callback function.
 * @since_tizen 2.3
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_device_set_bond_destroyed_cb()
 */
int bt_device_unset_bond_destroyed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Registers a callback function to be invoked when the authorization of device changes.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post  bt_device_authorization_changed_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_device_authorization_changed_cb()
 * @see bt_device_set_authorization_changed_cb()
 * @see bt_device_unset_authorization_changed_cb()
 */
int bt_device_set_authorization_changed_cb(bt_device_authorization_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief	Unregisters the callback function.
 * @since_tizen 2.3
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_device_set_authorization_changed_cb()
 */
int bt_device_unset_authorization_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Registers a callback function to be invoked when the process of service search finishes.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post  bt_device_service_searched_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_device_service_searched_cb()
 * @see bt_device_unset_service_searched_cb()
 */
int bt_device_set_service_searched_cb(bt_device_service_searched_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief	Unregisters the callback function.
 * @since_tizen 2.3
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_device_set_service_searched_cb()
 */
int bt_device_unset_service_searched_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief  Registers a callback function to be invoked when the connection state is changed.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post bt_device_connection_state_changed_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_device_connection_state_changed_cb()
 * @see bt_device_unset_connection_state_changed_cb()
 */
int bt_device_set_connection_state_changed_cb(bt_device_connection_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_DEVICE_MODULE
 * @brief	Unregisters the callback function to be invoked when the connection state is changed.
 * @since_tizen 2.3
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_device_set_connection_state_changed_cb()
 */
int bt_device_unset_connection_state_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Registers a rfcomm server socket with a specific UUID.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @remarks A socket can be destroyed by bt_socket_destroy_rfcomm().
 *
 * @param[in] service_uuid The UUID of service to provide
 * @param[out] socket_fd The file descriptor of socket to listen
 * @return 0 on success, otherwise a negative error value.
 *
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 *
 * @see bt_socket_listen_and_accept_rfcomm()
 * @see bt_socket_destroy_rfcomm()
 */
int bt_socket_create_rfcomm(const char *service_uuid, int *socket_fd);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Removes the rfcomm server socket which was created using bt_socket_create_rfcomm().
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @remarks If callback function bt_socket_connection_state_changed_cb() is set and the remote Bluetooth device is connected,
 * then bt_socket_connection_state_changed_cb() will be called when this function is finished successfully.
 *
 * @param[in] socket_fd The file descriptor of socket (which was created using bt_socket_create_rfcomm()) to destroy
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The socket must be created with bt_socket_create_rfcomm().
 * @post If callback function bt_socket_connection_state_changed_cb() is set and the remote Bluetooth device is connected,
 * then bt_socket_connection_state_changed_cb() will be called.
 * @see bt_socket_create_rfcomm()
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()
 */
int bt_socket_destroy_rfcomm(int socket_fd);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Starts listening on passed rfcomm socket and accepts connection requests.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @details Pop-up is shown automatically when a RFCOMM connection is requested.
 * bt_socket_connection_state_changed_cb() will be called with
 * #BT_SOCKET_CONNECTED if you click "yes" and connection is finished successfully.
 * @param[in] socket_fd The file descriptor of socket on which start to listen
 * @param[in] max_pending_connections The maximum number of pending connections
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
 * @post If callback function bt_socket_connection_state_changed_cb() is set,
 * then bt_socket_connection_state_changed_cb() will be called when the remote Bluetooth device is connected.
 * @see bt_socket_create_rfcomm()
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()
 */
int bt_socket_listen_and_accept_rfcomm(int socket_fd, int max_pending_connections);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Connects to a specific RFCOMM based service on a remote Bluetooth device UUID, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @remarks A connection can be disconnected by bt_socket_disconnect_rfcomm().
 *
 * @param[in] remote_address The address of the remote Bluetooth device
 * @param[in] service_uuid The UUID of service provided by the remote Bluetooth device
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device not bonded
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @pre The remote device must be discoverable with bt_adapter_start_device_discovery().
 * @pre The bond with the remote device must be created with bt_device_create_bond().
 * @post This function invokes bt_socket_connection_state_changed_cb().
 *
 * @see bt_device_create_bond()
 * @see bt_adapter_start_device_discovery()
 * @see bt_device_start_service_search()
 * @see bt_socket_disconnect_rfcomm()
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()
 */
int bt_socket_connect_rfcomm(const char *remote_address, const char *service_uuid);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Disconnects the RFCOMM connection with the given file descriptor of conneted socket.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] socket_fd  The file descriptor of socket to close which was received using bt_socket_connection_state_changed_cb().
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The connection must be established.
 *
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()
 */
int bt_socket_disconnect_rfcomm(int socket_fd);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief Sends data to the connected device.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @remark The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 *
 * @param[in] socket_fd The file descriptor of connected socket which was received using bt_socket_connection_state_changed_cb()
 * @param[in] data The data to be sent
 * @param[in] length The length of data to be sent
 *
 * @return the number of bytes written (zero indicates nothing was written).
 * @retval On error, -1 is returned, and errno is set appropriately. See write 2 man page.
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 * @exception BT_ERROR_PERMISSION_DENIED  Permission denied
 * @exception BT_ERROR_AGAIN  Resource temporarily unavailable
 *
 * @pre The connection must be established.
 *
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()
 */
int bt_socket_send_data(int socket_fd, const char *data, int length);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief  Register a callback function that will be invoked when you receive data.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post  bt_socket_data_received_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_socket_data_received_cb()
 * @see bt_socket_set_data_received_cb()
 * @see bt_socket_unset_data_received_cb()
 */
int bt_socket_set_data_received_cb(bt_socket_data_received_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief	Unregisters the callback function.
 * @since_tizen 2.3
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_socket_data_received_cb()
 * @see bt_socket_set_data_received_cb()
 */
int bt_socket_unset_data_received_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief  Register a callback function that will be invoked when a RFCOMM connection is requested.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post If you listen a socket by bt_socket_listen(), bt_socket_connection_requested_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_socket_unset_connection_requested_cb()
 */
int bt_socket_set_connection_requested_cb(bt_socket_connection_requested_cb callback, void *user_data);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief  Unregisters the callback function.
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre  The Bluetooth service must be initialized with bt_initialize().
 * @see  bt_initialize()
 * @see  bt_socket_set_connection_requested_cb()
 * @see  bt_socket_connection_requested_cb()
 */
int bt_socket_unset_connection_requested_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief  Register a callback function that will be invoked when the connection state changes.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @post bt_socket_connection_state_changed_cb() will be invoked.
 * @see bt_initialize()
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_unset_connection_state_changed_cb()
 */
int bt_socket_set_connection_state_changed_cb(bt_socket_connection_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_SOCKET_MODULE
 * @brief	Unregisters the callback function.
 * @since_tizen 2.3
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_socket_connection_state_changed_cb()
 * @see bt_socket_set_connection_state_changed_cb()
 */
int bt_socket_unset_connection_state_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_SERVER_MODULE
 * @brief Initializes the Bluetooth OPP server requested by bt_opp_server_connection_requested_cb().
 * @since_tizen 2.3
 * @details No popup appears when an OPP connection is requested from a remote device.
 * Instead, @a connection_requested_cb() will be called.
 * At that time, you can call either bt_opp_server_accept() or bt_opp_server_reject().
 * @remarks This function must be called to start Bluetooth OPP server. \n
 * You must free all resources of the Bluetooth service by calling bt_opp_server_deinitialize() if Bluetooth OPP service is no longer needed.
 * @param[in] destination  The destination path
 * @param[in] connection_requested_cb  The callback called when an OPP connection is requested
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
 * @see  bt_opp_server_connection_requested_cb()
 * @see  bt_opp_server_deinitialize()
 * @see  bt_opp_server_accept()
 * @see  bt_opp_server_reject()
 */
int bt_opp_server_initialize_by_connection_request(const char *destination, bt_opp_server_connection_requested_cb connection_requested_cb, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_SERVER_MODULE
 * @brief Denitializes the Bluetooth OPP server.
 * @since_tizen 2.3
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @see  bt_opp_server_initialize()
 * @see  bt_opp_server_deinitialize()
 */
int bt_opp_server_deinitialize(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_SERVER_MODULE
 * @brief Accepts the push request from the remote device.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @remarks If you initialize OPP server by bt_opp_server_initialize_by_connection_request(), then name is ignored.
 * You can cancel the pushes by bt_opp_server_cancel_transfer() with transfer_id.
 * @param[in] progress_cb  The callback called when a file is being transfered
 * @param[in] finished_cb  The callback called when a transfer is finished
 * @param[in] name  The name to store. This can be NULL if you initialize OPP server by bt_opp_server_initialize_by_connection_request().
 * @param[in] user_data The user data to be passed to the callback function
 * @param[out]  transfer_id  The ID of transfer
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation now in progress
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @see  bt_opp_server_reject()
 */
int bt_opp_server_accept(bt_opp_server_transfer_progress_cb progress_cb, bt_opp_server_transfer_finished_cb finished_cb, const char *name,
 void *user_data, int *transfer_id);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_SERVER_MODULE
 * @brief Rejects the push request from the remote device.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @see  bt_opp_server_accept()
 */
int bt_opp_server_reject(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_SERVER_MODULE
 * @brief Cancels the transfer.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] transfer_id  The ID of transfer
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @see  bt_opp_server_accept()
 */
int bt_opp_server_cancel_transfer(int transfer_id);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_SERVER_MODULE
 * @brief Sets the destination path of file to be pushed.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] destination  The destination path of file to be pushed
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @see  bt_opp_server_initialize()
 */
int bt_opp_server_set_destination(const char *destination);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_CLIENT_MODULE
 * @brief Initializes the Bluetooth OPP client.
 * @since_tizen 2.3
 * @remarks This function must be called before Bluetooth OPP client starts. \n
 * You must free all resources of the Bluetooth service by calling bt_opp_client_deinitialize()
 * if Bluetooth OPP service is no longer needed.
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_RESOURCE_BUSY  Device or resource busy
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @see  bt_opp_client_deinitialize()
 */
int bt_opp_client_initialize(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_CLIENT_MODULE
 * @brief Denitializes the Bluetooth OPP client.
 * @since_tizen 2.3
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @see  bt_opp_client_initialize()
 */
int bt_opp_client_deinitialize(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_CLIENT_MODULE
 * @brief Adds file to be pushed.
 * @since_tizen 2.3
 * @param[in] file  The path of file to be pushed
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @see  bt_opp_client_clear_files()
 * @see  bt_opp_client_push_files()
 */
int bt_opp_client_add_file(const char *file);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_CLIENT_MODULE
 * @brief Adds file to be pushed.
 * @since_tizen 2.3
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @see  bt_opp_client_add_file()
 * @see  bt_opp_client_push_files()
 */
int bt_opp_client_clear_files(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_CLIENT_MODULE
 * @brief Pushes the file to the remote device, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @details At first, bt_opp_client_push_responded_cb() will be called when OPP server responds to the push request.
 * After connection is established, bt_opp_client_push_progress_cb() will be called repeatedly until a file is tranfered completely.
 * If you send several files, then bt_opp_client_push_progress_cb() with another file will be called repeatedly until the file is tranfered completely.
 * bt_opp_client_push_finished_cb() will be called when the push request is finished.
 * @param[in] remote_address The remote address
 * @param[in] responded_cb  The callback called when OPP server responds to the push request
 * @param[in] progress_cb  The callback called when each file is being transfered
 * @param[in] finished_cb  The callback called when the push request is finished
 * @param[in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOW_IN_PROGRESS  Operation now in progress
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @see bt_opp_client_initialize()
 * @see bt_opp_client_cancel_push
 */
int bt_opp_client_push_files(const char *remote_address, bt_opp_client_push_responded_cb responded_cb,
 bt_opp_client_push_progress_cb progress_cb, bt_opp_client_push_finished_cb finished_cb, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_OPP_CLIENT_MODULE
 * @brief Cancels the push request in progress, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre bt_opp_client_push_files() must be called.
 * @post bt_opp_client_push_finished_cb() will be invoked with result #BT_ERROR_CANCELLED,
 * which is a parameter of bt_opp_client_push_files().
 * @see bt_opp_client_initialize()
 * @see bt_opp_client_push_files()
 */
int bt_opp_client_cancel_push(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Initializes the Bluetooth HID(Human Interface Device) Host.
 * @since_tizen 2.3
 * @remarks This function must be called before Bluetooth HID Host starts. \n
 * You must free all resources of the Bluetooth service by calling bt_hid_host_deinitialize()
 * if Bluetooth HID Host service is no longer needed.
 * @param[in] connection_cb  The callback called when the connection state is changed
 * @param[in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see  bt_hid_host_deinitialize()
 */
int bt_hid_host_initialize(bt_hid_host_connection_state_changed_cb connection_cb, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Deinitializes the Bluetooth HID(Human Interface Device) Host.
 * @since_tizen 2.3
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The Bluetooth HID service must be initialized with bt_hid_host_initialize().
 * @see  bt_hid_host_initialize()
 */
int bt_hid_host_deinitialize(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Connects the remote device with the HID(Human Interface Device) service, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] remote_address  The remote address
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device is not bonded
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The local device must be bonded with the remote device by bt_device_create_bond().
 * @pre The Bluetooth HID service must be initialized with bt_hid_host_initialize().
 * @post bt_hid_host_connection_state_changed_cb() will be invoked.
 * @see bt_hid_host_disconnect()
 * @see bt_hid_host_connection_state_changed_cb()
 */
int bt_hid_host_connect(const char *remote_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HID_MODULE
 * @brief Disconnects the remote device with the HID(Human Interface Device) service, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] remote_address  The remote address
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The remote device must be connected by bt_hid_host_connect().
 * @post bt_hid_host_connection_state_changed_cb() will be invoked.
 * @see bt_hid_host_connect()
 * @see bt_hid_host_connection_state_changed_cb()
 */
int bt_hid_host_disconnect(const char *remote_address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_MODULE
 * @brief Initializes the Bluetooth profiles related with audio.
 * @since_tizen 2.3
 * @remarks This function must be called before Bluetooth profiles related with audio starts. \n
 * You must free all resources of the this service by calling bt_audio_deinitialize()
 * if Bluetooth profiles related with audio service is no longer needed.
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_audio_deinitialize()
 */
int bt_audio_initialize(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_MODULE
 * @brief Deinitializes the Bluetooth profiles related with audio.
 * @since_tizen 2.3
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED   Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @see bt_audio_initialize()
 */
int bt_audio_deinitialize(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_MODULE
 * @brief Connects the remote device with the given audio profile, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @details If you input type as #BT_AUDIO_PROFILE_TYPE_ALL and connection request succeeds, then bt_audio_connection_state_changed_cb() will be called twice
 * when #BT_AUDIO_PROFILE_TYPE_HSP_HFP is connected and #BT_AUDIO_PROFILE_TYPE_A2DP is connected.
 * @param[in] remote_address  The remote address
 * @param[in] type  The type of audio profile
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device is not bonded
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported

 * @pre The Bluetooth audio service must be initialized with bt_audio_initialize().
 * @pre The local device must be bonded with the remote device by bt_device_create_bond().
 * @post bt_audio_connection_state_changed_cb() will be invoked.
 * @see bt_audio_disconnect()
 * @see bt_audio_connection_state_changed_cb()
 */
int bt_audio_connect(const char *remote_address, bt_audio_profile_type_e type);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_MODULE
 * @brief Disconnects the remote device with the given audio profile, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @details If you input type as #BT_AUDIO_PROFILE_TYPE_ALL and disconnection request succeeds, then bt_audio_connection_state_changed_cb() will be called twice
 * when #BT_AUDIO_PROFILE_TYPE_HSP_HFP is disconnected and #BT_AUDIO_PROFILE_TYPE_A2DP is disconnected.
 * @param[in] remote_address  The remote address
 * @param[in] type  The type of audio profile
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The remote device must be connected by bt_audio_connect().
 * @post bt_audio_connection_state_changed_cb() will be invoked.
 * @see bt_audio_connect()
 * @see bt_audio_connection_state_changed_cb()
 */
int bt_audio_disconnect(const char *remote_address, bt_audio_profile_type_e type);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_MODULE
 * @brief  Registers a callback function that will be invoked when the connection state is changed.
 * @since_tizen 2.3
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
int bt_audio_set_connection_state_changed_cb(bt_audio_connection_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AUDIO_MODULE
 * @brief  Unregisters a callback function that will be invoked when the connection state is changed.
 * @since_tizen 2.3
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
int bt_audio_unset_connection_state_changed_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief Initializes the Bluetooth AVRCP(Audio/Video Remote Control Profile) service.
 * @since_tizen 2.3
 * @remarks This function must be called before Bluetooth AVRCP service. \n
 * You must free all resources of the this service by calling bt_avrcp_target_deinitialize()
 * if Bluetooth AVRCP service is no longer needed.
 * @param[in] callback The callback function called when the connection state is changed
 * @param[in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_target_deinitialize()
 */
int bt_avrcp_target_initialize(bt_avrcp_target_connection_state_changed_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief Deinitializes the Bluetooth AVRCP(Audio/Video Remote Control Profile) service.
 * @since_tizen 2.3
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_avrcp_target_initialize().
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_deinitialize(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the equalize state to the remote device.
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] state The state of equalizer
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_equalizer_state(bt_avrcp_equalizer_state_e state);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the repeat mode to the remote device.
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] mode The repeat mode
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_repeat_mode(bt_avrcp_repeat_mode_e mode);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the shuffle mode to the remote device.
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] mode The repeat mode
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_shuffle_mode(bt_avrcp_shuffle_mode_e mode);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the scan mode to the remote device.
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] mode The scan mode
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_scan_mode(bt_avrcp_scan_mode_e mode);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the player state to the remote device.
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] state The player state
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_player_state(bt_avrcp_player_state_e state);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the current position of song to the remote device.
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] position The current position in milliseconds
 * @return  0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_position(unsigned int position);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the track to the remote device.
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] title The title of track
 * @param[in] artist The artist of track
 * @param[in] album The album of track
 * @param[in] genre The genre of track
 * @param[in] track_num The track number
 * @param[in] total_tracks The number of all tracks
 * @param[in] duration The duration of track in milliseconds
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_track(const char *title, const char *artist, const char *album, const char *genre, unsigned int track_num, unsigned int total_tracks, unsigned int duration);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Registers a callback function that will be invoked when the equalizer state is changed by the remote control device.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_unset_equalizer_state_changed_cb()
 */
int bt_avrcp_set_equalizer_state_changed_cb(bt_avrcp_equalizer_state_changed_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Unregisters a callback function that will be invoked when the equalizer state is changed by the remote control device.
 * @since_tizen 2.3
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_set_equalizer_state_changed_cb()
 */
int bt_avrcp_unset_equalizer_state_changed_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Registers a callback function that will be invoked when the repeat mode is changed by the remote control device.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_unset_repeat_mode_changed_cb()
 */
int bt_avrcp_set_repeat_mode_changed_cb(bt_avrcp_repeat_mode_changed_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Unregisters a callback function that will be invoked when the repeat mode is changed by the remote control device.
 * @since_tizen 2.3
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_set_repeat_mode_changed_cb()
 */
int bt_avrcp_unset_repeat_mode_changed_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Registers a callback function that will be invoked when the shuffle mode is changed by the remote control device.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_unset_shuffle_mode_changed_cb()
 */
int bt_avrcp_set_shuffle_mode_changed_cb(bt_avrcp_shuffle_mode_changed_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Unregisters a callback function that will be invoked when the shuffle mode is changed by the remote control device.
 * @since_tizen 2.3
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_set_shuffle_mode_changed_cb()
 */
int bt_avrcp_unset_shuffle_mode_changed_cb(void);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Registers a callback function that will be invoked when the scan mode is changed by the remote control device.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_unset_scan_mode_changed_cb()
 */
int bt_avrcp_set_scan_mode_changed_cb(bt_avrcp_scan_mode_changed_cb callback, void *user_data);

/**
 * @internal
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Unregisters a callback function that will be invoked when the scan mode is changed by the remote control device.
 * @since_tizen 2.3
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_set_scan_mode_changed_cb()
 */
int bt_avrcp_unset_scan_mode_changed_cb(void);


/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief Initializes the Bluetooth AVRCP(Audio/Video Remote Control Profile) service.
 * @since_tizen 2.4
 * @remarks This function must be called before Bluetooth AVRCP service. \n
 * You must free all resources of the this service by calling bt_avrcp_target_deinitialize()
 * if Bluetooth AVRCP service is no longer needed.
 * @param[in] callback The callback function called when the connection state is changed
 * @param[in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_target_deinitialize()
 */
int bt_avrcp_target_initialize(bt_avrcp_target_connection_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief Deinitializes the Bluetooth AVRCP(Audio/Video Remote Control Profile) service.
 * @since_tizen 2.4
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth audio service must be initialized with bt_avrcp_target_initialize().
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_deinitialize(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the equalize state to the remote device.
 * @since_tizen 2.4
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] state The state of equalizer
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_equalizer_state(bt_avrcp_equalizer_state_e state);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the repeat mode to the remote device.
 * @since_tizen 2.4
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] mode The repeat mode
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_repeat_mode(bt_avrcp_repeat_mode_e mode);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the shuffle mode to the remote device.
 * @since_tizen 2.4
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] mode The repeat mode
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_shuffle_mode(bt_avrcp_shuffle_mode_e mode);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the scan mode to the remote device.
 * @since_tizen 2.4
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] mode The scan mode
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_scan_mode(bt_avrcp_scan_mode_e mode);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the player state to the remote device.
 * @since_tizen 2.4
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] state The player state
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_player_state(bt_avrcp_player_state_e state);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the current position of song to the remote device.
 * @since_tizen 2.4
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] position The current position in milliseconds
 * @return  0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED  Remote device is not connected
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_position(unsigned int position);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Notifies the track to the remote device.
 * @since_tizen 2.4
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/bluetooth.admin
 * @param[in] title The title of track
 * @param[in] artist The artist of track
 * @param[in] album The album of track
 * @param[in] genre The genre of track
 * @param[in] track_num The track number
 * @param[in] total_tracks The number of all tracks
 * @param[in] duration The duration of track in milliseconds
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
 * @pre The remote device must be connected.
 * @see bt_avrcp_target_connection_state_changed_cb()
 * @see bt_avrcp_target_initialize()
 */
int bt_avrcp_target_notify_track(const char *title, const char *artist, const char *album, const char *genre, unsigned int track_num, unsigned int total_tracks, unsigned int duration);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Registers a callback function that will be invoked when the equalizer state is changed by the remote control device.
 * @since_tizen 2.4
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_unset_equalizer_state_changed_cb()
 */
int bt_avrcp_set_equalizer_state_changed_cb(bt_avrcp_equalizer_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Unregisters a callback function that will be invoked when the equalizer state is changed by the remote control device.
 * @since_tizen 2.4
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_set_equalizer_state_changed_cb()
 */
int bt_avrcp_unset_equalizer_state_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Registers a callback function that will be invoked when the repeat mode is changed by the remote control device.
 * @since_tizen 2.4
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_unset_repeat_mode_changed_cb()
 */
int bt_avrcp_set_repeat_mode_changed_cb(bt_avrcp_repeat_mode_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Unregisters a callback function that will be invoked when the repeat mode is changed by the remote control device.
 * @since_tizen 2.4
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_set_repeat_mode_changed_cb()
 */
int bt_avrcp_unset_repeat_mode_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Registers a callback function that will be invoked when the shuffle mode is changed by the remote control device.
 * @since_tizen 2.4
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_unset_shuffle_mode_changed_cb()
 */
int bt_avrcp_set_shuffle_mode_changed_cb(bt_avrcp_shuffle_mode_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Unregisters a callback function that will be invoked when the shuffle mode is changed by the remote control device.
 * @since_tizen 2.4
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_set_shuffle_mode_changed_cb()
 */
int bt_avrcp_unset_shuffle_mode_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Registers a callback function that will be invoked when the scan mode is changed by the remote control device.
 * @since_tizen 2.4
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_unset_scan_mode_changed_cb()
 */
int bt_avrcp_set_scan_mode_changed_cb(bt_avrcp_scan_mode_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_AVRCP_MODULE
 * @brief  Unregisters a callback function that will be invoked when the scan mode is changed by the remote control device.
 * @since_tizen 2.4
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized by bt_initialize().
 * @see bt_initialize()
 * @see bt_avrcp_set_scan_mode_changed_cb()
 */
int bt_avrcp_unset_scan_mode_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HDP_MODULE
 * @brief Registers an application that acts as the @a Sink role of HDP(Health Device Profile).
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @remarks The @a app_id must be released with free() by you.
 * @param[in] data_type  The data type of MDEP. This value is defined in ISO/IEEE 11073-20601 spec.
 * For example, pulse oximeter is 0x1004 and blood pressure monitor is 0x1007.
 * @param[out] app_id  The ID of application
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @see bt_hdp_unregister_sink_app()
 */
int bt_hdp_register_sink_app(unsigned short data_type, char **app_id);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HDP_MODULE
 * @brief Unregisters the given application that acts as the @a Sink role of HDP(Health Device Profile).
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] app_id  The ID of application
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_hdp_register_sink_app()
 */
int bt_hdp_unregister_sink_app(const char *app_id);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HDP_MODULE
 * @brief Connects the remote device which acts as @a Source role, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] remote_address  The remote address
 * @param[in] app_id  The ID of application
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_REMOTE_DEVICE_NOT_BONDED  Remote device is not bonded
 * @retval #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Sink role of HDP must be registered with bt_hdp_register_sink_app().
 * @pre The local device must be bonded with the remote device by bt_device_create_bond().
 * @post bt_hdp_connected_cb() will be invoked.
 * @see bt_hdp_disconnect()
 * @see bt_hdp_set_connection_state_changed_cb()
 * @see bt_hdp_unset_connection_state_changed_cb()
 */
int bt_hdp_connect_to_source(const char *remote_address, const char *app_id);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HDP_MODULE
 * @brief Disconnects the remote device, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] remote_address  The remote address
 * @param[in] channel  The connected data channel
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
 * @pre The remote device must be connected.
 * @post bt_hdp_disconnected_cb() will be invoked.
 * @see bt_hdp_set_connection_state_changed_cb()
 * @see bt_hdp_unset_connection_state_changed_cb()
 */
int bt_hdp_disconnect(const char *remote_address, unsigned int channel);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HDP_MODULE
 * @brief Sends the data to the remote device.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in] channel  The connected data channel
 * @param[in] data  The data to send
 * @param[in] size  The size of data to send (byte)
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The remote device must be connected.
 * @see bt_hdp_data_received_cb()
 * @see bt_hdp_set_data_received_cb()
 * @see bt_hdp_unset_data_received_cb()
 */
int bt_hdp_send_data(unsigned int channel, const char *data, unsigned int size);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HDP_MODULE
 * @brief  Registers a callback function that will be invoked when the connection state is changed.
 * @since_tizen 2.3
 * @param[in] connected_cb The callback function called when a connection is established
 * @param[in] disconnected_cb The callback function called when a connection is disconnected
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_hdp_unset_connection_state_changed_cb()
 */
int bt_hdp_set_connection_state_changed_cb(bt_hdp_connected_cb connected_cb, bt_hdp_disconnected_cb disconnected_cb, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HDP_MODULE
 * @brief  Unregisters a callback function that will be invoked when the connection state is changed.
 * @since_tizen 2.3
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_hdp_set_connection_state_changed_cb()
 */
int bt_hdp_unset_connection_state_changed_cb(void);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HDP_MODULE
 * @brief  Registers a callback function that will be invoked when you receive the data.
 * @since_tizen 2.3
 * @param[in] callback The callback function to register
 * @param[in] user_data The user data to be passed to the callback function
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_hdp_unset_data_received_cb()
 */
int bt_hdp_set_data_received_cb(bt_hdp_data_received_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_HDP_MODULE
 * @brief  Unregisters a callback function that will be invoked when you receive the data.
 * @since_tizen 2.3
 * @return   0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_hdp_set_data_received_cb()
 */
int bt_hdp_unset_data_received_cb(void);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Gets the primary services of GATT(Generic Attribute Profile).
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in]  remote_address  The address of the remote device
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval  #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retva l #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @post  @a callback will be called if there are primary services.
 * @see  bt_gatt_primary_service_cb()
 */
int bt_gatt_foreach_primary_services(const char *remote_address, bt_gatt_primary_service_cb callback, void *user_data);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Discovers the characteristics in service, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in]  service  The attribute handle of service
 * @param[in]  callback  The result callback
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval  #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @post  @a callback will be called.
 * @see  bt_gatt_characteristics_discovered_cb()
 */
int bt_gatt_discover_characteristics(bt_gatt_attribute_h service, bt_gatt_characteristics_discovered_cb callback, void *user_data);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Gets the UUID of service.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @remarks  @a uuid must be released with free() by you.
 * @param[in]  service  The attribute handle of service
 * @param[out]  uuid  The UUID of service
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval  #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval  #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 */
int bt_gatt_get_service_uuid(bt_gatt_attribute_h service, char **uuid);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Gets the included services in service.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in]  service  The attribute handle of service
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_NOT_ENABLED  Not enabled
 * @retval  #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval  #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @post  @a callback will be called if there are included services.
 * @see  bt_gatt_included_service_cb()
 */
int bt_gatt_foreach_included_services(bt_gatt_attribute_h service, bt_gatt_included_service_cb callback, void *user_data);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Registers a callback function that will be invoked when a characteristic value is changed.
 * @since_tizen 2.3
 * @param[in]  callback  The callback function to register
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The Bluetooth service must be initialized with bt_initialize().
 * @see  bt_gatt_unset_characteristic_changed_cb()
 */
int bt_gatt_set_characteristic_changed_cb(bt_gatt_characteristic_changed_cb callback, void *user_data);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Unregisters a callback function that will be invoked when a characteristic is changed.
 * @since_tizen 2.3
 * @return  0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_gatt_set_characteristic_changed_cb()
 */
int bt_gatt_unset_characteristic_changed_cb(void);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Watches all the characteristic value changes of the service
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in]  service  The attribute handle of service
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The Bluetooth service must be initialized with bt_initialize().
 * @see  bt_gatt_unset_characteristic_changed_cb()
 */
int bt_gatt_watch_characteristic_changes(bt_gatt_attribute_h service);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Remove watching of all the characteristic value changes of the service
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in]  service  The attribute handle of service
 * @return  0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @see bt_gatt_set_characteristic_changed_cb()
 */
int bt_gatt_unwatch_characteristic_changes(bt_gatt_attribute_h service);


/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Gets the characteristic declaration.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @remarks  @a uuid and @a value must be released with free() by you.
 * @param[in]  characteristic  The attribute handle of characteristic
 * @param[out]  uuid  The UUID of service
 * @param[out]  value  The value of characteristic (byte array)
 * @param[out]  value_length  The length of value
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval  #BT_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @see  bt_gatt_set_characteristic_value()
 */
int bt_gatt_get_characteristic_declaration(bt_gatt_attribute_h characteristic, char **uuid, unsigned char **value, int *value_length);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Sets the value of characteristic.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in]  characteristic  The attribute handle of characteristic
 * @param[in]  value  The value of characteristic (byte array)
 * @param[in]  value_length  The length of value
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval  #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @see  bt_gatt_get_characteristic_declaration()
 */
int bt_gatt_set_characteristic_value(bt_gatt_attribute_h characteristic, const unsigned char *value, int value_length);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Sets the value of characteristic request.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in]  characteristic  The attribute handle of characteristic
 * @param[in]  value  The value of characteristic (byte array)
 * @param[in]  value_length  The length of value
  * @param[in]  callback  The result callback
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retva l #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @see  bt_gatt_get_characteristic_declaration()
 */
int bt_gatt_set_characteristic_value_request(bt_gatt_attribute_h characteristic, const unsigned char *value,
				int value_length, bt_gatt_characteristic_write_cb callback);

/**
* @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
* @brief  Clones the attribute handle.
* @since_tizen 2.3
* @remarks  @a clone must be released with bt_gatt_destroy_attribute_handle().
* @param[out]  clone  The cloned attribute handle
* @param[in]  origin  The origin attribute handle
* @return  0 on success, otherwise negative error value.
* @retval  #BT_ERROR_NONE  Successful
* @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
* @retval  #BT_ERROR_OUT_OF_MEMORY  Out of memory
* @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
*
* @see  bt_gatt_destroy_attribute_handle()
*/
int bt_gatt_clone_attribute_handle(bt_gatt_attribute_h* clone, bt_gatt_attribute_h origin);

/**
* @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
* @brief  Destroys the attribute handle.
* @since_tizen 2.3
* @param[in]  handle  The attribute handle
* @return  0 on success, otherwise negative error value.
* @retval  #BT_ERROR_NONE  Successful
* @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
* @retval  #BT_ERROR_NOT_SUPPORTED  Not supported
*
* @see  bt_gatt_clone_attribute_handle()
*/
int bt_gatt_destroy_attribute_handle(bt_gatt_attribute_h handle);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Reads the value of characteristic from remote device
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in]  char_handle  The attribute handle of characteristic
 * @param[in]  callback  The result callback
 * @return	0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE	Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #BT_ERROR_OPERATION_FAILED	Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @see  bt_gatt_get_characteristic_declaration()
 */
int bt_gatt_read_characteristic_value(bt_gatt_attribute_h char_handle,
		bt_gatt_characteristic_read_cb callback);

/**
 * @ingroup  CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief  Discovers the characteristic descriptors of a characteristic within its definition, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 * @param[in]  characteristic_handle  The attribute handle of characteristic
 * @param[in]  callback  The result callback
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #BT_ERROR_NONE  Successful
 * @retval  #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval  #BT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #BT_ERROR_OPERATION_FAILED  Operation failed
 * @retval  #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre  The state of local Bluetooth must be #BT_ADAPTER_ENABLED.
 * @post  @a callback will be called.
 * @see  bt_gatt_characteristic_descriptor_discovered_cb()
 */
int bt_gatt_discover_characteristic_descriptor(bt_gatt_attribute_h characteristic_handle,
		bt_gatt_characteristic_descriptor_discovered_cb callback,
		void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief Connect to a specific LE based service on a remote bluetooth dievice address, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @remarks A connection can be disconnected by bt_gatt_disconnect().
 *
 * @param[in] address The address of the remote Bluetooth device.
 * @param[in] auto_connect The flag of the auto connection.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER Invalid paramater
 * @retval #BT_ERROR_OPERATION_FAILED Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The Bluetooth service must be initialized with bt_initialize().
 * @pre The remote device must support le connection.
 * @post This function invokes bt_gatt_connection_state_changed_cb().
 *
 * @see bt_initialize()
 * @see bt_gatt_disconnect()
 * @see bt_gatt_set_connection_state_changed_cb()
 * @see bt_gatt_unset_connection_state_changed_cb()
 * @see bt_gatt_connection_state_changed_cb()
 */
int bt_gatt_connect(const char *address, bool auto_connect);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief Disconnect to LE connection with the given remote Bluetooth dievice address, asynchronously.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/bluetooth
 *
 * @param[in] address The address of the remote Bluetooth device
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_ENABLED Not enabled
 * @retval #BT_ERROR_INVALID_PARAMETER Invalid paramater
 * @retval #BT_ERROR_OPERATION_FAILED Operation failed
 * @retval #BT_ERROR_PERMISSION_DENIED  Permission denied
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @pre The connection must be established.
 * @post This function invokes bt_gatt_connection_state_changed_cb().
 *
 * @see bt_initialize()
 * @see bt_gatt_connect()
 * @see bt_gatt_set_connection_state_changed_cb()
 * @see bt_gatt_unset_connection_state_changed_cb()
 * @see bt_gatt_connection_state_changed_cb()
 */
int bt_gatt_disconnect(const char *address);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief Registers a callback function that will be invoked when the connection state is changed.
 * @since_tizen 2.3
 *
 * @param[in] callback The callback function to register.
 * @param[in] user_data The user data to be passed  to the callback function.
 *
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_INVALID_PARAMETER Invalid paramater
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_gatt_connect()
 * @see bt_gatt_disconnect()
 * @see bt_gatt_unset_connection_state_changed_cb()
 */
int bt_gatt_set_connection_state_changed_cb(bt_gatt_connection_state_changed_cb callback, void *user_data);

/**
 * @ingroup CAPI_NETWORK_BLUETOOTH_GATT_MODULE
 * @brief Unregisters a callback function that will be invoked when the connection state is changed.
 * @since_tizen 2.3
 *
 * @retval #BT_ERROR_NONE  Successful
 * @retval #BT_ERROR_NOT_INITIALIZED  Not initialized
 * @retval #BT_ERROR_NOT_SUPPORTED  Not supported
 *
 * @see bt_gatt_connect()
 * @see bt_gatt_disconnect()
 * @see bt_gatt_connection_state_changed_cb()
 */
int bt_gatt_unset_connection_state_changed_cb(void);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __TIZEN_NETWORK_BLUETOOTH_H__
