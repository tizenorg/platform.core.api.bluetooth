#ifndef __BLUETOOTH_NTB_UUID_H
#define __BLUETOOTH_NTB_UUID_H

#define SPP_PROFILE_UUID_HEAD		"00001101"
#define LAP_PROFILE_UUID_HEAD		"00001102"
#define OBEX_SYNC_SERVICE_UUID_HEAD		"00001104"
#define OBEX_PUSH_SERVICE_UUID_HEAD		"00001105"
#define OBEX_FILE_TRANSFER_UUID_HEAD		"00001106"

#define DUN_PROFILE_UUID_HEAD		"00001103"
#define HS_PROFILE_UUID_HEAD		"00001131"
#define CTP_PROFILE_UUID_HEAD		"00001109"
#define AUDIO_SOURCE_UUID_HEAD		"0000110a"
#define AUDIO_SINK_UUID_HEAD		"0000110b"
#define VIDEO_SOURCE_UUID_HEAD		"00001303"
#define VIDEO_SINK_UUID_HEAD		"00001304"
#define AV_REMOTE_CONTROL_TARGET_UUID_HEAD		"0000110c"
#define ADVANCED_AUDIO_PROFILE_UUID_HEAD		"0000110d"
#define AV_REMOTE_CONTROL_UUID_HEAD		"0000110e"
#define ICP_PROFILE_UUID_HEAD		"00001110"
#define FAX_PROFILE_UUID_HEAD		"00001111"
#define HEADSET_AG_SERVICE_UUID_HEAD		"00001112"
#define PAN_PANU_PROFILE_UUID_HEAD		"00001115"
#define PAN_NAP_PROFILE_UUID_HEAD		"00001116"
#define PAN_GN_PROFILE_UUID_HEAD		"00001117"
#define REFERENCE_PRINTING_HEAD		"00001119"
#define OBEX_IMAGING_UUID_HEAD		"0000111a"
#define OBEX_IMAGING_RESPONDER_UUID_HEAD		"0000111b"
#define HF_PROFILE_UUID_HEAD		"0000111e"
#define HFG_PROFILE_UUID_HEAD	"0000111f"
#define DIRECT_PRINTING_REFERENCE_OBJ_UUID_HEAD		"00001120"
#define BASIC_PRINTING_HEAD		"00001122"
#define HID_PROFILE_UUID_HEAD		"00001124"
#define SIM_ACCESS_PROFILE_UUID_HEAD		"0000112d"
#define OBEX_PBAP_PROFILE_UUID_HEAD		"00001130"
#define OBEX_BPPS_PROFILE_UUID_HEAD		"00001120"
#define PNP_INFORMATION_UUID_HEAD		"00001200"
#define OBEX_PRINTING_STATUS_UUID_HEAD		"00001123"
#define HCR_PROFILE_UUID_HEAD		"00001125"
#define OBEX_SYNCML_TRANSFER_UUID_HEAD	""

#define BLUETOOTH_PROTOCOL_BASE 0x0000
#define BLUETOOTH_SDP_UUID (BLUETOOTH_PROTOCOL_BASE+0x0001)
#define BLUETOOTH_RFCOMM_UUID (BLUETOOTH_PROTOCOL_BASE+0x0003)
#define BLUETOOTH_TCS_UUID (BLUETOOTH_PROTOCOL_BASE+0x0005)
#define BLUETOOTH_ATT_UUID (BLUETOOTH_PROTOCOL_BASE+0x0006)
#define BLUETOOTH_OBEX_UUID (BLUETOOTH_PROTOCOL_BASE+0x0007)
#define BLUETOOTH_BNEP_UUID (BLUETOOTH_PROTOCOL_BASE+0x000f)
#define BLUETOOTH_UPNP_UUID (BLUETOOTH_PROTOCOL_BASE+0x0010)
#define BLUETOOTH_HIDP_UUID (BLUETOOTH_PROTOCOL_BASE+0x0011)
#define BLUETOOTH_HCCC_UUID (BLUETOOTH_PROTOCOL_BASE+0x0012)
#define BLUETOOTH_HCDC_UUID (BLUETOOTH_PROTOCOL_BASE+0x0014)
#define BLUETOOTH_HCN_UUID (BLUETOOTH_PROTOCOL_BASE+0x0016)
#define BLUETOOTH_AVCTP_UUID (BLUETOOTH_PROTOCOL_BASE+0x0017)
#define BLUETOOTH_AVDTP_UUID (BLUETOOTH_PROTOCOL_BASE+0x0019)
#define BLUETOOTH_CMTP_UUID (BLUETOOTH_PROTOCOL_BASE+0x001b)
#define BLUETOOTH_MCAPC_UUID (BLUETOOTH_PROTOCOL_BASE+0x001e)
#define BLUETOOTH_MCAPD_UUID (BLUETOOTH_PROTOCOL_BASE+0x001f)
#define BLUETOOTH_L2CAP_UUID (BLUETOOTH_PROTOCOL_BASE+0x0100)

#define BLUETOOTH_PROFILE_BASE 0x1000
#define BLUETOOTH_GROUP_ID 0x0100
#define BLUETOOTH_GROUP_BASE (BLUETOOTH_PROFILE_BASE \
				+BLUETOOTH_GROUP_ID)
