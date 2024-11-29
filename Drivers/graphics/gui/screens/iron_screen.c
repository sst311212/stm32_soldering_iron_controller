/*
 * settings_iron_screen.c
 *
 *  Created on: Jul 30, 2021
 *      Author: David
 */


#include "iron_screen.h"
#include "screen_common.h"

screen_t Screen_iron;
screen_t Screen_iron_advFilter;
static comboBox_item_t *comboItem_advFilter;
static comboBox_item_t *comboitem_ShakeFiltering;
static comboBox_item_t *comboitem_StandMode;
static comboBox_item_t *comboitem_StandDelay;
static comboBox_item_t *comboitem_smartActiveLoad;
static comboBox_item_t *comboItem_coldBoostTimeout;
static comboBox_item_t *comboItem_coldBoostTemp;
static editable_widget_t *editable_IRON_StandbyTemp;
static editable_widget_t *editable_IRON_BoostTemp;
static editable_widget_t *editable_IRON_ColdBoostTemp;
static editable_widget_t *editable_IRON_MaxTemp;
static editable_widget_t *editable_IRON_MinTemp;
static editable_widget_t *editable_IRON_Profile;

#ifdef USE_NTC
screen_t Screen_iron_ntc;
static comboBox_item_t *comboitem_PullRes;
static comboBox_item_t *comboitem_PullMode;
static comboBox_item_t *comboitem_AutoDetect;
static comboBox_item_t *comboitem_NTC_res;
static comboBox_item_t *comboitem_NTC_res_beta;
static comboBox_item_t *comboitem_Detect_high_res;
static comboBox_item_t *comboitem_Detect_low_res;
static comboBox_item_t *comboitem_Detect_high_res_beta;
static comboBox_item_t *comboitem_Detect_low_res_beta;
#endif

filter_t bak_f;

void updateTempValues();

#ifdef USE_NTC
ntc_data_t backup_ntc;

void update_NTC_menu(void){
  uint8_t NTC_auto = (backup_ntc.detection && backup_ntc.enabled);
  uint8_t NTC_fixed = (!backup_ntc.detection && backup_ntc.enabled);
  comboitem_PullMode->enabled = backup_ntc.enabled;
  comboitem_PullRes->enabled =  backup_ntc.enabled;
  comboitem_AutoDetect->enabled =  backup_ntc.enabled;
  comboitem_NTC_res->enabled = NTC_fixed;
  comboitem_NTC_res_beta->enabled = NTC_fixed;
  comboitem_Detect_high_res->enabled = NTC_auto;
  comboitem_Detect_low_res->enabled = NTC_auto;
  comboitem_Detect_high_res_beta->enabled = NTC_auto;
  comboitem_Detect_low_res_beta->enabled = NTC_auto;
}
#endif



