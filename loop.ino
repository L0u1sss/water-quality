void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  ec();
  String data1 = String(ECcurrent);
  data1.toCharArray(msg, (data1.length() + 1));
  client.publish("msg/ec", msg);

  tds();
  String data2 = String(tdsValueTDS);
  data2.toCharArray(msg, (data2.length() + 1));
  client.publish("msg/tds", msg);
  
  delay(1000);
}