#define BLUETOOTH_SDSSC_UUID BLUETOOTH_GROUP_BASE
#define BLUETOOTH_BGDSC_UUID (BLUETOOTH_PROFILE_BASE+0x0001)
#define BLUETOOTH_PBR_UUID (BLUETOOTH_PROFILE_BASE+0x0002)
#define BLUETOOTH_SP_UUID (BLUETOOTH_GROUP_BASE+0x0001)
#define BLUETOOTH_LAUP_UUID (BLUETOOTH_GROUP_BASE+0x0002)
#define BLUETOOTH_DN_UUID (BLUETOOTH_GROUP_BASE+0x0003)
#define BLUETOOTH_IrMCS_UUID (BLUETOOTH_GROUP_BASE+0x0004)
#define BLUETOOTH_OPP_UUID (BLUETOOTH_GROUP_BASE+0x0005)
#define BLUETOOTH_FTP_UUID (BLUETOOTH_GROUP_BASE+0x0006)
#define BLUETOOTH_IRMCSC_UUID (BLUETOOTH_GROUP_BASE+0x0007)
#define BLUETOOTH_HSP_UUID (BLUETOOTH_GROUP_BASE+0x0008)
#define BLUETOOTH_CT_UUID (BLUETOOTH_GROUP_BASE+0x0009)
#define BLUETOOTH_ASOURCE_UUID (BLUETOOTH_GROUP_BASE+0x000a)
#define BLUETOOTH_ASINK_UUID (BLUETOOTH_GROUP_BASE+0x000b)
#define BLUETOOTH_AVRCT_UUID (BLUETOOTH_GROUP_BASE+0x000c)
#define BLUETOOTH_AAD_UUID (BLUETOOTH_GROUP_BASE+0x000d)
#define BLUETOOTH_AVRC_UUID (BLUETOOTH_GROUP_BASE+0x000e)
#define BLUETOOTH_AVRCC_UUID (BLUETOOTH_GROUP_BASE+0x000f)
#define BLUETOOTH_INTERCOM_UUID (BLUETOOTH_GROUP_BASE+0x0010)
#define BLUETOOTH_FAX_UUID (BLUETOOTH_GROUP_BASE+0x0011)
#define BLUETOOTH_HSPG_UUID (BLUETOOTH_GROUP_BASE+0x0012)
#define BLUETOOTH_WAP_UUID (BLUETOOTH_GROUP_BASE+0x0013)
#define BLUETOOTH_WAPC_UUID (BLUETOOTH_GROUP_BASE+0x0014)
#define BLUETOOTH_PANU_UUID (BLUETOOTH_GROUP_BASE+0x0015)
#define BLUETOOTH_NAP_UUID (BLUETOOTH_GROUP_BASE+0x0016)
#define BLUETOOTH_GN_UUID (BLUETOOTH_GROUP_BASE+0x0017)
#define BLUETOOTH_DP_UUID (BLUETOOTH_GROUP_BASE+0x0018)
#define BLUETOOTH_RP_UUID (BLUETOOTH_GROUP_BASE+0x0019)
#define BLUETOOTH_BIP_UUID (BLUETOOTH_GROUP_BASE+0x001a)
#define BLUETOOTH_IR_UUID (BLUETOOTH_GROUP_BASE+0x001b)
#define BLUETOOTH_IAA_UUID (BLUETOOTH_GROUP_BASE+0x001c)
#define BLUETOOTH_IRO_UUID (BLUETOOTH_GROUP_BASE+0x001d)
#define BLUETOOTH_HFP_UUID (BLUETOOTH_GROUP_BASE+0x001e)
#define BLUETOOTH_HFPG_UUID (BLUETOOTH_GROUP_BASE+0x001f)
#define BLUETOOTH_DPROS_UUID (BLUETOOTH_GROUP_BASE+0x0020)
#define BLUETOOTH_RU_UUID (BLUETOOTH_GROUP_BASE+0x0021)
#define BLUETOOTH_BP_UUID (BLUETOOTH_GROUP_BASE+0x0022)
#define BLUETOOTH_PS_UUID (BLUETOOTH_GROUP_BASE+0x0023)
#define BLUETOOTH_HIDS_UUID (BLUETOOTH_GROUP_BASE+0x0024)
#define BLUETOOTH_HCR_UUID (BLUETOOTH_GROUP_BASE+0x0025)
#define BLUETOOTH_HCRP_UUID (BLUETOOTH_GROUP_BASE+0x0026)
#define BLUETOOTH_HCRS_UUID (BLUETOOTH_GROUP_BASE+0x0027)
#define BLUETOOTH_CIA_UUID (BLUETOOTH_GROUP_BASE+0x0028)
#define BLUETOOTH_SAP_UUID (BLUETOOTH_GROUP_BASE+0x002d)
#define BLUETOOTH_PBAPC_UUID (BLUETOOTH_GROUP_BASE+0x002e)
#define BLUETOOTH_PBAPS_UUID (BLUETOOTH_GROUP_BASE+0x002f)
#define BLUETOOTH_PBAP_UUID (BLUETOOTH_GROUP_BASE+0x0030)
#define BLUETOOTH_HSPHS_UUID (BLUETOOTH_GROUP_BASE+0x0031)
#define BLUETOOTH_MAPS_UUID (BLUETOOTH_GROUP_BASE+0x0032)
#define BLUETOOTH_MNS_UUID (BLUETOOTH_GROUP_BASE+0x0033)
#define BLUETOOTH_MAP_UUID (BLUETOOTH_GROUP_BASE+0x0034)
#define BLUETOOTH_GNSS_UUID (BLUETOOTH_GROUP_BASE+0x0035)
#define BLUETOOTH_GNSSS_UUID (BLUETOOTH_GROUP_BASE+0x0036)

#define BLUETOOTH_GROUP_ID_1 0x0200
#define BLUETOOTH_GROUP_BASE_1 (BLUETOOTH_PROFILE_BASE \
				+BLUETOOTH_GROUP_ID_1)
#define BLUETOOTH_PNPI_UUID BLUETOOTH_GROUP_BASE_1
#define BLUETOOTH_GENERICN_UUID (BLUETOOTH_GROUP_BASE_1+0x0001)
#define BLUETOOTH_GENERIFT_UUID (BLUETOOTH_GROUP_BASE_1+0x0002)
#define BLUETOOTH_GENERIAD_UUID (BLUETOOTH_GROUP_BASE_1+0x0003)
#define BLUETOOTH_GENERITP_UUID (BLUETOOTH_GROUP_BASE_1+0x0004)
#define BLUETOOTH_UPNPS_UUID (BLUETOOTH_GROUP_BASE_1+0x0005)
#define BLUETOOTH_UPNPIPS_UUID (BLUETOOTH_GROUP_BASE_1+0x0006)

#define BLUETOOTH_GROUP_ID_2 0x0300
#define BLUETOOTH_GROUP_BASE_2 (BLUETOOTH_PROFILE_BASE \
				+BLUETOOTH_GROUP_ID_2)
