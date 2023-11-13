在淘寶購入類似 KSGER 2.1S 的控制板
可以確定主控是 STM32F103C8T6 (實拍圖
https://item.taobao.com/item.htm?id=612228783159

把專案編譯的 MCU 從 F101 改成 F103
預設設定值已經修改成我慣用的模式，變動有以下設定
----
DEFAULT_TEMPERATURE: 320 -> 300
HWSTRING: "HW: XinYue T12"
C245_Cal250: 1800 -> 2000
C245_Cal400: 2800 -> 3200
contrastOrBrightness: 255 -> 125
dim_Timeout: 10000 -> 5000
guiTempDenoise: 5 -> 2
buttonWakeMode: wake_all -> wake_sleep
shakeWakeMode: wake_all -> wake_standby
language: lang_english -> lang_tchinese
standbyTemperature: 180 -> 150
MinSetTemperature: 180 -> 100
boostTimeout: 60000 -> 30000
coldBoostEnabled: true -> false
readPeriod: (200*200)-1 -> (100*200)-1
readDelay: (20*200)-1 -> (10*200)-1
shakeFiltering: disable -> enable
smartActiveEnabled: disable -> enable
standDelay: 0 -> 2
StandMode: mode_sleep -> mode_standby
----