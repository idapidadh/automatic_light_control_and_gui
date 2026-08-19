Two-part embedded system that auto-controls a light based on motion/light sensor readings and user-set preferences (room brightness, no-motion timeout). The control system and GUI communicate over UART (9600 bps) using custom message formats.

**Contributions**
This was a group project in 2nd semester. My primary contributions:

GUI (Python/Windows PC)
   - styresystemKommunikation.py

Control system (C++/Arduino)
   - GUIkommunikation.cpp
   - SystemindstillingKontrol.cpp
   - Systemindstillinger.cpp
   - AutomatiskLyskontrol.cpp
   - main.cpp

So in short: I was responsible for the UART communication between the systems, saving user settings in Arduino's non-volatile memory and the control class for the automatic control of the light source based on the user-set preferences 'systemindstillinger'.
   
Files not listed above were written by teammates as part of the shared codebase.


**Styresystem (control system)**
Runs on an Arduino Mega2560.

Hardware required:
- Arduino Mega250 I/O shield
- Motion sensor
- Light sensor
- Light source

Language: C++
Building: Open `styresystem.atsln` in Microhip Studio and build to Arduino Mega 2560.
Run: Click the Reset button on the shield.


**GUI**
Runs on Windows.
Language: Python
