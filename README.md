# MP3 Player

This is a Portable MP3 player which allows one to play music on the even at places where there is no internet access.
You can also view almost all the details you would require while listenting to music on the OLED dispaly that will be connected to it.
Also has a capbility to be programmed using a Arduino or a FTDI programmer.

**Untested Firmware**

Features-
- Atmega328p as a MCU
- DF player MINI (DFR0299) as a MP3 decoder(since i already had it lying around)
- 128x64 0.96 inch OLED display for UI
- Inbuilt charging using TP4056
- 4 iterfacing buttons Play/Pause  Prev/Vol-  Next/Vol+ and RESET for the board 
- Onboard leds for debugging,Power,Charging and Playing status

## Notes for V2 + last minute changes 
- The temp pin of the tp4056 ic needs to be grounded instead of being left open since it puss that pin to a random value and doesnt allow the battery to be charged
- i need to route the next and prev buttons to one of the io pins of the atmega chip since earlier i had it on the adkey mode of the df player which when pressed puts board in a where it no longer receives commands from the mcu
- one of the most obvious this i missed is adding a switch to turn off the 5v from the boost ic directly since now whenever i charge the board the board stays on permanently so to overcome that i have temporarily added button combination to put the df player to sleep.
- in the image u can see that ive added jumpers to the board for connecting the pay pause button to the mcu directly.


# PCB Schematic and CAD
<img width="695" height="582" alt="Screenshot 2025-10-25 133321" src="https://github.com/user-attachments/assets/1e41b7ca-78dd-4378-99c0-326a84a2edf6" />
<img width="615" height="555" alt="Screenshot 2025-10-25 133349" src="https://github.com/user-attachments/assets/f8b7e67e-485f-413b-8c9c-cf7a38d8dc1d" />
<img width="960" height="635" alt="image" src="https://github.com/user-attachments/assets/c3a44214-22f8-419a-955f-ac7c71c87541" />
<img width="1500" height="2000" alt="image" src="https://github.com/user-attachments/assets/c0b308a3-c0c2-435d-b0f5-58f58aba7e39" />

