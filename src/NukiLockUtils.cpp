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

#include "NukiLockUtils.h"

#include "esp_log.h"
#include <cstring>
#include <cstdint>


namespace NukiLock {

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

  void logLockErrorCode(uint8_t errorCode, bool debug) {
    if (debug) {
      switch (errorCode) {
        case (uint8_t)ErrorCode::ERROR_BAD_CRC :
          ESP_LOGE("NukiLock", "ERROR_BAD_CRC");
          break;
        case (uint8_t)ErrorCode::ERROR_BAD_LENGTH :
          ESP_LOGE("NukiLock", "ERROR_BAD_LENGTH");
          break;
        case (uint8_t)ErrorCode::ERROR_UNKNOWN :
          ESP_LOGE("NukiLock", "ERROR_UNKNOWN");
          break;
        case (uint8_t)ErrorCode::P_ERROR_NOT_PAIRING :
          ESP_LOGE("NukiLock", "P_ERROR_NOT_PAIRING");
          break;
        case (uint8_t)ErrorCode::P_ERROR_BAD_AUTHENTICATOR :
          ESP_LOGE("NukiLock", "P_ERROR_BAD_AUTHENTICATOR");
          break;
        case (uint8_t)ErrorCode::P_ERROR_BAD_PARAMETER :
          ESP_LOGE("NukiLock", "P_ERROR_BAD_PARAMETER");
          break;
        case (uint8_t)ErrorCode::P_ERROR_MAX_USER :
          ESP_LOGE("NukiLock", "P_ERROR_MAX_USER");
          break;
        case (uint8_t)ErrorCode::K_ERROR_AUTO_UNLOCK_TOO_RECENT :
          ESP_LOGE("NukiLock", "K_ERROR_AUTO_UNLOCK_TOO_RECENT");
          break;
        case (uint8_t)ErrorCode::K_ERROR_BAD_NONCE :
          ESP_LOGE("NukiLock", "K_ERROR_BAD_NONCE");
          break;
        case (uint8_t)ErrorCode::K_ERROR_BAD_PARAMETER :
          ESP_LOGE("NukiLock", "K_ERROR_BAD_PARAMETER");
          break;
        case (uint8_t)ErrorCode::K_ERROR_BAD_PIN :
          ESP_LOGE("NukiLock", "K_ERROR_BAD_PIN");
          break;
        case (uint8_t)ErrorCode::K_ERROR_BUSY :
          ESP_LOGE("NukiLock", "K_ERROR_BUSY");
          break;
        case (uint8_t)ErrorCode::K_ERROR_CANCELED :
          ESP_LOGE("NukiLock", "K_ERROR_CANCELED");
          break;
        case (uint8_t)ErrorCode::K_ERROR_CLUTCH_FAILURE :
          ESP_LOGE("NukiLock", "K_ERROR_CLUTCH_FAILURE");
          break;
        case (uint8_t)ErrorCode::K_ERROR_CLUTCH_POWER_FAILURE :
          ESP_LOGE("NukiLock", "K_ERROR_CLUTCH_POWER_FAILURE");
          break;
        case (uint8_t)ErrorCode::K_ERROR_CODE_ALREADY_EXISTS :
          ESP_LOGE("NukiLock", "K_ERROR_CODE_ALREADY_EXISTS");
          break;
        case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID :
          ESP_LOGE("NukiLock", "K_ERROR_CODE_INVALID");
          break;
        case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID_TIMEOUT_1 :
          ESP_LOGE("NukiLock", "K_ERROR_CODE_INVALID_TIMEOUT_1");
          break;
        case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID_TIMEOUT_2 :
          ESP_LOGE("NukiLock", "K_ERROR_CODE_INVALID_TIMEOUT_2");
          break;
        case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID_TIMEOUT_3 :
          ESP_LOGE("NukiLock", "K_ERROR_CODE_INVALID_TIMEOUT_3");
          break;
        case (uint8_t)ErrorCode::K_ERROR_DISABLED :
          ESP_LOGE("NukiLock", "K_ERROR_DISABLED");
          break;
        case (uint8_t)ErrorCode::K_ERROR_FIRMWARE_UPDATE_NEEDED :
          ESP_LOGE("NukiLock", "K_ERROR_FIRMWARE_UPDATE_NEEDED");
          break;
        case (uint8_t)ErrorCode::K_ERROR_INVALID_AUTH_ID :
          ESP_LOGE("NukiLock", "K_ERROR_INVALID_AUTH_ID");
          break;
        case (uint8_t)ErrorCode::K_ERROR_MOTOR_BLOCKED :
          ESP_LOGE("NukiLock", "K_ERROR_MOTOR_BLOCKED");
          break;
        case (uint8_t)ErrorCode::K_ERROR_MOTOR_LOW_VOLTAGE :
          ESP_LOGE("NukiLock", "K_ERROR_MOTOR_LOW_VOLTAGE");
          break;
        case (uint8_t)ErrorCode::K_ERROR_MOTOR_POSITION_LIMIT :
          ESP_LOGE("NukiLock", "K_ERROR_MOTOR_POSITION_LIMIT");
          break;
        case (uint8_t)ErrorCode::K_ERROR_MOTOR_POWER_FAILURE :
          ESP_LOGE("NukiLock", "K_ERROR_MOTOR_POWER_FAILURE");
          break;
        case (uint8_t)ErrorCode::K_ERROR_MOTOR_TIMEOUT :
          ESP_LOGE("NukiLock", "K_ERROR_MOTOR_TIMEOUT");
          break;
        case (uint8_t)ErrorCode::K_ERROR_NOT_AUTHORIZED :
          ESP_LOGE("NukiLock", "K_ERROR_NOT_AUTHORIZED");
          break;
        case (uint8_t)ErrorCode::K_ERROR_NOT_CALIBRATED :
          ESP_LOGE("NukiLock", "K_ERROR_NOT_CALIBRATED");
          break;
        case (uint8_t)ErrorCode::K_ERROR_POSITION_UNKNOWN :
          ESP_LOGE("NukiLock", "K_ERROR_POSITION_UNKNOWN");
          break;
        case (uint8_t)ErrorCode::K_ERROR_REMOTE_NOT_ALLOWED :
          ESP_LOGE("NukiLock", "K_ERROR_REMOTE_NOT_ALLOWED");
          break;
        case (uint8_t)ErrorCode::K_ERROR_TIME_NOT_ALLOWED :
          ESP_LOGE("NukiLock", "K_ERROR_TIME_NOT_ALLOWED");
          break;
        case (uint8_t)ErrorCode::K_ERROR_TOO_MANY_ENTRIES :
          ESP_LOGE("NukiLock", "K_ERROR_TOO_MANY_ENTRIES");
          break;
        case (uint8_t)ErrorCode::K_ERROR_TOO_MANY_PIN_ATTEMPTS :
          ESP_LOGE("NukiLock", "K_ERROR_TOO_MANY_PIN_ATTEMPTS");
          break;
        case (uint8_t)ErrorCode::K_ERROR_VOLTAGE_TOO_LOW :
          ESP_LOGE("NukiLock", "K_ERROR_VOLTAGE_TOO_LOW");
          break;
        default:
          ESP_LOGE("NukiLock", "UNDEFINED ERROR");
      }
    }
  }

