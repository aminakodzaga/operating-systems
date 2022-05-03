# Fashell(Amina & Fatima Shell)
Implementation of a Shell in C program
## Group Members
Amina Kodžaga

Fatima Ademović
## Files 
shell.c
## Answers from Task 1.5
## Q1:Do the following actions require the OS to use kernel mode or user mode is sufficient?
● A program wishes to read data from the hard drive. 
A ```read``` usually necessitates a hardware connection. Hardware access is time-consuming and error-prone, and it might cause the computer to become unusable. 
The operating system uses drivers to control the computer's hardware.
When a driver receives a ```read``` it sends a set of commands to the disk controller, instructing it to read the output,
pass it to main memory and so on. These are potentially dangerous operations that should never be performed in User Mode.

● The hardware clock is used to get the current time.
You can read memory-mapped registers from user mode if the hardware clocks include them, as long as the mapped region does not contain sensitive data.
## Q2: Explain the purpose of a system call. There are different sets of system calls: list them and give at least 2 examples of a system call for each category.
A system call is a way for a running program and the operating system to communicate. It allows the user to access the services provided by the operating system. 
These system calls make use of C, C++ and assembly language processes. Each operating system has its own name for each system call.
To identify each system call, it is given a unique number.
## System Calls:
## *1. Process Control:*
A program's execution is a procedure. Before a process can be executed, it must first be loaded into main memory.
While it is operating, it may be essential to wait, terminate, or start and stop child processes.

Unix/Windows examples:

``` ● fork()/CreateProcess() ```

``` ● wait()/WaitForSingleObject() ```

``` ● exit()/ExitProcess() ```

## *2. File Management:* 
The technology allows us to create and delete files. For the creation and deletion actions, the file's name and other properties are required.
File properties provide information such as the file type, size, security codes and accounting data. Systems utilize these attributes to perform operations on files    and folders. Once the file has been created, we can open and use it. File activities such as reading, writing and moving are also possible with the system.

Unix/Windows examples:

``` ●open()/CreateFile() ```

``` ●read()/ReadFile() ``` 

``` ●write()/WriteFile() ```

``` ●close()/CloseHandle() ```

## *3. Device Management:*
When a process is running, it necessitates the use of a number of resources in order to complete its task. These resources include main memory, hard drives, data, and so forth. If the resource is available, it is assigned to the process. Once the resource has been allocated to the device, the process can read, write and move it.

Unix/Windows examples:

``` ●read()/ReadConsole()```

``` ●write()/WriteConsole() ```

``` ●ioctl()/SetConsoleMode() ```

## *4. Information Maintenance:*
Data is transferred between user program and the operating system using system calls. System information includes the current date and time, the number of active users, the operating system version number, the amount of free memory or disk space and so forth. System functions such as get process characteristics and update program characteristics are used by the operating system to keep information about all of its processes.

Unix/Windows examples:

``` ●getpid()/GetCurrentProcessID() ```

``` ●alarm()/SetTimer() ```

``` ●sleep()/Sleep() ```

## *5. Communication:*
Processes in the system communicate with one another. The two communication models are message queue and shared memory. For message transfer, the sender process links to the receiving process by supplying the receiving process name or identity. The system disconnects the communicating processes once the conversation is concluded.

Unix/Windows examples:

``` ●pipe()/CreatePipe() ```

``` ●mmap()/MapViewOfFile() ```

``` ●shmget()/CreateFileMapping() ```

## Outline of the Assignment
We'll go through all of the important elements (commands) that were employed in the shell's implementation in the explanation.

``` cp ```

*This command copies files, groups of files, or directories.*
*Options: *

 **1. -i(interactive):** *Interactive copying is represented by the letter i. Before overwriting the target file, the system warns the user with this choice.*
 
 **2. -b(backup):** *The cp command creates a backup of the destination file in the same folder when this option is used.*
 
 **3. -f(force):** *If the system can't open the destination file because the user doesn't have writing permission, the -f option is used to destroy the file first, then copy the content from the source to the destination.*
 
 **4. -r or -R:** *The directory structure is being copied. The cp command copies the entire directory structure recursively with this option.*
 
 **5. -p(preserve):** *Cp preserves the properties of each source file (permission bits, ownership, etc.) in the matching destination file when using the -p option.*

