---
layout: blank
permalink: /lab01/instructions/
---

<h2>Lab 2 - Parallel Port </h2>

<h3>Introduction</h3>

In this lab, you are going to try parallel port communication, where a parallel port is used as the interface to communicate with a seven-segment display. Due to the prevailing conditions in the country, you are going to do this lab as a remote lab. Modify the codes you have implemented in the pre-lab according to the given circuit at the lab.

<h3>Lab Exercises</h3>

<b><u>Task 01: Display 0-9 numbers on a single 7 segment display</u></b>

The circuit is created using a common anode seven segment display. Seven segment display is connected to the parallel port pins as shown in the below figure 02.


Note that a separate resistor is connected in series to each segment of the seven-segment display.

Connect to the lab computer using the remote connection and modify the program written in the pre-lab to light up each segment of SSD one by one in the above circuit.



<b><u>Task 02: Display 0-9 numbers on a single 7 segment display using 74LS47 IC
</u></b>


Connect to the lab computer using the remote connection and modify the program written in the pre-lab to display characters from 0-9 in an infinite loop with a delay of 1 second between each character using the 74S47 IC.


<b><u>Task 03: Change the numbers displayed in the SSD with a push button</u></b>

Modify the code written in the pre-lab, and use it to change the numbers displayed in the SSD when the push button is pressed. A pull up Resistor is connected with the circuit as shown in Figure 04.

NOTE : Pull-up resistors are used to define the state of an otherwise "floating" input by pulling the voltage at the pin to a set voltage.
