#define MANUFACTURER_ID 7070
#define DEVICE_ID 50
#define REVISION 0

#define COMOBJ_dim_sw 0
#define COMOBJ_dim_rel 1
#define COMOBJ_dim_abs 2
#define COMOBJ_dim_state 3
#define COMOBJ_dim_value 4
#define COMOBJ_scene 5
#define COMOBJ_r 6
#define COMOBJ_g 7
#define COMOBJ_b 8
#define COMOBJ_w 9
#define COMOBJ_RGB 10
#define COMOBJ_RGBW 11
#define COMOBJ_h 12
#define COMOBJ_s 13
#define COMOBJ_v 14
#define COMOBJ_HSV 15
#define PARAM_led_type 0
#define PARAM_number_leds_strip 1
#define PARAM_r_correction 2
#define PARAM_g_correction 3
#define PARAM_b_correction 4
#define PARAM_w_correction 5
#define PARAM_gamma_correction 6
#define PARAM_wr 7
#define PARAM_wg 8
#define PARAM_wb 9
#define PARAM_time_soft 10
#define PARAM_time_rel 11
#define PARAM_day_min 12
#define PARAM_day_max 13
#define PARAM_night_min 14
#define PARAM_night_max 15
#define PARAM_uc1r 16
#define PARAM_uc1g 17
#define PARAM_uc1b 18
#define PARAM_uc1w 19
#define PARAM_uc2r 20
#define PARAM_uc2g 21
#define PARAM_uc2b 22
#define PARAM_uc2w 23
#define PARAM_uc3r 24
#define PARAM_uc3g 25
#define PARAM_uc3b 26
#define PARAM_uc3w 27
#define PARAM_uc4r 28
#define PARAM_uc4g 29
#define PARAM_uc4b 30
#define PARAM_uc4w 31
#define PARAM_uc5r 32
#define PARAM_uc5g 33
#define PARAM_uc5b 34
#define PARAM_uc5w 35
#define PARAM_scene01 36
#define PARAM_scene02 37
#define PARAM_scene03 38
#define PARAM_scene04 39
#define PARAM_scene05 40
#define PARAM_scene06 41
#define PARAM_scene07 42
#define PARAM_scene08 43
#define PARAM_scene09 44
#define PARAM_scene10 45
#define PARAM_scene11 46
#define PARAM_scene12 47
#define PARAM_scene13 48
#define PARAM_scene14 49
#define PARAM_scene15 50
#define PARAM_scene16 51
#define PARAM_scene17 52
#define PARAM_scene18 53
#define PARAM_scene19 54
#define PARAM_scene20 55
#define PARAM_scene21 56
#define PARAM_scene22 57
#define PARAM_scene23 58
#define PARAM_scene24 59
#define PARAM_scene25 60
#define PARAM_scene26 61
#define PARAM_scene27 62
#define PARAM_scene28 63
#define PARAM_scene29 64
#define PARAM_scene30 65
#define PARAM_scene31 66
#define PARAM_scene32 67
#define PARAM_scene33 68
#define PARAM_scene34 69
#define PARAM_scene35 70
#define PARAM_scene36 71
#define PARAM_scene37 72
#define PARAM_scene38 73
#define PARAM_scene39 74
#define PARAM_scene40 75
#define PARAM_scene41 76
#define PARAM_scene42 77
#define PARAM_scene43 78
#define PARAM_scene44 79
#define PARAM_scene45 80
#define PARAM_scene46 81
#define PARAM_scene47 82
#define PARAM_scene48 83
#define PARAM_scene49 84
#define PARAM_scene50 85
#define PARAM_scene51 86
#define PARAM_scene52 87
#define PARAM_scene53 88
#define PARAM_scene54 89
#define PARAM_scene55 90
#define PARAM_scene56 91
#define PARAM_scene57 92
#define PARAM_scene58 93
#define PARAM_scene59 94
#define PARAM_scene60 95
#define PARAM_scene61 96
#define PARAM_scene62 97
#define PARAM_scene63 98
#define PARAM_scene64 99
#define PARAM_ps_control 100
#define PARAM_ps_delay_off 101
        
