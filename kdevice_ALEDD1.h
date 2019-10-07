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
#define COMOBJ_scene_state 16
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
    /* Index 15 - HSV */ KnxComObject(KNX_DPT_232_600, 0x2a),
    /* Index 16 - scene_state */ KnxComObject(KNX_DPT_17_001, 0x34)
};
const byte KnxDevice::_numberOfComObjects = sizeof (_comObjectsList) / sizeof (KnxComObject); // do not change this code
       
byte KonnektingDevice::_paramSizeList[] = {
    /* Index 0 - led_type */ PARAM_UINT8,
    /* Index 1 - number_leds_strip */ PARAM_UINT16,
    /* Index 2 - r_correction */ PARAM_UINT8,
    /* Index 3 - g_correction */ PARAM_UINT8,
    /* Index 4 - b_correction */ PARAM_UINT8,
    /* Index 5 - w_correction */ PARAM_UINT8,
    /* Index 6 - gamma_correction */ PARAM_UINT8,
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
    /* Index 35 - uc5w */ PARAM_UINT8
};
const int KonnektingDevice::_numberOfParams = sizeof (_paramSizeList); // do not change this code
