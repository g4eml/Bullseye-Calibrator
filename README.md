# Bullseye-Calibrator
## An Arduino based Calibration tool for the Othernet Bullseye Satellite LNB
### Description
The Othernet Bullseye Satellite LNB is probably the most stable consumer grade Ku Band LNB currently available. Its Temperature Compensated Crystal Oscillator (TCXO) has a specification of ±2ppm and the LNB Local Oscilator is guaranteed by the manufacturer to be within 10Khz of the correct frequency of 9750.0 MHz. The TCXO is adjusted at manufacture to acheive this specification using a proprietary adjustment tool connected to the red connector. All oscillators drift to some extent with time, temperature and mechanical handling, so being able to occasionally re-calibrate them is a usefull feature for the end user.

With the kind support of Othernet and the LNB manufacturer Sy Science and Technology the specification for the adjustment interface has been made available. See the file https://github.com/g4eml/Bullseye-Calibrator/blob/main/Bullseye%20LO%20Re-Alignment%20Procedure.pdf included in this repository. 

This design is for a stand-alone Arduino based calibration tool which allows the LNB TCXO Frequency to be adjusted by the end user. It is also possible to connect this tool to a PC and send adjustment commands. 

### Details
In order to keep construction as simple as possible it was decided to use a readily available and low cost Arduino Nano as the controlling processor. This is programmed with the file https://github.com/g4eml/Bullseye-Calibrator/blob/main/Bullseye_Calibrator.ino using the normal Arduino IDE. Other Arduinos should work equally well. 

The Bullseye LNB is programmed through its Red F Type connector. As detailed in the Alignment Procedure PDF document the interface between the Arduino and the LNB is serial data at 9600 Baud with levels of 0V and +15V. Because the Arduino can only produce data at 5V it is necessary to build a simple level converter circuit using a few low cost components. There are three pushbuttons for control. The interface needs a power supply between 18 and 30 Volts DC. This can be from two 9V batteries or an external power supply. The LNB also needs to be powered through its normal Green F Type connector. 

The schematic for this interface is included in file Schematic.pdf.  None of the parts are particularly critical and may be surface mount or through hole parts. Some suggested part numbers are included on the schematic. 


