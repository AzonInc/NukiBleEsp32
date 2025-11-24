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
        ESP_LOGE("NukiBle.NukiLock", "ERROR_BAD_CRC");
        break;
      case (uint8_t)ErrorCode::ERROR_BAD_LENGTH :
        ESP_LOGE("NukiBle.NukiLock", "ERROR_BAD_LENGTH");
        break;
      case (uint8_t)ErrorCode::ERROR_UNKNOWN :
        ESP_LOGE("NukiBle.NukiLock", "ERROR_UNKNOWN");
        break;
      case (uint8_t)ErrorCode::P_ERROR_NOT_PAIRING :
        ESP_LOGE("NukiBle.NukiLock", "P_ERROR_NOT_PAIRING");
        break;
      case (uint8_t)ErrorCode::P_ERROR_BAD_AUTHENTICATOR :
        ESP_LOGE("NukiBle.NukiLock", "P_ERROR_BAD_AUTHENTICATOR");
        break;
      case (uint8_t)ErrorCode::P_ERROR_BAD_PARAMETER :
        ESP_LOGE("NukiBle.NukiLock", "P_ERROR_BAD_PARAMETER");
        break;
      case (uint8_t)ErrorCode::P_ERROR_MAX_USER :
        ESP_LOGE("NukiBle.NukiLock", "P_ERROR_MAX_USER");
        break;
      case (uint8_t)ErrorCode::K_ERROR_AUTO_UNLOCK_TOO_RECENT :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_AUTO_UNLOCK_TOO_RECENT");
        break;
      case (uint8_t)ErrorCode::K_ERROR_BAD_NONCE :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_BAD_NONCE");
        break;
      case (uint8_t)ErrorCode::K_ERROR_BAD_PARAMETER :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_BAD_PARAMETER");
        break;
      case (uint8_t)ErrorCode::K_ERROR_BAD_PIN :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_BAD_PIN");
        break;
      case (uint8_t)ErrorCode::K_ERROR_BUSY :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_BUSY");
        break;
      case (uint8_t)ErrorCode::K_ERROR_CANCELED :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_CANCELED");
        break;
      case (uint8_t)ErrorCode::K_ERROR_CLUTCH_FAILURE :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_CLUTCH_FAILURE");
        break;
      case (uint8_t)ErrorCode::K_ERROR_CLUTCH_POWER_FAILURE :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_CLUTCH_POWER_FAILURE");
        break;
      case (uint8_t)ErrorCode::K_ERROR_CODE_ALREADY_EXISTS :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_CODE_ALREADY_EXISTS");
        break;
      case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_CODE_INVALID");
        break;
      case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID_TIMEOUT_1 :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_CODE_INVALID_TIMEOUT_1");
        break;
      case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID_TIMEOUT_2 :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_CODE_INVALID_TIMEOUT_2");
        break;
      case (uint8_t)ErrorCode::K_ERROR_CODE_INVALID_TIMEOUT_3 :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_CODE_INVALID_TIMEOUT_3");
        break;
      case (uint8_t)ErrorCode::K_ERROR_DISABLED :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_DISABLED");
        break;
      case (uint8_t)ErrorCode::K_ERROR_FIRMWARE_UPDATE_NEEDED :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_FIRMWARE_UPDATE_NEEDED");
        break;
      case (uint8_t)ErrorCode::K_ERROR_INVALID_AUTH_ID :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_INVALID_AUTH_ID");
        break;
      case (uint8_t)ErrorCode::K_ERROR_MOTOR_BLOCKED :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_MOTOR_BLOCKED");
        break;
      case (uint8_t)ErrorCode::K_ERROR_MOTOR_LOW_VOLTAGE :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_MOTOR_LOW_VOLTAGE");
        break;
      case (uint8_t)ErrorCode::K_ERROR_MOTOR_POSITION_LIMIT :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_MOTOR_POSITION_LIMIT");
        break;
      case (uint8_t)ErrorCode::K_ERROR_MOTOR_POWER_FAILURE :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_MOTOR_POWER_FAILURE");
        break;
      case (uint8_t)ErrorCode::K_ERROR_MOTOR_TIMEOUT :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_MOTOR_TIMEOUT");
        break;
      case (uint8_t)ErrorCode::K_ERROR_NOT_AUTHORIZED :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_NOT_AUTHORIZED");
        break;
      case (uint8_t)ErrorCode::K_ERROR_NOT_CALIBRATED :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_NOT_CALIBRATED");
        break;
      case (uint8_t)ErrorCode::K_ERROR_POSITION_UNKNOWN :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_POSITION_UNKNOWN");
        break;
      case (uint8_t)ErrorCode::K_ERROR_REMOTE_NOT_ALLOWED :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_REMOTE_NOT_ALLOWED");
        break;
      case (uint8_t)ErrorCode::K_ERROR_TIME_NOT_ALLOWED :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_TIME_NOT_ALLOWED");
        break;
      case (uint8_t)ErrorCode::K_ERROR_TOO_MANY_ENTRIES :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_TOO_MANY_ENTRIES");
        break;
      case (uint8_t)ErrorCode::K_ERROR_TOO_MANY_PIN_ATTEMPTS :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_TOO_MANY_PIN_ATTEMPTS");
        break;
      case (uint8_t)ErrorCode::K_ERROR_VOLTAGE_TOO_LOW :
        ESP_LOGE("NukiBle.NukiLock", "K_ERROR_VOLTAGE_TOO_LOW");
        break;
      default:
        ESP_LOGE("NukiBle.NukiLock", "UNDEFINED ERROR");
    }
  }
}

void logConfig(Config config, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "nukiId: %d", (unsigned int)config.nukiId);
    ESP_LOGI("NukiBle.NukiLock", "name: %s", (const char*)config.name);
    ESP_LOGI("NukiBle.NukiLock", "latitude: %f", (const float)config.latitude);
    ESP_LOGI("NukiBle.NukiLock", "longitude: %f", (const float)config.longitude);
    ESP_LOGI("NukiBle.NukiLock", "autoUnlatch: %d", (unsigned int)config.autoUnlatch);
    ESP_LOGI("NukiBle.NukiLock", "pairingEnabled: %d", (unsigned int)config.pairingEnabled);
    ESP_LOGI("NukiBle.NukiLock", "buttonEnabled: %d", (unsigned int)config.buttonEnabled);
    ESP_LOGI("NukiBle.NukiLock", "ledEnabled: %d", (unsigned int)config.ledEnabled);
    ESP_LOGI("NukiBle.NukiLock", "ledBrightness: %d", (unsigned int)config.ledBrightness);
    ESP_LOGI("NukiBle.NukiLock", "currentTime Year: %d", (unsigned int)config.currentTimeYear);
    ESP_LOGI("NukiBle.NukiLock", "currentTime Month: %d", (unsigned int)config.currentTimeMonth);
    ESP_LOGI("NukiBle.NukiLock", "currentTime Day: %d", (unsigned int)config.currentTimeDay);
    ESP_LOGI("NukiBle.NukiLock", "currentTime Hour: %d", (unsigned int)config.currentTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "currentTime Minute: %d", (unsigned int)config.currentTimeMinute);
    ESP_LOGI("NukiBle.NukiLock", "currentTime Second: %d", (unsigned int)config.currentTimeSecond);
    ESP_LOGI("NukiBle.NukiLock", "timeZoneOffset: %d", (unsigned int)config.timeZoneOffset);
    ESP_LOGI("NukiBle.NukiLock", "dstMode: %d", (unsigned int)config.dstMode);
    ESP_LOGI("NukiBle.NukiLock", "hasFob: %d", (unsigned int)config.hasFob);
    ESP_LOGI("NukiBle.NukiLock", "fobAction1: %d", (unsigned int)config.fobAction1);
    ESP_LOGI("NukiBle.NukiLock", "fobAction2: %d", (unsigned int)config.fobAction2);
    ESP_LOGI("NukiBle.NukiLock", "fobAction3: %d", (unsigned int)config.fobAction3);
    ESP_LOGI("NukiBle.NukiLock", "singleLock: %d", (unsigned int)config.singleLock);
    ESP_LOGI("NukiBle.NukiLock", "advertisingMode: %d", (unsigned int)config.advertisingMode);
    ESP_LOGI("NukiBle.NukiLock", "hasKeypad: %d", (unsigned int)config.hasKeypad);
    ESP_LOGI("NukiBle.NukiLock", "firmwareVersion: %d.%d.%d", config.firmwareVersion[0], config.firmwareVersion[1], config.firmwareVersion[2]);
    ESP_LOGI("NukiBle.NukiLock", "hardwareRevision: %d.%d", config.hardwareRevision[0], config.hardwareRevision[1]);
    ESP_LOGI("NukiBle.NukiLock", "homeKitStatus: %d", (unsigned int)config.homeKitStatus);
    ESP_LOGI("NukiBle.NukiLock", "timeZoneId: %d", (unsigned int)config.timeZoneId);
    ESP_LOGI("NukiBle.NukiLock", "deviceType: %d", (unsigned int)config.deviceType);
    ESP_LOGI("NukiBle.NukiLock", "wifiCapable: %d", (unsigned int)config.capabilities & 1);
    ESP_LOGI("NukiBle.NukiLock", "threadCapable: %d", (unsigned int)(((unsigned int)config.capabilities & 2) != 0 ? 1:  0));
    ESP_LOGI("NukiBle.NukiLock", "hasKeypadV2: %d", (unsigned int)config.hasKeypadV2);
    ESP_LOGI("NukiBle.NukiLock", "matterStatus: %d", (unsigned int)config.matterStatus);
    ESP_LOGI("NukiBle.NukiLock", "productVariant: %d", (unsigned int)config.productVariant);
  }
}

