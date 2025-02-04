/**
 * A BLE client example to connect to Nuki smartlock 2.0
 * author Jeroen
 */

#include "NukiLock.h"
#include "NukiConstants.h"
#include "BleScanner.h"
 
uint32_t deviceId = 2020001;
std::string deviceName = "frontDoor";
NukiLock::NukiLock nukiLock(deviceName, deviceId);
BleScanner::Scanner scanner;

NukiLock::KeyTurnerState retrievedKeyTurnerState;
NukiLock::BatteryReport _batteryReport;
std::list<NukiLock::LogEntry> requestedLogEntries;
std::list<Nuki::KeypadEntry> requestedKeypadEntries;
std::list<Nuki::AuthorizationEntry> requestedAuthorizationEntries;
std::list<NukiLock::TimeControlEntry> requestedTimeControlEntries;
    
void addKeypadEntry() {
    Nuki::NewKeypadEntry newKeypadEntry;
    unsigned char nameBuff[20] = "test";
    
    newKeypadEntry.code = 111111;
    memcpy(newKeypadEntry.name, nameBuff, 20);
    newKeypadEntry.timeLimited = 1;
    newKeypadEntry.allowedFromYear = 2022;
    newKeypadEntry.allowedFromMonth = 2;
    newKeypadEntry.allowedFromDay = 1;
    newKeypadEntry.allowedFromHour = 0;
    newKeypadEntry.allowedFromMin = 0;
    newKeypadEntry.allowedFromSec = 0;
    newKeypadEntry.allowedUntilYear = 2023;
    newKeypadEntry.allowedUntilMonth = 1;
    newKeypadEntry.allowedUntilDay = 1;
    newKeypadEntry.allowedUntilHour = 0;
    newKeypadEntry.allowedUntilMin = 0;
    newKeypadEntry.allowedUntilSec = 0;
    newKeypadEntry.allowedFromTimeHour = 0;
    newKeypadEntry.allowedFromTimeMin = 0;
    newKeypadEntry.allowedUntilTimeHour = 23;
    newKeypadEntry.allowedUntilTimeMin = 59;
    
    nukiLock.addKeypadEntry(newKeypadEntry);
}
    
void batteryReport() {
    uint8_t result = nukiLock.requestBatteryReport(&_batteryReport);
    if (result == 1) {
        ESP_LOGD("Nuki", "Bat report voltage: %d Crit state: %d, start temp: %d", _batteryReport.batteryVoltage, _batteryReport.criticalBatteryState, _batteryReport.startTemperature);
    } else {
        ESP_LOGD("Nuki", "Bat report failed: %d", result);
    }
}
    
bool keyTurnerState() {
    uint8_t result = nukiLock.requestKeyTurnerState(&retrievedKeyTurnerState);
    if (result == 1) {

        char current_lock_state_as_string[30] = {0};
        NukiLock::lockstateToString(retrievedKeyTurnerState.lockState, current_lock_state_as_string);

        ESP_LOGD("Nuki", "Bat crit: %d, Bat perc: %d lock state: %s %d:%d:%d",
            nukiLock.isBatteryCritical(), nukiLock.getBatteryPerc(), current_lock_state_as_string, retrievedKeyTurnerState.currentTimeHour,
            retrievedKeyTurnerState.currentTimeMinute, retrievedKeyTurnerState.currentTimeSecond);
    } else {
        ESP_LOGD("Nuki", "cmd failed: %u", result);
    }
    return result;
}
    
void requestLogEntries() {
    uint8_t result = nukiLock.retrieveLogEntries(0, 10, 0, true);
    if (result == 1) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        nukiLock.getLogEntries(&requestedLogEntries);
        std::list<NukiLock::LogEntry>::iterator it = requestedLogEntries.begin();
        while (it != requestedLogEntries.end()) {
            ESP_LOGD("Nuki", "Log[%lu] %u-%u-%u %u:%u:%u", it->index, it->timeStampYear, it->timeStampMonth, it->timeStampDay, it->timeStampHour, it->timeStampMinute, it->timeStampSecond);
            it++;
        }
    } else {
        ESP_LOGD("Nuki", "get log failed: %u", result);
    }
}
    
