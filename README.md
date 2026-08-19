Two-part embedded system that auto-controls a light based on motion/light sensor readings and user-set preferences (room brightness, no-motion timeout). The control system and GUI communicate over UART (9600 bps) using custom message formats.

**Contributions**
This was a group project in 2nd semester. My primary contributions:

GUI (Python/Windows PC)
   - styresystemKommunikation.py (design and implementation)

Control system (C++/Arduino)
   - GUIkommunikation.cpp (design and implementation)
   - SystemindstillingKontrol.cpp (design and implementation)
   - Systemindstillinger.cpp (design and implementation)
   - AutomatiskLyskontrol.cpp (debugging)
   - main.cpp (debugging)

Files not listed above were developed by teammates as part of the shared codebase.

So in short: I was responsible for the UART communication between the systems, saving user settings in Arduino's non-volatile memory and the control class for the automatic control of the light source based on the user-set preferences 'systemindstillinger'.
   

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


**Pictures/video**
<img width="1132" height="452" alt="Styresystem_and_full_system" src="https://github.com/user-attachments/assets/b1f9c27e-da7a-4067-a92d-da1a078c767b" />
<img width="1067" height="397" alt="Adjusting_brightness_or_timeout" src="https://github.com/user-attachments/assets/ef4027f3-7412-43e4-b53b-33eb1645e469" />

https://github.com/user-attachments/assets/037e4c86-545c-42f0-b056-16fedefa4386

**Diagrams**

System sequence diagram - settings configuration:
<img width="3156" height="5204" alt="ssd_uc1_Settings_configuration" src="https://github.com/user-attachments/assets/d80b5929-a1ab-43b3-9948-6905a70e17a1" />

Sequence diagram from Styresystem's point of view - automatic light control:
<img width="4340" height="5408" alt="sd_Light_auto-control" src="https://github.com/user-attachments/assets/f6729672-05d6-4749-9fd1-f6ca857d8ca2" />

