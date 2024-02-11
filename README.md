# Lab 02: Hardware Interrupts and Program Flow 

Authors : Kyle G. Gayliyev <br>
Date: 9-February-2024<br>
Course: ECE 6780 - Embedded System Design, ECE Department, The University of Utah<br>
GitHub IDs: ggayliye <br>
Repo: https://github.com/ggayliye/Lab2_ECE6780EmbeddedSys_SR24 <br>
Date: By 16-February-2024 (Time of when submission is/will be ready to be evaluated)<br>
Copyright: ECE 6780, Kyle G. Gayliyev - This work may not be copied for use in Academic Coursework.

## Overview of the Lab 02

Lab 2 is consisted of 2 Parts:<br>

* Part 1: Setting up the Interrupt Handler  
* Part 2: Interrupt Nesting



### Part 1: Setting up the Interrupt Handler  
The red and blue LEDs should continue to blink while the green and <br>
orange LEDs toggle between each other whenever the user button is pressed.

Instructions:<br>
1. The file startup_stm32f072xb.s contains the names of interrupt handlers. Find the handler
name that matches the named interrupt number you found in the previous exercise.<br>
2. Use the handler name to declare the handler function in either main.c or stm32f0xx_it.h.
		* Although pre-generated interrupt handlers exist in stm32f0xx_it.h, they can be anywhere
within the project.
		* Remember that interrupt handler function declarations accept no arguments and have no
return value!<br>
3. Toggle both the green and orange LEDs (PC8 & PC9) in the EXTI interrupt handler.<br>
4. Clear the appropriate flag for input line 0 in the EXTI pending register within the handler.<br>
		- Otherwise the handler will loop because the interrupt request never acknowledged.
		- Read the bit description of the pending flags underneath the register map: these bits
require a different action to clear them.<br>
5. Compile and load your application onto the Discovery board.

### Part 2: Interrupt Nesting
This exercise demonstrates how a long running interrupt impacts the main application loop.<br>


Unlike systems having only hardware interrupt priorities, the NVIC allows important interrupts to
interrupt lower priority handlers; this process, called nesting, requires a more complex context-switch
mechanism but otherwise works identically to how interrupts pause execution of the main application
thread.<br>

Allowing nested interrupts introduces some complications: some interrupt tasks require uninterrupted
processing without losing or corrupting data (e.g., interrupts which move data between
communication peripherals). Many of these have limited buffer space and will overwrite data if the
interrupt execution delays or pauses for too long. <br>

Properly establishing the priorities between interrupts resolves much of the problem; in some
cases, however, it may be appropriate to mask. Masking temporarily disables other interrupts during
critical sections of code. The NVIC has capabilities to mask specific interrupts, and larger relatives
such as those in the Cortex M3 devices can mask interrupts by priority level. When the NVIC masks
an interrupt, it may still enter the pending state; this allows the NVIC to evaluate and launch the
appropriate handlers once the NVIC removes the mask.



<pre><ins>Future extensions</ins> :  There will be no future additions to this project. </pre>

# Partnership

We're partnered in the lab with students of two, but each student is required to complete
their work individually.

<ins> Progress Notes: </ins> <br>

<ins>1st Week Notes:</ins> <br>
- Created the "Lab2_ECE6780EmbeddedSys_SR24" GitHub repo.
- Created the "lab02" project using STM32CubeMX Software
- Worked on the 1st Part and almost completed. 
- Finished the assignment in the weekend.


## Testing
No Unit Test files are created as the nature of the project. Manual testing 
are performed in each step to ensure code improvements.

# Time Expenditures:
<pre>Lab01: Predicted Hours: 12h		Actual Hours:	12.17h		 </pre>

The actual hours recorded on top reflect the time spent for the assignment including the time spent in labs. It excludes time spent reading and understanding the lab assignment instructions at the beginning of the lab (pre-lab work).

# Comments to Evaluators:

<em>To able to fully test the main.c, other files and tools are required.<br>
For example, I created the project using the STM32CubeMX software first. Then <br>
clicked "Code Generation" button from the top menu after adjusting necessary <br>
settings. The instructions on how to adjust the settings will be given below. Then, <br>
the software automatically opens the Keil uVision5 softwhere where we code main.c.<br>
The main.c will be located under the "Application/User/Core" folder on the left menu of 
the Keil uVision5 softwhere.</em><br>

