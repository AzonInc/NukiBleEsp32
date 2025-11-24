/**
 * @file NukiUtills.cpp
 * Implementation of generic/helper functions
 *
 * Created on: 2022
 * License: GNU GENERAL PUBLIC LICENSE (see LICENSE)
 *
 * This library implements the communication from an ESP32 via BLE to a Nuki smart lock.
 * Based on the Nuki Smart Lock API V2.2.1
 * https://developer.nuki.io/page/nuki-smart-lock-api-2/2/
 *
 */

#include "NukiOpenerUtils.h"

#include <bitset>
#include <list>
#include <cstdint>
#include <cstring>
#include <string>

#include "esp_log.h"


namespace NukiOpener {
  
void cmdResultToString(const CmdResult state, char* str) {
  switch (state) {
    case CmdResult::Success:
      strcpy(str, "success");
      break;
    case CmdResult::Failed:
      strcpy(str, "failed");
      break;
    case CmdResult::TimeOut:
      strcpy(str, "timeOut");
      break;
    case CmdResult::Working:
      strcpy(str, "working");
      break;
    case CmdResult::NotPaired:
      strcpy(str, "notPaired");
      break;
    case CmdResult::Error:
      strcpy(str, "error");
      break;
    default:
      strcpy(str, "undefined");
      break;
  }
}

void logOpenerErrorCode(uint8_t errorCode, bool debug) {

  switch (errorCode) {
    case (uint8_t)ErrorCode::ERROR_BAD_CRC :
      ESP_LOGE("NukiBle.NukiOpener", "ERROR_BAD_CRC");
      break;
    case (uint8_t)ErrorCode::ERROR_BAD_LENGTH :
      ESP_LOGE("NukiBle.NukiOpener", "ERROR_BAD_LENGTH");
      break;
    case (uint8_t)ErrorCode::ERROR_UNKNOWN :
      ESP_LOGE("NukiBle.NukiOpener", "ERROR_UNKNOWN");
      break;
    case (uint8_t)ErrorCode::P_ERROR_NOT_PAIRING :
      ESP_LOGE("NukiBle.NukiOpener", "P_ERROR_NOT_PAIRING");
      break;
    case (uint8_t)ErrorCode::P_ERROR_BAD_AUTHENTICATOR :
      ESP_LOGE("NukiBle.NukiOpener", "P_ERROR_BAD_AUTHENTICATOR");
      break;
    case (uint8_t)ErrorCode::P_ERROR_BAD_PARAMETER :
      ESP_LOGE("NukiBle.NukiOpener", "P_ERROR_BAD_PARAMETER");
      break;
    case (uint8_t)ErrorCode::P_ERROR_MAX_USER :
      ESP_LOGE("NukiBle.NukiOpener", "P_ERROR_MAX_USER");
      break;
    case (uint8_t)ErrorCode::K_ERROR_AUTO_UNLOCK_TOO_RECENT :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_AUTO_UNLOCK_TOO_RECENT");
      break;
    case (uint8_t)ErrorCode::K_ERROR_BAD_NONCE :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_BAD_NONCE");
      break;
    case (uint8_t)ErrorCode::K_ERROR_BAD_PARAMETER :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_BAD_PARAMETER");
      break;
    case (uint8_t)ErrorCode::K_ERROR_BAD_PIN :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_BAD_PIN");
      break;
    case (uint8_t)ErrorCode::K_ERROR_BUSY :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_BUSY");
      break;
    case (uint8_t)ErrorCode::K_ERROR_CANCELED :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_CANCELED");
      break;
    case (uint8_t)ErrorCode::K_ERROR_CLUTCH_FAILURE :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_CLUTCH_FAILURE");
      break;
    case (uint8_t)ErrorCode::K_ERROR_CLUTCH_POWER_FAILURE :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_CLUTCH_POWER_FAILURE");
      break;
    case (uint8_t)ErrorCode::K_ERROR_CODE_ALREADY_EXISTS :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_CODE_ALREADY_EXISTS");
      break;
    case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_CODE_INVALID");
      break;
    case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID_TIMEOUT_1 :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_CODE_INVALID_TIMEOUT_1");
      break;
    case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID_TIMEOUT_2 :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_CODE_INVALID_TIMEOUT_2");
      break;
    case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID_TIMEOUT_3 :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_CODE_INVALID_TIMEOUT_3");
      break;
    case (uint8_t)ErrorCode::K_ERROR_DISABLED :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_DISABLED");
      break;
    case (uint8_t)ErrorCode::K_ERROR_FIRMWARE_UPDATE_NEEDED :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_FIRMWARE_UPDATE_NEEDED");
      break;
    case (uint8_t)ErrorCode::K_ERROR_INVALID_AUTH_ID :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_INVALID_AUTH_ID");
      break;
    case (uint8_t)ErrorCode::K_ERROR_MOTOR_BLOCKED :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_MOTOR_BLOCKED");
      break;
    case (uint8_t)ErrorCode::K_ERROR_MOTOR_LOW_VOLTAGE :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_MOTOR_LOW_VOLTAGE");
      break;
    case (uint8_t)ErrorCode::K_ERROR_MOTOR_POSITION_LIMIT :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_MOTOR_POSITION_LIMIT");
      break;
    case (uint8_t)ErrorCode::K_ERROR_MOTOR_POWER_FAILURE :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_MOTOR_POWER_FAILURE");
      break;
    case (uint8_t)ErrorCode::K_ERROR_MOTOR_TIMEOUT :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_MOTOR_TIMEOUT");
      break;
    case (uint8_t)ErrorCode::K_ERROR_NOT_AUTHORIZED :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_NOT_AUTHORIZED");
      break;
    case (uint8_t)ErrorCode::K_ERROR_NOT_CALIBRATED :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_NOT_CALIBRATED");
      break;
    case (uint8_t)ErrorCode::K_ERROR_POSITION_UNKNOWN :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_POSITION_UNKNOWN");
      break;
    case (uint8_t)ErrorCode::K_ERROR_REMOTE_NOT_ALLOWED :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_REMOTE_NOT_ALLOWED");
      break;
    case (uint8_t)ErrorCode::K_ERROR_TIME_NOT_ALLOWED :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_TIME_NOT_ALLOWED");
      break;
    case (uint8_t)ErrorCode::K_ERROR_TOO_MANY_ENTRIES :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_TOO_MANY_ENTRIES");
      break;
    case (uint8_t)ErrorCode::K_ERROR_TOO_MANY_PIN_ATTEMPTS :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_TOO_MANY_PIN_ATTEMPTS");
      break;
    case (uint8_t)ErrorCode::K_ERROR_VOLTAGE_TOO_LOW :
      ESP_LOGE("NukiBle.NukiOpener", "K_ERROR_VOLTAGE_TOO_LOW");
      break;
    default:
      ESP_LOGE("NukiBle.NukiOpener", "UNDEFINED ERROR");
  }
}

void logConfig(Config config, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "nukiId :%d", (unsigned int)config.nukiId);
    ESP_LOGI("NukiBle.NukiOpener", "name :%s", (const char*)config.name);
    ESP_LOGI("NukiBle.NukiOpener", "capabilities :%d", (unsigned int)config.capabilities);
    ESP_LOGI("NukiBle.NukiOpener", "latitude :%f", (const float)config.latitude);
    ESP_LOGI("NukiBle.NukiOpener", "longitude :%f", (const float)config.longitude);
    ESP_LOGI("NukiBle.NukiOpener", "pairingEnabled :%d", (unsigned int)config.pairingEnabled);
    ESP_LOGI("NukiBle.NukiOpener", "buttonEnabled :%d", (unsigned int)config.buttonEnabled);
    ESP_LOGI("NukiBle.NukiOpener", "currentTime Year :%d", (unsigned int)config.currentTimeYear);
    ESP_LOGI("NukiBle.NukiOpener", "currentTime Month :%d", (unsigned int)config.currentTimeMonth);
    ESP_LOGI("NukiBle.NukiOpener", "currentTime Day :%d", (unsigned int)config.currentTimeDay);
    ESP_LOGI("NukiBle.NukiOpener", "currentTime Hour :%d", (unsigned int)config.currentTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "currentTime Minute :%d", (unsigned int)config.currentTimeMinute);
    ESP_LOGI("NukiBle.NukiOpener", "currentTime Second :%d", (unsigned int)config.currentTimeSecond);
    ESP_LOGI("NukiBle.NukiOpener", "timeZoneOffset :%d", (unsigned int)config.timeZoneOffset);
    ESP_LOGI("NukiBle.NukiOpener", "dstMode :%d", (unsigned int)config.dstMode);
    ESP_LOGI("NukiBle.NukiOpener", "hasFob :%d", (unsigned int)config.hasFob);
    ESP_LOGI("NukiBle.NukiOpener", "fobAction1 :%d", (unsigned int)config.fobAction1);
    ESP_LOGI("NukiBle.NukiOpener", "fobAction2 :%d", (unsigned int)config.fobAction2);
    ESP_LOGI("NukiBle.NukiOpener", "fobAction3 :%d", (unsigned int)config.fobAction3);
    ESP_LOGI("NukiBle.NukiOpener", "operatingMode :%d", (unsigned int)config.operatingMode);    
    ESP_LOGI("NukiBle.NukiOpener", "advertisingMode :%d", (unsigned int)config.advertisingMode);
    ESP_LOGI("NukiBle.NukiOpener", "hasKeypad :%d", (unsigned int)config.hasKeypad);
    ESP_LOGI("NukiBle.NukiOpener", "firmwareVersion :%d.%d.%d", config.firmwareVersion[0], config.firmwareVersion[1], config.firmwareVersion[2]);
    ESP_LOGI("NukiBle.NukiOpener", "hardwareRevision :%d.%d", config.hardwareRevision[0], config.hardwareRevision[1]);
    ESP_LOGI("NukiBle.NukiOpener", "timeZoneId :%d", (unsigned int)config.timeZoneId);
    ESP_LOGI("NukiBle.NukiOpener", "hasKeypadV2 :%d", (unsigned int)config.hasKeypadV2);
  }
}