void logNewConfig(NewConfig newConfig, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "name: %s", (const char*)newConfig.name);
    ESP_LOGI("NukiBle.NukiLock", "latitude: %f", (const float)newConfig.latitude);
    ESP_LOGI("NukiBle.NukiLock", "longitude: %f", (const float)newConfig.longitude);
    ESP_LOGI("NukiBle.NukiLock", "autoUnlatch: %d", (unsigned int)newConfig.autoUnlatch);
    ESP_LOGI("NukiBle.NukiLock", "pairingEnabled: %d", (unsigned int)newConfig.pairingEnabled);
    ESP_LOGI("NukiBle.NukiLock", "buttonEnabled: %d", (unsigned int)newConfig.buttonEnabled);
    ESP_LOGI("NukiBle.NukiLock", "ledEnabled: %d", (unsigned int)newConfig.ledEnabled);
    ESP_LOGI("NukiBle.NukiLock", "ledBrightness: %d", (unsigned int)newConfig.ledBrightness);
    ESP_LOGI("NukiBle.NukiLock", "timeZoneOffset: %d", (unsigned int)newConfig.timeZoneOffset);
    ESP_LOGI("NukiBle.NukiLock", "dstMode: %d", (unsigned int)newConfig.dstMode);
    ESP_LOGI("NukiBle.NukiLock", "fobAction1: %d", (unsigned int)newConfig.fobAction1);
    ESP_LOGI("NukiBle.NukiLock", "fobAction2: %d", (unsigned int)newConfig.fobAction2);
    ESP_LOGI("NukiBle.NukiLock", "fobAction3: %d", (unsigned int)newConfig.fobAction3);
    ESP_LOGI("NukiBle.NukiLock", "singleLock: %d", (unsigned int)newConfig.singleLock);
    ESP_LOGI("NukiBle.NukiLock", "advertisingMode: %d", (unsigned int)newConfig.advertisingMode);
    ESP_LOGI("NukiBle.NukiLock", "timeZoneId: %d", (unsigned int)newConfig.timeZoneId);
  }
}

void logNewKeypadEntry(NewKeypadEntry newKeypadEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "code:%d", (unsigned int)newKeypadEntry.code);
    ESP_LOGI("NukiBle.NukiLock", "name:%s", (const char*)newKeypadEntry.name);
    ESP_LOGI("NukiBle.NukiLock", "timeLimited:%d", (unsigned int)newKeypadEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromYear:%d", (unsigned int)newKeypadEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMonth:%d", (unsigned int)newKeypadEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromDay:%d", (unsigned int)newKeypadEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromHour:%d", (unsigned int)newKeypadEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMin:%d", (unsigned int)newKeypadEntry.allowedFromMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromSec:%d", (unsigned int)newKeypadEntry.allowedFromSec);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilYear:%d", (unsigned int)newKeypadEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMonth:%d", (unsigned int)newKeypadEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilDay:%d", (unsigned int)newKeypadEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilHour:%d", (unsigned int)newKeypadEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMin:%d", (unsigned int)newKeypadEntry.allowedUntilMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilSec:%d", (unsigned int)newKeypadEntry.allowedUntilSec);
    ESP_LOGI("NukiBle.NukiLock", "allowedWeekdays:%d", (unsigned int)newKeypadEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeHour:%d", (unsigned int)newKeypadEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeMin:%d", (unsigned int)newKeypadEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeHour:%d", (unsigned int)newKeypadEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeMin:%d", (unsigned int)newKeypadEntry.allowedUntilTimeMin);
  }
}

void logKeypadEntry(KeypadEntry keypadEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "codeId:%d", (unsigned int)keypadEntry.codeId);
    ESP_LOGI("NukiBle.NukiLock", "code:%d", (unsigned int)keypadEntry.code);
    ESP_LOGI("NukiBle.NukiLock", "name:%s", (const char*)keypadEntry.name);
    ESP_LOGI("NukiBle.NukiLock", "enabled:%d", (unsigned int)keypadEntry.enabled);
    ESP_LOGI("NukiBle.NukiLock", "dateCreatedYear:%d", (unsigned int)keypadEntry.dateCreatedYear);
    ESP_LOGI("NukiBle.NukiLock", "dateCreatedMonth:%d", (unsigned int)keypadEntry.dateCreatedMonth);
    ESP_LOGI("NukiBle.NukiLock", "dateCreatedDay:%d", (unsigned int)keypadEntry.dateCreatedDay);
    ESP_LOGI("NukiBle.NukiLock", "dateCreatedHour:%d", (unsigned int)keypadEntry.dateCreatedHour);
    ESP_LOGI("NukiBle.NukiLock", "dateCreatedMin:%d", (unsigned int)keypadEntry.dateCreatedMin);
    ESP_LOGI("NukiBle.NukiLock", "dateCreatedSec:%d", (unsigned int)keypadEntry.dateCreatedSec);
    ESP_LOGI("NukiBle.NukiLock", "dateLastActiveYear:%d", (unsigned int)keypadEntry.dateLastActiveYear);
    ESP_LOGI("NukiBle.NukiLock", "dateLastActiveMonth:%d", (unsigned int)keypadEntry.dateLastActiveMonth);
    ESP_LOGI("NukiBle.NukiLock", "dateLastActiveDay:%d", (unsigned int)keypadEntry.dateLastActiveDay);
    ESP_LOGI("NukiBle.NukiLock", "dateLastActiveHour:%d", (unsigned int)keypadEntry.dateLastActiveHour);
    ESP_LOGI("NukiBle.NukiLock", "dateLastActiveMin:%d", (unsigned int)keypadEntry.dateLastActiveMin);
    ESP_LOGI("NukiBle.NukiLock", "dateLastActiveSec:%d", (unsigned int)keypadEntry.dateLastActiveSec);
    ESP_LOGI("NukiBle.NukiLock", "lockCount:%d", (unsigned int)keypadEntry.lockCount);
    ESP_LOGI("NukiBle.NukiLock", "timeLimited:%d", (unsigned int)keypadEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromYear:%d", (unsigned int)keypadEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMonth:%d", (unsigned int)keypadEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromDay:%d", (unsigned int)keypadEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromHour:%d", (unsigned int)keypadEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMin:%d", (unsigned int)keypadEntry.allowedFromMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromSec:%d", (unsigned int)keypadEntry.allowedFromSec);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilYear:%d", (unsigned int)keypadEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMonth:%d", (unsigned int)keypadEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilDay:%d", (unsigned int)keypadEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilHour:%d", (unsigned int)keypadEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMin:%d", (unsigned int)keypadEntry.allowedUntilMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilSec:%d", (unsigned int)keypadEntry.allowedUntilSec);
    ESP_LOGI("NukiBle.NukiLock", "allowedWeekdays:%d", (unsigned int)keypadEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeHour:%d", (unsigned int)keypadEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeMin:%d", (unsigned int)keypadEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeHour:%d", (unsigned int)keypadEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeMin:%d", (unsigned int)keypadEntry.allowedUntilTimeMin);
  }
}