#define BLUETOOTH_UPNPIPPAN_UUID BLUETOOTH_GROUP_BASE_2
#define BLUETOOTH_UPNPIPLAP_UUID (BLUETOOTH_GROUP_BASE_2+0x0001)
#define BLUETOOTH_UPNPIPL2CAP_UUID (BLUETOOTH_GROUP_BASE_2+0x0002)
#define BLUETOOTH_VSOURCE_UUID (BLUETOOTH_GROUP_BASE_2+0x0003)
#define BLUETOOTH_VSINK_UUID (BLUETOOTH_GROUP_BASE_2+0x0004)
#define BLUETOOTH_VDIST_UUID (BLUETOOTH_GROUP_BASE_2+0x0005)

#define BLUETOOTH_GROUP_ID_3 0x0400
#define BLUETOOTH_GROUP_BASE_3 (BLUETOOTH_PROFILE_BASE \
				+BLUETOOTH_GROUP_ID_3)
#define BLUETOOTH_HDP_UUID BLUETOOTH_GROUP_BASE_3
#define BLUETOOTH_HDPSOURCE_UUID (BLUETOOTH_GROUP_BASE_3+0x0001)
#define BLUETOOTH_HDPSINK_UUID (BLUETOOTH_GROUP_BASE_3+0x0002)

#define BLUETOOTH_GROUP_ID_4 0x0800
#define BLUETOOTH_GROUP_BASE_4 (BLUETOOTH_PROFILE_BASE \
				+BLUETOOTH_GROUP_ID_4)
#define BLUETOOTH_GAP_UUID BLUETOOTH_GROUP_BASE_4
#define BLUETOOTH_GATTP_UUID (BLUETOOTH_GROUP_BASE_4+0x0001)
#define BLUETOOTH_IAP_UUID (BLUETOOTH_GROUP_BASE_4+0x0002)
#define BLUETOOTH_LLOSTP_UUID (BLUETOOTH_GROUP_BASE_4+0x0003)
#define BLUETOOTH_TXP_UUID (BLUETOOTH_GROUP_BASE_4+0x0004)
#define BLUETOOTH_CTSP_UUID (BLUETOOTH_GROUP_BASE_4+0x0005)
#define BLUETOOTH_RTUS_UUID (BLUETOOTH_GROUP_BASE_4+0x0006)
#define BLUETOOTH_NDCS_UUID (BLUETOOTH_GROUP_BASE_4+0x0007)
#define BLUETOOTH_GLUCOSE_UUID (BLUETOOTH_GROUP_BASE_4+0x0008)
#define BLUETOOTH_HEALTHT_UUID (BLUETOOTH_GROUP_BASE_4+0x0009)
#define BLUETOOTH_DEVICEI_UUID (BLUETOOTH_GROUP_BASE_4+0x000a)
#define BLUETOOTH_HEARTR_UUID (BLUETOOTH_GROUP_BASE_4+0x000d)
#define BLUETOOTH_PASS_UUID (BLUETOOTH_GROUP_BASE_4+0x000e)
#define BLUETOOTH_BSP_UUID (BLUETOOTH_GROUP_BASE_4+0x000f)
#define BLUETOOTH_BLOODPP_UUID (BLUETOOTH_GROUP_BASE_4+0x0010)
#define BLUETOOTH_ANS_UUID (BLUETOOTH_GROUP_BASE_4+0x0011)
#define BLUETOOTH_HID_UUID (BLUETOOTH_GROUP_BASE_4+0x0012)
#define BLUETOOTH_SCANP_UUID (BLUETOOTH_GROUP_BASE_4+0x0013)
#define BLUETOOTH_RSAC_UUID (BLUETOOTH_GROUP_BASE_4+0x0014)
#define BLUETOOTH_CSAC_UUID (BLUETOOTH_GROUP_BASE_4+0x0016)

#define BLUETOOTH_PROFILE_BASE_0 0x2000
#define BLUETOOTH_GROUP_BASE_5 (BLUETOOTH_PROFILE_BASE_0 \
				+BLUETOOTH_GROUP_ID_4)
#define BLUETOOTH_PRIMARYS_UUID BLUETOOTH_GROUP_BASE_5
#define BLUETOOTH_SECONDS_UUID (BLUETOOTH_GROUP_BASE_5+0x0001)
#define BLUETOOTH_INCLUDE_UUID (BLUETOOTH_GROUP_BASE_5+0x0002)
#define BLUETOOTH_CHARACTER_UUID (BLUETOOTH_GROUP_BASE_5+0x0003)

#define BLUETOOTH_GROUP_ID_5 0x0900
#define BLUETOOTH_GROUP_BASE_6 (BLUETOOTH_PROFILE_BASE_0 \
				+BLUETOOTH_GROUP_ID_5)
#define BLUETOOTH_CHARACTEREP_UUID BLUETOOTH_GROUP_BASE_6
#define BLUETOOTH_CHARACTEREPUD_UUID (BLUETOOTH_GROUP_BASE_6+0x0001)
#define BLUETOOTH_CCHARACTEREPC_UUID (BLUETOOTH_GROUP_BASE_6+0x0002)
#define BLUETOOTH_SCHARACTEREPC_UUID (BLUETOOTH_GROUP_BASE_6+0x0003)
#define BLUETOOTH_CHARACTEREPF_UUID (BLUETOOTH_GROUP_BASE_6+0x0004)
#define BLUETOOTH_CHARACTEREPAF_UUID (BLUETOOTH_GROUP_BASE_6+0x0005)
#define BLUETOOTH_VALIDRANGE_UUID (BLUETOOTH_GROUP_BASE_6+0x0006)
#define BLUETOOTH_EXTERNALRR_UUID (BLUETOOTH_GROUP_BASE_6+0x0007)
#define BLUETOOTH_REPORTR_UUID (BLUETOOTH_GROUP_BASE_6+0x0008)

#define BLUETOOTH_GROUP_ID_6 0x0a00
#define BLUETOOTH_GROUP_BASE_7 (BLUETOOTH_PROFILE_BASE_0 \
				+BLUETOOTH_GROUP_ID_6)
