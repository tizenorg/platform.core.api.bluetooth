/*
 * capi-network-bluetooth
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact:  Hocheol Seo <hocheol.seo@samsung.com>
 *		 Girishashok Joshi <girish.joshi@samsung.com>
 *		 Chanyeol Park <chanyeol.park@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/**
 * @file       bt_unit_test.c
 * @brief      This is the source file for capi unit test.
 */

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <dbus/dbus-glib.h>

#include "bluetooth.h"

#define BUFFER_LEN 10
#define PRT(format, args...) printf("%s:%d() "format, __FUNCTION__, __LINE__, ##args)
#define TC_PRT(format, args...) PRT(format"\n", ##args)

const char *spp_uuid = "00001101-0000-1000-8000-00805F9B34FB";
const char *opp_uuid = "00001105-0000-1000-8000-00805f9b34fb";

static int server_fd;
static int client_fd;

GMainLoop *main_loop = NULL;

typedef struct {
	const char *tc_name;
	int tc_code;
} tc_table_t;

tc_table_t tc_table[] = {
	/* Adapter functions */
	{"bt_initialize"			, 1},
	{"bt_deinitialize"			, 2},
	{"bt_adapter_get_state"			, 3},
	{"bt_adapter_enable"			, 4},
	{"bt_adapter_disable"			, 5},
	{"bt_adapter_start_device_discovery"	, 6},
	{"bt_adapter_stop_device_discovery"	, 7},
	{"bt_adapter_is_discovering"		, 8},
	{"bt_adapter_get_bonded_device_info"	, 9},
	{"bt_adapter_is_service_used"		, 10},
	{"bt_adapter_set_device_discovery_state_changed_cb"	, 11},
	{"bt_adapter_unset_device_discovery_state_changed_cb"	, 12},

	/* Socket functions */
	{"bt_socket_create_rfcomm"		, 50},
	{"bt_socket_destroy_rfcomm"		, 51},
	{"bt_socket_listen_and_accept_rfcomm"	, 52},
	{"bt_socket_listen"			, 53},
	{"bt_socket_accept"			, 54},
	{"bt_socket_reject"			, 55},
	{"bt_socket_connect_rfcomm"		, 56},
	{"bt_socket_disconnect_rfcomm" 		, 57},
	{"bt_socket_send_data"			, 58},
	{"bt_socket_set_data_received_cb"	, 59},
	{"bt_socket_unset_data_received_cb"	, 60},
	{"bt_socket_set_connection_requested_cb"	, 61},
	{"bt_socket_unset_connection_requested_cb"	, 62},
	{"bt_socket_set_connection_state_changed_cb"	, 63},
	{"bt_socket_unset_connection_state_changed_cb"	, 64},

	/* OPP functions */
	{"bt_opp_client_initialize"		, 70},
	{"bt_opp_client_deinitialize"		, 71},
	{"bt_opp_client_add_file"		, 72},
	{"bt_opp_client_clear_files"		, 73},
	{"bt_opp_client_push_files"		, 74},
	{"bt_opp_client_cancel_push"		, 75},

	/* -----------------------------------------*/
	{"Finish"				, 0x00ff},
	{NULL					, 0x0000},
};

void tc_usage_print(void)
{
	int i = 0;

	while (tc_table[i].tc_name) {
		if (tc_table[i].tc_code != 0x00ff) {
			TC_PRT("Key %d : usage %s", tc_table[i].tc_code,
						tc_table[i].tc_name);
		} else {
			TC_PRT("Key %d : usage %s\n\n", 0x00ff,
						tc_table[i].tc_name);
		}

		i++;
	}
}

static void __bt_adapter_device_discovery_state_changed_cb(int result,
				bt_adapter_device_discovery_state_e discovery_state,
				bt_adapter_device_discovery_info_s *discovery_info,
				void *user_data)
{
	int i;

	TC_PRT("discovery_state: %d", discovery_state);

	if (discovery_info == NULL) {
		TC_PRT("No discovery_info!");
		return;
	}

	TC_PRT("remote_address: %s", discovery_info->remote_address);
	TC_PRT("remote_name: %s", discovery_info->remote_name);
	TC_PRT("rssi: %d", discovery_info->rssi);
	TC_PRT("is_bonded: %d", discovery_info->is_bonded);
	TC_PRT("service_count: %d", discovery_info->service_count);

	if (discovery_info->service_uuid == NULL) {
		TC_PRT("No uuids");
		return;
	}

	for (i = 0; i < discovery_info->service_count; i++) {
		TC_PRT("uuid: %s", discovery_info->service_uuid[i]);
	}
}