void logNewConfig(NewConfig newConfig, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "name: %s", (const char*)newConfig.name);
    ESP_LOGI("NukiBle.NukiOpener", "latitude: %f", (const float)newConfig.latitude);
    ESP_LOGI("NukiBle.NukiOpener", "longitude: %f", (const float)newConfig.longitude);
    ESP_LOGI("NukiBle.NukiOpener", "pairingEnabled: %d", (unsigned int)newConfig.pairingEnabled);
    ESP_LOGI("NukiBle.NukiOpener", "buttonEnabled: %d", (unsigned int)newConfig.buttonEnabled);
    ESP_LOGI("NukiBle.NukiOpener", "timeZoneOffset: %d", (unsigned int)newConfig.timeZoneOffset);
    ESP_LOGI("NukiBle.NukiOpener", "dstMode: %d", (unsigned int)newConfig.dstMode);
    ESP_LOGI("NukiBle.NukiOpener", "fobAction1: %d", (unsigned int)newConfig.fobAction1);
    ESP_LOGI("NukiBle.NukiOpener", "fobAction2: %d", (unsigned int)newConfig.fobAction2);
    ESP_LOGI("NukiBle.NukiOpener", "fobAction3: %d", (unsigned int)newConfig.fobAction3);
    ESP_LOGI("NukiBle.NukiOpener", "advertisingMode: %d", (unsigned int)newConfig.advertisingMode);
    ESP_LOGI("NukiBle.NukiOpener", "timeZoneId: %d", (unsigned int)newConfig.timeZoneId);
  }
}