#define BLUETOOTH_DEVICENAME_UUID BLUETOOTH_GROUP_BASE_7
#define BLUETOOTH_APPEARANCE_UUID (BLUETOOTH_GROUP_BASE_7+0x0001)
#define BLUETOOTH_PPF_UUID (BLUETOOTH_GROUP_BASE_7+0x0002)
#define BLUETOOTH_RECONNADDR_UUID (BLUETOOTH_GROUP_BASE_7+0x0003)
#define BLUETOOTH_PPCP_UUID (BLUETOOTH_GROUP_BASE_7+0x0004)
#define BLUETOOTH_SERVICEC_UUID (BLUETOOTH_GROUP_BASE_7+0x0005)
#define BLUETOOTH_ALEVEL_UUID (BLUETOOTH_GROUP_BASE_7+0x0006)
#define BLUETOOTH_TXPLEVEL_UUID (BLUETOOTH_GROUP_BASE_7+0x0007)
#define BLUETOOTH_DATATIME_UUID (BLUETOOTH_GROUP_BASE_7+0x0008)
#define BLUETOOTH_DOW_UUID (BLUETOOTH_GROUP_BASE_7+0x0009)
#define BLUETOOTH_DDT_UUID (BLUETOOTH_GROUP_BASE_7+0x000a)
#define BLUETOOTH_EXACTT256_UUID (BLUETOOTH_GROUP_BASE_7+0x000c)
#define BLUETOOTH_DSTOFF_UUID (BLUETOOTH_GROUP_BASE_7+0x000d)
#define BLUETOOTH_TIMEZ_UUID (BLUETOOTH_GROUP_BASE_7+0x000e)
#define BLUETOOTH_LOCALTI_UUID (BLUETOOTH_GROUP_BASE_7+0x000f)
#define BLUETOOTH_TIMEWDST_UUID (BLUETOOTH_GROUP_BASE_7+0x0011)
#define BLUETOOTH_TIMEACCURACY_UUID (BLUETOOTH_GROUP_BASE_7+0x0012)
#define BLUETOOTH_TIMESOURCE_UUID (BLUETOOTH_GROUP_BASE_7+0x0013)
#define BLUETOOTH_REFERENCETI_UUID (BLUETOOTH_GROUP_BASE_7+0x0014)
#define BLUETOOTH_TIMEUCP_UUID (BLUETOOTH_GROUP_BASE_7+0x0016)
#define BLUETOOTH_TIMEUS_UUID (BLUETOOTH_GROUP_BASE_7+0x0017)
#define BLUETOOTH_GLUCOSEM_UUID (BLUETOOTH_GROUP_BASE_7+0x0018)
#define BLUETOOTH_BATTERYL_UUID (BLUETOOTH_GROUP_BASE_7+0x0019)
#define BLUETOOTH_TEMPERATUREM_UUID (BLUETOOTH_GROUP_BASE_7+0x001c)
#define BLUETOOTH_TEMPERATURET_UUID (BLUETOOTH_GROUP_BASE_7+0x001d)
#define BLUETOOTH_INTERMEDIATET_UUID (BLUETOOTH_GROUP_BASE_7+0x001e)
#define BLUETOOTH_MEASUREMENTI_UUID (BLUETOOTH_GROUP_BASE_7+0x0021)
#define BLUETOOTH_BKIR_UUID (BLUETOOTH_GROUP_BASE_7+0x0022)
#define BLUETOOTH_SYSTEMID_UUID (BLUETOOTH_GROUP_BASE_7+0x0023)
#define BLUETOOTH_MODELNS_UUID (BLUETOOTH_GROUP_BASE_7+0x0024)
#define BLUETOOTH_SNS_UUID (BLUETOOTH_GROUP_BASE_7+0x0025)
#define BLUETOOTH_FIRMRS_UUID (BLUETOOTH_GROUP_BASE_7+0x0026)
#define BLUETOOTH_HARDRS_UUID (BLUETOOTH_GROUP_BASE_7+0x0027)
#define BLUETOOTH_SOFTRS_UUID (BLUETOOTH_GROUP_BASE_7+0x0028)
#define BLUETOOTH_MANUNS_UUID (BLUETOOTH_GROUP_BASE_7+0x0029)
#define BLUETOOTH_IEEE11073_UUID (BLUETOOTH_GROUP_BASE_7+0x002a)
#define BLUETOOTH_CURRENTT_UUID (BLUETOOTH_GROUP_BASE_7+0x002b)
#define BLUETOOTH_SCANR_UUID (BLUETOOTH_GROUP_BASE_7+0x0031)
#define BLUETOOTH_BKOR_UUID (BLUETOOTH_GROUP_BASE_7+0x0032)
#define BLUETOOTH_BMIR_UUID (BLUETOOTH_GROUP_BASE_7+0x0033)
#define BLUETOOTH_GMC_UUID (BLUETOOTH_GROUP_BASE_7+0x0034)
#define BLUETOOTH_BLOODPM_UUID (BLUETOOTH_GROUP_BASE_7+0x0035)
#define BLUETOOTH_INTERMEDIATECP_UUID (BLUETOOTH_GROUP_BASE_7+0x0036)
#define BLUETOOTH_HEARTRM_UUID (BLUETOOTH_GROUP_BASE_7+0x0037)
#define BLUETOOTH_BODYSL_UUID (BLUETOOTH_GROUP_BASE_7+0x0038)
#define BLUETOOTH_HEARTRCP_UUID (BLUETOOTH_GROUP_BASE_7+0x0039)
#define BLUETOOTH_ALERTS_UUID (BLUETOOTH_GROUP_BASE_7+0x003f)
#define BLUETOOTH_RINGERCP_UUID (BLUETOOTH_GROUP_BASE_7+0x0040)
#define BLUETOOTH_RINGERS_UUID (BLUETOOTH_GROUP_BASE_7+0x0041)
#define BLUETOOTH_ALERTCIBM_UUID (BLUETOOTH_GROUP_BASE_7+0x0042)
#define BLUETOOTH_ALERTCI_UUID (BLUETOOTH_GROUP_BASE_7+0x0043)
#define BLUETOOTH_ALERTNCP_UUID (BLUETOOTH_GROUP_BASE_7+0x0044)
#define BLUETOOTH_UNREADAS_UUID (BLUETOOTH_GROUP_BASE_7+0x0045)
#define BLUETOOTH_NEWALERT_UUID (BLUETOOTH_GROUP_BASE_7+0x0046)
#define BLUETOOTH_SNAC_UUID (BLUETOOTH_GROUP_BASE_7+0x0047)
#define BLUETOOTH_SUAC_UUID (BLUETOOTH_GROUP_BASE_7+0x0048)
#define BLUETOOTH_BLOODPF_UUID (BLUETOOTH_GROUP_BASE_7+0x0049)
#define BLUETOOTH_HIDINFO_UUID (BLUETOOTH_GROUP_BASE_7+0x004a)
#define BLUETOOTH_REPORTMAP_UUID (BLUETOOTH_GROUP_BASE_7+0x004b)
#define BLUETOOTH_HIDCP_UUID (BLUETOOTH_GROUP_BASE_7+0x004c)
#define BLUETOOTH_REPORT_UUID (BLUETOOTH_GROUP_BASE_7+0x004d)
#define BLUETOOTH_PROTOCALM_UUID (BLUETOOTH_GROUP_BASE_7+0x004e)
#define BLUETOOTH_SCANIW_UUID (BLUETOOTH_GROUP_BASE_7+0x004f)
#define BLUETOOTH_PNPID_UUID (BLUETOOTH_GROUP_BASE_7+0x0050)
#define BLUETOOTH_GLUCOSEF_UUID (BLUETOOTH_GROUP_BASE_7+0x0051)
#define BLUETOOTH_RECORDACP_UUID (BLUETOOTH_GROUP_BASE_7+0x0052)
#define BLUETOOTH_RSCM_UUID (BLUETOOTH_GROUP_BASE_7+0x0053)
#define BLUETOOTH_RSMF_UUID (BLUETOOTH_GROUP_BASE_7+0x0054)
#define BLUETOOTH_SCCP_UUID (BLUETOOTH_GROUP_BASE_7+0x0055)
#define BLUETOOTH_CSCM_UUID (BLUETOOTH_GROUP_BASE_7+0x005b)
#define BLUETOOTH_CSCF_UUID (BLUETOOTH_GROUP_BASE_7+0x005c)
#define BLUETOOTH_SENSORL_UUID (BLUETOOTH_GROUP_BASE_7+0x005d)