//=========================================================
static void set_filter(uint32_t *val) {
  bak_f.coefficient = *val;
  if(bak_f.min > bak_f.coefficient){
    bak_f.min = bak_f.coefficient;
  }
}
static void * get_filter() {
  temp = bak_f.coefficient;
  return &temp;
}
//=========================================================
static void set_threshold(uint32_t *val) {
  if(*val>=(bak_f.reset_threshold-100)){
    *val=bak_f.reset_threshold-100;
  }
  bak_f.threshold= *val;
}
static void * get_threshold() {
  temp = bak_f.threshold;
  return &temp;
}
//=========================================================
static void set_count_limit(uint32_t *val) {
  bak_f.count_limit= *val;
}
static void * get_count_limit() {
  temp = bak_f.count_limit;
  return &temp;
}
//=========================================================
static void set_limit_step(uint32_t *val) {
  bak_f.step= *val;
}
static void * get_limit_step() {
  temp = bak_f.step;
  return &temp;
}
//=========================================================
static void set_min_filter(uint32_t *val) {
  bak_f.min = *val;
  if(bak_f.min > bak_f.coefficient){
    bak_f.min = bak_f.coefficient;
  }
}
static void * get_min_filter() {
  temp = bak_f.min;
  return &temp;
}
//=========================================================
static void set_reset_threshold(uint32_t *val) {
  if(*val<=(bak_f.threshold+100)){
    *val=bak_f.threshold+100;
  }
  bak_f.reset_threshold= *val;
}
static void * get_reset_threshold() {
  temp = bak_f.reset_threshold;
  return &temp;
}
//=========================================================
void update_Iron_menu(void){
  comboitem_ShakeFiltering->enabled = (getProfileSettings()->WakeInputMode==mode_shake);
  comboitem_StandMode->enabled = (getProfileSettings()->WakeInputMode==mode_stand);
  comboitem_StandDelay->enabled = (getProfileSettings()->WakeInputMode==mode_stand);
  comboitem_smartActiveLoad->enabled = (getProfileSettings()->smartActiveEnabled==enable);
  comboItem_coldBoostTimeout->enabled = (getProfileSettings()->coldBoostEnabled==enable);
  comboItem_coldBoostTemp->enabled = (getProfileSettings()->coldBoostEnabled==enable);
}
//=========================================================
#ifdef USE_VIN
static void * getMaxPower() {
  temp = getProfileSettings()->power;
  return &temp;
}
static void setMaxPower(uint32_t *val) {
  getProfileSettings()->power = *val;
}
//=========================================================
static void * getTipImpedance() {
  temp = getProfileSettings()->impedance;
  return &temp;
}
static void setTipImpedance(uint32_t *val) {
  getProfileSettings()->impedance = *val;
}
#endif
//=========================================================
static void setSleepTime(uint32_t *val) {
  getProfileSettings()->sleepTimeout= *val*60000;
}
static void * getSleepTime() {
  temp = getProfileSettings()->sleepTimeout/60000;
  return &temp;
}
//=========================================================
static void setStandbyTime(uint32_t *val) {
  getProfileSettings()->standbyTimeout= *val*60000;
}
static void * getStandbyTime() {
  temp = getProfileSettings()->standbyTimeout/60000;
  return &temp;
}
//=========================================================
static void setStandbyTemp(uint32_t *val) {
  getProfileSettings()->standbyTemperature= *val;
}
static void * getStandbyTemp() {
  temp = getProfileSettings()->standbyTemperature;
  return &temp;
}
//=========================================================
static void * _getPwmMul() {
  temp=getProfileSettings()->pwmMul;
  return &temp;
}
static void _setPwmMul(uint32_t *val) {
  setPwmMul(*val);
}
//=========================================================
static void * _getReadDelay() {
  temp=(getProfileSettings()->readDelay+1)/20;
  return &temp;
}
static void _setReadDelay(uint32_t *val) {
  uint16_t delay=(*val*20)-1;
  if(delay>(getProfileSettings()->readPeriod-200)){
    delay = getProfileSettings()->readPeriod-200;
  }
  setReadDelay(delay);
}
//=========================================================
static void * _getReadPeriod() {
  temp=(getProfileSettings()->readPeriod+1)/200;
  return &temp;
}
static void _setReadPeriod(uint32_t *val) {
  uint16_t period=(*val*200)-1;

  if(period<(getProfileSettings()->readDelay+200)){
      period=getProfileSettings()->readDelay+200;
  }
  setReadPeriod(period);
}
//=========================================================
static void * getMaxTemp() {
  temp=getProfileSettings()->MaxSetTemperature;
  return &temp;
}
static void setMaxTemp(uint32_t *val) {
  getProfileSettings()->MaxSetTemperature=*val;
  updateTempValues();
}
//=========================================================
static void * getMinTemp() {
  temp=getProfileSettings()->MinSetTemperature;
  return &temp;
}
static void setMinTemp(uint32_t *val) {
  getProfileSettings()->MinSetTemperature=*val;
  updateTempValues();
}
//=========================================================
static void * geterrorDelay() {
  temp = getProfileSettings()->errorTimeout/100;
  return &temp;
}
static void seterrorDelay(uint32_t *val) {
  getProfileSettings()->errorTimeout = *val*100;
}
//=========================================================
static void * geterrorResume() {
  temp = getProfileSettings()->errorResumeMode;
  return &temp;
}
static void seterrorResume(uint32_t *val) {
  getProfileSettings()->errorResumeMode = *val;
}
//=========================================================
static void * getNoIronADC() {
  temp = getProfileSettings()->noIronValue;
  return &temp;
}
static void setNoIronADC(uint32_t *val) {
  getProfileSettings()->noIronValue = *val;
}
//=========================================================
static void setBoostTime(uint32_t *val) {
  getProfileSettings()->boostTimeout= *val*1000;
}
static void * getBoostTime() {
  temp = getProfileSettings()->boostTimeout/1000;
  return &temp;
}
//=========================================================
static void setBoostTemp(uint32_t *val) {
  getProfileSettings()->boostTemperature= *val;
}
static void * getBoostTemp() {
  temp = getProfileSettings()->boostTemperature;
  return &temp;
}
//=========================================================
static void * getColdBoost() {
  temp = getProfileSettings()->coldBoostEnabled;
  update_Iron_menu();
  return &temp;
}
static void setColdBoost(uint32_t *val) {
  getProfileSettings()->coldBoostEnabled = * val;
}
//=========================================================
static void * getColdBoostTemp() {
  temp = getProfileSettings()->coldBoostTemperature;
  return &temp;
}
static void setColdBoostTemp(uint32_t *val) {
  getProfileSettings()->coldBoostTemperature= *val;
}
//=========================================================
static void * getColdBoostTime() {
  temp = getProfileSettings()->coldBoostTimeout/1000;
  return &temp;
}
static void setColdBoostTime(uint32_t *val) {
  getProfileSettings()->coldBoostTimeout= *val*1000;
}
//=========================================================
static void * getWakeMode() {
  temp = getProfileSettings()->WakeInputMode;
  update_Iron_menu();
  return &temp;
}
static void setWakeMode(uint32_t *val) {
  getProfileSettings()->WakeInputMode = *val;
}
//=========================================================
static void * getStandMode() {
  temp = getProfileSettings()->StandMode;
  return &temp;
}
static void setStandMode(uint32_t *val) {
  getProfileSettings()->StandMode = *val;
}
//=========================================================
static void * getStandDelay() {
  temp = getProfileSettings()->standDelay;
  return &temp;
}
static void setStandDelay(uint32_t *val) {
  getProfileSettings()->standDelay = *val;
}
//=========================================================
static void setsmartActiveEnable(uint32_t *val) {
  getProfileSettings()->smartActiveEnabled = *val;
  update_Iron_menu();
}
static void * getsmartActiveEnable() {
  temp = getProfileSettings()->smartActiveEnabled;
  return &temp;
}
//=========================================================
static void setsmartActiveLoad(uint32_t *val) {
  getProfileSettings()->smartActiveLoad = *val;
}
static void * getsmartActiveLoad() {
  temp = getProfileSettings()->smartActiveLoad;
  return &temp;
}
//=========================================================
static void * getShakeFiltering() {
  temp = getProfileSettings()->shakeFiltering;
  return &temp;
}
static void setShakeFiltering(uint32_t *val) {
  getProfileSettings()->shakeFiltering = *val;
}

