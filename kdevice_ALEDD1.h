#define MANUFACTURER_ID 7070
#define DEVICE_ID 50
#define REVISION 1

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
#define COMOBJ_m1sw 17
#define COMOBJ_m1perc 18
#define COMOBJ_m1rgb 19
#define COMOBJ_m1rgbw 20
#define COMOBJ_m2sw 21
#define COMOBJ_m2perc 22
#define COMOBJ_m2rgb 23
#define COMOBJ_m2rgbw 24
#define COMOBJ_m3sw 25
#define COMOBJ_m3perc 26
#define COMOBJ_m3rgb 27
#define COMOBJ_m3rgbw 28
#define COMOBJ_m4sw 29
#define COMOBJ_m4perc 30
#define COMOBJ_m4rgb 31
#define COMOBJ_m4rgbw 32
#define COMOBJ_power_supply 33
#define COMOBJ_nightMode 34
#define PARAM_led_type 0
#define PARAM_number_leds_strip 1
#define PARAM_first_on_value 2
#define PARAM_r_correction 3
#define PARAM_g_correction 4
#define PARAM_b_correction 5
#define PARAM_w_correction 6
#define PARAM_gamma_correction 7
#define PARAM_wr 8
#define PARAM_wg 9
#define PARAM_wb 10
#define PARAM_time_soft 11
#define PARAM_time_rel 12
#define PARAM_day_min 13
#define PARAM_day_max 14
#define PARAM_night_min 15
#define PARAM_night_max 16
#define PARAM_uc1r 17
#define PARAM_uc1g 18
#define PARAM_uc1b 19
#define PARAM_uc1w 20
#define PARAM_uc2r 21
#define PARAM_uc2g 22
#define PARAM_uc2b 23
#define PARAM_uc2w 24
#define PARAM_uc3r 25
#define PARAM_uc3g 26
#define PARAM_uc3b 27
#define PARAM_uc3w 28
#define PARAM_uc4r 29
#define PARAM_uc4g 30
#define PARAM_uc4b 31
#define PARAM_uc4w 32
#define PARAM_uc5r 33
#define PARAM_uc5g 34
#define PARAM_uc5b 35
#define PARAM_uc5w 36
#define PARAM_m1first 37
#define PARAM_m1last 38
#define PARAM_m1r 39
#define PARAM_m1g 40
#define PARAM_m1b 41
#define PARAM_m1w 42
#define PARAM_m2first 43
#define PARAM_m2last 44
#define PARAM_m2r 45
#define PARAM_m2g 46
#define PARAM_m2b 47
#define PARAM_m2w 48
#define PARAM_m3first 49
#define PARAM_m3last 50
#define PARAM_m3r 51
#define PARAM_m3g 52
#define PARAM_m3b 53
#define PARAM_m3w 54
#define PARAM_m4first 55
#define PARAM_m4last 56
#define PARAM_m4r 57
#define PARAM_m4g 58
#define PARAM_m4b 59
#define PARAM_m4w 60
#define PARAM_ps_control 61
#define PARAM_ps_delay_off 62
        
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
    /* Index 16 - scene_state */ KnxComObject(KNX_DPT_17_001, 0x34),
    /* Index 17 - m1sw */ KnxComObject(KNX_DPT_1_001, 0x2a),
    /* Index 18 - m1perc */ KnxComObject(KNX_DPT_5_001, 0x2a),
    /* Index 19 - m1rgb */ KnxComObject(KNX_DPT_232_600, 0x2a),
    /* Index 20 - m1rgbw */ KnxComObject(KNX_DPT_251_600, 0x2a),
    /* Index 21 - m2sw */ KnxComObject(KNX_DPT_1_001, 0x2a),
    /* Index 22 - m2perc */ KnxComObject(KNX_DPT_5_001, 0x2a),
    /* Index 23 - m2rgb */ KnxComObject(KNX_DPT_232_600, 0x2a),
    /* Index 24 - m2rgbw */ KnxComObject(KNX_DPT_251_600, 0x2a),
    /* Index 25 - m3sw */ KnxComObject(KNX_DPT_1_001, 0x2a),
    /* Index 26 - m3perc */ KnxComObject(KNX_DPT_5_001, 0x2a),
    /* Index 27 - m3rgb */ KnxComObject(KNX_DPT_232_600, 0x2a),
    /* Index 28 - m3rgbw */ KnxComObject(KNX_DPT_251_600, 0x2a),
    /* Index 29 - m4sw */ KnxComObject(KNX_DPT_1_001, 0x2a),
    /* Index 30 - m4perc */ KnxComObject(KNX_DPT_5_001, 0x2a),
    /* Index 31 - m4rgb */ KnxComObject(KNX_DPT_232_600, 0x2a),
    /* Index 32 - m4rgbw */ KnxComObject(KNX_DPT_251_600, 0x2a),
    /* Index 33 - power_supply */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 34 - nightMode */ KnxComObject(KNX_DPT_1_001, 0x2b)
};
const byte KnxDevice::_numberOfComObjects = sizeof (_comObjectsList) / sizeof (KnxComObject); // do not change this code
       