#define BLUETOOTH_COMPANY_0	"Ericsson"
#define BLUETOOTH_COMPANY_1	"Nokia"
#define BLUETOOTH_COMPANY_2	"Intel"
#define BLUETOOTH_COMPANY_3	"IBM"
#define BLUETOOTH_COMPANY_4	"Toshiba"
#define BLUETOOTH_COMPANY_5	"3Com"
#define BLUETOOTH_COMPANY_6	"Microsoft"
#define BLUETOOTH_COMPANY_7	"Lucent"
#define BLUETOOTH_COMPANY_8	"Motorola"
#define BLUETOOTH_COMPANY_9	"Infineon"
#define BLUETOOTH_COMPANY_10	"Cambridge Silicon Radio"
#define BLUETOOTH_COMPANY_11	"Silicon Wave"
#define BLUETOOTH_COMPANY_12	"Digianswer"
#define BLUETOOTH_COMPANY_13	"Texas Instruments"
#define BLUETOOTH_COMPANY_14	"Ceva"
#define BLUETOOTH_COMPANY_15	"Broadcom"
#define BLUETOOTH_COMPANY_16	"Mitel Semiconductor"
#define BLUETOOTH_COMPANY_17	"Widcomm"
#define BLUETOOTH_COMPANY_18	"Zeevo"
#define BLUETOOTH_COMPANY_19	"Atmel"
#define BLUETOOTH_COMPANY_20	"Mitsubishi"
#define BLUETOOTH_COMPANY_21	"RTX Telecom"
#define BLUETOOTH_COMPANY_22	"KC"
#define BLUETOOTH_COMPANY_23	"NewLogic"
#define BLUETOOTH_COMPANY_24	"Transilica"
#define BLUETOOTH_COMPANY_25	"Rohde & Schwarz"
#define BLUETOOTH_COMPANY_26	"TTPCom"
#define BLUETOOTH_COMPANY_27	"Signia"
#define BLUETOOTH_COMPANY_28	"Conexant"
#define BLUETOOTH_COMPANY_29	"Qualcomm"
#define BLUETOOTH_COMPANY_30	"Inventel"
#define BLUETOOTH_COMPANY_31	"AVM Berlin"
#define BLUETOOTH_COMPANY_32	"BandSpeed"
#define BLUETOOTH_COMPANY_33	"Mansella"
#define BLUETOOTH_COMPANY_34	"NEC"
#define BLUETOOTH_COMPANY_35	"WavePlus"
#define BLUETOOTH_COMPANY_36	"Alcatel"
#define BLUETOOTH_COMPANY_37	"Philips"
#define BLUETOOTH_COMPANY_38	"C Technologies"
#define BLUETOOTH_COMPANY_39	"Open Interface"
#define BLUETOOTH_COMPANY_40	"R F Micro Devices"
#define BLUETOOTH_COMPANY_41	"Hitachi"
#define BLUETOOTH_COMPANY_42	"Symbol"
#define BLUETOOTH_COMPANY_43	"Tenovis"
#define BLUETOOTH_COMPANY_44	"Macronix"
#define BLUETOOTH_COMPANY_45	"GCT Semiconductor"
#define BLUETOOTH_COMPANY_46	"Norwood"
#define BLUETOOTH_COMPANY_47	"MewTel"
#define BLUETOOTH_COMPANY_48	"ST Microelectronics"
#define BLUETOOTH_COMPANY_49	"Synopsis"
#define BLUETOOTH_COMPANY_50	"Red-M"
#define BLUETOOTH_COMPANY_51	"Commil"
#define BLUETOOTH_COMPANY_52	"Computer Access"
#define BLUETOOTH_COMPANY_53	"Eclipse"
#define BLUETOOTH_COMPANY_54	"Renesas Technology"
#define BLUETOOTH_COMPANY_55	"Mobilian"
#define BLUETOOTH_COMPANY_56	"Terax"
#define BLUETOOTH_COMPANY_57	"Integrated System Solution"
#define BLUETOOTH_COMPANY_58	"Matsushita"
#define BLUETOOTH_COMPANY_59	"Gennum"
#define BLUETOOTH_COMPANY_60	"Research In Motion"
#define BLUETOOTH_COMPANY_61	"IPextreme"
#define BLUETOOTH_COMPANY_62	"Systems and Chips"
#define BLUETOOTH_COMPANY_63	"Bluetooth SIG"
#define BLUETOOTH_COMPANY_64	"Seiko Epson"
#define BLUETOOTH_COMPANY_65	"Integrated Silicon Solution"
#define BLUETOOTH_COMPANY_66	"CONWISE"
#define BLUETOOTH_COMPANY_67	"PARROT"
#define BLUETOOTH_COMPANY_68	"Socket"
#define BLUETOOTH_COMPANY_69	"Atheros"
#define BLUETOOTH_COMPANY_70	"MediaTek"
#define BLUETOOTH_COMPANY_71	"Bluegiga"
#define BLUETOOTH_COMPANY_72	"Marvel"
#define BLUETOOTH_COMPANY_73	"3DSP"
#define BLUETOOTH_COMPANY_74	"Accel"
#define BLUETOOTH_COMPANY_75	\
			"Continental Automotive Systems"