void logUpdatedKeypadEntry(UpdatedKeypadEntry updatedKeypadEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "codeId:%d", (unsigned int)updatedKeypadEntry.codeId);
    ESP_LOGI("NukiBle.NukiLock", "code:%d", (unsigned int)updatedKeypadEntry.code);
    ESP_LOGI("NukiBle.NukiLock", "name:%s", (const char*)updatedKeypadEntry.name);
    ESP_LOGI("NukiBle.NukiLock", "enabled:%d", (unsigned int)updatedKeypadEntry.enabled);
    ESP_LOGI("NukiBle.NukiLock", "timeLimited:%d", (unsigned int)updatedKeypadEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromYear:%d", (unsigned int)updatedKeypadEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMonth:%d", (unsigned int)updatedKeypadEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromDay:%d", (unsigned int)updatedKeypadEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromHour:%d", (unsigned int)updatedKeypadEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMin:%d", (unsigned int)updatedKeypadEntry.allowedFromMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromSec:%d", (unsigned int)updatedKeypadEntry.allowedFromSec);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilYear:%d", (unsigned int)updatedKeypadEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMonth:%d", (unsigned int)updatedKeypadEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilDay:%d", (unsigned int)updatedKeypadEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilHour:%d", (unsigned int)updatedKeypadEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMin:%d", (unsigned int)updatedKeypadEntry.allowedUntilMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilSec:%d", (unsigned int)updatedKeypadEntry.allowedUntilSec);
    ESP_LOGI("NukiBle.NukiLock", "allowedWeekdays:%d", (unsigned int)updatedKeypadEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeHour:%d", (unsigned int)updatedKeypadEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeMin:%d", (unsigned int)updatedKeypadEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeHour:%d", (unsigned int)updatedKeypadEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeMin:%d", (unsigned int)updatedKeypadEntry.allowedUntilTimeMin);
  }
}

void logAuthorizationEntry(AuthorizationEntry authorizationEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "id:%d", (unsigned int)authorizationEntry.authId);
    ESP_LOGI("NukiBle.NukiLock", "idType:%d", (unsigned int)authorizationEntry.idType);
    ESP_LOGI("NukiBle.NukiLock", "name:%s", (const char*)authorizationEntry.name);
    ESP_LOGI("NukiBle.NukiLock", "enabled:%d", (unsigned int)authorizationEntry.enabled);
    ESP_LOGI("NukiBle.NukiLock", "remoteAllowed:%d", (unsigned int)authorizationEntry.remoteAllowed);
    ESP_LOGI("NukiBle.NukiLock", "createdYear:%d", (unsigned int)authorizationEntry.createdYear);
    ESP_LOGI("NukiBle.NukiLock", "createdMonth:%d", (unsigned int)authorizationEntry.createdMonth);
    ESP_LOGI("NukiBle.NukiLock", "createdDay:%d", (unsigned int)authorizationEntry.createdDay);
    ESP_LOGI("NukiBle.NukiLock", "createdHour:%d", (unsigned int)authorizationEntry.createdHour);
    ESP_LOGI("NukiBle.NukiLock", "createdMin:%d", (unsigned int)authorizationEntry.createdMinute);
    ESP_LOGI("NukiBle.NukiLock", "createdSec:%d", (unsigned int)authorizationEntry.createdSecond);
    ESP_LOGI("NukiBle.NukiLock", "lastactYear:%d", (unsigned int)authorizationEntry.lastActYear);
    ESP_LOGI("NukiBle.NukiLock", "lastactMonth:%d", (unsigned int)authorizationEntry.lastActMonth);
    ESP_LOGI("NukiBle.NukiLock", "lastactDay:%d", (unsigned int)authorizationEntry.lastActDay);
    ESP_LOGI("NukiBle.NukiLock", "lastactHour:%d", (unsigned int)authorizationEntry.lastActHour);
    ESP_LOGI("NukiBle.NukiLock", "lastactMin:%d", (unsigned int)authorizationEntry.lastActMinute);
    ESP_LOGI("NukiBle.NukiLock", "lastactSec:%d", (unsigned int)authorizationEntry.lastActSecond);
    ESP_LOGI("NukiBle.NukiLock", "lockCount:%d", (unsigned int)authorizationEntry.lockCount);
    ESP_LOGI("NukiBle.NukiLock", "timeLimited:%d", (unsigned int)authorizationEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromYear:%d", (unsigned int)authorizationEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMonth:%d", (unsigned int)authorizationEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromDay:%d", (unsigned int)authorizationEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromHour:%d", (unsigned int)authorizationEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMin:%d", (unsigned int)authorizationEntry.allowedFromMinute);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromSec:%d", (unsigned int)authorizationEntry.allowedFromSecond);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilYear:%d", (unsigned int)authorizationEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMonth:%d", (unsigned int)authorizationEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilDay:%d", (unsigned int)authorizationEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilHour:%d", (unsigned int)authorizationEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMin:%d", (unsigned int)authorizationEntry.allowedUntilMinute);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilSec:%d", (unsigned int)authorizationEntry.allowedUntilSecond);
    ESP_LOGI("NukiBle.NukiLock", "allowedWeekdays:%d", (unsigned int)authorizationEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeHour:%d", (unsigned int)authorizationEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeMin:%d", (unsigned int)authorizationEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeHour:%d", (unsigned int)authorizationEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeMin:%d", (unsigned int)authorizationEntry.allowedUntilTimeMin);
  }
}

void logNewAuthorizationEntry(NewAuthorizationEntry newAuthorizationEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "name:%s", (const char*)newAuthorizationEntry.name);
    ESP_LOGI("NukiBle.NukiLock", "idType:%d", (unsigned int)newAuthorizationEntry.idType);
    ESP_LOGI("NukiBle.NukiLock", "remoteAllowed:%d", (unsigned int)newAuthorizationEntry.remoteAllowed);
    ESP_LOGI("NukiBle.NukiLock", "timeLimited:%d", (unsigned int)newAuthorizationEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromYear:%d", (unsigned int)newAuthorizationEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMonth:%d", (unsigned int)newAuthorizationEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromDay:%d", (unsigned int)newAuthorizationEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromHour:%d", (unsigned int)newAuthorizationEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMin:%d", (unsigned int)newAuthorizationEntry.allowedFromMinute);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromSec:%d", (unsigned int)newAuthorizationEntry.allowedFromSecond);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilYear:%d", (unsigned int)newAuthorizationEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMonth:%d", (unsigned int)newAuthorizationEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilDay:%d", (unsigned int)newAuthorizationEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilHour:%d", (unsigned int)newAuthorizationEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMin:%d", (unsigned int)newAuthorizationEntry.allowedUntilMinute);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilSec:%d", (unsigned int)newAuthorizationEntry.allowedUntilSecond);
    ESP_LOGI("NukiBle.NukiLock", "allowedWeekdays:%d", (unsigned int)newAuthorizationEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeHour:%d", (unsigned int)newAuthorizationEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeMin:%d", (unsigned int)newAuthorizationEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeHour:%d", (unsigned int)newAuthorizationEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeMin:%d", (unsigned int)newAuthorizationEntry.allowedUntilTimeMin);
  }
}

void logUpdatedAuthorizationEntry(UpdatedAuthorizationEntry updatedAuthorizationEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "id:%d", (unsigned int)updatedAuthorizationEntry.authId);
    ESP_LOGI("NukiBle.NukiLock", "name:%s", (const char*)updatedAuthorizationEntry.name);
    ESP_LOGI("NukiBle.NukiLock", "enabled:%d", (unsigned int)updatedAuthorizationEntry.enabled);
    ESP_LOGI("NukiBle.NukiLock", "remoteAllowed:%d", (unsigned int)updatedAuthorizationEntry.remoteAllowed);
    ESP_LOGI("NukiBle.NukiLock", "timeLimited:%d", (unsigned int)updatedAuthorizationEntry.timeLimited);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromYear:%d", (unsigned int)updatedAuthorizationEntry.allowedFromYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMonth:%d", (unsigned int)updatedAuthorizationEntry.allowedFromMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromDay:%d", (unsigned int)updatedAuthorizationEntry.allowedFromDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromHour:%d", (unsigned int)updatedAuthorizationEntry.allowedFromHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromMin:%d", (unsigned int)updatedAuthorizationEntry.allowedFromMinute);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromSec:%d", (unsigned int)updatedAuthorizationEntry.allowedFromSecond);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilYear:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilYear);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMonth:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilMonth);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilDay:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilDay);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilHour:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilMin:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilMinute);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilSec:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilSecond);
    ESP_LOGI("NukiBle.NukiLock", "allowedWeekdays:%d", (unsigned int)updatedAuthorizationEntry.allowedWeekdays);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeHour:%d", (unsigned int)updatedAuthorizationEntry.allowedFromTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedFromTimeMin:%d", (unsigned int)updatedAuthorizationEntry.allowedFromTimeMin);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeHour:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "allowedUntilTimeMin:%d", (unsigned int)updatedAuthorizationEntry.allowedUntilTimeMin);
  }
}