byte KonnektingDevice::_paramSizeList[] = {
    /* Index 0 - led_type */ PARAM_UINT8,
    /* Index 1 - number_leds_strip */ PARAM_UINT16,
    /* Index 2 - first_on_value */ PARAM_UINT8,
    /* Index 3 - r_correction */ PARAM_UINT8,
    /* Index 4 - g_correction */ PARAM_UINT8,
    /* Index 5 - b_correction */ PARAM_UINT8,
    /* Index 6 - w_correction */ PARAM_UINT8,
    /* Index 7 - gamma_correction */ PARAM_UINT8,
    /* Index 8 - wr */ PARAM_UINT8,
    /* Index 9 - wg */ PARAM_UINT8,
    /* Index 10 - wb */ PARAM_UINT8,
    /* Index 11 - time_soft */ PARAM_UINT8,
    /* Index 12 - time_rel */ PARAM_UINT8,
    /* Index 13 - day_min */ PARAM_UINT8,
    /* Index 14 - day_max */ PARAM_UINT8,
    /* Index 15 - night_min */ PARAM_UINT8,
    /* Index 16 - night_max */ PARAM_UINT8,
    /* Index 17 - uc1r */ PARAM_UINT8,
    /* Index 18 - uc1g */ PARAM_UINT8,
    /* Index 19 - uc1b */ PARAM_UINT8,
    /* Index 20 - uc1w */ PARAM_UINT8,
    /* Index 21 - uc2r */ PARAM_UINT8,
    /* Index 22 - uc2g */ PARAM_UINT8,
    /* Index 23 - uc2b */ PARAM_UINT8,
    /* Index 24 - uc2w */ PARAM_UINT8,
    /* Index 25 - uc3r */ PARAM_UINT8,
    /* Index 26 - uc3g */ PARAM_UINT8,
    /* Index 27 - uc3b */ PARAM_UINT8,
    /* Index 28 - uc3w */ PARAM_UINT8,
    /* Index 29 - uc4r */ PARAM_UINT8,
    /* Index 30 - uc4g */ PARAM_UINT8,
    /* Index 31 - uc4b */ PARAM_UINT8,
    /* Index 32 - uc4w */ PARAM_UINT8,
    /* Index 33 - uc5r */ PARAM_UINT8,
    /* Index 34 - uc5g */ PARAM_UINT8,
    /* Index 35 - uc5b */ PARAM_UINT8,
    /* Index 36 - uc5w */ PARAM_UINT8,
    /* Index 37 - m1first */ PARAM_UINT16,
    /* Index 38 - m1last */ PARAM_UINT16,
    /* Index 39 - m1r */ PARAM_UINT8,
    /* Index 40 - m1g */ PARAM_UINT8,
    /* Index 41 - m1b */ PARAM_UINT8,
    /* Index 42 - m1w */ PARAM_UINT8,
    /* Index 43 - m2first */ PARAM_UINT16,
    /* Index 44 - m2last */ PARAM_UINT16,
    /* Index 45 - m2r */ PARAM_UINT8,
    /* Index 46 - m2g */ PARAM_UINT8,
    /* Index 47 - m2b */ PARAM_UINT8,
    /* Index 48 - m2w */ PARAM_UINT8,
    /* Index 49 - m3first */ PARAM_UINT16,
    /* Index 50 - m3last */ PARAM_UINT16,
    /* Index 51 - m3r */ PARAM_UINT8,
    /* Index 52 - m3g */ PARAM_UINT8,
    /* Index 53 - m3b */ PARAM_UINT8,
    /* Index 54 - m3w */ PARAM_UINT8,
    /* Index 55 - m4first */ PARAM_UINT16,
    /* Index 56 - m4last */ PARAM_UINT16,
    /* Index 57 - m4r */ PARAM_UINT8,
    /* Index 58 - m4g */ PARAM_UINT8,
    /* Index 59 - m4b */ PARAM_UINT8,
    /* Index 60 - m4w */ PARAM_UINT8,
    /* Index 61 - ps_control */ PARAM_UINT8,
    /* Index 62 - ps_delay_off */ PARAM_UINT8
};
const int KonnektingDevice::_numberOfParams = sizeof (_paramSizeList); // do not change this code
