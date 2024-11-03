
#include <windows.h>
#include "privilege_escalation.h"
#include "utils.h"

// Funcția externă Assembly pentru escaladarea privilegiilor
extern int privilege_escalate();

/**
 * escalate_privileges
 * Obține permisiuni administrative apelând funcția privilege_escalate din Assembly.
 *
 * @return 1 dacă escaladarea a avut succes, 0 altfel
 */
int escalate_privileges() {
    log_event("Attempting privilege escalation...");

    int success = privilege_escalate();  // Apel Assembly pentru escaladare
    if (success) {
        log_event("Privilege escalation successful.");
    } else {
        log_event("Privilege escalation failed.");
    }

    return success;
}