void logNewTimeControlEntry(NewTimeControlEntry newTimeControlEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "weekdays:%d", (unsigned int)newTimeControlEntry.weekdays);
    ESP_LOGI("NukiBle.NukiLock", "time:%d:%d", (unsigned int)newTimeControlEntry.timeHour, newTimeControlEntry.timeMin);
    ESP_LOGI("NukiBle.NukiLock", "lockAction:%d", (unsigned int)newTimeControlEntry.lockAction);
  }
}

void logTimeControlEntry(TimeControlEntry timeControlEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "entryId:%d", (unsigned int)timeControlEntry.entryId);
    ESP_LOGI("NukiBle.NukiLock", "enabled:%d", (unsigned int)timeControlEntry.enabled);
    ESP_LOGI("NukiBle.NukiLock", "weekdays:%d", (unsigned int)timeControlEntry.weekdays);
    ESP_LOGI("NukiBle.NukiLock", "time:%d:%d", (unsigned int)timeControlEntry.timeHour, timeControlEntry.timeMin);
    ESP_LOGI("NukiBle.NukiLock", "lockAction:%d", (unsigned int)timeControlEntry.lockAction);
  }
}

void logCompletionStatus(CompletionStatus completionStatus, bool debug) {
  if (debug) {
    switch (completionStatus) {
      case CompletionStatus::Busy :
        ESP_LOGI("NukiBle.NukiLock", "Completion status: busy");
        break;
      case CompletionStatus::Canceled :
        ESP_LOGI("NukiBle.NukiLock", "Completion status: canceled");
        break;
      case CompletionStatus::ClutchFailure :
        ESP_LOGI("NukiBle.NukiLock", "Completion status: clutchFailure");
        break;
      case CompletionStatus::IncompleteFailure :
        ESP_LOGI("NukiBle.NukiLock", "Completion status: incompleteFailure");
        break;
      case CompletionStatus::LowMotorVoltage :
        ESP_LOGI("NukiBle.NukiLock", "Completion status: lowMotorVoltage");
        break;
      case CompletionStatus::MotorBlocked :
        ESP_LOGI("NukiBle.NukiLock", "Completion status: motorBlocked");
        break;
      case CompletionStatus::MotorPowerFailure :
        ESP_LOGI("NukiBle.NukiLock", "Completion status: motorPowerFailure");
        break;
      case CompletionStatus::OtherError :
        ESP_LOGI("NukiBle.NukiLock", "Completion status: otherError");
        break;
      case CompletionStatus::Success :
        ESP_LOGI("NukiBle.NukiLock", "Completion status: success");
        break;
      case CompletionStatus::TooRecent :
        ESP_LOGI("NukiBle.NukiLock", "Completion status: tooRecent");
        break;
      case CompletionStatus::InvalidCode :
        ESP_LOGI("NukiBle.NukiLock", "Completion status: invalid code");
        break;
      default:
        ESP_LOGW("NukiBle.NukiLock", "Completion status: unknown");
        break;
    }
  }
}

void logNukiTrigger(Trigger nukiTrigger, bool debug) {
  if (debug) {
    switch (nukiTrigger) {
      case Trigger::AutoLock :
        ESP_LOGI("NukiBle.NukiLock", "Trigger: autoLock");
        break;
      case Trigger::Automatic :
        ESP_LOGI("NukiBle.NukiLock", "Trigger: automatic");
        break;
      case Trigger::Button :
        ESP_LOGI("NukiBle.NukiLock", "Trigger: button");
        break;
      case Trigger::Manual :
        ESP_LOGI("NukiBle.NukiLock", "Trigger: manual");
        break;
      case Trigger::System :
        ESP_LOGI("NukiBle.NukiLock", "Trigger: system");
        break;
      default:
        ESP_LOGW("NukiBle.NukiLock", "Trigger: unknown");
        break;
    }
  }
}

void logLockAction(LockAction lockAction, bool debug) {
  if (debug) {
    switch (lockAction) {
      case LockAction::FobAction1 :
        ESP_LOGI("NukiBle.NukiLock", "action: autoLock");
        break;
      case LockAction::FobAction2 :
        ESP_LOGI("NukiBle.NukiLock", "action: automatic");
        break;
      case LockAction::FobAction3 :
        ESP_LOGI("NukiBle.NukiLock", "action: button");
        break;
      case LockAction::FullLock :
        ESP_LOGI("NukiBle.NukiLock", "action: manual");
        break;
      case LockAction::Lock :
        ESP_LOGI("NukiBle.NukiLock", "action: system");
        break;
      case LockAction::LockNgo :
        ESP_LOGI("NukiBle.NukiLock", "action: system");
        break;
      case LockAction::LockNgoUnlatch :
        ESP_LOGI("NukiBle.NukiLock", "action: system");
        break;
      case LockAction::Unlatch :
        ESP_LOGI("NukiBle.NukiLock", "action: system");
        break;
      case LockAction::Unlock :
        ESP_LOGI("NukiBle.NukiLock", "action: system");
        break;
      default:
        ESP_LOGW("NukiBle.NukiLock", "action: unknown");
        break;
    }
  }
}