//=========================================================
static void * getProfile() {
  temp = profile;
  return &temp;
}
static void setProfile(uint32_t *val) {
  profile=*val;
}
//=========================================================

static void iron_onEnter(screen_t *scr){
  update_Iron_menu();
  if(getSystemTempUnit()==mode_Farenheit){
    editable_IRON_MaxTemp->inputData.endString="\260F";
    editable_IRON_MinTemp->inputData.endString="\260F";
    editable_IRON_StandbyTemp->inputData.endString="\260F";
    editable_IRON_BoostTemp->inputData.endString="\260F";
    editable_IRON_ColdBoostTemp->inputData.endString="\260F";
  }
  else{
    editable_IRON_MaxTemp->inputData.endString="\260C";
    editable_IRON_MinTemp->inputData.endString="\260C";
    editable_IRON_StandbyTemp->inputData.endString="\260C";
    editable_IRON_BoostTemp->inputData.endString="\260C";
    editable_IRON_ColdBoostTemp->inputData.endString="\260C";
  }
  if(scr==&Screen_settings){
    comboResetIndex(Screen_iron.current_widget);
  }
  else if(scr==&Screen_iron){                                           // iron screen was reloaded after changing the profile
    editable_IRON_Profile->selectable.state=widget_edit;            // Set widget in editing mode
    editable_IRON_Profile->selectable.previous_state=widget_selected;
  }
}

static void iron_onExit(screen_t *scr){

  if( (profile != getCurrentProfile() || ((scr != &Screen_iron_advFilter) && (scr != &Screen_iron_ntc) && (scr != &Screen_iron))) && isCurrentProfileChanged() ){    // Going to main screen or current profile changed? Check if profile needs saving
    uint16_t userTemp = getUserTemperature();

    if(userTemp > getProfileSettings()->MaxSetTemperature)
      setUserTemperature(getProfileSettings()->MaxSetTemperature);

    else if (userTemp < getProfileSettings()->MinSetTemperature)
      setUserTemperature(getProfileSettings()->MinSetTemperature);

    saveSettings(save_profile, no_reboot);                            // Save now we have all heap free
  }

  if(profile != getCurrentProfile()){                                 // User changed the current profile?
    loadProfile(profile);                                             // Load profile
  }
}

int filter_Save(widget_t *w, RE_Rotation_t input){
  uint32_t _irq = __get_PRIMASK();
  __disable_irq();
  getProfileSettings()->tipFilter = bak_f;
  TIP.filter=bak_f;
  __set_PRIMASK(_irq);
  return last_scr;
}


#ifdef USE_NTC

