#ifndef EVASION_H
#define EVASION_H

/**
 * is_sandbox_detected
 * Detectează prezența unui sandbox pe baza unor tehnici de timing și verificări de interacțiune.
 * Folosește funcția `detect_sandbox` din Assembly pentru măsurători rapide de execuție,
 * detectând eventuale întârzieri caracteristice mediilor de sandbox.
 *
 * @return 1 dacă un sandbox este detectat, 0 altfel
 */
int is_sandbox_detected();

/**
 * is_vm_detected
 * Verifică dacă sistemul rulează într-o mașină virtuală (VM).
 * Folosește instrucțiuni specifice, cum ar fi `cpuid`, pentru a identifica semnele comune
 * unui mediu virtualizat, precum VMware sau VirtualBox.
 *
 * @return 1 dacă o mașină virtuală este detectată, 0 altfel
 */
int is_vm_detected();

/**
 * is_edr_detected
 * Detectează prezența unui EDR (Endpoint Detection and Response).
 * Funcția din Assembly poate verifica hook-urile sau procesele specifice soluțiilor EDR.
 *
 * @return 1 dacă un EDR activ este detectat, 0 altfel
 */
int is_edr_detected();

#endif // EVASION_H
