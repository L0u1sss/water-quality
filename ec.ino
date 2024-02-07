void ec() {
  if (millis() - AnalogSampleTime >= AnalogSampleInterval)
  {
    AnalogSampleTime = millis();
    // subtract the last reading:
    AnalogValueTotal = AnalogValueTotal - readings[ec55];
    // read from the sensor:
    readings[ec55] = analogRead(ECsensorPin);
    // add the reading to the total:
    AnalogValueTotal = AnalogValueTotal + readings[ec55];
    // advance to the next position in the array:
    ec55 = ec55 + 1;
    // if we're at the end of the array...
    if (ec55 >= numReadings)
      // ...wrap around to the beginning:
      ec55 = 0;
    // calculate the average:
    AnalogAverage = AnalogValueTotal / numReadings;
  }
  /*
    Every once in a while,MCU read the temperature from the DS18B20 and then let the DS18B20 start the convert.
    Attention:The interval between start the convert and read the temperature should be greater than 750 millisecond,or the temperature is not accurate!
  */
  if (millis() - tempSampleTime >= tempSampleInterval)
  {
    tempSampleTime = millis();
    temperature = TempProcess(ReadTemperature); // read the current temperature from the DS18B20
    TempProcess(StartConvert); //after the reading,start the convert for next reading
  }
  /*
    Every once in a while,print the information on the serial monitor.
  */
  if (millis() - printTime >= printInterval)
  {
    printTime = millis();
    averageVoltage = AnalogAverage * (float)5000 / 1024;
    Serial.print("Voltage: ");
    Serial.print(averageVoltage); //millivolt average,from 0mv to 4995mV
    Serial.print("mV\tTemperature: ");
    Serial.print(temperature); //current temperature
    Serial.print("degC\tEC: ");

    TempCoefficient = 1.0 + 0.0185 * (temperature - 25.0); //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.0185*(fTP-25.0));
    CoefficientVolatge = (float)averageVoltage / TempCoefficient;
    if (CoefficientVolatge < 150) Serial.println("No solution!"); //25^C 1413us/cm<-->about 216mv if the voltage(compensate)<150,that is <1ms/cm,out of the range
    else if (CoefficientVolatge > 3300) Serial.println("Out of the range!"); //>20ms/cm,out of the range
    else
    {
      if (CoefficientVolatge <= 448) ECcurrent = 6.84 * CoefficientVolatge - 64.32; //1ms/cm<EC<=3ms/cm
      else if (CoefficientVolatge <= 1457) ECcurrent = 6.98 * CoefficientVolatge - 127; //3ms/cm<EC<=10ms/cm
      else ECcurrent = 5.3 * CoefficientVolatge + 4322; //10ms/cm<EC<20ms/cm
      ECcurrent /= 1000; //convert us/cm to ms/cm
      Serial.print(ECcurrent, 2); //two decimal
      Serial.println("ms/cm");
    }
  }
}
float TempProcess(bool ch)
{
  //returns the temperature from one DS18B20 in DEG Celsius
  static byte data[12];
  static byte addr[8];
  static float TemperatureSum;
  if (!ch)
  {
    if ( !ds.search(addr)) {
      Serial.println("no more sensors on chain, reset search!");
      ds.reset_search();
      return 0;
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return 0;
    }
    if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized!");
      return 0;
    }
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1); // start conversion, with parasite power on at the end
  }
  else
  {
    byte present = ds.reset();
    ds.select(addr);
    ds.write(0xBE); // Read Scratchpad
    for (int i = 0; i < 9; i++) { // we need 9 bytes
      data[i] = ds.read();
    }
    ds.reset_search();
    byte MSB = data[1];
    byte LSB = data[0];
    float tempRead = ((MSB << 8) | LSB); //using two's compliment
    TemperatureSum = tempRead / 16;
  }
  return TemperatureSum;
}