#define BLUETOOTH_COMPANY_76	"Apple"
#define BLUETOOTH_COMPANY_77	"Staccato"
#define BLUETOOTH_COMPANY_78	"Avago"
#define BLUETOOTH_COMPANY_79	"APT"
#define BLUETOOTH_COMPANY_80	"SiRF"
#define BLUETOOTH_COMPANY_81	"Tzero"
#define BLUETOOTH_COMPANY_82	"J&M"
#define BLUETOOTH_COMPANY_83	"Free2move"
#define BLUETOOTH_COMPANY_84	"3DiJoy"
#define BLUETOOTH_COMPANY_85	"Plantronics"
#define BLUETOOTH_COMPANY_86	"Sony Ericsson"
#define BLUETOOTH_COMPANY_87	"Harman"
#define BLUETOOTH_COMPANY_88	"Vizio"
#define BLUETOOTH_COMPANY_89	"Nordic"
#define BLUETOOTH_COMPANY_90	"EM Microelectronic-Marin"
#define BLUETOOTH_COMPANY_91	"Ralink"
#define BLUETOOTH_COMPANY_92	"Belkin"
#define BLUETOOTH_COMPANY_93	"Realtek"
#define BLUETOOTH_COMPANY_94	"Stonestreet One"
#define BLUETOOTH_COMPANY_95	"Wicentric"
#define BLUETOOTH_COMPANY_96	"RivieraWaves"
#define BLUETOOTH_COMPANY_97	"RDA"
#define BLUETOOTH_COMPANY_98	"Gibson Guitars"
#define BLUETOOTH_COMPANY_99	"MiCommand"
#define BLUETOOTH_COMPANY_100	"Band XI International"
#define BLUETOOTH_COMPANY_101	"Hewlett-Packard"
#define BLUETOOTH_COMPANY_102	"9Solutions Oy"
#define BLUETOOTH_COMPANY_103	"GN Netcom"
#define BLUETOOTH_COMPANY_104	"General Motors"
#define BLUETOOTH_COMPANY_105	"A&D Engineering"
#define BLUETOOTH_COMPANY_106	"MindTree"
#define BLUETOOTH_COMPANY_107	"Polar Electro OY"
#define BLUETOOTH_COMPANY_108	"Beautiful Enterprise"
#define BLUETOOTH_COMPANY_109	"BriarTek"
#define BLUETOOTH_COMPANY_110	"Summit Data Communications"
#define BLUETOOTH_COMPANY_111	"Sound ID"
#define BLUETOOTH_COMPANY_112	"Monster"
#define BLUETOOTH_COMPANY_113	"connectBlue"
#define BLUETOOTH_COMPANY_114	"ShangHai Super Smart Electronics"
#define BLUETOOTH_COMPANY_115	"Group Sense"
#define BLUETOOTH_COMPANY_116	"Zomm"
#define BLUETOOTH_COMPANY_117	"Samsung"
#define BLUETOOTH_COMPANY_118	"Creative"
#define BLUETOOTH_COMPANY_119	"Laird"
#define BLUETOOTH_COMPANY_120	"Nike"
#define BLUETOOTH_COMPANY_121	"lesswire"
#define BLUETOOTH_COMPANY_122	"MStar"
#define BLUETOOTH_COMPANY_123	"Hanlynn"
#define BLUETOOTH_COMPANY_124	"A & R Cambridge"
#define BLUETOOTH_COMPANY_125	"Seers Technology"
#define BLUETOOTH_COMPANY_126	"Sports Tracking"
#define BLUETOOTH_COMPANY_127	"Autonet"
#define BLUETOOTH_COMPANY_128	"DeLorme Publishing"
#define BLUETOOTH_COMPANY_129	"WuXi Vimicro"
#define BLUETOOTH_COMPANY_130	"Sennheiser"
#define BLUETOOTH_COMPANY_131	"TimeKeeping Systems"
#define BLUETOOTH_COMPANY_132	"Ludus Helsinki"
#define BLUETOOTH_COMPANY_133	"BlueRadios"
#define BLUETOOTH_COMPANY_134	"equinox"
#define BLUETOOTH_COMPANY_135	"Garmin International"
#define BLUETOOTH_COMPANY_136	"Ecotest"
#define BLUETOOTH_COMPANY_137	"GN ReSound"
#define BLUETOOTH_COMPANY_138	"Jawbone"
#define BLUETOOTH_COMPANY_139	\
			"Topcorn Positioning Systems"
#define BLUETOOTH_COMPANY_140	"Qualcomm Retail Solutions"
#define BLUETOOTH_COMPANY_141	"Zscan Software"
#define BLUETOOTH_COMPANY_142	"Quintic"
#define BLUETOOTH_COMPANY_143	"Stollman E+V"
#define BLUETOOTH_COMPANY_144	"Funai"
#define BLUETOOTH_COMPANY_145	"Advanced PANMOBIL Systems"
#define BLUETOOTH_COMPANY_146	"ThinkOptics"
#define BLUETOOTH_COMPANY_147	"Universal"
#define BLUETOOTH_COMPANY_148	"Airoha"
#define BLUETOOTH_COMPANY_149	"NEC"
#define BLUETOOTH_COMPANY_150	"ODM"
#define BLUETOOTH_COMPANY_151	"ConnecteDevice"
#define BLUETOOTH_COMPANY_152	"zer01.tv"
#define BLUETOOTH_COMPANY_153	\
		"i.Tech Dynamic Global Distribution"
#define BLUETOOTH_COMPANY_154	"Alpwise"
#define BLUETOOTH_COMPANY_155	\
		"Jiangsu Toppower Automotive Electronics"
