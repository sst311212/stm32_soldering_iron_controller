/*
 * gui_strings.c
 *
 *  Created on: 27 ene. 2021
 *      Author: David
 */
#include "gui_strings.h"

// language indexes and LANGUAGE_COUNT defined in settings.h

const strings_t strings[LANGUAGE_COUNT] = {

    [lang_english] = {
      .boot_firstBoot = "First Boot!",
      .boot_Profile = "Profile",

      .main_error_noIron_Detected = "NO IRON DETECTED",
      .main_error_failsafe = "FAILSAFE MODE",
      .main_error_NTC_high = "NTC READ HIGH",
      .main_error_NTC_low = "NTC READ LOW",
      .main_error_VoltageLow = "VOLTAGE LOW",
      .main_mode_Sleep = "SLEEP",
      .main_mode_Sleep_xpos = 42,
      .main_mode_Standby = "STBY",
      .main_mode_Standby_xpos = 46,
      .main_mode_Boost = "BOOST",
      .main_mode_Boost_xpos = 41,

      .settings_IRON = "IRON",
      .settings_SYSTEM = "SYSTEM",
      .settings_DEBUG = "DEBUG",
      .settings_EDIT_TIPS = "EDIT TIPS",
      .settings_CALIBRATION = "CALIBRATION",
      .settings_EXIT = "EXIT",
#ifdef ENABLE_ADDONS
      .settings_ADDONS = "ADDONS/EXTRAS",
#endif

#ifdef ENABLE_ADDON_FUME_EXTRACTOR
      .FUME_EXTRACTOR_Title         = "FUME EXT. CTL.",
      .FUME_EXTRACTOR_Mode          = "Mode",
      .FUME_EXTRACTOR_Modes         = { "DISABLED", "AUTO", "ALW. ON" },
      .FUME_EXTRACTOR_AfterRun      = "After Run",
      .FUME_EXTRACTOR_AfterRunUnit  = "s",
#endif

#ifdef ENABLE_ADDON_SWITCH_OFF_REMINDER
      .SWITCH_OFF_REMINDER_Title               = "SW OFF REMINDER",
      .SWITCH_OFF_REMINDER_EnableDisableOption = "Reminder",
      .SWITCH_OFF_REMINDER_InactivityDelay     = "Delay",
      .SWITCH_OFF_REMINDER_ReminderPeriod     = "Period",
      .SWITCH_OFF_REMINDER_TimeUnit            = "m",
      .SWITCH_OFF_REMINDER_BeepType            = "Beep len.",
      .SWITCH_OFF_REMINDER_BeepTypes           = {"SHORT" ,"MED." ,"LONG"},
#endif

      .IRON_Profile = "Profile",
      .IRON_Max_Temp = "Max temp",
      .IRON_Min_Temp = "Min temp",
      .IRON_Standby = "Standby",
      .IRON_Sleep = "Sleep",
      .IRON_Boost = "Boost",
      .IRON_Boost_Add = " Increase",
      .IRON_Cold_Boost = "Cold Boost",
      .IRON_ColdBoost_Threshold = " Thresh.",
      .IRON_ColdBoost_Timeout = " Timeout",
      .IRON_Wake_Mode = "Wake mode",
      .IRON_Shake_Filtering = " Filter",
      .IRON_Stand_Mode = " In stand",
      .IRON_smartActiveEnable = "SMART",
      .IRON_smartActiveLoad = " LOAD",
      .IRON_Power = "Power",
      .IRON_Heater = "Heater",
      .IRON_ADC_Time = "ADC Time",
      .IRON_PWM_mul = "PWM mul.",
      .IRON_No_Iron = "No iron",
      .IRON_Error_Timeout = "Err time",
      .IRON_Error_Resume_Mode = " Resume",
      .IRON_FILTER_MENU = "FILTER MENU",
      .IRON_NTC_MENU = "NTC MENU",

      .FILTER_Filter = "Filter",
      .FILTER__Threshold = " Thresh.",
      .FILTER__Count_limit = " Count limit",
      .FILTER__Step_down = " Step down",
      .FILTER__Min = " Min",
      .FILTER_Reset_limit = "Reset limit",

      .SYSTEM_Boot = "Boot",
      .SYSTEM_Button_Wake = "Btn wake",
      .SYSTEM_Shake_Wake = "Shake wake",
      .SYSTEM_Encoder = "Encoder",
      .SYSTEM_Buzzer = "Buzzer",
      .SYSTEM_Temperature = "Temperature",
      .SYSTEM__Step = " Step",
      .SYSTEM__Big_Step = " Big step",
      .SYSTEM_Active_Detection = "Active det.",
      .SYSTEM_LVP = "LVP",
      .SYSTEM_Gui_Time = "Gui time",
      .SYSTEM_Battery = "Battery",
      .SYSTEM_DEBUG = "DEBUG",
      .SYSTEM_RESET_MENU = "RESET MENU",

      .SYSTEM_DISPLAY_MENU = "DISPLAY",
#ifndef ST756
      .DISPLAY_ContrastOrBrightness = "Brightness",
#else
      .DISPLAY_ContrastOrBrightness = "Contrast",
#endif
      .DISPLAY_StartColumn = "X",
      .DISPLAY_StartLine = "Y",
      .DISPLAY_Xflip = "X flip",
      .DISPLAY_Yflip = "Y flip",
      .DISPLAY_Ratio = "Ratio",
      .DISPLAY_Dim = "Dimmer",
      .DISPLAY_Dim_inSleep = " In sleep",
      .DISPLAY_Advanced = "ADVANCED",

      .NTC_Enable_NTC = "Enable NTC",
      .NTC_Pull = "Pull",
      .NTC__Res = " Res",
      .NTC__Beta = " Beta",
      .NTC_NTC_Detect = "NTC Detect",
      .NTC__High = " High",
      .NTC__Low = " Low",

      .RESET_Reset_Settings = "Reset Settings",
      .RESET_Reset_Profile = "Reset Profile",
      .RESET_Reset_Profiles = "Reset Profiles",
      .RESET_Reset_All = "Reset All",
      .RESET_Reset_msg_settings_1 = "RESET SYSTEM",
      .RESET_Reset_msg_settings_2 = "SETTINGS?",
      .RESET_Reset_msg_profile_1 = "RESET CURRENT",
      .RESET_Reset_msg_profile_2 = "PROFILE?",
      .RESET_Reset_msg_profiles_1 = "RESET ALL",
      .RESET_Reset_msg_profiles_2 = "PROFILES?",
      .RESET_Reset_msg_all_1 = "PERFORM FULL",
      .RESET_Reset_msg_all_2 = "SYSTEM RESET?",

      .TIP_SETTINGS_Name = "Name",
      .TIP_SETTINGS_PID_kp = "PID Kp",
      .TIP_SETTINGS_PID_ki = "PID Ki",
      .TIP_SETTINGS_PID_kd = "PID Kd",
      .TIP_SETTINGS_PID_Imax = "PID Imax",
      .TIP_SETTINGS_PID_Imin = "PID Imin",
      .TIP_SETTINGS_COPY = "COPY",
      .TIP_SETTINGS_DELETE = "DELETE",

      .CAL_ZeroSet = "Zero set   ",       // Must be 11 chars long
      .CAL_Sampling = "Sampling   ",      // Must be 11 chars long
      .CAL_Captured = "Captured   ",      // Must be 11 chars long
      .CAL_Step = "CAL STEP:",
      .CAL_Wait = "WAIT...",
      .CAL_Measured = "MEASURED:",
      .CAL_Success = "SUCCESS!",
      .CAL_Failed = "FAILED!",
      .CAL_DELTA_HIGH_1 = "DELTA TOO HIGH!",
      .CAL_DELTA_HIGH_2 = "Adjust manually",
      .CAL_DELTA_HIGH_3 = "and try again",
      .CAL_Error = "ERROR DETECTED!",
      .CAL_Aborting = "Aborting...",

      ._Language = "Language",
      .__Temp = " Temp",
      .__Delay = " Delay",
      .__Time = " Time",
      ._Cal_250 = "Cal 250\260C",
      ._Cal_400 = "Cal 400\260C",
      ._BACK = "BACK",
      ._SAVE = "SAVE",
      ._CANCEL = "CANCEL",
      ._STOP = "STOP",
      ._RESET = "RESET",
      ._START = "START",
      ._SETTINGS = "SETTINGS",
      ._ADD_NEW = "ADD NEW",

      .ERROR_RUNAWAY = "TEMP RUNAWAY",
      .ERROR_EXCEEDED = "EXCEEDED",
      .ERROR_UNKNOWN = "UNKNOWN ERROR",
      .ERROR_SYSTEM_HALTED = "SYSTEM HALTED",
      .ERROR_BTN_RESET = "Use btn to reset",

      .OffOn =       { "OFF", "ON" },
      .DownUp =      { "DOWN", "UP" },
      .WakeModes =   { "OFF", "STBY", "SLP", "ALL" },
      .wakeMode =    { "SHAKE", "STAND" },
      .encMode =     { "REV", "FWD" },
      .InitMode =    { "SLP", "STBY", "RUN" },
      .dimMode =     { "OFF", "SLP", "ALL" },
      .errMode =     { "SLP", "RUN", "LAST" },
    },

    [lang_tchinese] = {
      .boot_firstBoot = "初次開機！",
      .boot_Profile = "烙鐵類型",

      .main_error_noIron_Detected = "未插入烙鐵頭",
      .main_error_failsafe = "安全模式",
      .main_error_NTC_high = "NTC 讀值過高",
      .main_error_NTC_low = "NTC 讀值過低",
      .main_error_VoltageLow = "電壓過低",
      .main_mode_Sleep = "休眠",
      .main_mode_Sleep_xpos = 42,
      .main_mode_Standby = "睡眠",
      .main_mode_Standby_xpos = 42,
      .main_mode_Boost = "超溫",
      .main_mode_Boost_xpos = 42,

      .settings_IRON = "烙鐵設定",
      .settings_SYSTEM = "系統設定",
      .settings_DEBUG = "偵錯資訊",
      .settings_EDIT_TIPS = "編輯烙鐵頭",
      .settings_CALIBRATION = "溫度校正",
      .settings_EXIT = "離開",
#ifdef ENABLE_ADDONS
      .settings_ADDONS = "額外功能",
#endif

#ifdef ENABLE_ADDON_FUME_EXTRACTOR
      .FUME_EXTRACTOR_Title         = "排煙控制",
      .FUME_EXTRACTOR_Mode          = "模式",
      .FUME_EXTRACTOR_Modes         = { "關閉", "自動", "開啟" },
      .FUME_EXTRACTOR_AfterRun      = "持續運作",
      .FUME_EXTRACTOR_AfterRunUnit  = "s",
#endif

#ifdef ENABLE_ADDON_SWITCH_OFF_REMINDER
      .SWITCH_OFF_REMINDER_Title                = "關機提醒",
      .SWITCH_OFF_REMINDER_EnableDisableOption  = "定時提醒",
      .SWITCH_OFF_REMINDER_InactivityDelay      = "等待延時",
      .SWITCH_OFF_REMINDER_ReminderPeriod       = "蜂鳴間隔",
      .SWITCH_OFF_REMINDER_TimeUnit             = "m",
      .SWITCH_OFF_REMINDER_BeepType             = "蜂鳴時間",
      .SWITCH_OFF_REMINDER_BeepTypes            = { "短", "中", "長" },
#endif

      .IRON_Profile = "烙鐵類型",
      .IRON_Max_Temp = "最高溫度",
      .IRON_Min_Temp = "最低溫度",
      .IRON_Standby = "睡眠時間",
      .IRON_Sleep = "休眠時間",
      .IRON_Boost = "超溫時間",
      .IRON_Boost_Add = "└提高",
      .IRON_Cold_Boost = "冷頭速熱",
      .IRON_ColdBoost_Threshold = "└觸發溫差",
      .IRON_ColdBoost_Timeout = "└持續時長",
      .IRON_Wake_Mode = "喚醒模式",
      .IRON_Shake_Filtering = "└過濾",
      .IRON_Stand_Mode = "└進入",
      .IRON_smartActiveEnable = "智慧偵測",
      .IRON_smartActiveLoad = "└靈敏度",
      .IRON_Power = "功率限制",
      .IRON_Heater = "烙鐵電阻",
      .IRON_ADC_Time = "ADC 週期",
      .IRON_PWM_mul = "PWM 頻率",
      .IRON_No_Iron = "無烙鐵閾值",
      .IRON_Error_Timeout = "錯誤等待",
      .IRON_Error_Resume_Mode = "└還原狀態",
      .IRON_FILTER_MENU = "過濾器選單",
      .IRON_NTC_MENU = "NTC 選單",

      .FILTER_Filter = "過濾值",
      .FILTER__Threshold = "└閾值",
      .FILTER__Count_limit = "└計數限制",
      .FILTER__Step_down = "└縮小值",
      .FILTER__Min = "└最小值",
      .FILTER_Reset_limit = "重設限制",

      .SYSTEM_Boot = "開機進入",
      .SYSTEM_Button_Wake = "按鈕喚醒",
      .SYSTEM_Shake_Wake = "搖晃喚醒",
      .SYSTEM_Encoder = "編碼器",
      .SYSTEM_Buzzer = "蜂鳴器",
      .SYSTEM_Temperature = "溫度單位",
      .SYSTEM__Step = "└單格步進",
      .SYSTEM__Big_Step = "└快速步進",
      .SYSTEM_Active_Detection = "活動偵測",
      .SYSTEM_LVP = "低壓保護",
      .SYSTEM_Gui_Time = "顯示頻率",
      .SYSTEM_Battery = "系統電池",
      .SYSTEM_DEBUG = "偵錯選單",
      .SYSTEM_RESET_MENU = "重設選單",

      .SYSTEM_DISPLAY_MENU = "螢幕設定",
#ifndef ST756
      .DISPLAY_ContrastOrBrightness = "亮度",
#else
      .DISPLAY_ContrastOrBrightness = "對比度",
#endif
      .DISPLAY_StartColumn = "Ｘ軸起點",
      .DISPLAY_StartLine = "Ｙ軸起點",
      .DISPLAY_Xflip = "上下翻轉",
      .DISPLAY_Yflip = "左右翻轉",
      .DISPLAY_Ratio = "比例",
      .DISPLAY_Dim = "螢幕保護",
      .DISPLAY_Dim_inSleep = "└持續顯示",
      .DISPLAY_Advanced = "進階設定",

      .NTC_Enable_NTC = "外置 NTC",
      .NTC_Pull = "模式",
      .NTC__Res = "└阻值",
      .NTC__Beta = "└Ｂ值",
      .NTC_NTC_Detect = "NTC 偵測",
      .NTC__High = "└高阻值",
      .NTC__Low = "└低阻值",

      .RESET_Reset_Settings = "重設系統設定",
      .RESET_Reset_Profile = "重設目前烙鐵設定",
      .RESET_Reset_Profiles = "重設所有烙鐵設定",
      .RESET_Reset_All = "全部重設",
      .RESET_Reset_msg_settings_1 = "確定要重設",
      .RESET_Reset_msg_settings_2 = "系統設定嗎？",
      .RESET_Reset_msg_profile_1 = "確定要重設",
      .RESET_Reset_msg_profile_2 = "目前烙鐵設定嗎？",
      .RESET_Reset_msg_profiles_1 = "確定要重設",
      .RESET_Reset_msg_profiles_2 = "所有烙鐵設定嗎？",
      .RESET_Reset_msg_all_1 = "確定要還原",
      .RESET_Reset_msg_all_2 = "出廠預設值嗎？",

      .TIP_SETTINGS_Name = "名稱",
      .TIP_SETTINGS_PID_kp = "PID Kp",
      .TIP_SETTINGS_PID_ki = "PID Ki",
      .TIP_SETTINGS_PID_kd = "PID Kd",
      .TIP_SETTINGS_PID_Imax = "PID Imax",
      .TIP_SETTINGS_PID_Imin = "PID Imin",
      .TIP_SETTINGS_COPY = "複製",
      .TIP_SETTINGS_DELETE = "刪除",

      .CAL_ZeroSet = "參照值     ",       // Must be 11 chars long
      .CAL_Sampling = "取樣值     ",      // Must be 11 chars long
      .CAL_Captured = "設定值     ",      // Must be 11 chars long
      .CAL_Step = "校正溫度：",
      .CAL_Wait = "請稍等...",
      .CAL_Measured = "測量溫度：",
      .CAL_Success = "成功！",
      .CAL_Failed = "失敗！",
      .CAL_DELTA_HIGH_1 = "差值過大！",
      .CAL_DELTA_HIGH_2 = "請手動調整後",
      .CAL_DELTA_HIGH_3 = "再嘗試校正",
      .CAL_Error = "發生錯誤！",
      .CAL_Aborting = "正在退出...",

      ._Language = "系統語言",
      .__Temp = "└溫度",
      .__Delay = "└延時",
      .__Time = "└時間",
      ._Cal_250 = "250\260C 校值",
      ._Cal_400 = "400\260C 校值",
      ._BACK = "返回",
      ._SAVE = "儲存",
      ._CANCEL = "取消",
      ._STOP = "停止",
      ._RESET = "重設",
      ._START = "開始",
      ._SETTINGS = "設定值",
      ._ADD_NEW = "新增",

      .ERROR_RUNAWAY = "溫度過高",
      .ERROR_EXCEEDED = "數值超出",
      .ERROR_UNKNOWN = "未知錯誤",
      .ERROR_SYSTEM_HALTED = "系統當機",
      .ERROR_BTN_RESET = "使用按鈕來重設",

      .OffOn =       { "關閉", "開啟" },
      .DownUp =      { "下拉", "上拉" },
      .WakeModes =   { "關閉", "睡眠", "休眠", "全部" },
      .wakeMode =    { "搖晃", "支架" },
      .encMode =     { "逆時", "順時" },
      .InitMode =    { "休眠", "睡眠", "運作" },
      .dimMode =     { "關閉", "休眠", "全部" },
      .errMode =     { "休眠", "運作", "最後" },
    },

};

char * const tempUnit[2]              = { "\260C", "\260F" };
char * const profileStr[NUM_PROFILES] = { "T12", "C245", "C210" };
char * const Langs[LANGUAGE_COUNT]    = {
                                            [lang_english]  = "EN",
                                            [lang_tchinese] = "繁中",
                                        };