void logKeyturnerState(KeyTurnerState keyTurnerState, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "nukiState: %02x", (unsigned int)keyTurnerState.nukiState);
    ESP_LOGI("NukiBle.NukiLock", "lockState: %d", (unsigned int)keyTurnerState.lockState);
    logNukiTrigger(keyTurnerState.trigger, debug);
    ESP_LOGI("NukiBle.NukiLock", "currentTimeYear: %d", (unsigned int)keyTurnerState.currentTimeYear);
    ESP_LOGI("NukiBle.NukiLock", "currentTimeMonth: %d", (unsigned int)keyTurnerState.currentTimeMonth);
    ESP_LOGI("NukiBle.NukiLock", "currentTimeDay: %d", (unsigned int)keyTurnerState.currentTimeDay);
    ESP_LOGI("NukiBle.NukiLock", "currentTimeHour: %d", (unsigned int)keyTurnerState.currentTimeHour);
    ESP_LOGI("NukiBle.NukiLock", "currentTimeMinute: %d", (unsigned int)keyTurnerState.currentTimeMinute);
    ESP_LOGI("NukiBle.NukiLock", "currentTimeSecond: %d", (unsigned int)keyTurnerState.currentTimeSecond);
    ESP_LOGI("NukiBle.NukiLock", "timeZoneOffset: %d", (unsigned int)keyTurnerState.timeZoneOffset);
    ESP_LOGI("NukiBle.NukiLock", "criticalBatteryState composed value: %d", (unsigned int)keyTurnerState.criticalBatteryState);
    ESP_LOGI("NukiBle.NukiLock", "criticalBatteryState: %d", (unsigned int)(((unsigned int)keyTurnerState.criticalBatteryState) == 1 ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "batteryCharging: %d", (unsigned int)(((unsigned int)keyTurnerState.criticalBatteryState & 2) == 2 ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "batteryPercent: %d", (unsigned int)((keyTurnerState.criticalBatteryState & 0b11111100) >> 1));
    ESP_LOGI("NukiBle.NukiLock", "configUpdateCount: %d", (unsigned int)keyTurnerState.configUpdateCount);
    ESP_LOGI("NukiBle.NukiLock", "lockNgoTimer: %d", (unsigned int)keyTurnerState.lockNgoTimer);
    logLockAction((LockAction)keyTurnerState.lastLockAction, debug);
    ESP_LOGI("NukiBle.NukiLock", "lastLockActionTrigger: %d", (unsigned int)keyTurnerState.lastLockActionTrigger);
    logCompletionStatus(keyTurnerState.lastLockActionCompletionStatus, debug);
    ESP_LOGI("NukiBle.NukiLock", "doorSensorState: %d", (unsigned int)keyTurnerState.doorSensorState);
    ESP_LOGI("NukiBle.NukiLock", "nightModeActive: %d", (unsigned int)keyTurnerState.nightModeActive);
    ESP_LOGI("NukiBle.NukiLock", "accessoryBatteryState composed value: %d", (unsigned int)keyTurnerState.accessoryBatteryState);
    ESP_LOGI("NukiBle.NukiLock", "Keypad bat critical feature supported: %d", (unsigned int)(((unsigned int)keyTurnerState.accessoryBatteryState & 1) == 1 ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "Keypad Battery Critical: %d", (unsigned int)(((unsigned int)keyTurnerState.accessoryBatteryState & 3) == 3 ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "Doorsensor bat critical feature supported: %d", (unsigned int)(((unsigned int)keyTurnerState.accessoryBatteryState & 4) == 4 ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "Doorsensor Battery Critical: %d", (unsigned int)(((unsigned int)keyTurnerState.accessoryBatteryState & 12) == 12 ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "remoteAccessStatus composed value: %d", (unsigned int)keyTurnerState.remoteAccessStatus);
    ESP_LOGI("NukiBle.NukiLock", "remoteAccessEnabled: %d", (unsigned int)(((keyTurnerState.remoteAccessStatus & 1) == 1) ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "bridgePaired: %d", (unsigned int)((((keyTurnerState.remoteAccessStatus >> 1) & 1) == 1) ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "sseConnectedViaWifi: %d", (unsigned int)((((keyTurnerState.remoteAccessStatus >> 2) & 1) == 1) ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "sseConnectionEstablished: %d", (unsigned int)((((keyTurnerState.remoteAccessStatus >> 3) & 1) == 1) ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "isSseConnectedViaThread: %d", (unsigned int)((((keyTurnerState.remoteAccessStatus >> 4) & 1) == 1) ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "threadSseUplinkEnabledByUser: %d", (unsigned int)((((keyTurnerState.remoteAccessStatus >> 5) & 1) == 1) ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "nat64AvailableViaThread: %d", (unsigned int)((((keyTurnerState.remoteAccessStatus >> 6) & 1) == 1) ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "bleConnectionStrength: %d", (unsigned int)keyTurnerState.bleConnectionStrength);
    ESP_LOGI("NukiBle.NukiLock", "wifiConnectionStrength: %d", (unsigned int)keyTurnerState.wifiConnectionStrength);
    ESP_LOGI("NukiBle.NukiLock", "wifiConnectionStatus composed value: %d", (unsigned int)keyTurnerState.wifiConnectionStatus);
    ESP_LOGI("NukiBle.NukiLock", "wifiStatus: %d", (unsigned int)(keyTurnerState.wifiConnectionStatus & 3));
    ESP_LOGI("NukiBle.NukiLock", "sseStatus: %d", (unsigned int)((keyTurnerState.wifiConnectionStatus >> 2) & 3));
    ESP_LOGI("NukiBle.NukiLock", "wifiQuality: %d", (unsigned int)((keyTurnerState.wifiConnectionStatus >> 4) & 15));
    ESP_LOGI("NukiBle.NukiLock", "mqttConnectionStatus composed value: %d", (unsigned int)keyTurnerState.mqttConnectionStatus);
    ESP_LOGI("NukiBle.NukiLock", "mqttStatus: %d", (unsigned int)(keyTurnerState.mqttConnectionStatus & 3));
    ESP_LOGI("NukiBle.NukiLock", "mqttConnectionChannel: %d", (unsigned int)((keyTurnerState.mqttConnectionStatus >> 2) & 1));
    ESP_LOGI("NukiBle.NukiLock", "threadConnectionStatus composed value: %d", (unsigned int)keyTurnerState.threadConnectionStatus);
    ESP_LOGI("NukiBle.NukiLock", "threadConnectionStatus: %d", (unsigned int)(keyTurnerState.threadConnectionStatus & 3));
    ESP_LOGI("NukiBle.NukiLock", "threadSseStatus: %d", (unsigned int)((keyTurnerState.threadConnectionStatus >> 2) & 3));
    ESP_LOGI("NukiBle.NukiLock", "isCommissioningModeActive: %d", (unsigned int)(((unsigned int)keyTurnerState.threadConnectionStatus & 16) != 0 ? 1 : 0));
    ESP_LOGI("NukiBle.NukiLock", "isWifiDisabledBecauseOfThread: %d", (unsigned int)(((unsigned int)keyTurnerState.threadConnectionStatus & 32) != 0 ? 1 : 0));
  }
}

void logBatteryReport(BatteryReport batteryReport, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "batteryDrain:%d", (unsigned int)batteryReport.batteryDrain);
    ESP_LOGI("NukiBle.NukiLock", "batteryVoltage:%d", (unsigned int)batteryReport.batteryVoltage);
    ESP_LOGI("NukiBle.NukiLock", "criticalBatteryState:%d", (unsigned int)batteryReport.criticalBatteryState);
    ESP_LOGI("NukiBle.NukiLock", "lockAction:%d", (unsigned int)batteryReport.lockAction);
    ESP_LOGI("NukiBle.NukiLock", "startVoltage:%d", (unsigned int)batteryReport.startVoltage);
    ESP_LOGI("NukiBle.NukiLock", "lowestVoltage:%d", (unsigned int)batteryReport.lowestVoltage);
    ESP_LOGI("NukiBle.NukiLock", "lockDistance:%d", (unsigned int)batteryReport.lockDistance);
    ESP_LOGI("NukiBle.NukiLock", "startTemperature:%d", (unsigned int)batteryReport.startTemperature);
    ESP_LOGI("NukiBle.NukiLock", "maxTurnCurrent:%d", (unsigned int)batteryReport.maxTurnCurrent);
    ESP_LOGI("NukiBle.NukiLock", "batteryResistance:%d", (unsigned int)batteryReport.batteryResistance);
  }
}

void logLogEntry(LogEntry logEntry, bool debug) {
  ESP_LOGI("NukiBle.NukiLock", "[%lu] type: %u authId: %lu name: %s %d-%d-%d %d:%d:%d ", logEntry.index, (uint8_t)logEntry.loggingType, logEntry.authId, logEntry.name, logEntry.timeStampYear, logEntry.timeStampMonth, logEntry.timeStampDay, logEntry.timeStampHour, logEntry.timeStampMinute, logEntry.timeStampSecond);


  switch (logEntry.loggingType) {
    case LoggingType::LoggingEnabled: {
      ESP_LOGI("NukiBle.NukiLock", "Logging enabled: %d", (unsigned int)logEntry.data[0]);
      break;
    }
    case LoggingType::LockAction:
    case LoggingType::Calibration:
    case LoggingType::InitializationRun: {
      logLockAction((LockAction)logEntry.data[0], debug);
      logNukiTrigger((Trigger)logEntry.data[1], debug);
      ESP_LOGI("NukiBle.NukiLock", "Flags: %d", (unsigned int)logEntry.data[2]);
      logCompletionStatus((CompletionStatus)logEntry.data[3], debug);
      break;
    }
    case LoggingType::KeypadAction: {
      logLockAction((LockAction)logEntry.data[0], debug);
      ESP_LOGI("NukiBle.NukiLock", "Source: %d", (unsigned int)logEntry.data[1]);
      logCompletionStatus((CompletionStatus)logEntry.data[2], debug);
      uint16_t codeId = 0;
      memcpy(&codeId, &logEntry.data[3], 2);
      ESP_LOGI("NukiBle.NukiLock", "Code id: %d", (unsigned int)codeId);
      break;
    }
    case LoggingType::DoorSensor: {
      if (logEntry.data[0] == 0x00) {
        ESP_LOGI("NukiBle.NukiLock", "Door opened") ;
      }
      if (logEntry.data[0] == 0x01) {
        ESP_LOGI("NukiBle.NukiLock", "Door closed") ;
      }
      if (logEntry.data[0] == 0x02) {
        ESP_LOGI("NukiBle.NukiLock", "Door sensor jammed") ;
      }
      break;
    }
    case LoggingType::DoorSensorLoggingEnabled: {
      ESP_LOGI("NukiBle.NukiLock", "Logging enabled: %d", (unsigned int)logEntry.data[0]);
      break;
    }
    default:
      ESP_LOGW("NukiBle.NukiLock", "Unknown logging type");
      break;
  }
}

void logAdvancedConfig(AdvancedConfig advancedConfig, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "totalDegrees: %d", (unsigned int)advancedConfig.totalDegrees);
    ESP_LOGI("NukiBle.NukiLock", "unlockedPositionOffsetDegrees: %d", (unsigned int)advancedConfig.unlockedPositionOffsetDegrees);
    ESP_LOGI("NukiBle.NukiLock", "lockedPositionOffsetDegrees: %f", (const float)advancedConfig.lockedPositionOffsetDegrees);
    ESP_LOGI("NukiBle.NukiLock", "singleLockedPositionOffsetDegrees: %f", (const float)advancedConfig.singleLockedPositionOffsetDegrees);
    ESP_LOGI("NukiBle.NukiLock", "unlockedToLockedTransitionOffsetDegrees: %d", (unsigned int)advancedConfig.unlockedToLockedTransitionOffsetDegrees);
    ESP_LOGI("NukiBle.NukiLock", "lockNgoTimeout: %d", (unsigned int)advancedConfig.lockNgoTimeout);
    ESP_LOGI("NukiBle.NukiLock", "singleButtonPressAction: %d", (unsigned int)advancedConfig.singleButtonPressAction);
    ESP_LOGI("NukiBle.NukiLock", "doubleButtonPressAction: %d", (unsigned int)advancedConfig.doubleButtonPressAction);
    ESP_LOGI("NukiBle.NukiLock", "detachedCylinder: %d", (unsigned int)advancedConfig.detachedCylinder);
    ESP_LOGI("NukiBle.NukiLock", "batteryType: %d", (unsigned int)advancedConfig.batteryType);
    ESP_LOGI("NukiBle.NukiLock", "automaticBatteryTypeDetection: %d", (unsigned int)advancedConfig.automaticBatteryTypeDetection);
    ESP_LOGI("NukiBle.NukiLock", "unlatchDuration: %d", (unsigned int)advancedConfig.unlatchDuration);
    ESP_LOGI("NukiBle.NukiLock", "autoLockTimeOut: %d", (unsigned int)advancedConfig.autoLockTimeOut);
    ESP_LOGI("NukiBle.NukiLock", "autoUnLockDisabled: %d", (unsigned int)advancedConfig.autoUnLockDisabled);
    ESP_LOGI("NukiBle.NukiLock", "nightModeEnabled: %d", (unsigned int)advancedConfig.nightModeEnabled);
    ESP_LOGI("NukiBle.NukiLock", "nightModeStartTime Hour: %d", (unsigned int)advancedConfig.nightModeStartTime[0]);
    ESP_LOGI("NukiBle.NukiLock", "nightModeStartTime Minute: %d", (unsigned int)advancedConfig.nightModeStartTime[1]);
    ESP_LOGI("NukiBle.NukiLock", "nightModeEndTime Hour: %d", (unsigned int)advancedConfig.nightModeEndTime[0]);
    ESP_LOGI("NukiBle.NukiLock", "nightModeEndTime Minute: %d", (unsigned int)advancedConfig.nightModeEndTime[1]);
    ESP_LOGI("NukiBle.NukiLock", "nightModeAutoLockEnabled: %d", (unsigned int)advancedConfig.nightModeAutoLockEnabled);
    ESP_LOGI("NukiBle.NukiLock", "nightModeAutoUnlockDisabled: %d", (unsigned int)advancedConfig.nightModeAutoUnlockDisabled);
    ESP_LOGI("NukiBle.NukiLock", "nightModeImmediateLockOnStart: %d", (unsigned int)advancedConfig.nightModeImmediateLockOnStart);
    ESP_LOGI("NukiBle.NukiLock", "autoLockEnabled: %d", (unsigned int)advancedConfig.autoLockEnabled);
    ESP_LOGI("NukiBle.NukiLock", "immediateAutoLockEnabled: %d", (unsigned int)advancedConfig.immediateAutoLockEnabled);
    ESP_LOGI("NukiBle.NukiLock", "autoUpdateEnabled: %d", (unsigned int)advancedConfig.autoUpdateEnabled);
    ESP_LOGI("NukiBle.NukiLock", "motorSpeed: %d", (unsigned int)advancedConfig.motorSpeed);
    ESP_LOGI("NukiBle.NukiLock", "enableSlowSpeedDuringNightMode: %d", (unsigned int)advancedConfig.enableSlowSpeedDuringNightMode);
  }
}

void logNewAdvancedConfig(NewAdvancedConfig newAdvancedConfig, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "unlockedPositionOffsetDegrees: %d", (unsigned int)newAdvancedConfig.unlockedPositionOffsetDegrees);
    ESP_LOGI("NukiBle.NukiLock", "lockedPositionOffsetDegrees: %f", (const float)newAdvancedConfig.lockedPositionOffsetDegrees);
    ESP_LOGI("NukiBle.NukiLock", "singleLockedPositionOffsetDegrees: %f", (const float)newAdvancedConfig.singleLockedPositionOffsetDegrees);
    ESP_LOGI("NukiBle.NukiLock", "unlockedToLockedTransitionOffsetDegrees: %d", (unsigned int)newAdvancedConfig.unlockedToLockedTransitionOffsetDegrees);
    ESP_LOGI("NukiBle.NukiLock", "lockNgoTimeout: %d", (unsigned int)newAdvancedConfig.lockNgoTimeout);
    ESP_LOGI("NukiBle.NukiLock", "singleButtonPressAction: %d", (unsigned int)newAdvancedConfig.singleButtonPressAction);
    ESP_LOGI("NukiBle.NukiLock", "doubleButtonPressAction: %d", (unsigned int)newAdvancedConfig.doubleButtonPressAction);
    ESP_LOGI("NukiBle.NukiLock", "detachedCylinder: %d", (unsigned int)newAdvancedConfig.detachedCylinder);
    ESP_LOGI("NukiBle.NukiLock", "batteryType: %d", (unsigned int)newAdvancedConfig.batteryType);
    ESP_LOGI("NukiBle.NukiLock", "automaticBatteryTypeDetection: %d", (unsigned int)newAdvancedConfig.automaticBatteryTypeDetection);
    ESP_LOGI("NukiBle.NukiLock", "unlatchDuration: %d", (unsigned int)newAdvancedConfig.unlatchDuration);
    ESP_LOGI("NukiBle.NukiLock", "autoUnLockTimeOut: %d", (unsigned int)newAdvancedConfig.autoLockTimeOut);
    ESP_LOGI("NukiBle.NukiLock", "autoUnLockDisabled: %d", (unsigned int)newAdvancedConfig.autoUnLockDisabled);
    ESP_LOGI("NukiBle.NukiLock", "nightModeEnabled: %d", (unsigned int)newAdvancedConfig.nightModeEnabled);
    ESP_LOGI("NukiBle.NukiLock", "nightModeStartTime Hour: %d", (unsigned int)newAdvancedConfig.nightModeStartTime[0]);
    ESP_LOGI("NukiBle.NukiLock", "nightModeStartTime Minute: %d", (unsigned int)newAdvancedConfig.nightModeStartTime[1]);
    ESP_LOGI("NukiBle.NukiLock", "nightModeEndTime Hour: %d", (unsigned int)newAdvancedConfig.nightModeEndTime[0]);
    ESP_LOGI("NukiBle.NukiLock", "nightModeEndTime Minute: %d", (unsigned int)newAdvancedConfig.nightModeEndTime[1]);
    ESP_LOGI("NukiBle.NukiLock", "nightModeAutoLockEnabled: %d", (unsigned int)newAdvancedConfig.nightModeAutoLockEnabled);
    ESP_LOGI("NukiBle.NukiLock", "nightModeAutoUnlockDisabled: %d", (unsigned int)newAdvancedConfig.nightModeAutoUnlockDisabled);
    ESP_LOGI("NukiBle.NukiLock", "nightModeImmediateLockOnStart: %d", (unsigned int)newAdvancedConfig.nightModeImmediateLockOnStart);
    ESP_LOGI("NukiBle.NukiLock", "autoLockEnabled: %d", (unsigned int)newAdvancedConfig.autoLockEnabled);
    ESP_LOGI("NukiBle.NukiLock", "immediateAutoLockEnabled: %d", (unsigned int)newAdvancedConfig.immediateAutoLockEnabled);
    ESP_LOGI("NukiBle.NukiLock", "autoUpdateEnabled: %d", (unsigned int)newAdvancedConfig.autoUpdateEnabled);
  }
}

void logWifiScanEntry(WifiScanEntry wifiScanEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "ssid: %s", (const char*)wifiScanEntry.ssid);
    ESP_LOGI("NukiBle.NukiLock", "type: %d", (unsigned int)wifiScanEntry.type);
    ESP_LOGI("NukiBle.NukiLock", "signal raw: %d", (unsigned int)wifiScanEntry.signal);
    ESP_LOGI("NukiBle.NukiLock", "signal: %d", (unsigned int)(wifiScanEntry.signal & 255));
  }
}

void logMqttConfig(MqttConfig mqttConfig, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "enabled: %d", (unsigned int)mqttConfig.enabled);
    ESP_LOGI("NukiBle.NukiLock", "hostName: %s", (const char*)mqttConfig.hostName);
    ESP_LOGI("NukiBle.NukiLock", "userName: %s", (const char*)mqttConfig.userName);
    ESP_LOGI("NukiBle.NukiLock", "secureConnection: %d", (unsigned int)mqttConfig.secureConnection);
    ESP_LOGI("NukiBle.NukiLock", "autoDiscovery: %d", (unsigned int)mqttConfig.autoDiscovery);
    ESP_LOGI("NukiBle.NukiLock", "lockingEnabled: %d", (unsigned int)mqttConfig.lockingEnabled);
  }
}

void logMqttConfigForMigration(MqttConfigForMigration mqttConfigForMigration, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "enabled: %d", (unsigned int)mqttConfigForMigration.enabled);
    ESP_LOGI("NukiBle.NukiLock", "hostName: %s", (const char*)mqttConfigForMigration.hostName);
    ESP_LOGI("NukiBle.NukiLock", "userName: %s", (const char*)mqttConfigForMigration.userName);
    ESP_LOGI("NukiBle.NukiLock", "secureConnection: %d", (unsigned int)mqttConfigForMigration.secureConnection);
    ESP_LOGI("NukiBle.NukiLock", "autoDiscovery: %d", (unsigned int)mqttConfigForMigration.autoDiscovery);
    ESP_LOGI("NukiBle.NukiLock", "lockingEnabled: %d", (unsigned int)mqttConfigForMigration.lockingEnabled);
    ESP_LOGI("NukiBle.NukiLock", "passphrase: %s", (const char*)mqttConfigForMigration.passphrase);
  }
}