static void set_enable_NTC(uint32_t *val) {
  backup_ntc.enabled = *val;
  update_NTC_menu();
}
static void * get_enable_NTC() {
  temp = backup_ntc.enabled;
  return &temp;
}
//=========================================================
static void set_NTC_beta(uint32_t *val) {
  backup_ntc.NTC_beta = *val;
}
static void * get_NTC_beta() {
  temp = backup_ntc.NTC_beta;
  return &temp;
}
//=========================================================
static void set_NTC_res(uint32_t *val) {
  backup_ntc.NTC_res = *val;
}
static void * get_NTC_res() {
  temp = backup_ntc.NTC_res;
  return &temp;
}
//=========================================================
static void set_Pull_res(uint32_t *val) {
  backup_ntc.pull_res = *val;
}
static void * get_Pull_res() {
  temp = backup_ntc.pull_res;
  return &temp;
}
//=========================================================
static void set_Pull_mode(uint32_t *val) {
  backup_ntc.pullup = *val;
}
static void * get_Pull_mode() {
  temp = backup_ntc.pullup;
  return &temp;
}
//=========================================================
static void set_NTC_detect(uint32_t *val) {
  backup_ntc.detection = *val;
  update_NTC_menu();
}
static void * get_NTC_detect() {
  temp = backup_ntc.detection;
  return &temp;
}
//=========================================================
static void set_NTC_detect_high_res(uint32_t *val) {
  backup_ntc.high_NTC_res = *val;
}
static void * get_NTC_detect_high_res() {
  temp = backup_ntc.high_NTC_res;
  return &temp;
}
//=========================================================
static void set_NTC_detect_low_res(uint32_t *val) {
  backup_ntc.low_NTC_res = *val;
}
static void * get_NTC_detect_low_res() {
  temp = backup_ntc.low_NTC_res;
  return &temp;
}
//=========================================================
static void set_NTC_detect_high_res_beta(uint32_t *val) {
  backup_ntc.high_NTC_beta = *val;
}
static void * get_NTC_detect_high_res_beta() {
  temp = backup_ntc.high_NTC_beta;
  return &temp;
}
//=========================================================
static void set_NTC_detect_low_res_beta(uint32_t *val) {
  backup_ntc.low_NTC_beta = *val;
}
static void * get_NTC_detect_low_res_beta() {
  temp = backup_ntc.low_NTC_beta;
  return &temp;
}
//=========================================================
static int saveNTC(widget_t *w, RE_Rotation_t input) {
  uint32_t _irq = __get_PRIMASK();
  __disable_irq();
  getProfileSettings()->ntc = backup_ntc;
  detectNTC();

  __set_PRIMASK(_irq);
  return last_scr;
}
//=========================================================

static void iron_ntc_onEnter(screen_t *scr){
  comboResetIndex(Screen_iron_ntc.current_widget);
  backup_ntc = getProfileSettings()->ntc;
  update_NTC_menu();
}