#define BLUETOOTH_COMPANY_156	"Colorfy"
#define BLUETOOTH_COMPANY_157	"Geoforce"
#define BLUETOOTH_COMPANY_158	"Bose"
#define BLUETOOTH_COMPANY_159	"Suunto"
#define BLUETOOTH_COMPANY_160	"Kensington"
#define BLUETOOTH_COMPANY_161	"SR-Medizinelektronik"
#define BLUETOOTH_COMPANY_162	"Vertu"
#define BLUETOOTH_COMPANY_163	"Meta Watch"
#define BLUETOOTH_COMPANY_164	"LINAK"
#define BLUETOOTH_COMPANY_165	"OTL Dynamics"
#define BLUETOOTH_COMPANY_166	"Panda Ocean"
#define BLUETOOTH_COMPANY_167	"Visteon"
#define BLUETOOTH_COMPANY_168	"ARP"
#define BLUETOOTH_COMPANY_169	"Magneti Marelli"
#define BLUETOOTH_COMPANY_170	"CAEN RFID srl"
#define BLUETOOTH_COMPANY_171	"Ingenieur-Systemgruppe"
#define BLUETOOTH_COMPANY_172	"Green Throttle Games"
#define BLUETOOTH_COMPANY_173	"Peter Systemtechnik"
#define BLUETOOTH_COMPANY_174	"Omegawave"
#define BLUETOOTH_COMPANY_175	"Cinetix"
#define BLUETOOTH_COMPANY_176	"Passif"
#define BLUETOOTH_COMPANY_177	"Saris Cycling"
#define BLUETOOTH_COMPANY_178	"Bekey"
#define BLUETOOTH_COMPANY_179	"Clarinox"
#define BLUETOOTH_COMPANY_180	"BDE"
#define BLUETOOTH_COMPANY_181	"Swirl Networks"
#define BLUETOOTH_COMPANY_182	"Meso"
#define BLUETOOTH_COMPANY_183	"TreLab"
#define BLUETOOTH_COMPANY_184	"Qualcomm Innovation Center"
#define BLUETOOTH_COMPANY_185	"Johnson Controls"
#define BLUETOOTH_COMPANY_186	"Starkey"
#define BLUETOOTH_COMPANY_187	"S-Power"
#define BLUETOOTH_COMPANY_188	"Ace Sensor"
#define BLUETOOTH_COMPANY_189	"Aplix"
#define BLUETOOTH_COMPANY_190	"AAMP of America"
#define BLUETOOTH_COMPANY_191	"Stalmart"
#define BLUETOOTH_COMPANY_192	"AMICCOM"
#define BLUETOOTH_COMPANY_193	"Shenzhen Excelsecu Data"
#define BLUETOOTH_COMPANY_194	"Geneq"
#define BLUETOOTH_COMPANY_195	"adidas"
#define BLUETOOTH_COMPANY_196	"LG"
#define BLUETOOTH_COMPANY_197	"Onset"
#define BLUETOOTH_COMPANY_198	"Selfly"
#define BLUETOOTH_COMPANY_199	"Quuppa"
#define BLUETOOTH_COMPANY_200	"GeLo"
#define BLUETOOTH_COMPANY_201	"Evluma"
#define BLUETOOTH_COMPANY_202	"MC10"
#define BLUETOOTH_COMPANY_203	"Binauric"
#define BLUETOOTH_COMPANY_204	"Beats"
#define BLUETOOTH_COMPANY_205	"Microchip"
#define BLUETOOTH_COMPANY_206	"Elgato Systems"
#define BLUETOOTH_COMPANY_207	"ARCHOS"
#define BLUETOOTH_COMPANY_208	"Dexcom"
#define BLUETOOTH_COMPANY_209	"Polar Electro"
#define BLUETOOTH_COMPANY_210	"Dialog"
#define BLUETOOTH_COMPANY_211	"Taixingbang"
#define BLUETOOTH_COMPANY_212	"Kawantech"
#define BLUETOOTH_COMPANY_213	"Austco"
#define BLUETOOTH_COMPANY_214	"Timex"
#define BLUETOOTH_COMPANY_215	"Qualcomm Technologies"
#define BLUETOOTH_COMPANY_216	\
			"Qualcomm Connected Experiences"
