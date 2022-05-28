## [warning] - In Development - [warning]

# NoahFC
- Atmega328 based Flight Controller.

### Features
- [X] PPM
- [X] GPS
- [ ] Failsafe
- [X] Manual mode
- [X] Stable mode
- [ ] Return to home
- [X] Low cost

### Used Pins
Arduino | Component
---------|---------
D2| PPM Input (interrupt)
D3| NeoSWSerial (GPS) RX
D4| NeoSWSerial (GPS) TX
D6| ESC Controller
SDA| MPU6050
SCL| MPU6050
D9| Left Wing Servo
D10| Right Wing Servo
D11| Elevator Servo
A2| Voltage read

### Free Pins
Arduino | Type
---------|---------
A0| Analog pin
A1| Analog pin
A3| Analog pin
D6| PWM Digital pin
D13| Digital pin (SCK) 
D12| Digital pin (MOSI)

## Scheme
![Scheme](images/scheme.png)

## Boards
Board|PCB filled
---------|---------
![Board](images/board.png)|![View 1](images/pcb.png)

## Panels
Board|PCB filled
---------|---------
![Board](images/panel_board.png)|![View 1](images/panel.png)