static void iron_ntc_create(screen_t *scr){
  widget_t* w;
  displayOnly_widget_t* dis;
  editable_widget_t* edit;

  //  [ SYSTEM COMBO ]
  //
  newWidget(&w,widget_combo,scr,NULL);

  //  [ NTC enabled Widget ]
  //
  newComboMultiOption(w, strings[lang].NTC_Enable_NTC,&edit, NULL);
  dis=&edit->inputData;
  dis->reservedChars=3;
  dis->getData = &get_enable_NTC;
  edit->big_step = 1;
  edit->step = 1;
  edit->setData = (setterFn)&set_enable_NTC;
  edit->options = strings[lang].OffOn;
  edit->numberOfOptions = 2;

  //  [ Pullup mode Widget ]
  //
  newComboMultiOption(w, strings[lang].NTC_Pull,&edit, &comboitem_PullMode);
  dis=&edit->inputData;
  dis->reservedChars=4;
  dis->getData = &get_Pull_mode;
  edit->big_step = 1;
  edit->step = 1;
  edit->setData = (setterFn)&set_Pull_mode;
  edit->options = strings[lang].DownUp;
  edit->numberOfOptions = 2;

  //  [ Pull res Widget ]
  //
  newComboEditable(w, strings[lang].NTC__Res, &edit, &comboitem_PullRes);
  dis=&edit->inputData;
  dis->number_of_dec=1;
  dis->reservedChars=7;
  dis->endString="KΩ";
  dis->getData = &get_Pull_res;
  edit->big_step = 10;
  edit->step = 1;
  edit->setData = (setterFn)&set_Pull_res;
  edit->max_value = 5000;
  edit->min_value = 1;

  //  [ Auto detect Widget ]
  //
  newComboMultiOption(w, strings[lang].NTC_NTC_Detect,&edit, &comboitem_AutoDetect);
  dis=&edit->inputData;
  dis->reservedChars=3;
  dis->getData = &get_NTC_detect;
  edit->big_step = 1;
  edit->step = 1;
  edit->setData = (setterFn)&set_NTC_detect;
  edit->options = strings[lang].OffOn;
  edit->numberOfOptions = 2;

  //  [ NTC auto higher Widget ]
  //
  newComboEditable(w, strings[lang].NTC__High, &edit, &comboitem_Detect_high_res);
  dis=&edit->inputData;
  dis->number_of_dec=1;
  dis->reservedChars=7;
  dis->endString="KΩ";
  dis->getData = &get_NTC_detect_high_res;
  edit->big_step = 10;
  edit->step = 1;
  edit->setData = (setterFn)&set_NTC_detect_high_res;
  edit->max_value = 5000;
  edit->min_value = 1;

  //  [ NTC auto higher beta Widget ]
  //
  newComboEditable(w, strings[lang].NTC__Beta, &edit, &comboitem_Detect_high_res_beta);
  dis=&edit->inputData;
  dis->reservedChars=5;
  dis->getData = &get_NTC_detect_high_res_beta;
  edit->big_step = 100;
  edit->step = 10;
  edit->setData = (setterFn)&set_NTC_detect_high_res_beta;
  edit->max_value = 50000;
  edit->min_value = 500;

  //  [ NTC auto lower Widget ]
  //
  newComboEditable(w, strings[lang].NTC__Low, &edit, &comboitem_Detect_low_res);
  dis=&edit->inputData;
  dis->number_of_dec=1;
  dis->reservedChars=7;
  dis->endString="KΩ";
  dis->getData = &get_NTC_detect_low_res;
  edit->big_step = 10;
  edit->step = 1;
  edit->setData = (setterFn)&set_NTC_detect_low_res;
  edit->max_value = 5000;
  edit->min_value = 1;

  //  [ NTC auto lower beta Widget ]
  //
  newComboEditable(w, strings[lang].NTC__Beta, &edit, &comboitem_Detect_low_res_beta);
  dis=&edit->inputData;
  dis->reservedChars=5;
  dis->getData = &get_NTC_detect_low_res_beta;
  edit->big_step = 100;
  edit->step = 10;
  edit->setData = (setterFn)&set_NTC_detect_low_res_beta;
  edit->max_value = 50000;
  edit->min_value = 500;

  //  [ NTC res Widget ]
  //
  newComboEditable(w, strings[lang].NTC__Res, &edit, &comboitem_NTC_res);
  dis=&edit->inputData;
  dis->number_of_dec=1;
  dis->reservedChars=7;
  dis->endString="KΩ";
  dis->getData = &get_NTC_res;
  edit->big_step = 10;
  edit->step = 1;
  edit->setData = (setterFn)&set_NTC_res;
  edit->max_value = 5000;
  edit->min_value = 1;

  //  [ NTC Beta Widget ]
  //
  newComboEditable(w, strings[lang].NTC__Beta, &edit, &comboitem_NTC_res_beta);
  dis=&edit->inputData;
  dis->reservedChars=5;
  dis->getData = &get_NTC_beta;
  edit->big_step = 100;
  edit->step = 10;
  edit->setData = (setterFn)&set_NTC_beta;
  edit->max_value = 50000;
  edit->min_value = 500;

  newComboAction(w, strings[lang]._SAVE, &saveNTC, NULL);
  newComboScreen(w, strings[lang]._BACK, last_scr , NULL);
}

#endif

