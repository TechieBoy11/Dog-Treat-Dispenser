# Dog Treat Dispenser

An Arduino-based automatic dog treat dispenser designed to deliver treats on a scheduled timer. The device provides audible countdown notifications, displays the remaining time on a seven-segment display, and actuates a servo to release a treat once the timer expires. This project was designed to help pet owners deliver treats or medication while away from home.

---

## Features

- Adjustable countdown timer
- Supports hour or minute countdown modes
- Quarter-hour (15-minute) increments
- Audible startup, warning, and progress tones
- Seven-segment LED countdown display
- Servo-driven treat dispenser
- Powered by USB wall power or a USB battery pack

---

## Requirements

### Hardware

- Arduino board
- Breadboard
- Jumper wires
- Servo motor
- Servo horn (blade)
- Passive buzzer
- Single-digit seven-segment LED display
- Three push buttons
- USB breadboard power supply
- USB power bank or USB wall adapter
- Cardboard or other construction material
- Hot glue
- Box cutter or scissors

### Software

- Arduino IDE
- This repository

---

## Installation

### 1. Install Arduino IDE

Download and install the Arduino IDE from the official Arduino website:

https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE

### 2. Download the Project

1. Click the green **Code** button on GitHub.
2. Select **Download ZIP**.
3. Extract the ZIP file.

### 3. Open the Project

Open the following file using the Arduino IDE:

```text
DogTreatDispenser/DogTreatDispenser.ino
```

### 4. Configure the Settings

The following variables can be adjusted to customize the dispenser before uploading:

```cpp
// Servo positions
const int drop = 0;
const int hold = 65;

// Timer
const bool isHours = true;
const int defaultTime = 8;
const int warningNum = 4;
const int buttonDelay = 500;

// Progress tones
const bool hourlyTone = true;
const bool quarterlyTone = false;
```

| Variable | Description |
|-----------|-------------|
| `drop` | Servo angle used to release the treat |
| `hold` | Servo angle used to hold the treat |
| `isHours` | `true` = timer uses hours, `false` = timer uses minutes |
| `defaultTime` | Initial countdown value |
| `warningNum` | Number of warning cycles before dispensing |
| `buttonDelay` | Button debounce delay (milliseconds) |
| `hourlyTone` | Plays a reminder tone every hour |
| `quarterlyTone` | Plays a reminder tone every 15 minutes |

### 5. Upload the Sketch

1. Connect the Arduino to your computer using a USB cable.
2. Select the correct board and COM port in the Arduino IDE.
3. Click the **Upload (▶)** button.
4. Wait for the upload to complete.

---

## Hardware Setup

After uploading the sketch:

1. Disconnect the Arduino from the computer.
2. Connect the Arduino to the breadboard power supply.
3. Connect the breadboard power supply to either:
   - A USB wall adapter (recommended)
   - A USB battery pack
4. Turn on the power supply.

> **Note:** The dispenser can run for approximately **8 hours** on a USB battery pack, depending on battery capacity. For longer timers, a wall adapter is recommended.

---

## Using the Dispenser

1. Fill the dispenser with treats.
2. Place the dispenser in the desired location.
3. Attach the counterweight to the rear of the dispenser to prevent tipping.
4. Turn on the power supply.

### Controls

#### Up Button

- Increase the timer by one hour (or one minute when using minute mode).

#### Down Button

- Decrease the timer by one hour (or one minute when using minute mode).

#### Up + Down Buttons

Press both buttons simultaneously to cycle through quarter-hour increments.

| Display | Time Offset |
|---------|-------------|
| Number only | :00 |
| Blinking number | :15 |
| Number with decimal point | :30 |
| Blinking number with decimal point | :45 |

#### Start Button

Press the Start button to begin the countdown.

The device will:

1. Play a startup tone.
2. Display the remaining time.
3. Optionally play reminder tones every hour or every 15 minutes (configurable).
4. Play the warning sequence when the timer expires.
5. Activate the servo multiple times to ensure the treat is dispensed.
6. Automatically reset and wait for the next timer.

---

## Circuit Diagram

<img width="3000" height="1196" alt="Circuit Diagram" src="https://github.com/user-attachments/assets/7a8e53a4-8840-43f4-b74f-e417d12b67f5" />

---

## Future Improvements

- Real-time clock (RTC) support
- OLED or LCD display
- Rechargeable battery enclosure
- Wi-Fi or Bluetooth configuration
- Mobile app integration
- Multiple scheduled dispensing times