The main.c includes the 1st and 2nd part of the assignment. One of the assignments<br>
must be commented out. To test the commented out part, you'll need to uncomment that <br>
section and comment out the already uncommented section. Follow the comments<br>
out the sections in the main.c file.

## Testing Instructions:
After reading the discussion above, let's adjust the settings of
STM32CubeMX and Keil uVision5 softwares. <br><br>
STM32CubeMX:<br>

Select STM32F0 in the Series filter.<br>
* Select STM32F0x2 in the Lines filter
* Select LQFP64 in the Package filter <br>
At this point, there should only be a few choices available, select STM32F072RBTx and press the OK
button.<br>
Come to Project ->Menu->Settings.<br>
Name the new project. Select a directory where STMCube can create subfolders to store project files.<br>
Change the Toolchain/IDE dropdown menu to MDK-ARM V5.<br>
On the Project tab, move to the Code Generator tab at the top of the window.<br>
STMCube may take a while to copy the files to the directory specified in the settings. Afterward,
you may be asked if you want to open the project folder or project file itself. Click "project file".<br>
Now you should be in the "Keil uVision5" program as it's opened automatically.<br><br>

Keil uVision5:<br>

Click "Flash" -> "Configure flash tools" from the top menu.<br>
Click "Target" from the top menu. Find "Arm complier" menu and select 
"use default compiler version..".


One the setting is done, replace the main.c file in the "Application/User/Core" folder <br>
with my main.c file you downloaded.<br>
From the top menu, "Project"->"Build Target".<br>
Plug in your STM32F072 Discovery Microcontroller to your computer. <br>
Click "Flash" -> "Download" from the top menu. Test it on your STM32F072 Discovery Microcontroller.

Thank you for evaluating this project and providing feedback. <br>

Have a wonderful day!

# Consulted Peers:
N/A

# Caution/Warnings

* Never use any sort of delay within an interrupt handler! Handler functions should perform<br>
work quickly and then return—the HAL delay functions will deadlock within an interrupt with <br>
the same or higher priority than the SysTick. 


# Examples of Good Software Practice (GSP)
<pre><ins>DRY</ins> :</pre>
DRY is an abbreviation of "Don't repeat yourself". It's a principle of Software Engineering that
has the goal of reducing repetition and redundancy in the coding. Using abstractions and normalization
are advised over redundancy <a href="https://en.wikipedia.org/wiki/Don%27t_repeat_yourself">[2]</a>.

<pre><ins>Separation of Concerns</ins> :</pre>
This concept is similar to the "divide and conquer" principle where you divide
a big software project into small projects to complete. A software design technique that focuses on separating 
and freeing functionalities of a program is called Modular programming. Making each of the divided small 
projects independent and addressing a separate concern, it'll make it easy to reduce, detect 
and fix the errors. <a href="https://en.wikipedia.org/wiki/Separation_of_concerns">[3]</a>

<pre><ins>Good Code Typing Practices</ins> :</pre>
Good coding practices can be listed as: Naming variables with a relevant name, commenting 
in between code lines with a brief explanation if the code is not self-explanatory, creating 
helper methods that can be used multiple times and by other sections.


<pre><ins>Testing Strategies</ins> :</pre>
Unit Testing can be summarized in 3 types of techniques:<br>

1. <ins>Black Box Testing : </ins> In this testing, input, user interface, and output parts are covered.
2. <ins>White Box Testing : </ins> In this testing, functionality, design structure, and code models are covered.
3. <ins>Gray Box Testing : </ins> In this testing, analysis of code performance, relevant test cases,
methods, and functions are covered.<a href="https://www.geeksforgeeks.org/unit-testing-software-testing/">[4]</a>


# References:
1. Canvas Page Class Materials.(For example, lecture slides, additional resources and pdf files). <br>
2. https://en.wikipedia.org/wiki/Don%27t_repeat_yourself<br>
3. https://en.wikipedia.org/wiki/Separation_of_concerns<br>
4. https://www.geeksforgeeks.org/unit-testing-software-testing/<br>