void requestKeyPadEntries() {
    uint8_t result = nukiLock.retrieveKeypadEntries(0, 10);
    if (result == 1) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        nukiLock.getKeypadEntries(&requestedKeypadEntries);
        std::list<Nuki::KeypadEntry>::iterator it = requestedKeypadEntries.begin();
        while (it != requestedKeypadEntries.end()) {
            ESP_LOGD("Nuki", "Keypad entry[%u] %lu", it->codeId, it->code);
            it++;
        }
    } else {
        ESP_LOGD("Nuki", "get keypadentries failed: %u", result);
    }
}
    
void requestAuthorizationEntries() {
    uint8_t result = nukiLock.retrieveAuthorizationEntries(0, 10);
    if (result == 1) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        nukiLock.getAuthorizationEntries(&requestedAuthorizationEntries);
        std::list<Nuki::AuthorizationEntry>::iterator it = requestedAuthorizationEntries.begin();
        while (it != requestedAuthorizationEntries.end()) {
            ESP_LOGD("Nuki", "Authorization entry[%lu] type: %u name: %s", it->authId, it->idType, it->name);
            it++;
        }
    } else {
        ESP_LOGD("Nuki", "get authorization entries failed: %u", result);
    }
}
    
void setPincode(uint16_t pincode) {
    uint8_t result = nukiLock.setSecurityPin(pincode);
    if (result == 1) {
        ESP_LOGD("Nuki", "Set pincode done");
    
    } else {
        ESP_LOGD("Nuki", "Set pincode failed: %u", result);
    }
}

void addTimeControl(uint8_t weekdays, uint8_t hour, uint8_t minute, NukiLock::LockAction lockAction) {
    NukiLock::NewTimeControlEntry newEntry;
    newEntry.weekdays = weekdays;
    newEntry.timeHour = hour;
    newEntry.timeMin = minute;
    newEntry.lockAction = lockAction;
    
    nukiLock.addTimeControlEntry(newEntry);
}
    
void requestTimeControlEntries() {
    Nuki::CmdResult result = nukiLock.retrieveTimeControlEntries();
    if (result == Nuki::CmdResult::Success) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        nukiLock.getTimeControlEntries(&requestedTimeControlEntries);
        std::list<NukiLock::TimeControlEntry>::iterator it = requestedTimeControlEntries.begin();
        while (it != requestedTimeControlEntries.end()) {

            char lock_action_as_string[30] = {0};
            NukiLock::lockactionToString(it->lockAction, lock_action_as_string);

            ESP_LOGD("Nuki", "TimeEntry[%u] weekdays:%d %d:%d enabled: %d lock action: %s", it->entryId, it->weekdays, it->timeHour, it->timeMin, it->enabled, lock_action_as_string);
            it++;
        }
    } else {
        ESP_LOGD("Nuki", "get log failed: %u, error %d", result, static_cast<int>(nukiLock.getLastError()));
    }
}
    
void getConfig() {
    NukiLock::Config config;
    if (nukiLock.requestConfig(&config) == 1) {
        ESP_LOGD("Nuki", "Name: %s", config.name);
    } else {
        ESP_LOGW("Nuki", "getConfig failed");
    }
    
}
    
bool notified = false;
class Handler: public Nuki::SmartlockEventHandler {
    public:
        virtual ~Handler() {};
        void notify(Nuki::EventType eventType) {
            notified = true;
        }
};
    
Handler handler;
    
extern "C" void app_main() {
    ESP_LOGD("Nuki", "Starting NUKI BLE...");
    scanner.initialize();
    nukiLock.registerBleScanner(&scanner);
    nukiLock.initialize();

    if (nukiLock.isPairedWithLock()) {
        ESP_LOGD("Nuki", "paired");
        nukiLock.setEventHandler(&handler);
        getConfig();
        nukiLock.enableLedFlash(false);
    }

    // nukiLock.savePincode(9999);
    // nukiLock.unPairNuki();

    while(1) {
        scanner.update();
        if (!nukiLock.isPairedWithLock()) {
            if (nukiLock.pairNuki() == Nuki::PairingResult::Success) {
                ESP_LOGD("Nuki", "paired");
                nukiLock.setEventHandler(&handler);
                getConfig();
            }
        }
    
        if (notified) {
            if (keyTurnerState()) {
                notified = false;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}