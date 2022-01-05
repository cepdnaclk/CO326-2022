---
layout: blank
permalink: /lab01/instructions/
---

<h2>Lab 2 - Parallel Port </h2>

<h3>Introduction</h3>

In this lab, you are going to try parallel port communication, where a parallel port is used as the interface to communicate with a seven-segment display. Due to the prevailing conditions in the country, you are going to do this lab as a remote lab. Modify the codes you have implemented in the pre-lab according to the given circuit at the lab.

<div class="container">
<img src="{{ '/assets/img/parallel_port.gif' | relative_url }}" class="img img-thumb mr-auto" />
</div>

<h3>Lab Exercises</h3>

<b><u>Task 01: Display 0-9 numbers on a single 7 segment display</u></b>

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


<b><u>Task 02:
</u></b>

Implement the previous algorithm as counter.

- Count Up will increase the value shown in the 7 segment display.
- Count Down will decrease the value shown in the 7 segment display.

You can use the buttons in the right side of this window to give the input signals into the parallel port

Count Up signal is wired to XXX port and Count Up is wired to YYY port.




### Note

Please make sure to delete your lab codes from the remote machine after complete your lab experiment.