void logNewKeypadEntry(NewKeypadEntry newKeypadEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "code:%d", (unsigned int)newKeypadEntry.code);
    ESP_LOGI("NukiBle.NukiOpener", "name:%s", (const char*)newKeypadEntry.name);
    ESP_LOGI("NukiBle.NukiOpener", "timeLimited:%d", (unsigned int)newKeypadEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromYear:%d", (unsigned int)newKeypadEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMonth:%d", (unsigned int)newKeypadEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromDay:%d", (unsigned int)newKeypadEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromHour:%d", (unsigned int)newKeypadEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMin:%d", (unsigned int)newKeypadEntry.allowedFromMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromSec:%d", (unsigned int)newKeypadEntry.allowedFromSec);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilYear:%d", (unsigned int)newKeypadEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMonth:%d", (unsigned int)newKeypadEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilDay:%d", (unsigned int)newKeypadEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilHour:%d", (unsigned int)newKeypadEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMin:%d", (unsigned int)newKeypadEntry.allowedUntilMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilSec:%d", (unsigned int)newKeypadEntry.allowedUntilSec);
    ESP_LOGI("NukiBle.NukiOpener", "allowedWeekdays:%d", (unsigned int)newKeypadEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeHour:%d", (unsigned int)newKeypadEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeMin:%d", (unsigned int)newKeypadEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeHour:%d", (unsigned int)newKeypadEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeMin:%d", (unsigned int)newKeypadEntry.allowedUntilTimeMin);
  }
}