#define BLUETOOTH_COMPANY_217	"Voyetra Turtle Beach"
#define BLUETOOTH_COMPANY_218	"txtr"
#define BLUETOOTH_COMPANY_219	"Biosentronics"
#define BLUETOOTH_COMPANY_220	"Procter & Gamble"
#define BLUETOOTH_COMPANY_221	"Hosiden"
#define BLUETOOTH_COMPANY_222	"Muzik LLC"
#define BLUETOOTH_COMPANY_223	"Misfit Wearables"
#define BLUETOOTH_COMPANY_224	"Google"
#define BLUETOOTH_COMPANY_225	"Danlers"
#define BLUETOOTH_COMPANY_226	"Semilink"
#define BLUETOOTH_COMPANY_227	"inMusic Brands"
#define BLUETOOTH_COMPANY_228	"L.S. Research"
#define BLUETOOTH_COMPANY_229	"Eden"
#define BLUETOOTH_COMPANY_230	"Freshtemp"
#define BLUETOOTH_COMPANY_231	"KS"
#define BLUETOOTH_COMPANY_232	"ACTS"
#define BLUETOOTH_COMPANY_233	"Vtrack"
#define BLUETOOTH_COMPANY_234	"Nielsen-Kellerman"
#define BLUETOOTH_COMPANY_235	"Server Technology"
#define BLUETOOTH_COMPANY_236	"BioResearch Associates"
#define BLUETOOTH_COMPANY_237	"Jolly Logic"
#define BLUETOOTH_COMPANY_238	"Above Average Outcomes"
#define BLUETOOTH_COMPANY_239	"Bitsplitters"
#define BLUETOOTH_COMPANY_240	"PayPal"
#define BLUETOOTH_COMPANY_241	"Witron"
#define BLUETOOTH_COMPANY_242	"Aether Things"
#define BLUETOOTH_COMPANY_243	"Kent Displays"
#define BLUETOOTH_COMPANY_244	"Nautilus"
#define BLUETOOTH_COMPANY_245	"Smartifier"
#define BLUETOOTH_COMPANY_246	"Elcometer"
#define BLUETOOTH_COMPANY_247	"VSN"
#define BLUETOOTH_COMPANY_248	"AceUni"
#define BLUETOOTH_COMPANY_249	"StickNFind"
#define BLUETOOTH_COMPANY_250	"Crystal Code"
#define BLUETOOTH_COMPANY_251	"KOUKAAM a.s."
#define BLUETOOTH_COMPANY_252	"Delphi"
#define BLUETOOTH_COMPANY_253	"ValenceTech"
#define BLUETOOTH_COMPANY_254	"Reserved"
#define BLUETOOTH_COMPANY_255	"Typo Products"
#define BLUETOOTH_COMPANY_256	"TomTom"
#define BLUETOOTH_COMPANY_257	"Fugoo"
#define BLUETOOTH_COMPANY_258	"Keiser"
#define BLUETOOTH_COMPANY_259	"Bang & Olufsen"
#define BLUETOOTH_COMPANY_260	"PLUS Locations Systems"
#define BLUETOOTH_COMPANY_261	"Ubiquitous"
#define BLUETOOTH_COMPANY_262	"Innovative Yachtter Solutions"
#define BLUETOOTH_COMPANY_263	"William Demant Holding"
#define BLUETOOTH_COMPANY_264	"Chicony"
#define BLUETOOTH_COMPANY_265	"Atus"
#define BLUETOOTH_COMPANY_266	"Codegate"
#define BLUETOOTH_COMPANY_267	"ERi"
#define BLUETOOTH_COMPANY_268	"Transducers Direct"
#define BLUETOOTH_COMPANY_269	"Fujitsu"
#define BLUETOOTH_COMPANY_270	"Audi"
#define BLUETOOTH_COMPANY_271	"HiSilicon"
#define BLUETOOTH_COMPANY_272	"Nippon Seiki"
#define BLUETOOTH_COMPANY_273	"Steelseries ApS"
#define BLUETOOTH_COMPANY_274	"vyzybl"
#define BLUETOOTH_COMPANY_275	"Openbrain"
#define BLUETOOTH_COMPANY_276	"Xensr"
#define BLUETOOTH_COMPANY_277	"e.solutions"
#define BLUETOOTH_COMPANY_278	"1OAK"
#define BLUETOOTH_COMPANY_279	"Wimoto"
#define BLUETOOTH_COMPANY_280	"Radius Networks"
#define BLUETOOTH_COMPANY_281	"Wize"
#define BLUETOOTH_COMPANY_282	"Qualcomm Labs"
#define BLUETOOTH_COMPANY_283	"Aruba Networks"
#define BLUETOOTH_COMPANY_284	"Baidu"
#define BLUETOOTH_COMPANY_285	"Arendi AG"
#define BLUETOOTH_COMPANY_286	"Skoda Auto a.s."
#define BLUETOOTH_COMPANY_287	"Volkswagon"
#define BLUETOOTH_COMPANY_288	"Porsche"
#define BLUETOOTH_COMPANY_289	"Sino Wealth"
#define BLUETOOTH_COMPANY_290	"AirTurn"
#define BLUETOOTH_COMPANY_291	"Kinsa"
#define BLUETOOTH_COMPANY_292	"HID Global"
#define BLUETOOTH_COMPANY_293	"SEAT es"
#define BLUETOOTH_COMPANY_294	"Promethean"
#define BLUETOOTH_COMPANY_295	"Salutica Allied Solutions"
#define BLUETOOTH_COMPANY_296	"GPSI Group Pty"
#define BLUETOOTH_COMPANY_297	"Nimble Devices"
#define BLUETOOTH_COMPANY_298	"Changzhou Yongse Infotech"
#define BLUETOOTH_COMPANY_299	"SportIQ"
#define BLUETOOTH_COMPANY_300	"TEMEC Instruments B.V."
#define BLUETOOTH_COMPANY_301	"Sony"
#define BLUETOOTH_COMPANY_302	"ASSA ABLOY"
#define BLUETOOTH_COMPANY_303	"Clarion"
#define BLUETOOTH_COMPANY_304	"Warehouse Innovations"
#define BLUETOOTH_COMPANY_305	"Cypress"
#define BLUETOOTH_COMPANY_306	"MADS"
#define BLUETOOTH_COMPANY_307	"Blue Maestro"
#define BLUETOOTH_COMPANY_308	"Resolution Products"
#define BLUETOOTH_COMPANY_309	"Airewear"
#define BLUETOOTH_COMPANY_310	"ETC sp. z.o.o."
#define BLUETOOTH_COMPANY_311	"Prestigio Plaza"
#define BLUETOOTH_COMPANY_312	"NTEO"
#define BLUETOOTH_COMPANY_313	"Focus"
#define BLUETOOTH_COMPANY_314	"Tencent"
#define BLUETOOTH_COMPANY_315	"Allegion"
#define BLUETOOTH_COMPANY_316	"Murata"
#define BLUETOOTH_COMPANY_317	"WirelessWERX"
#define BLUETOOTH_COMPANY_318	"Nod"
#define BLUETOOTH_COMPANY_319	"B&B"
#define BLUETOOTH_COMPANY_320	"Alpine"
#define BLUETOOTH_COMPANY_321	"FedEx"
#define BLUETOOTH_COMPANY_322	"Grape"
#define BLUETOOTH_COMPANY_323	"Bkon Connect"
#define BLUETOOTH_COMPANY_324	"Lintech"
#define BLUETOOTH_COMPANY_325	"Novatel"
#define BLUETOOTH_COMPANY_326	"Ciright"
#define BLUETOOTH_COMPANY_327	"Mighty Cast"
#define BLUETOOTH_COMPANY_328	"Ambimat"
#define BLUETOOTH_COMPANY_329	"Perytons"
#define BLUETOOTH_COMPANY_330	"Tivoli Audio"
#define BLUETOOTH_COMPANY_331	"Master Lock"
#define BLUETOOTH_COMPANY_332	"Mesh-Net"
#define BLUETOOTH_COMPANY_333	"HUIZHOU DESAY SV AUTOMOTIVE"
#define BLUETOOTH_COMPANY_334	"Tangerine"
#define BLUETOOTH_COMPANY_335	"B&W"
#define BLUETOOTH_COMPANY_MAX	"internal use"

#endif
