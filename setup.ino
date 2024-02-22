void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  LINE.setToken(LINE_TOKEN);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(sw, INPUT);
  pinMode(TdsSensorPin, INPUT);
  
  lcd.init(); // SDA 21 SCL 22
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Water Quality");
  
  client.setServer(mqtt_server, mqtt_port);
  for (byte thisReading = 0; thisReading < numReadings; thisReading++) readings[thisReading] = 0;
  TempProcess(StartConvert); //let the DS18B20 start the convert
}