static void __bt_socket_data_received_cb(bt_socket_received_data_s *data, void *user_data)
{
	TC_PRT("+");

	if (data == NULL) {
		TC_PRT("No recieved data!");
		return;
	}

	TC_PRT("Socket fd: %d", data->socket_fd);
	TC_PRT("Data: %s", data->data);
	TC_PRT("Size: %d", data->data_size);
}

static void __bt_socket_connection_requested_cb(int socket_fd, const char *remote_address, void *user_data)
{
	TC_PRT("Socket fd: %d", socket_fd);
	TC_PRT("remote_address: %s", remote_address);
}

static void __bt_socket_connection_state_changed_cb(int result,
				bt_socket_connection_state_e connection_state,
				bt_socket_connection_s *connection,
				void *user_data)
{
	TC_PRT("result: %d", result);
	TC_PRT("connection_state: %d", connection_state);

	if (connection == NULL) {
		TC_PRT("No connection data!");
		return;
	}

	TC_PRT("socket fd: %d", connection->socket_fd);
	TC_PRT("role: %d", connection->local_role);
	TC_PRT("remote address: %s", connection->remote_address);
	TC_PRT("service_uuid: %s", connection->service_uuid);
}

void __bt_opp_client_push_responded_cb(int result,
					const char *remote_address,
					void *user_data)
{
	TC_PRT("result: %d", result);
	TC_PRT("remote_address: %s", remote_address);
}

void __bt_opp_client_push_progress_cb(const char *file,
					long long size,
					int percent,
					void *user_data)
{
	TC_PRT("size: %ld", (long)size);
	TC_PRT("percent: %d", percent);
	TC_PRT("file: %s", file);
}

void __bt_opp_client_push_finished_cb(int result,
				const char *remote_address,
				void *user_data)
{
	TC_PRT("result: %d", result);
	TC_PRT("remote_address: %s", remote_address);
}