void logKeypadEntry(KeypadEntry keypadEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "codeId:%d", (unsigned int)keypadEntry.codeId);
    ESP_LOGI("NukiBle.NukiOpener", "code:%d", (unsigned int)keypadEntry.code);
    ESP_LOGI("NukiBle.NukiOpener", "name:%s", (const char*)keypadEntry.name);
    ESP_LOGI("NukiBle.NukiOpener", "enabled:%d", (unsigned int)keypadEntry.enabled);
    ESP_LOGI("NukiBle.NukiOpener", "dateCreatedYear:%d", (unsigned int)keypadEntry.dateCreatedYear);
    ESP_LOGI("NukiBle.NukiOpener", "dateCreatedMonth:%d", (unsigned int)keypadEntry.dateCreatedMonth);
    ESP_LOGI("NukiBle.NukiOpener", "dateCreatedDay:%d", (unsigned int)keypadEntry.dateCreatedDay);
    ESP_LOGI("NukiBle.NukiOpener", "dateCreatedHour:%d", (unsigned int)keypadEntry.dateCreatedHour);
    ESP_LOGI("NukiBle.NukiOpener", "dateCreatedMin:%d", (unsigned int)keypadEntry.dateCreatedMin);
    ESP_LOGI("NukiBle.NukiOpener", "dateCreatedSec:%d", (unsigned int)keypadEntry.dateCreatedSec);
    ESP_LOGI("NukiBle.NukiOpener", "dateLastActiveYear:%d", (unsigned int)keypadEntry.dateLastActiveYear);
    ESP_LOGI("NukiBle.NukiOpener", "dateLastActiveMonth:%d", (unsigned int)keypadEntry.dateLastActiveMonth);
    ESP_LOGI("NukiBle.NukiOpener", "dateLastActiveDay:%d", (unsigned int)keypadEntry.dateLastActiveDay);
    ESP_LOGI("NukiBle.NukiOpener", "dateLastActiveHour:%d", (unsigned int)keypadEntry.dateLastActiveHour);
    ESP_LOGI("NukiBle.NukiOpener", "dateLastActiveMin:%d", (unsigned int)keypadEntry.dateLastActiveMin);
    ESP_LOGI("NukiBle.NukiOpener", "dateLastActiveSec:%d", (unsigned int)keypadEntry.dateLastActiveSec);
    ESP_LOGI("NukiBle.NukiOpener", "lockCount:%d", (unsigned int)keypadEntry.lockCount);
    ESP_LOGI("NukiBle.NukiOpener", "timeLimited:%d", (unsigned int)keypadEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromYear:%d", (unsigned int)keypadEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMonth:%d", (unsigned int)keypadEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromDay:%d", (unsigned int)keypadEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromHour:%d", (unsigned int)keypadEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMin:%d", (unsigned int)keypadEntry.allowedFromMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromSec:%d", (unsigned int)keypadEntry.allowedFromSec);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilYear:%d", (unsigned int)keypadEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMonth:%d", (unsigned int)keypadEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilDay:%d", (unsigned int)keypadEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilHour:%d", (unsigned int)keypadEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMin:%d", (unsigned int)keypadEntry.allowedUntilMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilSec:%d", (unsigned int)keypadEntry.allowedUntilSec);
    ESP_LOGI("NukiBle.NukiOpener", "allowedWeekdays:%d", (unsigned int)keypadEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeHour:%d", (unsigned int)keypadEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeMin:%d", (unsigned int)keypadEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeHour:%d", (unsigned int)keypadEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeMin:%d", (unsigned int)keypadEntry.allowedUntilTimeMin);
  }
}

void logUpdatedKeypadEntry(UpdatedKeypadEntry updatedKeypadEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "codeId:%d", (unsigned int)updatedKeypadEntry.codeId);
    ESP_LOGI("NukiBle.NukiOpener", "code:%d", (unsigned int)updatedKeypadEntry.code);
    ESP_LOGI("NukiBle.NukiOpener", "name:%s", (const char*)updatedKeypadEntry.name);
    ESP_LOGI("NukiBle.NukiOpener", "enabled:%d", (unsigned int)updatedKeypadEntry.enabled);
    ESP_LOGI("NukiBle.NukiOpener", "timeLimited:%d", (unsigned int)updatedKeypadEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromYear:%d", (unsigned int)updatedKeypadEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMonth:%d", (unsigned int)updatedKeypadEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromDay:%d", (unsigned int)updatedKeypadEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromHour:%d", (unsigned int)updatedKeypadEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMin:%d", (unsigned int)updatedKeypadEntry.allowedFromMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromSec:%d", (unsigned int)updatedKeypadEntry.allowedFromSec);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilYear:%d", (unsigned int)updatedKeypadEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMonth:%d", (unsigned int)updatedKeypadEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilDay:%d", (unsigned int)updatedKeypadEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilHour:%d", (unsigned int)updatedKeypadEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMin:%d", (unsigned int)updatedKeypadEntry.allowedUntilMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilSec:%d", (unsigned int)updatedKeypadEntry.allowedUntilSec);
    ESP_LOGI("NukiBle.NukiOpener", "allowedWeekdays:%d", (unsigned int)updatedKeypadEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeHour:%d", (unsigned int)updatedKeypadEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeMin:%d", (unsigned int)updatedKeypadEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeHour:%d", (unsigned int)updatedKeypadEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeMin:%d", (unsigned int)updatedKeypadEntry.allowedUntilTimeMin);
  }
}