void logWifiConfig(WifiConfig wifiConfig, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "serverBridgeId: %d", (unsigned int)wifiConfig.serverBridgeId);
    ESP_LOGI("NukiBle.NukiLock", "wifiEnabled: %d", (unsigned int)wifiConfig.wifiEnabled);
    ESP_LOGI("NukiBle.NukiLock", "wifiExpertSettings composed value: %d", (unsigned int)wifiConfig.wifiExpertSettings);
    ESP_LOGI("NukiBle.NukiLock", "expertSettingsMode: %d", (unsigned int)(wifiConfig.wifiExpertSettings & 3));
    ESP_LOGI("NukiBle.NukiLock", "broadcastFilterSettings: %d", (unsigned int)((wifiConfig.wifiExpertSettings >> 2) & 3));
    ESP_LOGI("NukiBle.NukiLock", "dtimSkipSettings: %d", (unsigned int)((wifiConfig.wifiExpertSettings >> 4) & 7));
    ESP_LOGI("NukiBle.NukiLock", "sseSkipSettings: %d", (unsigned int)((wifiConfig.wifiExpertSettings >> 7) & 7));
    ESP_LOGI("NukiBle.NukiLock", "powersafeMode: %d", (unsigned int)((wifiConfig.wifiExpertSettings >> 10) & 3));
    ESP_LOGI("NukiBle.NukiLock", "activePingEnabled: %d", (unsigned int)((wifiConfig.wifiExpertSettings >> 12) & 1));
  }
}

