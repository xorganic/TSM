# D@rkCondwit




A Covert Remote Access Tool
##Installation:

    No installation required. Simply download the code and compile it using a C++ compiler.

## Usage:

    1-Run the compiled executable file on the victim's machine.
    
    2-Replace the IP address and port number in the code with that of the attacker's machine.
    
    3-Run a netcat listener on the specified port to receive the command output.
    
    4-Connect to the victim's machine using the specified IP address and port number.
    
    5-Once connected, the input/output will be redirected to the attacker's machine and
    the attacker can execute commands on the victim's machine.
    
    6-To exit, simply terminate the netcat listener and the remote process will exit automatically.

## Note:

    This code is for educational purposes only and should not be used for illegal activities.
    The victim machine must have the necessary runtime libraries installed for the code to run.
    The code is provided as is, without any warranties or guarantees.