static void iron_create(screen_t *scr){
  widget_t* w;
  displayOnly_widget_t* dis;
  editable_widget_t* edit;
  uint16_t maxTemp = (getSystemTempUnit()==mode_Celsius ? 480 : 900);

  //  [ IRON COMBO ]
  //
  newWidget(&w,widget_combo,scr,NULL);

  //  [ Profile Widget ]
  //
  newComboMultiOption(w, strings[lang].IRON_Profile, &edit, NULL);
  editable_IRON_Profile = edit;
  edit->inputData.getData = &getProfile;
  edit->big_step = 1;
  edit->step = 1;
  edit->setData = (void (*)(void *))&setProfile;
  edit->options = profileStr;
  edit->numberOfOptions = NUM_PROFILES;

  //  [ Max Temp Widget ]
  //
  newComboEditable(w, strings[lang].IRON_Max_Temp, &edit, NULL);
  editable_IRON_MaxTemp=edit;
  dis=&edit->inputData;
  dis->reservedChars=5;
  dis->getData = &getMaxTemp;
  edit->big_step = 10;
  edit->step = 5;
  edit->max_value = maxTemp;
  edit->setData = (setterFn)&setMaxTemp;

  //  [ Min Temp Widget ]
  //
  newComboEditable(w, strings[lang].IRON_Min_Temp, &edit, NULL);
  editable_IRON_MinTemp=edit;
  dis=&edit->inputData;
  dis->reservedChars=5;
  dis->getData = &getMinTemp;
  edit->big_step = 10;
  edit->step = 5;
  edit->max_value = maxTemp;
  edit->min_value = 50;
  edit->setData = (setterFn)&setMinTemp;

  //  [ Stby Time Widget ]
  //
  newComboEditable(w, strings[lang].IRON_Standby, &edit, NULL);
  dis=&edit->inputData;
  dis->endString="min";
  dis->reservedChars=5;
  dis->getData = &getStandbyTime;
  edit->big_step = 5;
  edit->step = 1;
  edit->setData = (setterFn)&setStandbyTime;
  edit->max_value = 60;

  //  [ Stby Temp Widget ]
  //
  newComboEditable(w, strings[lang].__Temp, &edit, NULL);
  editable_IRON_StandbyTemp = edit;
  dis=&edit->inputData;
  dis->reservedChars=5;
  dis->getData = &getStandbyTemp;
  edit->big_step = 10;
  edit->step = 5;
  edit->max_value = 350;
  edit->min_value = 50;
  edit->setData = (setterFn)&setStandbyTemp;

  //  [ Sleep Time Widget ]
  //
  newComboEditable(w, strings[lang].IRON_Sleep, &edit, NULL);
  dis=&edit->inputData;
  dis->endString="min";
  dis->reservedChars=5;
  dis->getData = &getSleepTime;
  edit->big_step = 5;
  edit->step = 1;
  edit->setData = (setterFn)&setSleepTime;
  edit->max_value = 60;
  edit->min_value = 1;

  //  [ Boost Time Widget ]
  //
  newComboEditable(w, strings[lang].IRON_Boost, &edit, NULL);
  dis=&edit->inputData;
  dis->endString="s";
  dis->reservedChars=5;
  dis->getData = &getBoostTime;
  edit->big_step = 30;
  edit->step = 5;
  edit->max_value = 600;
  edit->min_value = 30;
  edit->setData = (setterFn)&setBoostTime;

  //  [ Boost Temp Widget ]
  //
  newComboEditable(w, strings[lang].IRON_Boost_Add, &edit, NULL);
  editable_IRON_BoostTemp = edit;
  dis=&edit->inputData;
  dis->reservedChars=5;
  dis->getData = &getBoostTemp;
  edit->big_step = 10;
  edit->step = 5;
  edit->max_value = maxTemp/2;
  edit->min_value = 10;
  edit->setData = (setterFn)&setBoostTemp;

  //  [ Cold Boost Widget ]
  //
  newComboMultiOption(w, strings[lang].IRON_Cold_Boost,&edit, NULL);
  dis=&edit->inputData;
  dis->getData = &getColdBoost;
  edit->big_step = 1;
  edit->step = 1;
  edit->setData = (setterFn)&setColdBoost;
  edit->options = strings[lang].OffOn;
  edit->numberOfOptions = 2;

  //  [ Cold Boost Temp trigger Widget ]
  //
  newComboEditable(w, strings[lang].IRON_ColdBoost_Threshold, &edit, &comboItem_coldBoostTemp);
  editable_IRON_ColdBoostTemp = edit;
  dis=&edit->inputData;
  dis->reservedChars=5;
  dis->getData = &getColdBoostTemp;
  edit->big_step = 10;
  edit->step = 5;
  edit->max_value = maxTemp/2;
  edit->min_value = 50;
  edit->setData = (setterFn)&setColdBoostTemp;

  //  [ Cold boost Time Widget ]
  //
  newComboEditable(w, strings[lang].IRON_ColdBoost_Timeout, &edit, &comboItem_coldBoostTimeout);
  dis=&edit->inputData;
  dis->endString="s";
  dis->reservedChars=5;
  dis->getData = &getColdBoostTime;
  edit->big_step = 10;
  edit->step = 1;
  edit->max_value = 60;
  edit->min_value = 1;
  edit->setData = (setterFn)&setColdBoostTime;

  //  [ Wake mode Widget ]
  //
  newComboMultiOption(w, strings[lang].IRON_Wake_Mode, &edit, NULL);
  dis=&edit->inputData;
  dis->getData = &getWakeMode;
  edit->big_step = 1;
  edit->step = 1;
  edit->setData = (setterFn)&setWakeMode;
  edit->options = strings[lang].wakeMode;
  edit->numberOfOptions = 2;

  //  [ Shake filtering Widget ]
  //
  newComboMultiOption(w, strings[lang].IRON_Shake_Filtering, &edit, &comboitem_ShakeFiltering);
  dis=&edit->inputData;
  dis->getData = &getShakeFiltering;
  edit->big_step = 1;
  edit->step = 1;
  edit->setData = (setterFn)&setShakeFiltering;
  edit->options = strings[lang].OffOn;
  edit->numberOfOptions = 2;

  //  [ Stand mode Widget ]
  //
  newComboMultiOption(w, strings[lang].IRON_Stand_Mode, &edit, &comboitem_StandMode);
  dis=&edit->inputData;
  dis->getData = &getStandMode;
  edit->big_step = 1;
  edit->step = 1;
  edit->setData = (setterFn)&setStandMode;
  edit->options = strings[lang].InitMode;
  edit->numberOfOptions = 2;

  //  [ Stand delay Widget ]
  //
  newComboEditable(w, strings[lang].__Delay, &edit, &comboitem_StandDelay);
  dis=&edit->inputData;
  dis->endString="s";
  dis=&edit->inputData;
  dis->reservedChars=4;
  dis->getData = &getStandDelay;
  edit->big_step = 10;
  edit->step = 1;
  edit->setData = (setterFn)&setStandDelay;
  edit->max_value = 240;
  edit->min_value = 0;

  //  [ smartActive Enabled Widget ]
  //
  newComboMultiOption(w, strings[lang].IRON_smartActiveEnable,&edit, NULL);
  dis=&edit->inputData;
  dis->reservedChars=3;
  dis->getData = &getsmartActiveEnable;
  edit->big_step = 1;
  edit->step = 1;
  edit->setData = (setterFn)&setsmartActiveEnable;
  edit->options = strings[lang].OffOn;
  edit->numberOfOptions = 2;

  //  [ smartActive Load Widget ]
  //
  newComboEditable(w, strings[lang].IRON_smartActiveLoad, &edit, &comboitem_smartActiveLoad);
  dis=&edit->inputData;
  dis->reservedChars=4;
  dis->getData = &getsmartActiveLoad;
  edit->big_step = 10;
  edit->step = 1;
  edit->max_value = 500;
  edit->min_value = 1;
  edit->setData = (setterFn)&setsmartActiveLoad;
#ifdef USE_VIN
  //  [ Power Widget ]
  //
  newComboEditable(w, strings[lang].IRON_Power, &edit, NULL);
  dis=&edit->inputData;
  dis->reservedChars=4;
  dis->endString="W";
  dis->getData = &getMaxPower;
  edit->big_step = 20;
  edit->step = 5;
  edit->setData = (setterFn)&setMaxPower;
  edit->max_value = 500;
  edit->min_value = 5;

  //  [ Impedance Widget ]
  //
  newComboEditable(w, strings[lang].IRON_Heater, &edit, NULL);
  dis=&edit->inputData;
  dis->reservedChars=6;
  dis->number_of_dec=1;
  dis->endString="Ω";                                   // Unicode, needs 2 bytes. So "10.0Ω" string uses 6 bytes
  dis->getData = &getTipImpedance;
  edit->big_step = 10;
  edit->step = 1;
  edit->setData = (setterFn)&setTipImpedance;
  edit->max_value = 160;
  edit->min_value = 10;
#endif

  //  [ Read Period Widget ]
  //
  newComboEditable(w, strings[lang].IRON_ADC_Time, &edit, NULL);
  dis=&edit->inputData;
  dis->endString="ms";
  dis->reservedChars=7;
  dis->number_of_dec = 0;
  dis->getData = &_getReadPeriod;
  edit->big_step = 10;
  edit->step = 1;
  edit->setData = (setterFn)&_setReadPeriod;
  edit->max_value = 200;
  edit->min_value = 10;

  //  [ Read Delay Widget ]
  //
  newComboEditable(w, strings[lang].__Delay, &edit, NULL);
  dis=&edit->inputData;
  dis->endString="ms";
  dis->reservedChars=7;
  dis->number_of_dec = 1;
  dis->getData = &_getReadDelay;
  edit->big_step = 10;
  edit->step = 1;
  edit->setData = (setterFn)&_setReadDelay;
  edit->max_value = 900;
  edit->min_value = 1;

  //  [ PWM Mult Widget ]
  //
  newComboEditable(w, strings[lang].IRON_PWM_mul, &edit, NULL);
  dis=&edit->inputData;
  dis->endString="x";
  dis->reservedChars=7;
  dis->number_of_dec = 0;
  dis->getData = &_getPwmMul;
  edit->big_step = 5;
  edit->step = 1;
  edit->setData = (setterFn)&_setPwmMul;
  edit->max_value = 20;
  edit->min_value = 1;

  //  [ ADC Limit Widget ]
  //
  newComboEditable(w, strings[lang].IRON_No_Iron, &edit, NULL);
  dis=&edit->inputData;
  dis->reservedChars=4;
  dis->getData = &getNoIronADC;
  edit->big_step = 50;
  edit->step = 10;
  edit->setData = (setterFn)&setNoIronADC;
  edit->max_value = 4100;
  edit->min_value = 200;

  //  [ Error Delay Widget ]
  //
  newComboEditable(w, strings[lang].IRON_Error_Timeout, &edit, NULL);
  dis=&edit->inputData;
  dis->endString="s";
  dis->reservedChars=5;
  dis->number_of_dec = 1;
  dis->getData = &geterrorDelay;
  edit->big_step = 5;
  edit->step = 1;
  edit->setData = (setterFn)&seterrorDelay;
  edit->max_value = 250;
  edit->min_value = 1;

  //  [ Error resume mode Widget ]
  //
  newComboMultiOption(w, strings[lang].IRON_Error_Resume_Mode, &edit, NULL);
  dis=&edit->inputData;
  dis->getData = &geterrorResume;
  edit->big_step = 1;
  edit->step = 1;
  edit->setData = (setterFn)&seterrorResume;
  edit->options = strings[lang].errMode;
  edit->numberOfOptions = 3;

  //  [ Filter screen ]
  //
  newComboScreen(w, strings[lang].IRON_FILTER_MENU, screen_iron_advFilter, &comboItem_advFilter);

  #ifdef USE_NTC
  //  [ NTC screen ]
  //
  newComboScreen(w, strings[lang].IRON_NTC_MENU, screen_iron_ntc, NULL);
  #endif

  //  [ BACK button ]
  //
  newComboScreen(w, strings[lang]._BACK, screen_settings, NULL);

  updateTempValues();
  update_Iron_menu();
}

