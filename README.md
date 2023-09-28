## [warning] - In Development

# NoahFC
- Trying to make lowcost Atmega328 based Flight Controller with necessary features.

### Features
- [X] PPM
- [X] GPS
- [X] Compass
- [ ] Failsafe
- [X] Manual mode
- [X] Stable mode
- [ ] Return to home
- [X] OSD
- [X] Low cost


## OSD
![OSD](images/osd.jpg)

### Used Pins
Arduino | Component| | Arduino | Component
---------|---------|---------|---------|---------
D0| UART RX||D9| Alerons
D1| UART TX||RST| DTR
D2| GPS RX (interrupt)||D10| SS (OSD)
D3| PPM Input (interrupt)||D11| MOSI (OSD)
D4| LED MODE||D12| MISO (OSD)
D5| Throttle||D13| SCK (OSD)
D6| Elevator||A0| Voltage read
D7| LED GPS||SDA| MPU6050
D8| GPS TX||SCL| MPU6050

### Firmware
Download here: [Firmware](firmware.hex)
```
Sketch uses 24584 bytes (80%) of program storage space. Maximum is 30720 bytes.
Global variables use 1151 bytes (56%) of dynamic memory, leaving 897 bytes for local variables. Maximum is 2048 bytes.
```
Installation:
avrdude -p m328 -c arduino -P /dev/ttyUSB0 -b 115200 -F -U flash:w:firmware.hex

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
https://www.seeedstudio.com/pcb-assembly.html

## Reasons to choose Seeed Studio
- They provide PCB services at extremely low pricing and with excellent quality.
- Their offer is structured in such a way that everyone may have these boards at a reasonable price.
- They have a highly knowledgeable crew that leads their clients to avail deals and guides them about the costs and rates of different services.
- A four-layer board with a comparable feature costs $5 for 10 pieces and is made in four days.
- SMT stencil with size (10cm x 13cm) is available for $8.00 per piece.

