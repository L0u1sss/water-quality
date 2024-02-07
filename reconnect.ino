void reconnect() {
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password))
    {
      lcd.setCursor(0, 1);
      lcd.print("MQTT Connected");
      Serial.println("connected");
    }
    else
    {
      lcd.setCursor(0, 1);
      lcd.print("  Reconnection  ");
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}
