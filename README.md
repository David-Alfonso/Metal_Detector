# Metal_Detector

This repository contains two distinct implementations of a **metal detector** project, both solving the same problem using different approaches. Each project is housed in its own folder and detects metal by sending a sine wave through a **transmitter coil** and monitoring the resulting wave through a **receiver coil**. When metal is present, the wave pattern changes, and the system detects this variation. It uses a PIC microcontroller.

## Table of Contents

- [Project Overview](##project-overview)
- [Repository Structure](##repository-structure)
- [How It Works](##how-it-works)
- [Analog Approach (UART)](##analog-approach-uart)
- [Digital Approach (Nextion UI)](##digital-approach-nextion-ui)
- [Getting Started](##getting-started)

## Project Overview

The metal detector works by:
1. Generating a sine wave through a **transmitter coil**.
2. A **receiver coil** senses this signal, the communication between the coils is **QAM**.
3. When a metallic object is near, the presence of metal alters the magnetic field, causing a distortion in the received sine wave.
4. This sine wave is filtered because the changes because of the metal are present in low frequencies.
5. The sine wive has a frequency greater than that of these frequencies so it can be filtered.
6. The system detects these changes and displays the results either through a simple UART communication (in the analog project) or on a graphical user interface powered by **Nextion** (in the digital project).

## Repository Structure

```
/MetalDetectorProject
│
├── /Analog/EUESART.X
│   ├── mcc_generated_files
│   └── main.c
│
├── /Digital/NEXTION4.X
│   ├── mcc_generated_files
│   └── main.c
│
└── LICENSE
└── README.md
```

## How It Works

Both projects use the same fundamental concept: the **transmitter coil** emits a sine wave, and the **receiver coil** detects any changes to the signal caused by metal objects. The communication is based on Quadrature Amplitud Modulation (QAM) in which the signal sensed in the receiver coil is multiplied for the original sine and it's equivalent cosine, these multiplications are filtered so it can see the changes made by the presence of a metal. The difference between the two projects lies in how they handle and display this information:

- The **analog project** relies on simple UART communication to show data changes, also, the generation of the sine wave and the filter is with an analog circuit.
- The **digital project** uses a graphical interface powered by a **Nextion screen** to display the detected variations visually, generates with a square wave filtered the sine wave and filters the resulting multiplication, which is made by changing the moments when it receives signal from the receiver coil.

## Analog Approach (UART)

The analog approach focuses on transmitting the wave data using **UART communication** to show changes in the wave. The project is more circuit-based and simpler in terms of user interaction. It outputs information that indicates the detection of metal without a user interface, making it suitable for debugging or low-level monitoring. It prints the result of the analog filter from the analog multiplication, using a mux and a comparator from the original sine wave, both the sine and cosine multiplication and, in a serial plotter, it can be seen the changes in time.

- **Key Files:** `main.c` and all those in `mcc_generated_files`
- **Method:** Uses a UART connection to send and receive data, the sine wave, multiplication and filter process is with a circuit.
- **Usage:** Ideal for users who prefer a raw data output and an easier software implementation.

## Digital Approach (Nextion UI)

The digital approach leverages a **Nextion screen** for an improved user experience, providing a graphical interface to display detection results. It is designed to offer more intuitive and visual feedback, making it user-friendly and interactive. The generation of the sine wave, filter process and multiplication of the signal is digital based. It has 4 different work-modes, one for calibration where it can be chosen the sensitivity, which changes the gain of a Programmable Gain Amplifier (PGA), a real time graph of the sine and cosine signal and it's variations, a color mode, where it changes from green to red depending on how strong the signal changes, and finally an X-Y graph to see how the sine and cosine components change over time.

- **Key Files:** `main.c` and all those in `mcc_generated_files`, specially the timers where the sine wave and the multiplication are made.
- **Method:** Utilizes a Nextion screen to provide real-time visual feedback.
- **Usage:** Recommended for users who prefer a graphical user interface (GUI) to monitor and control the system.

## Getting Started

To get started with either project, a PIC microcontroller is needed, these projects were made using MPLAB IDE and MCC Classic incorporated function. The analog project uses PIC16F18426 microcontroller and the digital project PIC18F46K42, when you import all of the folder, wether the analog or digital one, it shows all the conections needed for it to work. The digital one requires an SPI DAC and a Nextion Display.
  
Additional details about required libraries and dependencies can be found in each respective project folder.
