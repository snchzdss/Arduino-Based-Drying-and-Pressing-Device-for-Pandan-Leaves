void serialCommand() {
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    Serial.print("Command received: ");
    Serial.println(cmd);

    if (cmd == "fwd") {
    if (digitalRead(LMS_FWD) == HIGH) {
      Serial.println("ROLLING FWD");
      digitalWrite(MOVE_FWD, RELAY_ON);
      while (digitalRead(LMS_FWD) == HIGH){
        delay(10);
      }
      delay(50);
      Serial.println("Stop");
      digitalWrite(MOVE_FWD, RELAY_OFF);
    }
  }
  else if (cmd == "bwd") {
    if (digitalRead(LMS_BWD) == HIGH) {
      Serial.println("ROLLING BWD");
      digitalWrite(MOVE_BWD, RELAY_ON);
      while (digitalRead(LMS_BWD) == HIGH){
        delay(10);
      }
      delay(50);
      Serial.println("Stop");
      digitalWrite(MOVE_BWD, RELAY_OFF);
    }
  }
  else if (cmd == "buzz") {
    Serial.println("BUZZING");
    digitalWrite(BUZZER, RELAY_OFF);
    delay(3000);
    digitalWrite(BUZZER, RELAY_ON);
  }
  else if (cmd == "heat") {
    Serial.println("HEATING");
    digitalWrite(HEATER, RELAY_OFF);
    delay(60000);
    digitalWrite(HEATER, RELAY_ON);
  }
  else if (cmd == "fan") {
    Serial.println("FAN");
    digitalWrite(FAN, RELAY_ON);
    delay(5000);
    digitalWrite(FAN, RELAY_OFF);
  }
  }
}