void logAuthorizationEntry(AuthorizationEntry authorizationEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "id:%d", (unsigned int)authorizationEntry.authId);
    ESP_LOGI("NukiBle.NukiOpener", "idType:%d", (unsigned int)authorizationEntry.idType);
    ESP_LOGI("NukiBle.NukiOpener", "name:%s", (const char*)authorizationEntry.name);
    ESP_LOGI("NukiBle.NukiOpener", "enabled:%d", (unsigned int)authorizationEntry.enabled);
    ESP_LOGI("NukiBle.NukiOpener", "remoteAllowed:%d", (unsigned int)authorizationEntry.remoteAllowed);
    ESP_LOGI("NukiBle.NukiOpener", "createdYear:%d", (unsigned int)authorizationEntry.createdYear);
    ESP_LOGI("NukiBle.NukiOpener", "createdMonth:%d", (unsigned int)authorizationEntry.createdMonth);
    ESP_LOGI("NukiBle.NukiOpener", "createdDay:%d", (unsigned int)authorizationEntry.createdDay);
    ESP_LOGI("NukiBle.NukiOpener", "createdHour:%d", (unsigned int)authorizationEntry.createdHour);
    ESP_LOGI("NukiBle.NukiOpener", "createdMin:%d", (unsigned int)authorizationEntry.createdMinute);
    ESP_LOGI("NukiBle.NukiOpener", "createdSec:%d", (unsigned int)authorizationEntry.createdSecond);
    ESP_LOGI("NukiBle.NukiOpener", "lastactYear:%d", (unsigned int)authorizationEntry.lastActYear);
    ESP_LOGI("NukiBle.NukiOpener", "lastactMonth:%d", (unsigned int)authorizationEntry.lastActMonth);
    ESP_LOGI("NukiBle.NukiOpener", "lastactDay:%d", (unsigned int)authorizationEntry.lastActDay);
    ESP_LOGI("NukiBle.NukiOpener", "lastactHour:%d", (unsigned int)authorizationEntry.lastActHour);
    ESP_LOGI("NukiBle.NukiOpener", "lastactMin:%d", (unsigned int)authorizationEntry.lastActMinute);
    ESP_LOGI("NukiBle.NukiOpener", "lastactSec:%d", (unsigned int)authorizationEntry.lastActSecond);
    ESP_LOGI("NukiBle.NukiOpener", "lockCount:%d", (unsigned int)authorizationEntry.lockCount);
    ESP_LOGI("NukiBle.NukiOpener", "timeLimited:%d", (unsigned int)authorizationEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromYear:%d", (unsigned int)authorizationEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMonth:%d", (unsigned int)authorizationEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromDay:%d", (unsigned int)authorizationEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromHour:%d", (unsigned int)authorizationEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMin:%d", (unsigned int)authorizationEntry.allowedFromMinute);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromSec:%d", (unsigned int)authorizationEntry.allowedFromSecond);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilYear:%d", (unsigned int)authorizationEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMonth:%d", (unsigned int)authorizationEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilDay:%d", (unsigned int)authorizationEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilHour:%d", (unsigned int)authorizationEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMin:%d", (unsigned int)authorizationEntry.allowedUntilMinute);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilSec:%d", (unsigned int)authorizationEntry.allowedUntilSecond);
    ESP_LOGI("NukiBle.NukiOpener", "allowedWeekdays:%d", (unsigned int)authorizationEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeHour:%d", (unsigned int)authorizationEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeMin:%d", (unsigned int)authorizationEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeHour:%d", (unsigned int)authorizationEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeMin:%d", (unsigned int)authorizationEntry.allowedUntilTimeMin);
  }
}

