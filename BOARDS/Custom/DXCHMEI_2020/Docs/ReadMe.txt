2021年在露天購入的舊版 T12-A，主控確定是 CKS32F103CBT6
目前淘寶賣家已經更新新版，不確定是否能直接使用
https://www.ruten.com.tw/item/show?21913499224758

預設設定值已經修改成我慣用的模式，變動有以下設定
----
DEFAULT_TEMPERATURE: 320 -> 300
HWSTRING: "HW: DXCHMEI T12"
T12_Cal250: 1300 -> 1200
T12_Cal400: 1900 -> 1800
C245_Cal250: 1200 -> 1300
C245_Cal400: 1750 -> 2200
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