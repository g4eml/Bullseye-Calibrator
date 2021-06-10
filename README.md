# Bullseye-Calibrator
## An Arduino based Calibration tool for the Othernet Bullseye Satellite LNB
### Description
The Othernet Bullseye Satellite LNB is probably the most stable consumer grade Ku Band LNB currently available. Its Temperature Compensated Crystal Oscillator (TCXO) has a specification of ±2ppm and the LNB Local Oscilator is guaranteed by the manufacturer to be within 10Khz of the correct frequency of 9750.0 MHz. The TCXO is adjusted at manufacture to acheive this specification using a proprietary adjustment tool connected to the red connector. All oscillators drift to some extent with time, temperature and mechanical handling, so being able to occasionally re-calibrate them is a usefull feature for the end user.

With the kind support of Othernet and the LNB manufacturer Sy Science and Technology the specification for the adjustment interface has been made available. See the file https://github.com/g4eml/Bullseye-Calibrator/blob/main/Bullseye%20LO%20Re-Alignment%20Procedure.pdf included in this repository. 

This design is for a stand-alone Arduino based calibration tool which allows the LNB TCXO Frequency to be adjusted by the end user. It is also possible to connect this tool to a PC and send adjustment commands. 