``` history ```

*The history command is used to see what commands have been run previously.*

*Options:* 

**1. -c:** *Delete all of the entries in the history list to clear it.*

**2. -d offset:** *Delete the history entry at offset OFFSET*

**3. -a:** *Add the lines from this session's history to the history file.*

**4. -n:** *Read all history lines from the history file that haven't already been read.*

**5. -r:** *Read the contents of the history file and add them to the history list.*

**6: -w:** *Append the current history to the history list by writing it to the history file.*

**7. -p:** *Expand each ARG's history and display the result without saving it in the history list.*

**8. -s:** *Add the ARGs as a single entry to the history list.*

``` free ```

*The free command displays the entire amount of free space in the system, as well as the amount of memory used and swap memory, as well as the kernel's buffers.*

*Options:*

**1. -b, bytes:** *It shows the amount of memory in bytes.*

**2. -k, kilo:** *It shows how much memory you have in kilobytes.*

**3. -m, mega:** *It shows how much memory you have in megabytes.*

**4. -g, giga:** *It shows how much memory you have in gigabytes.*

**5. tera:** *It displays the amount of memory in terabytes.*

**6. -h, human:** *All output columns are automatically scaled to the smallest three-digit unit, and the units of print out are also displayed. B (bytes), K (kilos), M (megas), G (gigas), and T (terabytes) are the units utilized (teras).*

**7. -c, count:** *It repeats the output c times and this option is compatible with the -s option.*

**8. -l, lohi:** *t shows the detailed low and high memory statistics.*

**9. -o, old:** *This option turns off the buffer adjusted line's display.*

**10. -s, seconds:** *This option allows you to continuously display the output after a delay of s seconds. In practice, the usleepsystem function is used to calculate microsecond delay periods.*

**11. -t, total:** *It adds a line to the output that shows the column totals.*

**12. -help:** *It displays a help message and exit.*

**13. -v, version:** *It exits after displaying version information.*

``` fortune/ Random Quotes```
*Randomly displays frightening, uplifting, silly, or sarcastic statements from a quotation database.*

*Options:*

**1. -a:** *Select from any database, regardless of whether or not it is judged "offensive."*

**2. -e:** *Make the chance of picking a fortune file equal to the chance of picking any other file.*

**3. -f:** *Do not print a fortune; instead, publish a list of all fortune files that would have been searched.*

**4. -i:** *Make regular expression searching case-insensitive when used with -m.*

**5. -l:** *Only use quotations that are longer than the -n length, or 160 characters if -n is not supplied.*

**6. -m:** *[pattern] Print all fortunes matching the regular expression specified in [pattern]*

**7. -n:** *[length] Override the length used by -l and -s to determine whether a message is "long" or "short" (default 160 characters).*

**8. -o:** *Only use databases that are "offensive."*

**9. -s:** *Only utilize quotations that are less than the length supplied by -n, or 160 characters if -n is not specified.*

**10.-w:** *Wait a certain amount of time before terminating; this is important in instances when a fortune must be read before the screen is cleared.*

``` vfork```

*Vfork() is a system call that starts a new process. Because both processes share the same address space, child process suspends parent process execution until child process completes its execution, whereas fork() child and parent processes have independent memory spaces.*

```forkbomb```

*A fork bomb is a type of denial-of-service (DoS) attack that targets a Linux system. To fill memory, it forks processes indefinitely.*

## Instructions for compiling

```gcc shell.c -o shell```

```./shell```

## Challenges
Lack of knowledge and resources 

Difficulties in finding resources

## Sources/Tutorials

https://www.guru99.com/introduction-to-shell-scripting.html

https://www.tutorialspoint.com/c_standard_library/c_function_free.htm

https://securitronlinux.com/bejiitaswrath/very-useful-c-program-print-a-random-fortune/

https://www.programiz.com/c-programming/c-file-input-output

https://tuxthink.blogspot.com/2012/12/c-program-in-linux-to-find-username-of.html







