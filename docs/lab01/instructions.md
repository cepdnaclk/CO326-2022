---
layout: blank
permalink: /lab01/instructions/
---

<h2>Lab 2 - Parallel Port </h2>

<h3>Introduction</h3>

In this lab, you are going to try parallel port communication, where a parallel port is used as the interface to communicate with a seven-segment display. Due to the prevailing conditions in the country, you are going to do this lab as a remote lab. Modify the codes you have implemented in the pre-lab according to the given circuit at the lab.

The detailed lab sheet can be downloaded from the *Course Page*.

<div class="container">
<img src="{{ '/assets/img/parallel_port.gif' | relative_url }}" class="img img-thumb mr-auto" />
</div>

<h3>Lab Exercises</h3>

<b><u>Task 01 (Exercise 1): Display 0-9 numbers on a single 7 segment display</u></b>

Implement a timer counter, to count from 0 to 9.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>
#include <time.h>

#define DATA_PORT 0x378         // Parallel port base addr
#define STATUS_PORT DATA_PORT+1
#define CONTROL_PORT DATA_PORT+2

unsigned char data;

int main() {

    if (ioperm(DATA_PORT,1,1)){

        fprintf(stderr, "Access denied to %x\n", DATA_PORT);
        exit(1);
    }

    // outb(data, DATA_PORT);
    // sleep();
}
```

Compile Instructions:

```bash
gcc -o ./ex1 ./ex1.c
sudo ./ex1
```


<b><u>Task 02 (Exercise 2): Implement an up/down counter</u></b>

Improve the previous implementation as counter.
- Can count numbers from 0 to 9.
- Count Up should increase the value shown in the 7 segment display by 1.
- Count Down should decrease the value shown in the 7 segment display by 1.

You can use the buttons in the right side of this window to give the input signals into the parallel port.

Count Up signal is wired to S7 port and Count Down is wired to S6 port.

<div class="container">
<img src="{{ '/assets/img/lab1_circuit.jpg' | relative_url }}" class="img img-thumb mr-auto" />
</div>

### Note

Please make sure to delete your lab codes from the remote machine before log out from the *Team Viewer* session
