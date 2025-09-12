# PocketMage PDA
[Please note that this project is a work in progress and incomplete]

@Ashtf 2025

<img width="1245" height="882" alt="Screenshot 2025-09-10 203805" src="https://github.com/user-attachments/assets/f021dc66-12d8-489f-9078-9c7eeeb4ad03" />

<img width="1151" height="807" alt="Screenshot 2025-09-10 203851" src="https://github.com/user-attachments/assets/676fe6bb-d124-4707-828f-a3c22c24fd00" />

# [Project Summary]
  This project is a PDA powered by an ESP32-S3 running a custom OS written in C++ using PlatformIO. This project utilizes an E-Ink and OLED screen in tandem to mitigate the refresh rate restrictions of an E-Ink panel while retaining the aesthetics and benefits of using E-Ink. This project is a work in progress and currently amounts to a simple GUI for navigating between apps, a text (.txt) file editor, and a basic file manager. More applications are planned for the future and a list of TO-DOs can be found below.

  At this point, the plan for this project is to get the software and hardware to maturity and once a finished product is achieved, a few things will happen. First, the project files (Code, KiCad schematics, 3D files) will be open-sourced and free for anyone to access. Next, I will likely begin selling kits that allow people to purchase all the parts required to build a device for themselves if they don't want to source the parts themselves. Finally, the community will be encouraged to help develop the software for the device and hopefully push it even further than I could myself.

  I will try my best to keep this GitHub up to date with the development of the device.

# [Creating Your Own Apps]
  Check out the /Code/BlankApp folder for a simple example app template. Check out the following video as a tutorial on how to create and format your app:

[Developing For the PocketMage](https://www.youtube.com/watch?v=3Ytc-3-BbMM)

# [Hardware]
- ESP32-S3 WROOM1 with 16mb flash and 8mb RAM. WiFi and Bluetooth supported.
- 3.1" 320x240px 1-bit SPI Eink panel (GDEQ031T10) with integrated driver
- 256x32px 1-bit SPI OLED (SSD1326, ER-OLED018-1W) with integrated driver
- MicroSD card slot with support for up to 2TB
- TCA8418 I2C Keyboard Matrix IC
- Piezo Buzzer (Simple Tones)
- Power Button
- 1200mAh pouch-style LiPo battery with JST PH (2mm) connector
- USB Type-C connector
- PCF8563T I2C RTC (Real Time Clock) module
- Expansion port with the following breakouts:
    - +3.3v
    - GND
    - I2C SDA
    - I2C SCL
    - SPI MOSI
    - SPI SCK
    - SPI MISO
    - GPIO A
    - GPIO B
    - GPIO C
    - GPIO D / UART TX (changeable with solder jumper, default TX)
    - GPIO E / UART RX (changeable with solder jumper, default RX)


# [Software]
- Text editor app
- FileWizard file-management app
- Calendar app
- USB file transfer app
- Settings app
- Tasks app
- Journal app
- Dictionary app (Lexicon)
- Basic commands supported through the home menu:
    - roll dN (dice roll, N=number of sides)
    - set time and date
    - directly open files in Notes or FileWiz by typing the name
    - etc.

# [Planned Features]
- Timers and alarms
- E-book reader
- WiFi notes/calendar sync (Google Docs/Calendar)
- LoRa/Meshtastic add-on module
- Battery expansion add-on module
- Custom abbreviations
- Bluetooth keyboard support

# License
All files are distributed under CC BY-NC-SA 4.0 license:

PocketMage PDA - A clamshell note-taking and productivity device using E-Ink and OLED.

Copyright (C) 2025 Ashtf

[![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC--BY--NC--SA%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc-sa/4.0/)  

This project is licensed under the **Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License (CC BY-NC-SA 4.0)**.  

You are free to:  
- **Share** — copy and redistribute the material in any medium or format  
- **Adapt** — remix, transform, and build upon the material  

Under the following terms:  
- **Attribution** — You must give appropriate credit.  
- **NonCommercial** — You may not use this material for commercial purposes.  
- **ShareAlike** — If you remix, transform, or build upon it, you must distribute your contributions under the same license.  

The original author retains the right to use this work commercially.  

Full license details: [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/)  