void logNewAuthorizationEntry(NewAuthorizationEntry newAuthorizationEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "name:%s", (const char*)newAuthorizationEntry.name);
    ESP_LOGI("NukiBle.NukiOpener", "idType:%d", (unsigned int)newAuthorizationEntry.idType);
    ESP_LOGI("NukiBle.NukiOpener", "remoteAllowed:%d", (unsigned int)newAuthorizationEntry.remoteAllowed);
    ESP_LOGI("NukiBle.NukiOpener", "timeLimited:%d", (unsigned int)newAuthorizationEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromYear:%d", (unsigned int)newAuthorizationEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMonth:%d", (unsigned int)newAuthorizationEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromDay:%d", (unsigned int)newAuthorizationEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromHour:%d", (unsigned int)newAuthorizationEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMin:%d", (unsigned int)newAuthorizationEntry.allowedFromMinute);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromSec:%d", (unsigned int)newAuthorizationEntry.allowedFromSecond);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilYear:%d", (unsigned int)newAuthorizationEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMonth:%d", (unsigned int)newAuthorizationEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilDay:%d", (unsigned int)newAuthorizationEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilHour:%d", (unsigned int)newAuthorizationEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMin:%d", (unsigned int)newAuthorizationEntry.allowedUntilMinute);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilSec:%d", (unsigned int)newAuthorizationEntry.allowedUntilSecond);
    ESP_LOGI("NukiBle.NukiOpener", "allowedWeekdays:%d", (unsigned int)newAuthorizationEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeHour:%d", (unsigned int)newAuthorizationEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeMin:%d", (unsigned int)newAuthorizationEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeHour:%d", (unsigned int)newAuthorizationEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeMin:%d", (unsigned int)newAuthorizationEntry.allowedUntilTimeMin);
  }
}

void logUpdatedAuthorizationEntry(UpdatedAuthorizationEntry updatedAuthorizationEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "id:%d", (unsigned int)updatedAuthorizationEntry.authId);
    ESP_LOGI("NukiBle.NukiOpener", "name:%s", (const char*)updatedAuthorizationEntry.name);
    ESP_LOGI("NukiBle.NukiOpener", "enabled:%d", (unsigned int)updatedAuthorizationEntry.enabled);
    ESP_LOGI("NukiBle.NukiOpener", "remoteAllowed:%d", (unsigned int)updatedAuthorizationEntry.remoteAllowed);
    ESP_LOGI("NukiBle.NukiOpener", "timeLimited:%d", (unsigned int)updatedAuthorizationEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromYear:%d", (unsigned int)updatedAuthorizationEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMonth:%d", (unsigned int)updatedAuthorizationEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromDay:%d", (unsigned int)updatedAuthorizationEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromHour:%d", (unsigned int)updatedAuthorizationEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromMin:%d", (unsigned int)updatedAuthorizationEntry.allowedFromMinute);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromSec:%d", (unsigned int)updatedAuthorizationEntry.allowedFromSecond);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilYear:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMonth:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilDay:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilHour:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilMin:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilMinute);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilSec:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilSecond);
    ESP_LOGI("NukiBle.NukiOpener", "allowedWeekdays:%d", (unsigned int)updatedAuthorizationEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeHour:%d", (unsigned int)updatedAuthorizationEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedFromTimeMin:%d", (unsigned int)updatedAuthorizationEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeHour:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "allowedUntilTimeMin:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilTimeMin);
  }
}

void logNewTimeControlEntry(NewTimeControlEntry newTimeControlEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "weekdays:%d", (unsigned int)newTimeControlEntry.weekdays);
    ESP_LOGI("NukiBle.NukiOpener", "time:%d:%d", (unsigned int)newTimeControlEntry.timeHour, newTimeControlEntry.timeMin);
    ESP_LOGI("NukiBle.NukiOpener", "lockAction:%d", (unsigned int)newTimeControlEntry.lockAction);
  }
}

void logTimeControlEntry(TimeControlEntry timeControlEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "entryId:%d", (unsigned int)timeControlEntry.entryId);
    ESP_LOGI("NukiBle.NukiOpener", "enabled:%d", (unsigned int)timeControlEntry.enabled);
    ESP_LOGI("NukiBle.NukiOpener", "weekdays:%d", (unsigned int)timeControlEntry.weekdays);
    ESP_LOGI("NukiBle.NukiOpener", "time:%d:%d", (unsigned int)timeControlEntry.timeHour, timeControlEntry.timeMin);
    ESP_LOGI("NukiBle.NukiOpener", "lockAction:%d", (unsigned int)timeControlEntry.lockAction);
  }
}

void logCompletionStatus(CompletionStatus completionStatus, bool debug) {
  switch (completionStatus) {
    case CompletionStatus::Busy :
      ESP_LOGI("NukiBle.NukiOpener", "Completion status: busy");
      break;
    case CompletionStatus::Incomplete :
      ESP_LOGI("NukiBle.NukiOpener", "Completion status: incomplete");
      break;
    case CompletionStatus::Canceled :
      ESP_LOGI("NukiBle.NukiOpener", "Completion status: canceled");
      break;
    case CompletionStatus::OtherError :
      ESP_LOGI("NukiBle.NukiOpener", "Completion status: otherError");
      break;
    case CompletionStatus::Success :
      ESP_LOGI("NukiBle.NukiOpener", "Completion status: success");
      break;
    case CompletionStatus::TooRecent :
      ESP_LOGI("NukiBle.NukiOpener", "Completion status: tooRecent");
      break;
    default:
      ESP_LOGW("NukiBle.NukiOpener", "Completion status: unknown");
      break;
  }
}

