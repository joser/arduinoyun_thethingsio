#include <Process.h>

void setup() {
  // Initialize Bridge
  Bridge.begin();

  // Initialize Serial
  Serial.begin(9600);

 }

void loop() {
  // Read temperature in celsius
  double temp_cel = readTemp(analogRead(0)); 
  // Read light in luxes
  int light_lux = readLux(analogRead(1));
  // Send to TheThingsIO
  sendToThingsIO(String(temp_cel), String(light_lux));
  // Wait one sec
  delay(1000);
}

// Launch writeThingsIO python script to compose the json
void sendToThingsIO(String temp, String lux) {
  Process p;        // Create a process and call it "p"
  p.begin("python");
  p.addParameter("/www/python_scripts/writeThingsIO.py");
  p.addParameter(temp);
  p.addParameter(lux);
  p.run();      
}


// Read Temperature with a 50k 503 thermistor 
double readTemp(int RawADC) {
  double Temp;
  Temp = log(10000.0*((1024.0/RawADC-1)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius  
  return Temp;
}

// Read Light with a 10k LDR 
int readLux(int rawAdc){
  double vout=rawAdc*0.0048828125;
  int lux=(2500/vout-500)/10;
  return lux;
}  

