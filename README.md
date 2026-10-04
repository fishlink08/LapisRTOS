# A Dynamic RTOS for ARM Cortex-M Microcontrollers

This allows you to dynamically (during runtime) add, update, or remove modules of code or drivers. This gives you the ability to avoid recompiling the program as a whole, as well as giving your code a safe environment with tools such as heap allocation and task scheduling.

There are two main parts you may change during runtime:

* **Code Modules:** These are modular pieces of code that are run automatically once put into the environment. You may use drivers you have added in these pieces of code.
* **Drivers:** These are drivers which the code modules may use, automatically updated for each code module currently using them. These are typically for the ARM Cortex registers and peripherals.

LapisRTOS provides a safe and direct environment for each code module and driver to run in. This environment also provides various tools which the LapisRTOS kernel handles, such as heap allocation, task scheduling, error containment, and more. This gives the programmer plenty of tools to use without having to worry about fragmentation or completely crashing the microcontroller as a whole.

**Actively Working on This Project :)**