void logNukiTrigger(Trigger nukiTrigger, bool debug) {
  switch (nukiTrigger) {
    case Trigger::Automatic :
      ESP_LOGI("NukiBle.NukiOpener", "Trigger: automatic");
      break;
    case Trigger::Button :
      ESP_LOGI("NukiBle.NukiOpener", "Trigger: button");
      break;
    case Trigger::Manual :
      ESP_LOGI("NukiBle.NukiOpener", "Trigger: manual");
      break;
    case Trigger::System :
      ESP_LOGI("NukiBle.NukiOpener", "Trigger: system");
      break;
    default:
      ESP_LOGW("NukiBle.NukiOpener", "Trigger: unknown");
      break;
  }
}

void logLockAction(LockAction lockAction, bool debug) {
  switch (lockAction) {
    case LockAction::ActivateRTO :
      ESP_LOGI("NukiBle.NukiOpener", "action: ActivateRTO");
      break;
    case LockAction::DeactivateRTO :
      ESP_LOGI("NukiBle.NukiOpener", "action: DeactivateRTO");
      break;
    case LockAction::ElectricStrikeActuation :
      ESP_LOGI("NukiBle.NukiOpener", "action: ElectricStrikeActuation");
      break;
    case LockAction::ActivateCM :
      ESP_LOGI("NukiBle.NukiOpener", "action: ActivateCM");
      break;
    case LockAction::DeactivateCM :
      ESP_LOGI("NukiBle.NukiOpener", "action: DeactivateCM");
      break;
    case LockAction::FobAction1 :
      ESP_LOGI("NukiBle.NukiOpener", "action: autoLock");
      break;
    case LockAction::FobAction2 :
      ESP_LOGI("NukiBle.NukiOpener", "action: automatic");
      break;
    case LockAction::FobAction3 :
      ESP_LOGI("NukiBle.NukiOpener", "action: button");
      break;
    default:
      ESP_LOGW("NukiBle.NukiOpener", "action: unknown");
      break;
  }
}


void logKeyturnerState(OpenerState keyTurnerState, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "nukiState: %02x", (unsigned int)keyTurnerState.nukiState);
    ESP_LOGI("NukiBle.NukiOpener", "lockState: %d", (unsigned int)keyTurnerState.lockState);
    logNukiTrigger(keyTurnerState.trigger, debug);
    ESP_LOGI("NukiBle.NukiOpener", "currentTimeYear: %d", (unsigned int)keyTurnerState.currentTimeYear);
    ESP_LOGI("NukiBle.NukiOpener", "currentTimeMonth: %d", (unsigned int)keyTurnerState.currentTimeMonth);
    ESP_LOGI("NukiBle.NukiOpener", "currentTimeDay: %d", (unsigned int)keyTurnerState.currentTimeDay);
    ESP_LOGI("NukiBle.NukiOpener", "currentTimeHour: %d", (unsigned int)keyTurnerState.currentTimeHour);
    ESP_LOGI("NukiBle.NukiOpener", "currentTimeMinute: %d", (unsigned int)keyTurnerState.currentTimeMinute);
    ESP_LOGI("NukiBle.NukiOpener", "currentTimeSecond: %d", (unsigned int)keyTurnerState.currentTimeSecond);
    ESP_LOGI("NukiBle.NukiOpener", "timeZoneOffset: %d", (unsigned int)keyTurnerState.timeZoneOffset);
    ESP_LOGI("NukiBle.NukiOpener", "criticalBatteryState composed value: %d", (unsigned int)keyTurnerState.criticalBatteryState);
    ESP_LOGI("NukiBle.NukiOpener", "configUpdateCount: %d", (unsigned int)keyTurnerState.configUpdateCount);
    logLockAction((LockAction)keyTurnerState.lastLockAction, debug);
    ESP_LOGI("NukiBle.NukiOpener", "lastLockActionTrigger: %d", (unsigned int)keyTurnerState.lastLockActionTrigger);
    logCompletionStatus(keyTurnerState.lastLockActionCompletionStatus, debug);
    ESP_LOGI("NukiBle.NukiOpener", "Keypad bat critical feature supported: %d", (unsigned int)(((unsigned int)keyTurnerState.accessoryBatteryState & 1) == 1 ? 1 : 0));
    ESP_LOGI("NukiBle.NukiOpener", "Keypad Battery Critical: %d", (unsigned int)(((unsigned int)keyTurnerState.accessoryBatteryState & 3) == 3 ? 1 : 0));  
    }
}

