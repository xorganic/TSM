// evasion.c
#include "evasion.h"
#include "utils.h"

extern int detect_sandbox();
extern int detect_vm();
extern int detect_edr();

int is_sandbox_detected() {
    log_event("Checking for sandbox...");
    return detect_sandbox();
}

int is_vm_detected() {
    log_event("Checking for virtual machine...");
    return detect_vm();
}

int is_edr_detected() {
    log_event("Checking for EDR presence...");
    return detect_edr();
}

