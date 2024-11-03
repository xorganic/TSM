#ifndef SHADOW_INJECT_H
#define SHADOW_INJECT_H

void initialize_shadow_injection();       // Configurează mediul pentru injectare shadow
void inject_to_shadow(const char *payload);  // Injectează payload-ul în shadow cache
void cleanup_shadow_injection();          // Curăță injectarea din shadow cache

#endif // SHADOW_INJECT_H

