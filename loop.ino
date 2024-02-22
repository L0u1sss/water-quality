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
//   Serial.print("ปุ่ม :");
//   Serial.println(swstate);
  if ((previousValue != swstate) && (previousValue == 0)) {
    previousValue = swstate;
    String data1 = String(ECcurrent);
    data1.toCharArray(msg, (data1.length() + 1));
    client.publish("msg/ec", msg);
    lcd.setCursor(0, 2);
    lcd.print("EC  :");
    lcd.setCursor(5, 2);
    lcd.print("                ");
    lcd.setCursor(5, 2);
    lcd.print(ECcurrent);
    String data2 = String(tdsValueTDS);
    data2.toCharArray(msg, (data2.length() + 1));
    client.publish("msg/tds", msg);
    lcd.setCursor(0, 3);
    lcd.print("TDS :");
    lcd.setCursor(5, 3);
    lcd.print("                ");
    lcd.setCursor(5, 3);
    lcd.print(tdsValueTDS);
    String LEC = "EC :" + String(ECcurrent);
    String LTDS = "TDS :" + String(tdsValueTDS);
    LINE.notify(LEC);
    LINE.notify(LTDS);
  }
  
  if ((previousValue != swstate) && (previousValue == 1)) {
    previousValue = 0;
  }
  
}