  void logConfig(Config config, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "nukiId :%d", (unsigned int)config.nukiId);
      ESP_LOGD("NukiLock", "name :%s", (const char*)config.name);
      ESP_LOGD("NukiLock", "latitude :%f", (const float)config.latitude);
      ESP_LOGD("NukiLock", "longitude :%f", (const float)config.longitude);
      ESP_LOGD("NukiLock", "autoUnlatch :%d", (unsigned int)config.autoUnlatch);
      ESP_LOGD("NukiLock", "pairingEnabled :%d", (unsigned int)config.pairingEnabled);
      ESP_LOGD("NukiLock", "buttonEnabled :%d", (unsigned int)config.buttonEnabled);
      ESP_LOGD("NukiLock", "ledEnabled :%d", (unsigned int)config.ledEnabled);
      ESP_LOGD("NukiLock", "ledBrightness :%d", (unsigned int)config.ledBrightness);
      ESP_LOGD("NukiLock", "currentTime Year :%d", (unsigned int)config.currentTimeYear);
      ESP_LOGD("NukiLock", "currentTime Month :%d", (unsigned int)config.currentTimeMonth);
      ESP_LOGD("NukiLock", "currentTime Day :%d", (unsigned int)config.currentTimeDay);
      ESP_LOGD("NukiLock", "currentTime Hour :%d", (unsigned int)config.currentTimeHour);
      ESP_LOGD("NukiLock", "currentTime Minute :%d", (unsigned int)config.currentTimeMinute);
      ESP_LOGD("NukiLock", "currentTime Second :%d", (unsigned int)config.currentTimeSecond);
      ESP_LOGD("NukiLock", "timeZoneOffset :%d", (unsigned int)config.timeZoneOffset);
      ESP_LOGD("NukiLock", "dstMode :%d", (unsigned int)config.dstMode);
      ESP_LOGD("NukiLock", "hasFob :%d", (unsigned int)config.hasFob);
      ESP_LOGD("NukiLock", "fobAction1 :%d", (unsigned int)config.fobAction1);
      ESP_LOGD("NukiLock", "fobAction2 :%d", (unsigned int)config.fobAction2);
      ESP_LOGD("NukiLock", "fobAction3 :%d", (unsigned int)config.fobAction3);
      ESP_LOGD("NukiLock", "singleLock :%d", (unsigned int)config.singleLock);
      ESP_LOGD("NukiLock", "advertisingMode :%d", (unsigned int)config.advertisingMode);
      ESP_LOGD("NukiLock", "hasKeypad :%d", (unsigned int)config.hasKeypad);
      ESP_LOGD("NukiLock", "firmwareVersion :%d.%d.%d", config.firmwareVersion[0], config.firmwareVersion[1], config.firmwareVersion[2]);
      ESP_LOGD("NukiLock", "hardwareRevision :%d.%d", config.hardwareRevision[0], config.hardwareRevision[1]);
      ESP_LOGD("NukiLock", "homeKitStatus :%d", (unsigned int)config.homeKitStatus);
      ESP_LOGD("NukiLock", "timeZoneId :%d", (unsigned int)config.timeZoneId);
      ESP_LOGD("NukiLock", "deviceType :%d", (unsigned int)config.deviceType);
      ESP_LOGD("NukiLock", "channel :%d", (unsigned int)config.network);
      ESP_LOGD("NukiLock", "wifiCapable :%d", (unsigned int)config.network & 1);
      ESP_LOGD("NukiLock", "threadCapable :%d", (unsigned int)(((unsigned int)config.network & 2) != 0 ? 1 : 0));
      ESP_LOGD("NukiLock", "hasKeypadV2 :%d", (unsigned int)config.hasKeypadV2);
      ESP_LOGD("NukiLock", "matterStatus :%d", (unsigned int)config.matterStatus);
      ESP_LOGD("NukiLock", "productVariant :%d", (unsigned int)config.productVariant);
    }
  }

  void logNewConfig(NewConfig newConfig, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "name :%s", (const char*)newConfig.name);
      ESP_LOGD("NukiLock", "latitude :%f", (const float)newConfig.latitude);
      ESP_LOGD("NukiLock", "longitude :%f", (const float)newConfig.longitude);
      ESP_LOGD("NukiLock", "autoUnlatch :%d", (unsigned int)newConfig.autoUnlatch);
      ESP_LOGD("NukiLock", "pairingEnabled :%d", (unsigned int)newConfig.pairingEnabled);
      ESP_LOGD("NukiLock", "buttonEnabled :%d", (unsigned int)newConfig.buttonEnabled);
      ESP_LOGD("NukiLock", "ledEnabled :%d", (unsigned int)newConfig.ledEnabled);
      ESP_LOGD("NukiLock", "ledBrightness :%d", (unsigned int)newConfig.ledBrightness);
      ESP_LOGD("NukiLock", "timeZoneOffset :%d", (unsigned int)newConfig.timeZoneOffset);
      ESP_LOGD("NukiLock", "dstMode :%d", (unsigned int)newConfig.dstMode);
      ESP_LOGD("NukiLock", "fobAction1 :%d", (unsigned int)newConfig.fobAction1);
      ESP_LOGD("NukiLock", "fobAction2 :%d", (unsigned int)newConfig.fobAction2);
      ESP_LOGD("NukiLock", "fobAction3 :%d", (unsigned int)newConfig.fobAction3);
      ESP_LOGD("NukiLock", "singleLock :%d", (unsigned int)newConfig.singleLock);
      ESP_LOGD("NukiLock", "advertisingMode :%d", (unsigned int)newConfig.advertisingMode);
      ESP_LOGD("NukiLock", "timeZoneId :%d", (unsigned int)newConfig.timeZoneId);
    }
  }

  void logNewKeypadEntry(NewKeypadEntry newKeypadEntry, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "code:%d", (unsigned int)newKeypadEntry.code);
      ESP_LOGD("NukiLock", "name:%s", (const char*)newKeypadEntry.name);
      ESP_LOGD("NukiLock", "timeLimited:%d", (unsigned int)newKeypadEntry.timeLimited);
      ESP_LOGD("NukiLock", "allowedFromYear:%d", (unsigned int)newKeypadEntry.allowedFromYear);
      ESP_LOGD("NukiLock", "allowedFromMonth:%d", (unsigned int)newKeypadEntry.allowedFromMonth);
      ESP_LOGD("NukiLock", "allowedFromDay:%d", (unsigned int)newKeypadEntry.allowedFromDay);
      ESP_LOGD("NukiLock", "allowedFromHour:%d", (unsigned int)newKeypadEntry.allowedFromHour);
      ESP_LOGD("NukiLock", "allowedFromMin:%d", (unsigned int)newKeypadEntry.allowedFromMin);
      ESP_LOGD("NukiLock", "allowedFromSec:%d", (unsigned int)newKeypadEntry.allowedFromSec);
      ESP_LOGD("NukiLock", "allowedUntilYear:%d", (unsigned int)newKeypadEntry.allowedUntilYear);
      ESP_LOGD("NukiLock", "allowedUntilMonth:%d", (unsigned int)newKeypadEntry.allowedUntilMonth);
      ESP_LOGD("NukiLock", "allowedUntilDay:%d", (unsigned int)newKeypadEntry.allowedUntilDay);
      ESP_LOGD("NukiLock", "allowedUntilHour:%d", (unsigned int)newKeypadEntry.allowedUntilHour);
      ESP_LOGD("NukiLock", "allowedUntilMin:%d", (unsigned int)newKeypadEntry.allowedUntilMin);
      ESP_LOGD("NukiLock", "allowedUntilSec:%d", (unsigned int)newKeypadEntry.allowedUntilSec);
      ESP_LOGD("NukiLock", "allowedWeekdays:%d", (unsigned int)newKeypadEntry.allowedWeekdays);
      ESP_LOGD("NukiLock", "allowedFromTimeHour:%d", (unsigned int)newKeypadEntry.allowedFromTimeHour);
      ESP_LOGD("NukiLock", "allowedFromTimeMin:%d", (unsigned int)newKeypadEntry.allowedFromTimeMin);
      ESP_LOGD("NukiLock", "allowedUntilTimeHour:%d", (unsigned int)newKeypadEntry.allowedUntilTimeHour);
      ESP_LOGD("NukiLock", "allowedUntilTimeMin:%d", (unsigned int)newKeypadEntry.allowedUntilTimeMin);
    }
  }

  void logKeypadEntry(KeypadEntry keypadEntry, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "codeId:%d", (unsigned int)keypadEntry.codeId);
      ESP_LOGD("NukiLock", "code:%d", (unsigned int)keypadEntry.code);
      ESP_LOGD("NukiLock", "name:%s", (const char*)keypadEntry.name);
      ESP_LOGD("NukiLock", "enabled:%d", (unsigned int)keypadEntry.enabled);
      ESP_LOGD("NukiLock", "dateCreatedYear:%d", (unsigned int)keypadEntry.dateCreatedYear);
      ESP_LOGD("NukiLock", "dateCreatedMonth:%d", (unsigned int)keypadEntry.dateCreatedMonth);
      ESP_LOGD("NukiLock", "dateCreatedDay:%d", (unsigned int)keypadEntry.dateCreatedDay);
      ESP_LOGD("NukiLock", "dateCreatedHour:%d", (unsigned int)keypadEntry.dateCreatedHour);
      ESP_LOGD("NukiLock", "dateCreatedMin:%d", (unsigned int)keypadEntry.dateCreatedMin);
      ESP_LOGD("NukiLock", "dateCreatedSec:%d", (unsigned int)keypadEntry.dateCreatedSec);
      ESP_LOGD("NukiLock", "dateLastActiveYear:%d", (unsigned int)keypadEntry.dateLastActiveYear);
      ESP_LOGD("NukiLock", "dateLastActiveMonth:%d", (unsigned int)keypadEntry.dateLastActiveMonth);
      ESP_LOGD("NukiLock", "dateLastActiveDay:%d", (unsigned int)keypadEntry.dateLastActiveDay);
      ESP_LOGD("NukiLock", "dateLastActiveHour:%d", (unsigned int)keypadEntry.dateLastActiveHour);
      ESP_LOGD("NukiLock", "dateLastActiveMin:%d", (unsigned int)keypadEntry.dateLastActiveMin);
      ESP_LOGD("NukiLock", "dateLastActiveSec:%d", (unsigned int)keypadEntry.dateLastActiveSec);
      ESP_LOGD("NukiLock", "lockCount:%d", (unsigned int)keypadEntry.lockCount);
      ESP_LOGD("NukiLock", "timeLimited:%d", (unsigned int)keypadEntry.timeLimited);
      ESP_LOGD("NukiLock", "allowedFromYear:%d", (unsigned int)keypadEntry.allowedFromYear);
      ESP_LOGD("NukiLock", "allowedFromMonth:%d", (unsigned int)keypadEntry.allowedFromMonth);
      ESP_LOGD("NukiLock", "allowedFromDay:%d", (unsigned int)keypadEntry.allowedFromDay);
      ESP_LOGD("NukiLock", "allowedFromHour:%d", (unsigned int)keypadEntry.allowedFromHour);
      ESP_LOGD("NukiLock", "allowedFromMin:%d", (unsigned int)keypadEntry.allowedFromMin);
      ESP_LOGD("NukiLock", "allowedFromSec:%d", (unsigned int)keypadEntry.allowedFromSec);
      ESP_LOGD("NukiLock", "allowedUntilYear:%d", (unsigned int)keypadEntry.allowedUntilYear);
      ESP_LOGD("NukiLock", "allowedUntilMonth:%d", (unsigned int)keypadEntry.allowedUntilMonth);
      ESP_LOGD("NukiLock", "allowedUntilDay:%d", (unsigned int)keypadEntry.allowedUntilDay);
      ESP_LOGD("NukiLock", "allowedUntilHour:%d", (unsigned int)keypadEntry.allowedUntilHour);
      ESP_LOGD("NukiLock", "allowedUntilMin:%d", (unsigned int)keypadEntry.allowedUntilMin);
      ESP_LOGD("NukiLock", "allowedUntilSec:%d", (unsigned int)keypadEntry.allowedUntilSec);
      ESP_LOGD("NukiLock", "allowedWeekdays:%d", (unsigned int)keypadEntry.allowedWeekdays);
      ESP_LOGD("NukiLock", "allowedFromTimeHour:%d", (unsigned int)keypadEntry.allowedFromTimeHour);
      ESP_LOGD("NukiLock", "allowedFromTimeMin:%d", (unsigned int)keypadEntry.allowedFromTimeMin);
      ESP_LOGD("NukiLock", "allowedUntilTimeHour:%d", (unsigned int)keypadEntry.allowedUntilTimeHour);
      ESP_LOGD("NukiLock", "allowedUntilTimeMin:%d", (unsigned int)keypadEntry.allowedUntilTimeMin);
    }
  }

  void logUpdatedKeypadEntry(UpdatedKeypadEntry updatedKeypadEntry, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "codeId:%d", (unsigned int)updatedKeypadEntry.codeId);
      ESP_LOGD("NukiLock", "code:%d", (unsigned int)updatedKeypadEntry.code);
      ESP_LOGD("NukiLock", "name:%s", (const char*)updatedKeypadEntry.name);
      ESP_LOGD("NukiLock", "enabled:%d", (unsigned int)updatedKeypadEntry.enabled);
      ESP_LOGD("NukiLock", "timeLimited:%d", (unsigned int)updatedKeypadEntry.timeLimited);
      ESP_LOGD("NukiLock", "allowedFromYear:%d", (unsigned int)updatedKeypadEntry.allowedFromYear);
      ESP_LOGD("NukiLock", "allowedFromMonth:%d", (unsigned int)updatedKeypadEntry.allowedFromMonth);
      ESP_LOGD("NukiLock", "allowedFromDay:%d", (unsigned int)updatedKeypadEntry.allowedFromDay);
      ESP_LOGD("NukiLock", "allowedFromHour:%d", (unsigned int)updatedKeypadEntry.allowedFromHour);
      ESP_LOGD("NukiLock", "allowedFromMin:%d", (unsigned int)updatedKeypadEntry.allowedFromMin);
      ESP_LOGD("NukiLock", "allowedFromSec:%d", (unsigned int)updatedKeypadEntry.allowedFromSec);
      ESP_LOGD("NukiLock", "allowedUntilYear:%d", (unsigned int)updatedKeypadEntry.allowedUntilYear);
      ESP_LOGD("NukiLock", "allowedUntilMonth:%d", (unsigned int)updatedKeypadEntry.allowedUntilMonth);
      ESP_LOGD("NukiLock", "allowedUntilDay:%d", (unsigned int)updatedKeypadEntry.allowedUntilDay);
      ESP_LOGD("NukiLock", "allowedUntilHour:%d", (unsigned int)updatedKeypadEntry.allowedUntilHour);
      ESP_LOGD("NukiLock", "allowedUntilMin:%d", (unsigned int)updatedKeypadEntry.allowedUntilMin);
      ESP_LOGD("NukiLock", "allowedUntilSec:%d", (unsigned int)updatedKeypadEntry.allowedUntilSec);
      ESP_LOGD("NukiLock", "allowedWeekdays:%d", (unsigned int)updatedKeypadEntry.allowedWeekdays);
      ESP_LOGD("NukiLock", "allowedFromTimeHour:%d", (unsigned int)updatedKeypadEntry.allowedFromTimeHour);
      ESP_LOGD("NukiLock", "allowedFromTimeMin:%d", (unsigned int)updatedKeypadEntry.allowedFromTimeMin);
      ESP_LOGD("NukiLock", "allowedUntilTimeHour:%d", (unsigned int)updatedKeypadEntry.allowedUntilTimeHour);
      ESP_LOGD("NukiLock", "allowedUntilTimeMin:%d", (unsigned int)updatedKeypadEntry.allowedUntilTimeMin);
    }
  }

  void logAuthorizationEntry(AuthorizationEntry authorizationEntry, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "id:%d", (unsigned int)authorizationEntry.authId);
      ESP_LOGD("NukiLock", "idType:%d", (unsigned int)authorizationEntry.idType);
      ESP_LOGD("NukiLock", "name:%s", (const char*)authorizationEntry.name);
      ESP_LOGD("NukiLock", "enabled:%d", (unsigned int)authorizationEntry.enabled);
      ESP_LOGD("NukiLock", "remoteAllowed:%d", (unsigned int)authorizationEntry.remoteAllowed);
      ESP_LOGD("NukiLock", "createdYear:%d", (unsigned int)authorizationEntry.createdYear);
      ESP_LOGD("NukiLock", "createdMonth:%d", (unsigned int)authorizationEntry.createdMonth);
      ESP_LOGD("NukiLock", "createdDay:%d", (unsigned int)authorizationEntry.createdDay);
      ESP_LOGD("NukiLock", "createdHour:%d", (unsigned int)authorizationEntry.createdHour);
      ESP_LOGD("NukiLock", "createdMin:%d", (unsigned int)authorizationEntry.createdMinute);
      ESP_LOGD("NukiLock", "createdSec:%d", (unsigned int)authorizationEntry.createdSecond);
      ESP_LOGD("NukiLock", "lastactYear:%d", (unsigned int)authorizationEntry.lastActYear);
      ESP_LOGD("NukiLock", "lastactMonth:%d", (unsigned int)authorizationEntry.lastActMonth);
      ESP_LOGD("NukiLock", "lastactDay:%d", (unsigned int)authorizationEntry.lastActDay);
      ESP_LOGD("NukiLock", "lastactHour:%d", (unsigned int)authorizationEntry.lastActHour);
      ESP_LOGD("NukiLock", "lastactMin:%d", (unsigned int)authorizationEntry.lastActMinute);
      ESP_LOGD("NukiLock", "lastactSec:%d", (unsigned int)authorizationEntry.lastActSecond);
      ESP_LOGD("NukiLock", "lockCount:%d", (unsigned int)authorizationEntry.lockCount);
      ESP_LOGD("NukiLock", "timeLimited:%d", (unsigned int)authorizationEntry.timeLimited);
      ESP_LOGD("NukiLock", "allowedFromYear:%d", (unsigned int)authorizationEntry.allowedFromYear);
      ESP_LOGD("NukiLock", "allowedFromMonth:%d", (unsigned int)authorizationEntry.allowedFromMonth);
      ESP_LOGD("NukiLock", "allowedFromDay:%d", (unsigned int)authorizationEntry.allowedFromDay);
      ESP_LOGD("NukiLock", "allowedFromHour:%d", (unsigned int)authorizationEntry.allowedFromHour);
      ESP_LOGD("NukiLock", "allowedFromMin:%d", (unsigned int)authorizationEntry.allowedFromMinute);
      ESP_LOGD("NukiLock", "allowedFromSec:%d", (unsigned int)authorizationEntry.allowedFromSecond);
      ESP_LOGD("NukiLock", "allowedUntilYear:%d", (unsigned int)authorizationEntry.allowedUntilYear);
      ESP_LOGD("NukiLock", "allowedUntilMonth:%d", (unsigned int)authorizationEntry.allowedUntilMonth);
      ESP_LOGD("NukiLock", "allowedUntilDay:%d", (unsigned int)authorizationEntry.allowedUntilDay);
      ESP_LOGD("NukiLock", "allowedUntilHour:%d", (unsigned int)authorizationEntry.allowedUntilHour);
      ESP_LOGD("NukiLock", "allowedUntilMin:%d", (unsigned int)authorizationEntry.allowedUntilMinute);
      ESP_LOGD("NukiLock", "allowedUntilSec:%d", (unsigned int)authorizationEntry.allowedUntilSecond);
      ESP_LOGD("NukiLock", "allowedWeekdays:%d", (unsigned int)authorizationEntry.allowedWeekdays);
      ESP_LOGD("NukiLock", "allowedFromTimeHour:%d", (unsigned int)authorizationEntry.allowedFromTimeHour);
      ESP_LOGD("NukiLock", "allowedFromTimeMin:%d", (unsigned int)authorizationEntry.allowedFromTimeMin);
      ESP_LOGD("NukiLock", "allowedUntilTimeHour:%d", (unsigned int)authorizationEntry.allowedUntilTimeHour);
      ESP_LOGD("NukiLock", "allowedUntilTimeMin:%d", (unsigned int)authorizationEntry.allowedUntilTimeMin);
    }
  }

  void logNewAuthorizationEntry(NewAuthorizationEntry newAuthorizationEntry, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "name:%s", (const char*)newAuthorizationEntry.name);
      ESP_LOGD("NukiLock", "idType:%d", (unsigned int)newAuthorizationEntry.idType);
      ESP_LOGD("NukiLock", "remoteAllowed:%d", (unsigned int)newAuthorizationEntry.remoteAllowed);
      ESP_LOGD("NukiLock", "timeLimited:%d", (unsigned int)newAuthorizationEntry.timeLimited);
      ESP_LOGD("NukiLock", "allowedFromYear:%d", (unsigned int)newAuthorizationEntry.allowedFromYear);
      ESP_LOGD("NukiLock", "allowedFromMonth:%d", (unsigned int)newAuthorizationEntry.allowedFromMonth);
      ESP_LOGD("NukiLock", "allowedFromDay:%d", (unsigned int)newAuthorizationEntry.allowedFromDay);
      ESP_LOGD("NukiLock", "allowedFromHour:%d", (unsigned int)newAuthorizationEntry.allowedFromHour);
      ESP_LOGD("NukiLock", "allowedFromMin:%d", (unsigned int)newAuthorizationEntry.allowedFromMinute);
      ESP_LOGD("NukiLock", "allowedFromSec:%d", (unsigned int)newAuthorizationEntry.allowedFromSecond);
      ESP_LOGD("NukiLock", "allowedUntilYear:%d", (unsigned int)newAuthorizationEntry.allowedUntilYear);
      ESP_LOGD("NukiLock", "allowedUntilMonth:%d", (unsigned int)newAuthorizationEntry.allowedUntilMonth);
      ESP_LOGD("NukiLock", "allowedUntilDay:%d", (unsigned int)newAuthorizationEntry.allowedUntilDay);
      ESP_LOGD("NukiLock", "allowedUntilHour:%d", (unsigned int)newAuthorizationEntry.allowedUntilHour);
      ESP_LOGD("NukiLock", "allowedUntilMin:%d", (unsigned int)newAuthorizationEntry.allowedUntilMinute);
      ESP_LOGD("NukiLock", "allowedUntilSec:%d", (unsigned int)newAuthorizationEntry.allowedUntilSecond);
      ESP_LOGD("NukiLock", "allowedWeekdays:%d", (unsigned int)newAuthorizationEntry.allowedWeekdays);
      ESP_LOGD("NukiLock", "allowedFromTimeHour:%d", (unsigned int)newAuthorizationEntry.allowedFromTimeHour);
      ESP_LOGD("NukiLock", "allowedFromTimeMin:%d", (unsigned int)newAuthorizationEntry.allowedFromTimeMin);
      ESP_LOGD("NukiLock", "allowedUntilTimeHour:%d", (unsigned int)newAuthorizationEntry.allowedUntilTimeHour);
      ESP_LOGD("NukiLock", "allowedUntilTimeMin:%d", (unsigned int)newAuthorizationEntry.allowedUntilTimeMin);
    }
  }

  void logUpdatedAuthorizationEntry(UpdatedAuthorizationEntry updatedAuthorizationEntry, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "id:%d", (unsigned int)updatedAuthorizationEntry.authId);
      ESP_LOGD("NukiLock", "name:%s", (const char*)updatedAuthorizationEntry.name);
      ESP_LOGD("NukiLock", "enabled:%d", (unsigned int)updatedAuthorizationEntry.enabled);
      ESP_LOGD("NukiLock", "remoteAllowed:%d", (unsigned int)updatedAuthorizationEntry.remoteAllowed);
      ESP_LOGD("NukiLock", "timeLimited:%d", (unsigned int)updatedAuthorizationEntry.timeLimited);
      ESP_LOGD("NukiLock", "allowedFromYear:%d", (unsigned int)updatedAuthorizationEntry.allowedFromYear);
      ESP_LOGD("NukiLock", "allowedFromMonth:%d", (unsigned int)updatedAuthorizationEntry.allowedFromMonth);
      ESP_LOGD("NukiLock", "allowedFromDay:%d", (unsigned int)updatedAuthorizationEntry.allowedFromDay);
      ESP_LOGD("NukiLock", "allowedFromHour:%d", (unsigned int)updatedAuthorizationEntry.allowedFromHour);
      ESP_LOGD("NukiLock", "allowedFromMin:%d", (unsigned int)updatedAuthorizationEntry.allowedFromMinute);
      ESP_LOGD("NukiLock", "allowedFromSec:%d", (unsigned int)updatedAuthorizationEntry.allowedFromSecond);
      ESP_LOGD("NukiLock", "allowedUntilYear:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilYear);
      ESP_LOGD("NukiLock", "allowedUntilMonth:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilMonth);
      ESP_LOGD("NukiLock", "allowedUntilDay:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilDay);
      ESP_LOGD("NukiLock", "allowedUntilHour:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilHour);
      ESP_LOGD("NukiLock", "allowedUntilMin:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilMinute);
      ESP_LOGD("NukiLock", "allowedUntilSec:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilSecond);
      ESP_LOGD("NukiLock", "allowedWeekdays:%d", (unsigned int)updatedAuthorizationEntry.allowedWeekdays);
      ESP_LOGD("NukiLock", "allowedFromTimeHour:%d", (unsigned int)updatedAuthorizationEntry.allowedFromTimeHour);
      ESP_LOGD("NukiLock", "allowedFromTimeMin:%d", (unsigned int)updatedAuthorizationEntry.allowedFromTimeMin);
      ESP_LOGD("NukiLock", "allowedUntilTimeHour:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilTimeHour);
      ESP_LOGD("NukiLock", "allowedUntilTimeMin:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilTimeMin);
    }
  }

  void logNewTimeControlEntry(NewTimeControlEntry newTimeControlEntry, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "weekdays:%d", (unsigned int)newTimeControlEntry.weekdays);
      ESP_LOGD("NukiLock", "time:%d:%d", (unsigned int)newTimeControlEntry.timeHour, newTimeControlEntry.timeMin);
      ESP_LOGD("NukiLock", "lockAction:%d", (unsigned int)newTimeControlEntry.lockAction);
    }
  }

  void logTimeControlEntry(TimeControlEntry timeControlEntry, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "entryId:%d", (unsigned int)timeControlEntry.entryId);
      ESP_LOGD("NukiLock", "enabled:%d", (unsigned int)timeControlEntry.enabled);
      ESP_LOGD("NukiLock", "weekdays:%d", (unsigned int)timeControlEntry.weekdays);
      ESP_LOGD("NukiLock", "time:%d:%d", (unsigned int)timeControlEntry.timeHour, timeControlEntry.timeMin);
      ESP_LOGD("NukiLock", "lockAction:%d", (unsigned int)timeControlEntry.lockAction);
    }
  }

  void logCompletionStatus(CompletionStatus completionStatus, bool debug) {
    if (debug) {
      switch (completionStatus) {
        case CompletionStatus::Busy :
          ESP_LOGD("NukiLock", "Completion status: busy");
          break;
        case CompletionStatus::Canceled :
          ESP_LOGD("NukiLock", "Completion status: canceled");
          break;
        case CompletionStatus::ClutchFailure :
          ESP_LOGD("NukiLock", "Completion status: clutchFailure");
          break;
        case CompletionStatus::IncompleteFailure :
          ESP_LOGD("NukiLock", "Completion status: incompleteFailure");
          break;
        case CompletionStatus::LowMotorVoltage :
          ESP_LOGD("NukiLock", "Completion status: lowMotorVoltage");
          break;
        case CompletionStatus::MotorBlocked :
          ESP_LOGD("NukiLock", "Completion status: motorBlocked");
          break;
        case CompletionStatus::MotorPowerFailure :
          ESP_LOGD("NukiLock", "Completion status: motorPowerFailure");
          break;
        case CompletionStatus::OtherError :
          ESP_LOGD("NukiLock", "Completion status: otherError");
          break;
        case CompletionStatus::Success :
          ESP_LOGD("NukiLock", "Completion status: success");
          break;
        case CompletionStatus::TooRecent :
          ESP_LOGD("NukiLock", "Completion status: tooRecent");
          break;
        case CompletionStatus::InvalidCode :
          ESP_LOGD("NukiLock", "Completion status: invalid code");
          break;
        default:
          ESP_LOGW("NukiLock", "Completion status: unknown");
          break;
      }
    }
  }

  void logNukiTrigger(Trigger nukiTrigger, bool debug) {
    if (debug) {
      switch (nukiTrigger) {
        case Trigger::AutoLock :
          ESP_LOGD("NukiLock", "Trigger: autoLock");
          break;
        case Trigger::Automatic :
          ESP_LOGD("NukiLock", "Trigger: automatic");
          break;
        case Trigger::Button :
          ESP_LOGD("NukiLock", "Trigger: button");
          break;
        case Trigger::Manual :
          ESP_LOGD("NukiLock", "Trigger: manual");
          break;
        case Trigger::System :
          ESP_LOGD("NukiLock", "Trigger: system");
          break;
        default:
          ESP_LOGW("NukiLock", "Trigger: unknown");
          break;
      }
    }
  }

  void logLockAction(LockAction lockAction, bool debug) {
    if (debug) {
      switch (lockAction) {
        case LockAction::FobAction1 :
          ESP_LOGD("NukiLock", "action: autoLock");
          break;
        case LockAction::FobAction2 :
          ESP_LOGD("NukiLock", "action: automatic");
          break;
        case LockAction::FobAction3 :
          ESP_LOGD("NukiLock", "action: button");
          break;
        case LockAction::FullLock :
          ESP_LOGD("NukiLock", "action: manual");
          break;
        case LockAction::Lock :
          ESP_LOGD("NukiLock", "action: system");
          break;
        case LockAction::LockNgo :
          ESP_LOGD("NukiLock", "action: system");
          break;
        case LockAction::LockNgoUnlatch :
          ESP_LOGD("NukiLock", "action: system");
          break;
        case LockAction::Unlatch :
          ESP_LOGD("NukiLock", "action: system");
          break;
        case LockAction::Unlock :
          ESP_LOGD("NukiLock", "action: system");
          break;
        default:
          ESP_LOGW("NukiLock", "action: unknown");
          break;
      }
    }
  }

  void logKeyturnerState(KeyTurnerState keyTurnerState, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "nukiState: %02x", (unsigned int)keyTurnerState.nukiState);
      ESP_LOGD("NukiLock", "lockState: %d", (unsigned int)keyTurnerState.lockState);
      logNukiTrigger(keyTurnerState.trigger, debug);
      ESP_LOGD("NukiLock", "currentTimeYear: %d", (unsigned int)keyTurnerState.currentTimeYear);
      ESP_LOGD("NukiLock", "currentTimeMonth: %d", (unsigned int)keyTurnerState.currentTimeMonth);
      ESP_LOGD("NukiLock", "currentTimeDay: %d", (unsigned int)keyTurnerState.currentTimeDay);
      ESP_LOGD("NukiLock", "currentTimeHour: %d", (unsigned int)keyTurnerState.currentTimeHour);
      ESP_LOGD("NukiLock", "currentTimeMinute: %d", (unsigned int)keyTurnerState.currentTimeMinute);
      ESP_LOGD("NukiLock", "currentTimeSecond: %d", (unsigned int)keyTurnerState.currentTimeSecond);
      ESP_LOGD("NukiLock", "timeZoneOffset: %d", (unsigned int)keyTurnerState.timeZoneOffset);
      ESP_LOGD("NukiLock", "criticalBatteryState composed value: %d", (unsigned int)keyTurnerState.criticalBatteryState);
      ESP_LOGD("NukiLock", "criticalBatteryState: %d", (unsigned int)(((unsigned int)keyTurnerState.criticalBatteryState) == 1 ? 1 : 0));
      ESP_LOGD("NukiLock", "batteryCharging: %d", (unsigned int)(((unsigned int)keyTurnerState.criticalBatteryState & 2) == 2 ? 1 : 0));
      ESP_LOGD("NukiLock", "batteryPercent: %d", (unsigned int)((keyTurnerState.criticalBatteryState & 0b11111100) >> 1));
      ESP_LOGD("NukiLock", "configUpdateCount: %d", (unsigned int)keyTurnerState.configUpdateCount);
      ESP_LOGD("NukiLock", "lockNgoTimer: %d", (unsigned int)keyTurnerState.lockNgoTimer);
      logLockAction((LockAction)keyTurnerState.lastLockAction, debug);
      ESP_LOGD("NukiLock", "lastLockActionTrigger: %d", (unsigned int)keyTurnerState.lastLockActionTrigger);
      logCompletionStatus(keyTurnerState.lastLockActionCompletionStatus, debug);
      ESP_LOGD("NukiLock", "doorSensorState: %d", (unsigned int)keyTurnerState.doorSensorState);
      ESP_LOGD("NukiLock", "nightModeActive: %d", (unsigned int)keyTurnerState.nightModeActive);
      ESP_LOGD("NukiLock", "accessoryBatteryState composed value: %d", (unsigned int)keyTurnerState.accessoryBatteryState);
      ESP_LOGD("NukiLock", "Keypad bat critical feature supported: %d", (unsigned int)(((unsigned int)keyTurnerState.accessoryBatteryState & 1) == 1 ? 1 : 0));
      ESP_LOGD("NukiLock", "Keypad Battery Critical: %d", (unsigned int)(((unsigned int)keyTurnerState.accessoryBatteryState & 3) == 3 ? 1 : 0));
      ESP_LOGD("NukiLock", "Doorsensor bat critical feature supported: %d", (unsigned int)(((unsigned int)keyTurnerState.accessoryBatteryState & 4) == 4 ? 1 : 0));
      ESP_LOGD("NukiLock", "Doorsensor Battery Critical: %d", (unsigned int)(((unsigned int)keyTurnerState.accessoryBatteryState & 12) == 12 ? 1 : 0));
      ESP_LOGD("NukiLock", "network composed value: %d", (unsigned int)keyTurnerState.network);
      ESP_LOGD("NukiLock", "remoteAccessEnabled: %d", (unsigned int)(((keyTurnerState.network & 1) == 1) ? 1 : 0));
      ESP_LOGD("NukiLock", "bridgePaired: %d", (unsigned int)((((keyTurnerState.network >> 1) & 1) == 1) ? 1 : 0));
      ESP_LOGD("NukiLock", "sseConnectedViaWifi: %d", (unsigned int)((((keyTurnerState.network >> 2) & 1) == 1) ? 1 : 0));
      ESP_LOGD("NukiLock", "sseConnectionEstablished: %d", (unsigned int)((((keyTurnerState.network >> 3) & 1) == 1) ? 1 : 0));
      ESP_LOGD("NukiLock", "isSseConnectedViaThread: %d", (unsigned int)((((keyTurnerState.network >> 4) & 1) == 1) ? 1 : 0));
      ESP_LOGD("NukiLock", "threadSseUplinkEnabledByUser: %d", (unsigned int)((((keyTurnerState.network >> 5) & 1) == 1) ? 1 : 0));
      ESP_LOGD("NukiLock", "nat64AvailableViaThread: %d", (unsigned int)((((keyTurnerState.network >> 6) & 1) == 1) ? 1 : 0));
      ESP_LOGD("NukiLock", "bleConnectionStrength: %d", (unsigned int)keyTurnerState.bleConnectionStrength);
      ESP_LOGD("NukiLock", "wifiConnectionStrength: %d", (unsigned int)keyTurnerState.wifiConnectionStrength);
      ESP_LOGD("NukiLock", "wifi composed value: %d", (unsigned int)keyTurnerState.wifi);
      ESP_LOGD("NukiLock", "wifiStatus: %d", (unsigned int)(keyTurnerState.wifi & 3));
      ESP_LOGD("NukiLock", "sseStatus: %d", (unsigned int)((keyTurnerState.wifi >> 2) & 3));
      ESP_LOGD("NukiLock", "wifiQuality: %d", (unsigned int)((keyTurnerState.wifi >> 4) & 15));
      ESP_LOGD("NukiLock", "mqtt composed value: %d", (unsigned int)keyTurnerState.mqtt);
      ESP_LOGD("NukiLock", "mqttStatus: %d", (unsigned int)(keyTurnerState.mqtt & 3));
      ESP_LOGD("NukiLock", "mqttConnectionChannel: %d", (unsigned int)((keyTurnerState.mqtt >> 2) & 1));
      ESP_LOGD("NukiLock", "thread composed value: %d", (unsigned int)keyTurnerState.thread);
      ESP_LOGD("NukiLock", "threadConnectionStatus: %d", (unsigned int)(keyTurnerState.thread & 3));
      ESP_LOGD("NukiLock", "threadSseStatus: %d", (unsigned int)((keyTurnerState.thread >> 2) & 3));
      ESP_LOGD("NukiLock", "isCommissioningModeActive: %d", (unsigned int)(((unsigned int)keyTurnerState.thread & 16) != 0 ? 1 : 0));
      ESP_LOGD("NukiLock", "isWifiDisabledBecauseOfThread: %d", (unsigned int)(((unsigned int)keyTurnerState.thread & 32) != 0 ? 1 : 0));
    }
  }

  void logBatteryReport(BatteryReport batteryReport, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "batteryDrain:%d", (unsigned int)batteryReport.batteryDrain);
      ESP_LOGD("NukiLock", "batteryVoltage:%d", (unsigned int)batteryReport.batteryVoltage);
      ESP_LOGD("NukiLock", "criticalBatteryState:%d", (unsigned int)batteryReport.criticalBatteryState);
      ESP_LOGD("NukiLock", "lockAction:%d", (unsigned int)batteryReport.lockAction);
      ESP_LOGD("NukiLock", "startVoltage:%d", (unsigned int)batteryReport.startVoltage);
      ESP_LOGD("NukiLock", "lowestVoltage:%d", (unsigned int)batteryReport.lowestVoltage);
      ESP_LOGD("NukiLock", "lockDistance:%d", (unsigned int)batteryReport.lockDistance);
      ESP_LOGD("NukiLock", "startTemperature:%d", (unsigned int)batteryReport.startTemperature);
      ESP_LOGD("NukiLock", "maxTurnCurrent:%d", (unsigned int)batteryReport.maxTurnCurrent);
      ESP_LOGD("NukiLock", "batteryResistance:%d", (unsigned int)batteryReport.batteryResistance);
    }
  }

  void logLogEntry(LogEntry logEntry, bool debug) {
    ESP_LOGD("NukiLock", "[%lu] type: %u authId: %lu name: %s %d-%d-%d %d:%d:%d ", logEntry.index, (uint8_t)logEntry.loggingType, logEntry.authId, logEntry.name, logEntry.timeStampYear, logEntry.timeStampMonth, logEntry.timeStampDay, logEntry.timeStampHour, logEntry.timeStampMinute, logEntry.timeStampSecond);


    switch (logEntry.loggingType) {
      case LoggingType::LoggingEnabled: {
        ESP_LOGD("NukiLock", "Logging enabled: %d", (unsigned int)logEntry.data[0]);
        break;
      }
      case LoggingType::LockAction:
      case LoggingType::Calibration:
      case LoggingType::InitializationRun: {
        logLockAction((LockAction)logEntry.data[0], debug);
        logNukiTrigger((Trigger)logEntry.data[1], debug);
        ESP_LOGD("NukiLock", "Flags: %d", (unsigned int)logEntry.data[2]);
        logCompletionStatus((CompletionStatus)logEntry.data[3], debug);
        break;
      }
      case LoggingType::KeypadAction: {
        logLockAction((LockAction)logEntry.data[0], debug);
        ESP_LOGD("NukiLock", "Source: %d", (unsigned int)logEntry.data[1]);
        logCompletionStatus((CompletionStatus)logEntry.data[2], debug);
        uint16_t codeId = 0;
        memcpy(&codeId, &logEntry.data[3], 2);
        ESP_LOGD("NukiLock", "Code id: %d", (unsigned int)codeId);
        break;
      }
      case LoggingType::DoorSensor: {
        if (logEntry.data[0] == 0x00) {
          ESP_LOGD("NukiLock", "Door opened") ;
        }
        if (logEntry.data[0] == 0x01) {
          ESP_LOGD("NukiLock", "Door closed") ;
        }
        if (logEntry.data[0] == 0x02) {
          ESP_LOGD("NukiLock", "Door sensor jammed") ;
        }
        break;
      }
      case LoggingType::DoorSensorLoggingEnabled: {
        ESP_LOGD("NukiLock", "Logging enabled: %d", (unsigned int)logEntry.data[0]);
        break;
      }
      default:
        ESP_LOGW("NukiLock", "Unknown logging type");
        break;
    }
  }

  void logAdvancedConfig(AdvancedConfig advancedConfig, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "totalDegrees :%d", (unsigned int)advancedConfig.totalDegrees);
      ESP_LOGD("NukiLock", "unlockedPositionOffsetDegrees :%d", (unsigned int)advancedConfig.unlockedPositionOffsetDegrees);
      ESP_LOGD("NukiLock", "lockedPositionOffsetDegrees :%f", (const float)advancedConfig.lockedPositionOffsetDegrees);
      ESP_LOGD("NukiLock", "singleLockedPositionOffsetDegrees :%f", (const float)advancedConfig.singleLockedPositionOffsetDegrees);
      ESP_LOGD("NukiLock", "unlockedToLockedTransitionOffsetDegrees :%d", (unsigned int)advancedConfig.unlockedToLockedTransitionOffsetDegrees);
      ESP_LOGD("NukiLock", "lockNgoTimeout :%d", (unsigned int)advancedConfig.lockNgoTimeout);
      ESP_LOGD("NukiLock", "singleButtonPressAction :%d", (unsigned int)advancedConfig.singleButtonPressAction);
      ESP_LOGD("NukiLock", "doubleButtonPressAction :%d", (unsigned int)advancedConfig.doubleButtonPressAction);
      ESP_LOGD("NukiLock", "detachedCylinder :%d", (unsigned int)advancedConfig.detachedCylinder);
      ESP_LOGD("NukiLock", "batteryType :%d", (unsigned int)advancedConfig.batteryType);
      ESP_LOGD("NukiLock", "automaticBatteryTypeDetection :%d", (unsigned int)advancedConfig.automaticBatteryTypeDetection);
      ESP_LOGD("NukiLock", "unlatchDuration :%d", (unsigned int)advancedConfig.unlatchDuration);
      ESP_LOGD("NukiLock", "autoLockTimeOut :%d", (unsigned int)advancedConfig.autoLockTimeOut);
      ESP_LOGD("NukiLock", "autoUnLockDisabled :%d", (unsigned int)advancedConfig.autoUnLockDisabled);
      ESP_LOGD("NukiLock", "nightModeEnabled :%d", (unsigned int)advancedConfig.nightModeEnabled);
      ESP_LOGD("NukiLock", "nightModeStartTime Hour :%d", (unsigned int)advancedConfig.nightModeStartTime[0]);
      ESP_LOGD("NukiLock", "nightModeStartTime Minute :%d", (unsigned int)advancedConfig.nightModeStartTime[1]);
      ESP_LOGD("NukiLock", "nightModeEndTime Hour :%d", (unsigned int)advancedConfig.nightModeEndTime[0]);
      ESP_LOGD("NukiLock", "nightModeEndTime Minute :%d", (unsigned int)advancedConfig.nightModeEndTime[1]);
      ESP_LOGD("NukiLock", "nightModeAutoLockEnabled :%d", (unsigned int)advancedConfig.nightModeAutoLockEnabled);
      ESP_LOGD("NukiLock", "nightModeAutoUnlockDisabled :%d", (unsigned int)advancedConfig.nightModeAutoUnlockDisabled);
      ESP_LOGD("NukiLock", "nightModeImmediateLockOnStart :%d", (unsigned int)advancedConfig.nightModeImmediateLockOnStart);
      ESP_LOGD("NukiLock", "autoLockEnabled :%d", (unsigned int)advancedConfig.autoLockEnabled);
      ESP_LOGD("NukiLock", "immediateAutoLockEnabled :%d", (unsigned int)advancedConfig.immediateAutoLockEnabled);
      ESP_LOGD("NukiLock", "autoUpdateEnabled :%d", (unsigned int)advancedConfig.autoUpdateEnabled);
      ESP_LOGD("NukiLock", "speedMode :%d", (unsigned int)advancedConfig.speedMode);
      ESP_LOGD("NukiLock", "slowSpeedDuringNightMode :%d", (unsigned int)advancedConfig.slowSpeedDuringNightMode);
    }
  }

  void logNewAdvancedConfig(NewAdvancedConfig newAdvancedConfig, bool debug) {
    if (debug) {
      ESP_LOGD("NukiLock", "unlockedPositionOffsetDegrees :%d", (unsigned int)newAdvancedConfig.unlockedPositionOffsetDegrees);
      ESP_LOGD("NukiLock", "lockedPositionOffsetDegrees :%f", (const float)newAdvancedConfig.lockedPositionOffsetDegrees);
      ESP_LOGD("NukiLock", "singleLockedPositionOffsetDegrees :%f", (const float)newAdvancedConfig.singleLockedPositionOffsetDegrees);
      ESP_LOGD("NukiLock", "unlockedToLockedTransitionOffsetDegrees :%d", (unsigned int)newAdvancedConfig.unlockedToLockedTransitionOffsetDegrees);
      ESP_LOGD("NukiLock", "lockNgoTimeout :%d", (unsigned int)newAdvancedConfig.lockNgoTimeout);
      ESP_LOGD("NukiLock", "singleButtonPressAction :%d", (unsigned int)newAdvancedConfig.singleButtonPressAction);
      ESP_LOGD("NukiLock", "doubleButtonPressAction :%d", (unsigned int)newAdvancedConfig.doubleButtonPressAction);
      ESP_LOGD("NukiLock", "detachedCylinder :%d", (unsigned int)newAdvancedConfig.detachedCylinder);
      ESP_LOGD("NukiLock", "batteryType :%d", (unsigned int)newAdvancedConfig.batteryType);
      ESP_LOGD("NukiLock", "automaticBatteryTypeDetection :%d", (unsigned int)newAdvancedConfig.automaticBatteryTypeDetection);
      ESP_LOGD("NukiLock", "unlatchDuration :%d", (unsigned int)newAdvancedConfig.unlatchDuration);
      ESP_LOGD("NukiLock", "autoUnLockTimeOut :%d", (unsigned int)newAdvancedConfig.autoLockTimeOut);
      ESP_LOGD("NukiLock", "autoUnLockDisabled :%d", (unsigned int)newAdvancedConfig.autoUnLockDisabled);
      ESP_LOGD("NukiLock", "nightModeEnabled :%d", (unsigned int)newAdvancedConfig.nightModeEnabled);
      ESP_LOGD("NukiLock", "nightModeStartTime Hour :%d", (unsigned int)newAdvancedConfig.nightModeStartTime[0]);
      ESP_LOGD("NukiLock", "nightModeStartTime Minute :%d", (unsigned int)newAdvancedConfig.nightModeStartTime[1]);
      ESP_LOGD("NukiLock", "nightModeEndTime Hour :%d", (unsigned int)newAdvancedConfig.nightModeEndTime[0]);
      ESP_LOGD("NukiLock", "nightModeEndTime Minute :%d", (unsigned int)newAdvancedConfig.nightModeEndTime[1]);
      ESP_LOGD("NukiLock", "nightModeAutoLockEnabled :%d", (unsigned int)newAdvancedConfig.nightModeAutoLockEnabled);
      ESP_LOGD("NukiLock", "nightModeAutoUnlockDisabled :%d", (unsigned int)newAdvancedConfig.nightModeAutoUnlockDisabled);
      ESP_LOGD("NukiLock", "nightModeImmediateLockOnStart :%d", (unsigned int)newAdvancedConfig.nightModeImmediateLockOnStart);
      ESP_LOGD("NukiLock", "autoLockEnabled :%d", (unsigned int)newAdvancedConfig.autoLockEnabled);
      ESP_LOGD("NukiLock", "immediateAutoLockEnabled :%d", (unsigned int)newAdvancedConfig.immediateAutoLockEnabled);
      ESP_LOGD("NukiLock", "autoUpdateEnabled :%d", (unsigned int)newAdvancedConfig.autoUpdateEnabled);
    }
  }

} // namespace Nuki