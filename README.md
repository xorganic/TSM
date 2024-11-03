# Temporal Shadow Manipulator (TSM)

**Temporal Shadow Manipulator (TSM)** is a sophisticated red team tool for establishing stealth persistence and bypassing security controls on Windows systems. Built with high precision, TSM leverages Assembly and C to interact directly with Windows internals, avoiding standard APIs and evading detection through unconventional shadow cache manipulation, temporary file obfuscation, and direct syscall invocation.

---

## Key Technical Features

### Shadow Cache Injection
TSM injects payloads into Windows' Volume Shadow Copy (shadow cache), a less-monitored storage area often overlooked by traditional EDR solutions. By directly manipulating this area with syscall-level instructions, TSM achieves persistent storage while evading most conventional detection mechanisms. Unlike common persistence techniques, this approach is more covert and significantly reduces the footprint.

- **Assembly-based Syscall Manipulation**: Avoids API calls, directly invoking syscalls to interact with the shadow cache, making detection harder.
- **Selective Cleanup and Restoration**: Automatically cleans up traces and regenerates payloads if detected or removed.

### Temporary File Staging
TSM utilizes temporary directories to store and manage payloads. This enables payload staging and regeneration with minimal observable I/O activity, allowing it to blend in with normal system behavior.

- **Obfuscation through Hidden File Attributes**: Sets specific file attributes to hide temporary files from standard directory views.
- **Dynamic Payload Generation**: Uses randomization and unique naming conventions to evade pattern-based detection in temporary storage.

### Evasion and Anti-Sandbox Techniques
TSM’s evasion techniques are engineered to identify and bypass sandbox environments, virtual machines, and active EDR solutions. Low-level CPU checks and memory probing allow it to determine execution within virtualized or monitored environments.

- **CPUID and RDTSC Checks**: Detects virtual machines by analyzing hardware-level data returned from CPU instructions.
- **Memory Artefact Scanning**: Identifies common sandbox markers within system memory, such as hooks and debug artifacts set by analysis tools.

### Privilege Escalation
For scenarios requiring elevated privileges, TSM attempts to escalate user permissions through direct token manipulation. Assembly-based functions bypass common Windows security layers, invoking syscalls to manage tokens at a granular level.

- **Direct Syscall-Based Token Manipulation**: Bypasses Windows API to avoid hooks set by security solutions.
- **Configurable Privilege Targets**: Attempts elevation based on configuration settings, allowing tailored privilege escalation efforts per engagement requirements.

### Persistent Payload Regeneration
TSM employs advanced persistence strategies that utilize both shadow cache and temporary file regeneration to maintain its foothold. Even if initial payloads are removed, TSM can regenerate them under specific conditions, leveraging Windows startup behaviors to re-inject its code.

- **Self-Regenerating Shadow Cache Payloads**: Restores payloads automatically in the shadow cache if deleted.
- **Auto-Startup via Temp Files**: Executes from temporary storage upon each reboot to re-establish presence without modifying critical system files.

---

## Usage Instructions

### Prerequisites
Ensure the following tools and libraries are available for compilation and configuration:
- **GCC**: To compile C modules.
- **NASM**: For compiling syscall-based Assembly files.
- **JSON-C**: Parses configuration options from `config.json`.

### Compilation
Compile the project by executing:
```bash
make all
```

The output TSM.exe will be generated in the build/ directory.

Command-Line Flags
Flag	Description
--inject-shadow	Activates shadow cache injection routines
--persistence	Enables persistence via shadow cache and temporary files
--evasion	Enables sandbox/VM/EDR evasion mechanisms
--priv-escalate	Attempts to elevate privileges
--debug	Enables verbose logging for debugging purposes
--clean	Cleans up all created files and injected payloads
Examples
To execute TSM with shadow injection and persistence enabled:
```
TSM.exe --inject-shadow --persistence
```
For privilege escalation and evasion:
```
TSM.exe --priv-escalate --evasion
```
Configuration
JSON Configuration (config.json)
TSM's behavior can be customized via config.json to adjust targets and operational settings dynamically:

target_directories: Specifies directories to stage payloads within shadow and temp files.
enable_persistence: Boolean to enable or disable persistent payload regeneration.
escalate_privileges: Boolean to activate privilege escalation routines as required.
Security and Usage Considerations
TSM is strictly for authorized red team use and testing in isolated environments. Unauthorized use may violate laws and ethical guidelines. Use only in environments with explicit permission.
