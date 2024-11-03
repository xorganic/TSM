section .text
    global detect_sandbox
    global detect_vm
    global detect_edr

; Detectează dacă sistemul rulează într-un sandbox
detect_sandbox:
    ; Folosim instrucțiunea RDTSC pentru a măsura un delay de execuție
    rdtsc                     ; Timpul curent în EAX:EDX
    mov r8, eax
    ; (simulare simplă) Verificăm dacă delay-ul este prea scurt
    rdtsc
    sub eax, r8
    cmp eax, 100              ; Threshold pentru sandbox (ajustabil)
    jl sandbox_detected       ; Dacă e mai mic, e posibil sandbox
    xor rax, rax              ; Returnează 0 dacă nu e detectat sandbox
    ret

sandbox_detected:
    mov rax, 1                ; Returnează 1 dacă detectează sandbox
    ret

; Detectează dacă sistemul rulează într-un VM
detect_vm:
    mov eax, 1                ; Folosim CPUID pentru a verifica VMware
    cpuid
    mov rax, 0                ; Inițial, presupunem că nu e VM
    cmp ecx, 'VMXh'           ; Verifică ECX pentru indicator VMXh (specific VMware)
    jne not_vm
    mov rax, 1                ; Returnează 1 dacă e VM
not_vm:
    ret

; Detectează dacă există un EDR activ pe sistem
detect_edr:
    ; Aici se pot implementa verificări pentru hook-uri și procese de securitate
    xor rax, rax              ; Temporar, returnăm 0 pentru nicio detecție
    ret