void logWifiConfigForMigration(WifiConfigForMigration wifiConfigForMigration, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "ssid: %s", (const char*)wifiConfigForMigration.ssid);
    ESP_LOGI("NukiBle.NukiLock", "type: %d", (unsigned int)wifiConfigForMigration.type);
    ESP_LOGI("NukiBle.NukiLock", "passphrase: %s", (const char*)wifiConfigForMigration.passphrase);
  }
}

void logKeypad2Config(Keypad2Config keypad2Config, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "updatePending: %d", (unsigned int)keypad2Config.updatePending);
    ESP_LOGI("NukiBle.NukiLock", "ledBrightness: %d", (unsigned int)keypad2Config.ledBrightness);
    ESP_LOGI("NukiBle.NukiLock", "batteryType: %d", (unsigned int)keypad2Config.batteryType);
    ESP_LOGI("NukiBle.NukiLock", "buttonMode: %d", (unsigned int)keypad2Config.buttonMode);
    ESP_LOGI("NukiBle.NukiLock", "lockAction: %d", (unsigned int)keypad2Config.lockAction);
  }
}

void logDoorSensorConfig(DoorSensorConfig doorSensorConfig, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "enabled: %d", (unsigned int)doorSensorConfig.enabled);
    ESP_LOGI("NukiBle.NukiLock", "doorAjarTimeout: %d", (unsigned int)doorSensorConfig.doorAjarTimeout);
    ESP_LOGI("NukiBle.NukiLock", "doorAjarLoggingEnabled: %d", (unsigned int)doorSensorConfig.doorAjarLoggingEnabled);
    ESP_LOGI("NukiBle.NukiLock", "doorStatusMismatchLoggingEnabled: %d", (unsigned int)doorSensorConfig.doorStatusMismatchLoggingEnabled);
  }
}

void logFingerprintEntry(FingerprintEntry fingerprintEntry, bool debug) {
  if (debug) {
    char hexString[65]; // 32 bytes * 2 chars + 1 null terminator
    for (size_t i = 0; i < 32; i++) {
        sprintf(&hexString[i*2], "%02x", fingerprintEntry.fingerprintId[i]);
    }
    hexString[64] = '\0';

    ESP_LOGI("NukiBle.NukiLock", "fingerprintId: %s", hexString);
    ESP_LOGI("NukiBle.NukiLock", "keypadCodeId: %d", (unsigned int)fingerprintEntry.keypadCodeId);
    ESP_LOGI("NukiBle.NukiLock", "name: %s", fingerprintEntry.name);
  }
}

void logAccessoryInfo(AccessoryInfo accessoryInfo, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "dateYear: %d", (unsigned int)accessoryInfo.dateYear);
    ESP_LOGI("NukiBle.NukiLock", "dateMonth: %d", (unsigned int)accessoryInfo.dateMonth);
    ESP_LOGI("NukiBle.NukiLock", "dateDay: %d", (unsigned int)accessoryInfo.dateDay);
    ESP_LOGI("NukiBle.NukiLock", "dateHour: %d", (unsigned int)accessoryInfo.dateHour);
    ESP_LOGI("NukiBle.NukiLock", "dateMinute: %d", (unsigned int)accessoryInfo.dateMinute);
    ESP_LOGI("NukiBle.NukiLock", "dateSecond: %d", (unsigned int)accessoryInfo.dateSecond);
    ESP_LOGI("NukiBle.NukiLock", "accessoryNukiId: %d", (unsigned int)accessoryInfo.accessoryNukiId);
    ESP_LOGI("NukiBle.NukiLock", "accessoryType: %d", (unsigned int)accessoryInfo.accessoryType);
    ESP_LOGI("NukiBle.NukiLock", "firmwareVersion: %d.%d.%d", accessoryInfo.firmwareVersion[0], accessoryInfo.firmwareVersion[1], accessoryInfo.firmwareVersion[2]);
    ESP_LOGI("NukiBle.NukiLock", "hardwareRevision: %d.%d", accessoryInfo.hardwareRevision[0], accessoryInfo.hardwareRevision[1]);
    ESP_LOGI("NukiBle.NukiLock", "productVariantDifferentiator: %d", (unsigned int)accessoryInfo.productVariantDifferentiator);
    ESP_LOGI("NukiBle.NukiLock", "mostRecentBatteryVoltage: %d", (unsigned int)accessoryInfo.mostRecentBatteryVoltage);
    ESP_LOGI("NukiBle.NukiLock", "mostRecentTemperature: %d", (unsigned int)accessoryInfo.mostRecentTemperature);
  }
}

