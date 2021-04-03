# **IDEA**  
  
The idea of this project is to create a temperature display using Arduino. A temperature sensor is used to estimate temperature, which is used to light up LEDs of different colour indicating different temperature ranges. Temperature values are displayed on screen using the serial monitor.    
  
# **MATERIALS**
  
•	Arduino UNO & Breadboard  
•	TMP36  
•	LEDs (x3)  
•	Momentary switch  
•	220Ω resistors (x3)  
•	10kΩ resistor  
•	Jumper wires  
  
# **PROCESS**  
  
## **Board**  
Three LEDs are connected to pins 2,3 and 4, set as output pins. They are connected to ground with 220 Ω resistors. A switch is connected to pin 9, set as an input pin, and connected to ground with a 10kΩ resistor. The TMP36 sensor is connected to analog pin A0.   
  
<p align="center" width="100%">
    <img width="50%" src="https://github.com/AlexEcoVis/hot-n-cold/blob/main/Board.jpg"> 
</p>
  
## Program (**[Code](https://github.com/AlexEcoVis/hot-n-cold/blob/main/Code.ino)**)  
The switch is used to activate or deactivate the whole system. The default state is deactivated. Once the switch is pressed, the system activates and begins an initialization process, whereby it records N consecutive temperature values. When these are recorded, then per cycle, the average temperature value is calculated and used to activate the corresponding LED.  
  
*The average value is calculated as a more representative indicator of the actual temperature, since variation is expected owing to the properties of the sensor and inaccuracies of the output voltage. In any case, recorded temperature values are not entirely accurate.*  

The LEDs represent ranges of temperature values – in this case, the following:  
•	Blue: less than 19 degrees C  
•	Orange: between 19 and 21 degrees C  
•	Red: more than 21 degrees C  
  
If the switch is pressed again, the system deactivates and all LEDs are turned off. Upon activation, initialization occurs again to calculate average temperature and continue the cycle of temperature display (previous values are overwritten).  

*All average temperature values, including standard deviation per group, are displayed on the serial monitor.*   
  
  
<p align="center" width="100%">
    <img width="50%" src="https://github.com/AlexEcoVis/hot-n-cold/blob/main/Display.gif"> 
</p>
  
  
<p align="center" width="100%">
    <img width="50%" src="https://github.com/AlexEcoVis/hot-n-cold/blob/main/Serial%20Monitor.gif"> 
</p>