static void iron_advFilter_onEnter(screen_t *scr){
  comboResetIndex(Screen_iron_advFilter.current_widget);
  bak_f = getProfileSettings()->tipFilter;
}
static void iron_advFilter_create(screen_t *scr){
  widget_t *w;
  displayOnly_widget_t *dis;
  editable_widget_t *edit;

  //  [ IRON COMBO ]
  //
  newWidget(&w,widget_combo,scr,NULL);

  //  [ Low noise filter Widget ]
  //
  newComboEditable(w, strings[lang].FILTER_Filter, &edit, NULL);
  dis=&edit->inputData;
  dis->reservedChars=4;
  dis->getData = &get_filter;
  dis->endString = "%";
  edit->big_step = 5;
  edit->step = 1;
  edit->setData = (setterFn)&set_filter;
  edit->max_value = 99;
  edit->min_value = 0;

  //  [ Threshold Widget ]
  //
  newComboEditable(w, strings[lang].FILTER__Threshold, &edit, NULL);
  dis=&edit->inputData;
  dis->reservedChars=3;
  dis->getData = &get_threshold;
  edit->big_step = 10;
  edit->step = 1;
  edit->setData = (setterFn)&set_threshold;
  edit->max_value = 500;
  edit->min_value = 10;

  //  [ Count limit widget]
  //
  newComboEditable(w, strings[lang].FILTER__Count_limit, &edit, NULL);
  dis=&edit->inputData;
  dis->reservedChars=3;
  dis->getData = &get_count_limit;
  edit->big_step = 5;
  edit->step = 1;
  edit->setData = (setterFn)&set_count_limit;
  edit->max_value = 100;
  edit->min_value = 0;

  //  [ Filter down steppping Widget ]
  //
  newComboEditable(w, strings[lang].FILTER__Step_down, &edit, NULL);
  dis=&edit->inputData;
  dis->reservedChars=4;
  dis->getData = &get_limit_step;
  dis->endString="%";
  edit->big_step = 5;
  edit->step = 1;
  edit->setData = (setterFn)&set_limit_step;
  edit->max_value = -1;
  edit->min_value = -20;

  //  [ Min Filtering Widget ]
  //
  newComboEditable(w, strings[lang].FILTER__Min, &edit, NULL);
  dis=&edit->inputData;
  dis->reservedChars=4;
  dis->getData = &get_min_filter;
  dis->endString="%";
  edit->big_step = 5;
  edit->step = 1;
  edit->setData = (setterFn)&set_min_filter;
  edit->max_value = 99;
  edit->min_value = 0;

  //  [ Reset threshold Widget ]
  //
  newComboEditable(w, strings[lang].FILTER_Reset_limit, &edit, NULL);
  dis=&edit->inputData;
  dis->reservedChars=4;
  dis->getData = &get_reset_threshold;
  edit->big_step = 20;
  edit->step = 5;
  edit->setData = (setterFn)&set_reset_threshold;
  edit->max_value = 1000;
  edit->min_value = 10;

  newComboAction(w, strings[lang]._SAVE, &filter_Save , NULL);
  newComboScreen(w, strings[lang]._CANCEL, last_scr, NULL);
}

void iron_screen_setup(screen_t *scr){
  scr->onEnter = &iron_onEnter;
  scr->processInput = &autoReturn_ProcessInput;
  scr->create = &iron_create;
  scr->onExit = &iron_onExit;

  scr = &Screen_iron_advFilter;
  oled_addScreen(scr, screen_iron_advFilter);
  scr->onEnter = &iron_advFilter_onEnter;
  scr->onExit = &iron_onExit;
  scr->processInput = &autoReturn_ProcessInput;
  scr->create = &iron_advFilter_create;

  #ifdef USE_NTC
  scr=&Screen_iron_ntc;
  oled_addScreen(scr, screen_iron_ntc);
  scr->onEnter = &iron_ntc_onEnter;
  scr->onExit = &iron_onExit;
  scr->processInput=&autoReturn_ProcessInput;
  scr->create = &iron_ntc_create;
  #endif

}

void updateTempValues()
{
  editable_IRON_MinTemp->max_value = getProfileSettings()->MaxSetTemperature - 1;
  editable_IRON_MaxTemp->min_value = getProfileSettings()->MinSetTemperature + 1;
}