int test_input_callback(void *data)
{
	int ret = 0;
	int test_id = (int)data;

	switch (test_id) {
	case 0x00ff:
		TC_PRT("Finished");
		g_main_loop_quit(main_loop);
		break;

	case 1:
		ret = bt_initialize();
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		break;
	case 2:
		ret = bt_deinitialize();
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		break;
	case 3: {
		bt_adapter_state_e state = BT_ADAPTER_DISABLED;

		ret = bt_adapter_get_state(&state);
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);

		TC_PRT("state: %d", state);
		break;
	}
	case 4:
		ret = bt_adapter_enable();
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		break;
	case 5:
		ret = bt_adapter_disable();
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		break;
	case 6:
		ret = bt_adapter_start_device_discovery();
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		break;
	case 7:
		ret = bt_adapter_stop_device_discovery();
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		break;
	case 8: {
		bool is_discovering = FALSE;
		ret = bt_adapter_is_discovering(&is_discovering);
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		else
			TC_PRT("is_discovering: %d", is_discovering);

		break;
	}
	case 9: {
		char *address;
		bt_device_info_s *device_info = NULL;

		address = g_strdup("00:19:0E:01:61:17");

		ret = bt_adapter_get_bonded_device_info((const char *)address,
							&device_info);
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);

		g_free(address);

		if (device_info) {
			TC_PRT("address: %s", device_info->remote_address);
			TC_PRT("name: %s", device_info->remote_name);
		}

		bt_adapter_free_device_info(device_info);
		break;
	}
	case 10: {
		bool used = FALSE;

		ret = bt_adapter_is_service_used(opp_uuid, &used);
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);

		TC_PRT("used: %d", used);
		break;
	}
	case 11:
		ret = bt_adapter_set_device_discovery_state_changed_cb(__bt_adapter_device_discovery_state_changed_cb, NULL);
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		break;
	case 12:
		ret = bt_adapter_unset_device_discovery_state_changed_cb();
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		break;

	/* Socket functions */
	case 50: {
		int socket_fd = 0;

		ret = bt_socket_create_rfcomm(spp_uuid, &socket_fd);
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		} else {
			TC_PRT("socket_fd: %d", socket_fd);
			server_fd = socket_fd;
		}
		break;
	}
	case 51:
		ret = bt_socket_destroy_rfcomm(server_fd);
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		break;
	case 52:
		ret = bt_socket_listen_and_accept_rfcomm(server_fd, 1);
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		break;
	case 53:
		ret = bt_socket_listen(server_fd, 1);
		if (ret < BT_ERROR_NONE)
			TC_PRT("failed with [0x%04x]", ret);
		break;
	case 54: {
		int socket_fd = 0;

		ret = bt_socket_accept(server_fd, &socket_fd);
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		} else {
			TC_PRT("socket_fd: %d", socket_fd);
			client_fd = socket_fd;
		}
		break;
	}
	case 55:
		ret = bt_socket_reject(server_fd);
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 56: {
		char *address;

		address = g_strdup("00:02:48:F4:3E:D2");

		ret = bt_socket_connect_rfcomm(address, spp_uuid);
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}

		g_free(address);
		break;
	}
	case 57:
		ret = bt_socket_disconnect_rfcomm(client_fd);
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 58:
		ret = bt_socket_send_data(client_fd, "Sending test\0", 20);
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 59:
		ret = bt_socket_set_data_received_cb(__bt_socket_data_received_cb, NULL);
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 60:
		ret = bt_socket_unset_data_received_cb();
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 61:
		ret = bt_socket_set_connection_requested_cb(__bt_socket_connection_requested_cb, NULL);
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 62:
		ret = bt_socket_unset_connection_requested_cb();
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 63:
		ret = bt_socket_set_connection_state_changed_cb(__bt_socket_connection_state_changed_cb, NULL);
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 64:
		ret = bt_socket_unset_connection_state_changed_cb();
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 70:
		ret = bt_opp_client_initialize();
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 71:
		ret = bt_opp_client_deinitialize();
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 72:
		ret = bt_opp_client_add_file("/opt/media/Images/image1.jpg");
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 73:
		ret = bt_opp_client_clear_files();
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	case 74: {
		char *address;

		address = g_strdup("00:02:37:A9:17:9E");

		ret = bt_opp_client_push_files(address,__bt_opp_client_push_responded_cb,
					__bt_opp_client_push_progress_cb,
					__bt_opp_client_push_finished_cb,
					NULL);
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;
	}
	case 75:
		ret = bt_opp_client_cancel_push();
		if (ret < BT_ERROR_NONE) {
			TC_PRT("failed with [0x%04x]", ret);
		}
		break;

	default:
		break;
	}

	return 0;
}

static gboolean key_event_cb(GIOChannel *chan,
				GIOCondition cond,
				gpointer data)
{
	char buf[BUFFER_LEN] = { 0 };

	unsigned int len = 0;
	int test_id;

	memset(buf, 0, sizeof(buf));

	if(g_io_channel_read_chars(chan, buf, sizeof(buf),
				&len, NULL) == G_IO_STATUS_ERROR) {
		TC_PRT("IO Channel read error");
		return FALSE;
	}

	TC_PRT("%s", buf);
	tc_usage_print();

	test_id = atoi(buf);

	if(test_id)
		g_idle_add(test_input_callback, (void *)test_id);

	return TRUE;
}

int main()
{
	GIOChannel *key_io;

	g_type_init();

	key_io = g_io_channel_unix_new(fileno(stdin));

	g_io_channel_set_encoding(key_io, NULL, NULL);
	g_io_channel_set_flags(key_io, G_IO_FLAG_NONBLOCK, NULL);

	g_io_add_watch(key_io, G_IO_IN | G_IO_HUP | G_IO_ERR | G_IO_NVAL,
			key_event_cb, NULL);

	g_io_channel_unref(key_io);

	main_loop = g_main_loop_new(NULL, FALSE);

	g_main_loop_run(main_loop);

	bt_deinitialize();

	return 0;
}