KnxComObject KnxDevice::_comObjectsList[] = {
    /* Index 0 - dim_sw */ KnxComObject(KNX_DPT_1_001, 0x2b),
    /* Index 1 - dim_rel */ KnxComObject(KNX_DPT_3_007, 0x2a),
    /* Index 2 - dim_abs */ KnxComObject(KNX_DPT_5_004, 0x2a),
    /* Index 3 - dim_state */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 4 - dim_value */ KnxComObject(KNX_DPT_5_004, 0x34),
    /* Index 5 - scene */ KnxComObject(KNX_DPT_17_001, 0x2a),
    /* Index 6 - r */ KnxComObject(KNX_DPT_5_004, 0x2a),
    /* Index 7 - g */ KnxComObject(KNX_DPT_5_004, 0x2a),
    /* Index 8 - b */ KnxComObject(KNX_DPT_5_004, 0x2a),
    /* Index 9 - w */ KnxComObject(KNX_DPT_5_004, 0x2a),
    /* Index 10 - RGB */ KnxComObject(KNX_DPT_232_600, 0x2a),
    /* Index 11 - RGBW */ KnxComObject(KNX_DPT_251_600, 0x2a),
    /* Index 12 - h */ KnxComObject(KNX_DPT_5_004, 0x2a),
    /* Index 13 - s */ KnxComObject(KNX_DPT_5_004, 0x2a),
    /* Index 14 - v */ KnxComObject(KNX_DPT_5_004, 0x2a),
    /* Index 15 - HSV */ KnxComObject(KNX_DPT_232_600, 0x2a)
};
const byte KnxDevice::_numberOfComObjects = sizeof (_comObjectsList) / sizeof (KnxComObject); // do not change this code
       
