## [warning] - In Development

# NoahFC
- Trying to make low cost Atmega328 based Flight Controller with necessary features.

# Testing on
- [X] ZOHD Drift
- [ ] Wing

### Features
- [X] **PPM**
- [X] **GPS**
- [ ] Failsafe
- [X] **Manual mode**
- [X] **Stable mode**
- [ ] Return to home
- [X] **OSD**

### Used Pins
Arduino | Component| | Arduino | Component
---------|---------|---------|---------|---------
D0| UART RX||D9| Alerons
D1| UART TX||D10| SS (OSD)
D2| GPS RX (interrupt)||D11| MOSI (OSD)
D3| PPM Input (interrupt)||D12| MISO (OSD)
D4| LED MODE||D13| SCK (OSD)
D5| Throttle||SDA| MPU6050
D6| Elevator||SCL| MPU6050
D7| LED GPS||RST| DTR
D8| GPS TX||

### Transmitter setup
Channel | Info
-----|-----
CH1 | Elevator
CH2 | Alerons
CH3 | Throttle
CH4 | N/A
CH5 | Modes

### Modes
Channel 5 should be 3-position switch
- Min [**Manual**]
- Mid [**Stable**]
- Max [**RTH**]

### Leds
- Blue blink when GPS signal received
- Yellow lights when is in stable / rth mode

### Firmware
**Download**: [Firmware](firmware.hex)
```
Sketch uses 23196 bytes (75%) of program storage space. Maximum is 30720 bytes.
Global variables use 1077 bytes (52%) of dynamic memory, leaving 971 bytes for local variables. Maximum is 2048 bytes.
```
**Installation**:
`avrdude -p m328 -c arduino -P /dev/ttyUSB0 -b 115200 -F -U flash:w:firmware.hex`

## OSD
![OSD](images/osd.jpg)

## Scheme
![Scheme](images/scheme.png)

## Boards Preview
Board|PCB
---------|---------
![Board](images/board.png)|![View 1](images/pcb.png)

## PCB Design

For PCB design i will use services from SeeedFusion. 

Seeed Fusion PCB Assembly Service offers one-stop prototyping for PCB manufacture, PCB assembly and as a result they produce superior quality PCBs and Fast Turnkey PCBA from 7 working days. When you prototype with Seeed Fusion, they can definitely provide Free DFA and Free functional tests for you! 

Check out their website to know about their manufacturing capabilities and service.
https://www.seeedstudio.com/fusion.html

## Reasons to choose Seeed Studio
- They provide PCB services at extremely low pricing and with excellent quality.
- Their offer is structured in such a way that everyone may have these boards at a reasonable price.
- They have a highly knowledgeable crew that leads their clients to avail deals and guides them about the costs and rates of different services.
- A four-layer board with a comparable feature costs $5 for 10 pieces and is made in four days.
- SMT stencil with size (10cm x 13cm) is available for $8.00 per piece.
