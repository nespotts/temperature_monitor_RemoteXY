// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
  
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
    Serial.print(",");
  }
}

// function to print the temperature for a device
double printTemperature(DeviceAddress deviceAddress)
{
  float tempF = sensors.getTempF(deviceAddress);
  if (tempF == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: Could not read temperature data");
    return -100;
  }
  Serial.print("Temp F: ");
  Serial.print(tempF);
  return tempF;
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress) {
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();
}

// main function to print information about a device
double printData(DeviceAddress deviceAddress) {
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  double tempF = printTemperature(deviceAddress);
  Serial.println();
  return tempF;
}

void setupSensors() {
  // start serial port
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();

  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // Search for devices on the bus and assign based on an index. Ideally,
  // you would do this to initially discover addresses on the bus and then
  // use those addresses and manually assign them (see above) once you know
  // the devices on your bus (and assuming they don't change).
  //
  // method 1: by index
  // if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");
  // if (!sensors.getAddress(outsideThermometer, 1)) Serial.println("Unable to find address for Device 1");
  // if (!sensors.getAddress(electricalThermometer, 2)) Serial.println("Unable to find address for Device 2");

  // method 2: search()
  // search() looks for the next device. Returns 1 if a new address has been
  // returned. A zero might mean that the bus is shorted, there are no devices,
  // or you have already retrieved all of them. It might be a good idea to
  // check the CRC to make sure you didn't get garbage. The order is
  // deterministic. You will always get the same devices in the same order
  //
  // Must be called before search()
  //oneWire.reset_search();
  // assigns the first address found to insideThermometer
  //if (!oneWire.search(insideThermometer)) Serial.println("Unable to find address for insideThermometer");
  // assigns the seconds address found to outsideThermometer
  //if (!oneWire.search(outsideThermometer)) Serial.println("Unable to find address for outsideThermometer");

  // show the addresses we found on the bus
  Serial.print("Inside Thermometer: ");
  printAddress(insideThermometer);
  Serial.println();

  Serial.print("Outside Thermometer: ");
  printAddress(outsideThermometer);
  Serial.println();

  Serial.print("Electrical Cabinet: ");
  printAddress(electricalThermometer);
  Serial.println();

  // set the resolution to 9 bit per device
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(electricalThermometer, TEMPERATURE_PRECISION);

  Serial.print("Inside Thermometer Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC);
  Serial.println();

  Serial.print("Outside Thermometer Resolution: ");
  Serial.print(sensors.getResolution(outsideThermometer), DEC);
  Serial.println();

  Serial.print("Electrical Cabinet Resolution: ");
  Serial.print(sensors.getResolution(electricalThermometer), DEC);
  Serial.println();
}


void readTemps() {
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  // print the device information
  insideTemp = printData(insideThermometer);
  outsideTemp = printData(outsideThermometer);
  electricalTemp = printData(electricalThermometer);

  set_temps(insideTemp, outsideTemp, electricalTemp);
}