void logDailyStatistics(DailyStatistics dailyStatistics, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "dateYear: %d", (unsigned int)dailyStatistics.dateYear);
    ESP_LOGI("NukiBle.NukiLock", "dateMonth: %d", (unsigned int)dailyStatistics.dateMonth);
    ESP_LOGI("NukiBle.NukiLock", "dateDay: %d", (unsigned int)dailyStatistics.dateDay);
    //ESP_LOGI("NukiBle.NukiLock", "dateHour: %d", (unsigned int)dailyStatistics.dateHour);
    //ESP_LOGI("NukiBle.NukiLock", "dateMinute: %d", (unsigned int)dailyStatistics.dateMinute);
    //ESP_LOGI("NukiBle.NukiLock", "dateSecond: %d", (unsigned int)dailyStatistics.dateSecond);
    ESP_LOGI("NukiBle.NukiLock", "version: %d", (unsigned int)dailyStatistics.version);
    ESP_LOGI("NukiBle.NukiLock", "countSuccessfulLockActions: %d", (unsigned int)dailyStatistics.countSuccessfulLockActions);
    ESP_LOGI("NukiBle.NukiLock", "countErroneousLockActions: %d", (unsigned int)dailyStatistics.countErroneousLockActions);
    ESP_LOGI("NukiBle.NukiLock", "avgCurrentConsumptionLock: %d", (unsigned int)dailyStatistics.avgCurrentConsumptionLock);
    ESP_LOGI("NukiBle.NukiLock", "maxCurrentConsumptionLock: %d", (unsigned int)dailyStatistics.maxCurrentConsumptionLock);
    ESP_LOGI("NukiBle.NukiLock", "batteryMinStartVoltageLock: %d", (unsigned int)dailyStatistics.batteryMinStartVoltageLock);
    ESP_LOGI("NukiBle.NukiLock", "countSuccessfulUnlatchActions: %d", (unsigned int)dailyStatistics.countSuccessfulUnlatchActions);
    ESP_LOGI("NukiBle.NukiLock", "countErroneousUnlatchActions: %d", (unsigned int)dailyStatistics.countErroneousUnlatchActions);
    ESP_LOGI("NukiBle.NukiLock", "avgCurrentConsumptionUnlatch: %d", (unsigned int)dailyStatistics.avgCurrentConsumptionUnlatch);
    ESP_LOGI("NukiBle.NukiLock", "maxCurrentConsumptionUnlatch: %d", (unsigned int)dailyStatistics.maxCurrentConsumptionUnlatch);
    ESP_LOGI("NukiBle.NukiLock", "batteryMinStartVoltageUnlatch: %d", (unsigned int)dailyStatistics.batteryMinStartVoltageUnlatch);
    ESP_LOGI("NukiBle.NukiLock", "incomingCommands: %d", (unsigned int)dailyStatistics.incomingCommands);
    ESP_LOGI("NukiBle.NukiLock", "outgoingCommands: %d", (unsigned int)dailyStatistics.outgoingCommands);
    ESP_LOGI("NukiBle.NukiLock", "maxTemperature: %d", (unsigned int)dailyStatistics.maxTemperature);
    ESP_LOGI("NukiBle.NukiLock", "minTemperature: %d", (unsigned int)dailyStatistics.minTemperature);
    ESP_LOGI("NukiBle.NukiLock", "avgTemperature: %d", (unsigned int)dailyStatistics.avgTemperature);
    ESP_LOGI("NukiBle.NukiLock", "numDoorSensorStatusChanges: %d", (unsigned int)dailyStatistics.numDoorSensorStatusChanges);
    ESP_LOGI("NukiBle.NukiLock", "maxBatteryPercentage: %d", (unsigned int)dailyStatistics.maxBatteryPercentage);
    ESP_LOGI("NukiBle.NukiLock", "minBatteryPercentage: %d", (unsigned int)dailyStatistics.minBatteryPercentage);
    ESP_LOGI("NukiBle.NukiLock", "idleTime: %d", (unsigned int)dailyStatistics.idleTime);
    ESP_LOGI("NukiBle.NukiLock", "connectionTime: %d", (unsigned int)dailyStatistics.connectionTime);
    ESP_LOGI("NukiBle.NukiLock", "actionTime: %d", (unsigned int)dailyStatistics.actionTime);
  }
}

void logGeneralStatistics(GeneralStatistics generalStatistics, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "version: %d", (unsigned int)generalStatistics.version);
    ESP_LOGI("NukiBle.NukiLock", "firstCalibrationYear: %d", (unsigned int)generalStatistics.firstCalibrationYear);
    ESP_LOGI("NukiBle.NukiLock", "firstCalibrationMonth: %d", (unsigned int)generalStatistics.firstCalibrationMonth);
    ESP_LOGI("NukiBle.NukiLock", "firstCalibrationDay: %d", (unsigned int)generalStatistics.firstCalibrationDay);
    ESP_LOGI("NukiBle.NukiLock", "calibrationCount: %d", (unsigned int)generalStatistics.calibrationCount);
    ESP_LOGI("NukiBle.NukiLock", "lockActionCount: %d", (unsigned int)generalStatistics.lockActionCount);
    ESP_LOGI("NukiBle.NukiLock", "unlatchCount: %d", (unsigned int)generalStatistics.unlatchCount);
    ESP_LOGI("NukiBle.NukiLock", "lastRebootDateYear: %d", (unsigned int)generalStatistics.lastRebootDateYear);
    ESP_LOGI("NukiBle.NukiLock", "lastRebootDateMonth: %d", (unsigned int)generalStatistics.lastRebootDateMonth);
    ESP_LOGI("NukiBle.NukiLock", "lastRebootDateDay: %d", (unsigned int)generalStatistics.lastRebootDateDay);
    ESP_LOGI("NukiBle.NukiLock", "lastRebootDateHour: %d", (unsigned int)generalStatistics.lastRebootDateHour);
    ESP_LOGI("NukiBle.NukiLock", "lastRebootDateMinute: %d", (unsigned int)generalStatistics.lastRebootDateMinute);
    ESP_LOGI("NukiBle.NukiLock", "lastRebootDateSecond: %d", (unsigned int)generalStatistics.lastRebootDateSecond);
    ESP_LOGI("NukiBle.NukiLock", "lastChargeDateYear: %d", (unsigned int)generalStatistics.lastChargeDateYear);
    ESP_LOGI("NukiBle.NukiLock", "lastChargeDateMonth: %d", (unsigned int)generalStatistics.lastChargeDateMonth);
    ESP_LOGI("NukiBle.NukiLock", "lastChargeDateDay: %d", (unsigned int)generalStatistics.lastChargeDateDay);
    ESP_LOGI("NukiBle.NukiLock", "lastChargeDateHour: %d", (unsigned int)generalStatistics.lastChargeDateHour);
    ESP_LOGI("NukiBle.NukiLock", "lastChargeDateMinute: %d", (unsigned int)generalStatistics.lastChargeDateMinute);
    ESP_LOGI("NukiBle.NukiLock", "lastChargeDateSecond: %d", (unsigned int)generalStatistics.lastChargeDateSecond);
    ESP_LOGI("NukiBle.NukiLock", "initialBatteryVoltage: %d", (unsigned int)generalStatistics.initialBatteryVoltage);
    ESP_LOGI("NukiBle.NukiLock", "numActionsDuringBatteryCycle: %d", (unsigned int)generalStatistics.numActionsDuringBatteryCycle);
    ESP_LOGI("NukiBle.NukiLock", "numUnexpectedReboots: %d", (unsigned int)generalStatistics.numUnexpectedReboots);
  }
}

void logInternalLogEntry(InternalLogEntry internalLogEntry, bool debug) {
  if (debug) {
    ESP_LOGI("NukiBle.NukiLock", "[%d] type: %d authId: %d %d-%d-%d %d:%d:%d",
      (unsigned int)internalLogEntry.index,
      (unsigned int)internalLogEntry.loggingType,
      (unsigned int)internalLogEntry.authId,
      internalLogEntry.timeStampYear,
      internalLogEntry.timeStampMonth,
      internalLogEntry.timeStampDay,
      internalLogEntry.timeStampHour,
      internalLogEntry.timeStampMinute,
      internalLogEntry.timeStampSecond
    );
    ESP_LOGI("NukiBle.NukiLock", "data: %d", (unsigned int)internalLogEntry.data);
  }
}

} // namespace Nuki