byte KonnektingDevice::_paramSizeList[] = {
    /* Index 0 - led_type */ PARAM_UINT8,
    /* Index 1 - number_leds_strip */ PARAM_UINT16,
    /* Index 2 - r_correction */ PARAM_UINT8,
    /* Index 3 - g_correction */ PARAM_UINT8,
    /* Index 4 - b_correction */ PARAM_UINT8,
    /* Index 5 - w_correction */ PARAM_UINT8,
    /* Index 6 - w_type */ PARAM_UINT8,
    /* Index 7 - wr */ PARAM_UINT8,
    /* Index 8 - wg */ PARAM_UINT8,
    /* Index 9 - wb */ PARAM_UINT8,
    /* Index 10 - time_soft */ PARAM_UINT8,
    /* Index 11 - time_rel */ PARAM_UINT8,
    /* Index 12 - day_min */ PARAM_UINT8,
    /* Index 13 - day_max */ PARAM_UINT8,
    /* Index 14 - night_min */ PARAM_UINT8,
    /* Index 15 - night_max */ PARAM_UINT8,
    /* Index 16 - uc1r */ PARAM_UINT8,
    /* Index 17 - uc1g */ PARAM_UINT8,
    /* Index 18 - uc1b */ PARAM_UINT8,
    /* Index 19 - uc1w */ PARAM_UINT8,
    /* Index 20 - uc2r */ PARAM_UINT8,
    /* Index 21 - uc2g */ PARAM_UINT8,
    /* Index 22 - uc2b */ PARAM_UINT8,
    /* Index 23 - uc2w */ PARAM_UINT8,
    /* Index 24 - uc3r */ PARAM_UINT8,
    /* Index 25 - uc3g */ PARAM_UINT8,
    /* Index 26 - uc3b */ PARAM_UINT8,
    /* Index 27 - uc3w */ PARAM_UINT8,
    /* Index 28 - uc4r */ PARAM_UINT8,
    /* Index 29 - uc4g */ PARAM_UINT8,
    /* Index 30 - uc4b */ PARAM_UINT8,
    /* Index 31 - uc4w */ PARAM_UINT8,
    /* Index 32 - uc5r */ PARAM_UINT8,
    /* Index 33 - uc5g */ PARAM_UINT8,
    /* Index 34 - uc5b */ PARAM_UINT8,
    /* Index 35 - uc5w */ PARAM_UINT8,
    /* Index 36 - scene01 */ PARAM_UINT8,
    /* Index 37 - scene02 */ PARAM_UINT8,
    /* Index 38 - scene03 */ PARAM_UINT8,
    /* Index 39 - scene04 */ PARAM_UINT8,
    /* Index 40 - scene05 */ PARAM_UINT8,
    /* Index 41 - scene06 */ PARAM_UINT8,
    /* Index 42 - scene07 */ PARAM_UINT8,
    /* Index 43 - scene08 */ PARAM_UINT8,
    /* Index 44 - scene09 */ PARAM_UINT8,
    /* Index 45 - scene10 */ PARAM_UINT8,
    /* Index 46 - scene11 */ PARAM_UINT8,
    /* Index 47 - scene12 */ PARAM_UINT8,
    /* Index 48 - scene13 */ PARAM_UINT8,
    /* Index 49 - scene14 */ PARAM_UINT8,
    /* Index 50 - scene15 */ PARAM_UINT8,
    /* Index 51 - scene16 */ PARAM_UINT8,
    /* Index 52 - scene17 */ PARAM_UINT8,
    /* Index 53 - scene18 */ PARAM_UINT8,
    /* Index 54 - scene19 */ PARAM_UINT8,
    /* Index 55 - scene20 */ PARAM_UINT8,
    /* Index 56 - scene21 */ PARAM_UINT8,
    /* Index 57 - scene22 */ PARAM_UINT8,
    /* Index 58 - scene23 */ PARAM_UINT8,
    /* Index 59 - scene24 */ PARAM_UINT8,
    /* Index 60 - scene25 */ PARAM_UINT8,
    /* Index 61 - scene26 */ PARAM_UINT8,
    /* Index 62 - scene27 */ PARAM_UINT8,
    /* Index 63 - scene28 */ PARAM_UINT8,
    /* Index 64 - scene29 */ PARAM_UINT8,
    /* Index 65 - scene30 */ PARAM_UINT8,
    /* Index 66 - scene31 */ PARAM_UINT8,
    /* Index 67 - scene32 */ PARAM_UINT8,
    /* Index 68 - scene33 */ PARAM_UINT8,
    /* Index 69 - scene34 */ PARAM_UINT8,
    /* Index 70 - scene35 */ PARAM_UINT8,
    /* Index 71 - scene36 */ PARAM_UINT8,
    /* Index 72 - scene37 */ PARAM_UINT8,
    /* Index 73 - scene38 */ PARAM_UINT8,
    /* Index 74 - scene39 */ PARAM_UINT8,
    /* Index 75 - scene40 */ PARAM_UINT8,
    /* Index 76 - scene41 */ PARAM_UINT8,
    /* Index 77 - scene42 */ PARAM_UINT8,
    /* Index 78 - scene43 */ PARAM_UINT8,
    /* Index 79 - scene44 */ PARAM_UINT8,
    /* Index 80 - scene45 */ PARAM_UINT8,
    /* Index 81 - scene46 */ PARAM_UINT8,
    /* Index 82 - scene47 */ PARAM_UINT8,
    /* Index 83 - scene48 */ PARAM_UINT8,
    /* Index 84 - scene49 */ PARAM_UINT8,
    /* Index 85 - scene50 */ PARAM_UINT8,
    /* Index 86 - scene51 */ PARAM_UINT8,
    /* Index 87 - scene52 */ PARAM_UINT8,
    /* Index 88 - scene53 */ PARAM_UINT8,
    /* Index 89 - scene54 */ PARAM_UINT8,
    /* Index 90 - scene55 */ PARAM_UINT8,
    /* Index 91 - scene56 */ PARAM_UINT8,
    /* Index 92 - scene57 */ PARAM_UINT8,
    /* Index 93 - scene58 */ PARAM_UINT8,
    /* Index 94 - scene59 */ PARAM_UINT8,
    /* Index 95 - scene60 */ PARAM_UINT8,
    /* Index 96 - scene61 */ PARAM_UINT8,
    /* Index 97 - scene62 */ PARAM_UINT8,
    /* Index 98 - scene63 */ PARAM_UINT8,
    /* Index 99 - scene64 */ PARAM_UINT8,
    /* Index 100 - ps_control */ PARAM_UINT8,
    /* Index 101 - ps_delay_off */ PARAM_UINT8
};
const int KonnektingDevice::_numberOfParams = sizeof (_paramSizeList); // do not change this code