void logBatteryReport(BatteryReport batteryReport, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "batteryDrain:%d", (unsigned int)batteryReport.batteryDrain);
    ESP_LOGI("NukiBle.NukiOpener", "batteryVoltage:%d", (unsigned int)batteryReport.batteryVoltage);
    ESP_LOGI("NukiBle.NukiOpener", "criticalBatteryState:%d", (unsigned int)batteryReport.criticalBatteryState);
    ESP_LOGI("NukiBle.NukiOpener", "lockAction:%d", (unsigned int)batteryReport.lockAction);
    ESP_LOGI("NukiBle.NukiOpener", "startVoltage:%d", (unsigned int)batteryReport.startVoltage);
    ESP_LOGI("NukiBle.NukiOpener", "lowestVoltage:%d", (unsigned int)batteryReport.lowestVoltage);
    ESP_LOGI("NukiBle.NukiOpener", "lockDistance:%d", (unsigned int)batteryReport.lockDistance);
    ESP_LOGI("NukiBle.NukiOpener", "startTemperature:%d", (unsigned int)batteryReport.startTemperature);
    ESP_LOGI("NukiBle.NukiOpener", "maxTurnCurrent:%d", (unsigned int)batteryReport.maxTurnCurrent);
    ESP_LOGI("NukiBle.NukiOpener", "batteryResistance:%d", (unsigned int)batteryReport.batteryResistance);
  }
}

void logLogEntry(LogEntry logEntry, bool debug) {
  ESP_LOGI("NukiBle.NukiOpener", "[%lu] type: %u authId: %lu name: %s %d-%d-%d %d:%d:%d ", logEntry.index, (uint8_t)logEntry.loggingType, logEntry.authId, logEntry.name, logEntry.timeStampYear, logEntry.timeStampMonth, logEntry.timeStampDay, logEntry.timeStampHour, logEntry.timeStampMinute, logEntry.timeStampSecond);

  switch (logEntry.loggingType) {
    case LoggingType::LoggingEnabled: {
      ESP_LOGI("NukiBle.NukiOpener", "Logging enabled: %d", (unsigned int)logEntry.data[0]);
      break;
    }
    case LoggingType::LockAction:
    case LoggingType::Calibration:
    case LoggingType::KeypadAction: {
      logLockAction((LockAction)logEntry.data[0], debug);
      ESP_LOGI("NukiBle.NukiOpener", "Source: %d", (unsigned int)logEntry.data[1]);
      logCompletionStatus((CompletionStatus)logEntry.data[2], debug);
      uint16_t codeId = 0;
      memcpy(&codeId, &logEntry.data[3], 2);
      ESP_LOGI("NukiBle.NukiOpener", "Code id: %d", (unsigned int)codeId);
      break;
    }
    case LoggingType::DoorbellRecognition: {
      // TODO
      break;
    }
    default:
      ESP_LOGW("NukiBle.NukiOpener", "Unknown logging type");
      break;
  }
}

void logAdvancedConfig(AdvancedConfig advancedConfig, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "singleButtonPressAction :%d", (unsigned int)advancedConfig.singleButtonPressAction);
    ESP_LOGI("NukiBle.NukiOpener", "doubleButtonPressAction :%d", (unsigned int)(unsigned int)advancedConfig.doubleButtonPressAction);
    ESP_LOGI("NukiBle.NukiOpener", "batteryType :%d", (unsigned int)advancedConfig.batteryType);
    ESP_LOGI("NukiBle.NukiOpener", "automaticBatteryTypeDetection :%d", (unsigned int)advancedConfig.automaticBatteryTypeDetection);
  }
}

void logNewAdvancedConfig(NewAdvancedConfig newAdvancedConfig, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiOpener", "singleButtonPressAction :%d", (unsigned int)newAdvancedConfig.singleButtonPressAction);
    ESP_LOGI("NukiBle.NukiOpener", "doubleButtonPressAction :%d", (unsigned int)newAdvancedConfig.doubleButtonPressAction);
    ESP_LOGI("NukiBle.NukiOpener", "batteryType :%d", (unsigned int)newAdvancedConfig.batteryType);
    ESP_LOGI("NukiBle.NukiOpener", "automaticBatteryTypeDetection :%d", (unsigned int)newAdvancedConfig.automaticBatteryTypeDetection);
  }
}

} // namespace Nuki
