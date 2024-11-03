#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "utils.h"

// Logare simplă într-un fișier text (ex. log.txt)
void log_event(const char *message) {
    FILE *file = fopen("log.txt", "a");
    if (file) {
        fprintf(file, "%s\n", message);
        fclose(file);
    }
}

// Funcție pentru citirea unei valori din config.json
int read_config(const char *key) {
    FILE *file = fopen("resources/config.json", "r");
    if (!file) {
        log_event("Failed to open config.json");
        return 0;
    }

    struct json_object *parsed_json;
    struct json_object *value;
    char buffer[2048];

    fread(buffer, sizeof(char), 2048, file);
    fclose(file);

    parsed_json = json_tokener_parse(buffer);
    if (json_object_object_get_ex(parsed_json, key, &value)) {
        return json_object_get_boolean(value);
    } else {
        log_event("Config key not found.");
        return 0;
    }
}


