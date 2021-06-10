# Bullseye-Calibrator
## An Arduino based Calibration tool for the Othernet Bullseye Satellite LNB
### Description
The Othernet Bullseye Satellite LNB is probably the most stable consumer grade Ku Band LNB currently available. Its Temperature Compensated Crystal Oscillator (TCXO) has a specification of ±2ppm and the LNB Local Oscilator is guaranteed by the manufacturer to be within 10Khz of the correct frequency of 9750.0 MHz. The TCXO is adjusted at manufacture to acheive this specification using a proprietary adjustment tool connected to the red connector. All oscillators drift to some extent with time, temperature and mechanical handling, so being able to occasionally re-calibrate them is a usefull feature for the end user.

With the kind support of Othernet and the LNB manufacturer Sy Science and Technology the specification for the adjustment interface has been made available. See the file https://github.com/g4eml/Bullseye-Calibrator/blob/main/Bullseye%20LO%20Re-Alignment%20Procedure.pdf included in this repository. 

This design is for a stand-alone Arduino based calibration tool which allows the LNB TCXO Frequency to be adjusted by the end user. It is also possible to connect this tool to a PC and send adjustment commands. 

### Warning
Note that the Alignment document makes it clear that any attempt to adjust the LNB will invalidate the warrenty. If you try to adjust your LNB using this calibrator you are doing so at your own risk.  

### Details
In order to keep construction as simple as possible it was decided to use a readily available and low cost Arduino Nano as the controlling processor. This is programmed with the file https://github.com/g4eml/Bullseye-Calibrator/blob/main/Bullseye_Calibrator.ino using the normal Arduino IDE. Other Arduinos should work equally well. 

The Bullseye LNB is programmed through its Red F Type connector. As detailed in the Alignment Procedure PDF document the interface between the Arduino and the LNB is serial data at 9600 Baud with levels of 0V and +15V. Because the Arduino can only produce data at 5V it is necessary to build a simple level converter circuit using a few low cost components. There are three pushbuttons for control. The interface needs a power supply between 18 and 30 Volts DC. This can be from two 9V batteries or an external power supply. The LNB also needs to be powered through its normal Green F Type connector. 

The schematic for this interface is included in file Schematic.pdf.  None of the parts are particularly critical and may be surface mount or through hole parts. Some suggested part numbers are included on the schematic. 

### Stand-Alone Operation
To adjust the calibration of the LNB using the calibrator you need to do the following...

Set up the LNB as normal using the Green Connector and tune your receiver to a known frequency signal such as one of the QO-100 Beacons, a terrestrial 10GHz beacon or a GPS locked signal source.   

If you are using SDR software that can compensate for LNB errors make sure that this compensation is turned off so that you can see the amount of error that needs correcting. 

Observe the beacon signal, and note how much it needs to be moved in order to indicate the correct frequency. A waterfall display makes this fairly easy.

Allow the LNB temperature to stabilise for about 10 minutes. The LNB will drift a little initially but should then stabilise. 

Connect the calibrator to the LNB Red connector using a short length of 75 ohm cable. (It is not currently known how long this cable can be, if it is too long it may cause problems with the calibration commands.) 

Connect an 18 to 30 V power supply to the calibrator. 

Press the PLUS or MINUS buttons to adjust the LNB LO Frequency. This should move in steps of approximately 200Hz. If you need to move a long way you can hold down the button which will then move at 10 steps per second. You should observe the beacon signal moving along the receiver waterfall display.

When the displayed frequency is a close as possible to the correct frequency of the beacon press the SAVE button. This will save the new setting into the LNB memory and will be used every time the LNB is powered on. 

If you make a mistake press all three buttons at the same time. This will restore the factory calibration value. 

### PC Operation
It is also possible to connect the Calibrator to a PC through the Arduino USB port. This allows the calibration commands to be sent from the PC Keyboard. 
Use a Terminal program on the PC and set the communications to 9600 Baud, 8 Bits, No Parity, 1 Stop Bit. 
Commands are single upper case characters as listed in the PDF document. 








