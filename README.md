
# Sampling, Line Codes, and USART

## Overview
This repository contains the solution for **Lab 1: Sampling, Line Codes, and USART**. The objective is to implement a full-duplex communication scheme using USART on Arduino devices. The lab emphasizes synchronization over clock and data channels for efficient data transfer.

---

## Objective
- Implement **`usart_tx()`** to transmit data and a clock signal to the receiver.
- Implement **`usart_rx()`** to read the transmitted data based on the clock signal.
- Ensure full-duplex communication between two devices without busy waiting.
- Allow flexibility in the number of bits transmitted (default is 8 bits, extendable to 12 bits).

---

## Features
- **Full-Duplex Communication**:
  - Independent transmission and reception functions.
  - Synchronization using a clock signal.
- **Clock Channel**:
  - Generates a "0101…" stream at a frequency of 50 Hz.
- **Data Channel**:
  - Transmits data serially (bit by bit) synchronized with the clock signal.
- **Random Delay**:
  - Randomized delay after transmission without using sleep/busy waiting.

---

## Implementation Details

### Functions
1. **`usart_tx()`**:
   - Transmits 8-bit data (LSB first).
   - Sends clock signal simultaneously.
   - Implements a random delay after transmission.

2. **`usart_rx()`**:
   - Reads the clock pin to detect transmission.
   - Reads the data pin when the clock falls from `1` to `0`.

### Key Requirements
- **No Busy Waiting**:
  - Alternates between `usart_tx()` and `usart_rx()` calls without idle loops.
- **Loopback Support**:
  - Functions work with the transmitter and receiver on the same board.
- **Flexibility**:
  - Number of transmitted bits can be changed easily using `#define`.

---

## Usage

### Hardware Setup
- **Pins**:
  - Set `TX_PIN` as output and `RX_PIN` as input.
- **Clock Channel**:
  - Operates at 50 Hz (`BIT_TIME = 1/50 sec`).

### Software
1. Open the `.ino` file in the Arduino IDE.
2. Configure `BIT_TIME` and other parameters as needed.
3. Upload the code to the Arduino board.
4. Verify functionality using a loopback connection or multiple boards.

---

## Code Structure
- **Loopback Mode**:
  - `TX_PIN` and `RX_PIN` are connected on the same board.
- **Full-Duplex Mode**:
  - `TX_PIN` of one board connects to `RX_PIN` of another board and vice versa.

---

## Tools and References
- **Simulator**: [Tinkercad](https://www.tinkercad.com)
- **Arduino Reference**:
  - [PinMode](https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/)
  - [DigitalWrite](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/)
  - [DigitalRead](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/)
  - [Millis](https://www.arduino.cc/reference/en/language/functions/time/millis/)
  - [Serial.print](https://www.arduino.cc/reference/en/language/functions/communication/serial/print/)
  - [Bit Manipulation](https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/bitwrite/)

---

## Repository Structure
```plaintext
.
├── Lab file.pdf           # Lab assignment details
├── arduino.ino  # Arduino solution
├── README.md           # Project documentation
```

---

## How to Run
1. Open the `.ino` file in the Arduino IDE.
2. Set `BIT_TIME = 1` initially for debugging.
3. Test the solution using loopback mode.
4. Connect two Arduino boards for full-duplex communication and validate.

---

## Notes
- Document all code for better readability.
- Use `Serial.print()` for debugging in the absence of a debugger.
- Follow modular coding practices for easier extensions.

---

## Author
Developed as part of **Lab 1: Sampling, Line Codes, and USART** in the **371.1.2413** course.

