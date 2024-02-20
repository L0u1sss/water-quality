void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  ec();
  tds();
  bool swstate = digitalRead(sw);

  if ((previousValue != swstate) && (previousValue == 0)) {
    previousValue = swstate;
    String data1 = String(ECcurrent);
    data1.toCharArray(msg, (data1.length() + 1));
    client.publish("msg/ec", msg);
    lcd.setCursor(0, 0);
    lcd.print("EC :");
    lcd.setCursor(4, 0);
    lcd.print(ECcurrent);
    String data2 = String(tdsValueTDS);
    data2.toCharArray(msg, (data2.length() + 1));
    client.publish("msg/tds", msg);
    lcd.setCursor(0, 1);
    lcd.print("TDS :");
    lcd.setCursor(5, 1);
    lcd.print(tdsValueTDS);
    String LEC = "EC :" + String(ECcurrent);
    String LTDS = "TDS :" + String(tdsValueTDS);
    LINE.notify(LEC);
    LINE.notify(LTDS);
  }
  
  if ((previousValue != swstate) && (previousValue == 1)) {
    previousValue = 0;
  }
  
  delay(1000);

}
