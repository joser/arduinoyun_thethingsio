#include <Process.h>

void setup() {
  // Initialize Bridge
  Bridge.begin();

  // Initialize Serial
  Serial.begin(9600);

  // Wait until a Serial Monitor is connected.
  //while (!Serial);

 }


void loop() {
  double temp_cel = readTemp(analogRead(0)); 
  int light_lux = readLux(analogRead(1));
  sendToThingsIO(String(temp_cel), String(light_lux));
  delay(1000);
}

void sendToThingsIO(String temp, String lux) {
  // Launch "curl" command and get Arduino ascii art logo from the network
  // curl is command line program for transferring data using different internet protocols
  Process p;        // Create a process and call it "p"
  p.begin("python");
  p.addParameter("/www/python_scripts/writeThingsIO.py");
  p.addParameter(temp);
  p.addParameter(lux);
  p.run();      // Run the process and wait for its termination
  //Serial.print("Temp measure sent: " + String(temp));
}


double readTemp(int RawADC) {
  double Temp;
  Temp = log(10000.0*((1024.0/RawADC-1)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius  Serial.print("Temperature measured: " + String(Temp));
  return Temp;
}


int readLux(int rawAdc){
  double vout=rawAdc*0.0048828125;
  int lux=(2500/vout-500)/10;
  //Serial.print("Light measured: " + String(lux));
  return lux;
}  

