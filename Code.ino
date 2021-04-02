//
//
// This sketch runs a program where analog temperature readings from a temp sensor
// activate LEDs depending on the temperature. Using a baseline temperature, LEDs
// are activated in series by two degree increments. 

// LED activation depends on mean temperature of consecutive readings, in order to 
// minimize variation not directly attributed to temperature (also to reduce
// flickering of LEDs when temperature value is near their limits). LEDs begin
// activation and descriptive values are calculated and displayed on the serial monitor only 
// after value initialization has occured (wait time depends on extent of value memory recorded).

// The system can also be activated/deactivated with the press of a switch. After an
// activation, memory is erased and all values are initialized.


// import libraries
#include <math.h> // to use power for calculating standard deviation

// set up temperature variables
const int TempSensor = A0; // analog input pin connected to temp sensor
const float baseLineTemp = 19.0; // 19 degrees
const int MemoryExtent = 20; // the number of consecutive temperature values to keep as record
float TempMemory[MemoryExtent]; // array to keep record of values to calculate mean temperature
int Reading = 0; // temperature reading (used to avoid printing first readings)

// set up system state variables
int SystemState = 0; // system variable (ON/OFF = 1/0)
int Switch = 9; // input pin 

// delay after switch press
int DELAY = 200;

void setup() {
  // open up connection between Arduino and PC to send analog values
  Serial.begin(9600); // 9600 bits per second
  
  // set output pins (default state: LOW)
  for (int pinNumber = 2; pinNumber < 5; pinNumber++){
    pinMode(pinNumber, OUTPUT);
  }
  
  // set pin 13 as output to indicate system state (HIGH for ON, LOW for OFF)
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); // active when system OFF
}

void loop() {
  // if system is active, follow action depending on whether switch is pressed
  if (SystemState == 1){ //
    // if switch is pressed
    if (digitalRead(Switch) == HIGH){
     // deactivate all LEDs
     for (int pinNumber = 2; pinNumber < 5; pinNumber++){
      digitalWrite(pinNumber, LOW);
     }
     // update system variable to deactivate and activate
     SystemState = 0;
     digitalWrite(13, HIGH);
     delay(DELAY);
    } 
    
    // if switch is not pressed, conduct temperature reading
    else {        
      // read temperature analog value and print on monitor
      int sensorVal = analogRead(TempSensor);
  
      // convert analog reading to voltage and print
      float Voltage = (sensorVal/1024.0) * 5.0;
  
      // convert voltage to temperature and print
      float Temperature = (Voltage - 0.5) * 100;
      
      // add temperature to array 
      for (int i = 0; i < MemoryExtent - 1; i++){ // remove first record and drag each value one position back
        TempMemory[i] = TempMemory [i + 1];
      }
    
      TempMemory[MemoryExtent - 1] = Temperature; 
      
      Reading++; // add a reading

      // After initialization, calculate average temperature and std - then activate LEDs 
      // depending on temperature & print values
      if (Reading >= MemoryExtent){
        // calculate mean value
        float sum = 0.0; // store sum of values
        float averageTemp = 0.0; // store average of values
      
        for (int i = 0; i < MemoryExtent; i++){
        sum = sum + TempMemory[i];
        }
      
        averageTemp = sum / MemoryExtent; // calculate average value
      
        // calculate standard deviation
        float std = 0.0;
      
        for (int i = 0; i < MemoryExtent; i++){
          std = std + pow(TempMemory[i] - averageTemp, 2);
        }
      
        std = std / MemoryExtent;
        
        if (averageTemp < baseLineTemp){ // if temperature less than baseline
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
        }
  
        else if (baseLineTemp <= averageTemp  && averageTemp < baseLineTemp + 2){ // if temperature between baseline and baseline +2
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          digitalWrite(4, LOW);
        }
  
        else if (averageTemp >= baseLineTemp + 2){ // if temperature more than baseline +2
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);
        }
        
        // print mean and standard deviation (avoid first readings)
        Serial.print(" Avg. Temperature: "); Serial.print(averageTemp);
        Serial.print(" +- "); Serial.println(std);
        
        delay(2); // note: a small delay is advised for ADC
      }
      
      // else do not pass information to any LED
    }
  }
  // if system is off, take action only if switch is pressed
  else if (SystemState == 0){
    if (digitalRead(Switch) == HIGH){ // if switch is pressed
    
    // update system variable and deactivate LED 13
    SystemState = 1;
    digitalWrite(13, LOW);
    
    // begin reading values from start (for initialization) - array values 
    // will be substituted by new values
    Reading = 0;
    delay(DELAY);
    }
  // else do nothing
  }
      
}
