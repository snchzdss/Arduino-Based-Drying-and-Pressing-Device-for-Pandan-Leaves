void startHeating(int sheatingHours, int sheatingMinutes, int sheatingSeconds) {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Heating...");

  int totalTime = (sheatingHours * 3600) + (sheatingMinutes * 60) + sheatingSeconds;
  int elapsedTime = 0;

  digitalWrite(HEATER, RELAY_OFF);  // Turn on heater
  digitalWrite(FAN, RELAY_ON);     // Turn on fan

  while (elapsedTime < totalTime) {
    delay(1000);  // Wait 1 second
    elapsedTime++;

    // Calculate remaining time
    int remainingTime = totalTime - elapsedTime;
    int hours = remainingTime / 3600;
    int minutes = (remainingTime % 3600) / 60;
    int seconds = remainingTime % 60;

    // Display the remaining time
    lcd.setCursor(0, 2);
    lcd.print("Time Left: ");
    if (hours < 10) lcd.print("0");
    lcd.print(hours); lcd.print(":");
    if (minutes < 10) lcd.print("0");
    lcd.print(minutes); lcd.print(":");
    if (seconds < 10) lcd.print("0");
    lcd.print(seconds); lcd.print(" ");
  }

  // Stop heater and fan
  digitalWrite(HEATER, RELAY_ON);
  digitalWrite(FAN, RELAY_OFF);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Heating Complete");
  delay(2000);
}

void startPressing(int pressingHours, int pressingMinutes, int pressingSeconds) {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("      Pressing");
  lcd.setCursor(0, 2);
  lcd.print("     Activated!");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pressing...");

  unsigned long totalMillis = ((unsigned long)pressingHours * 3600UL + pressingMinutes * 60UL + pressingSeconds) * 1000UL;
  unsigned long startMillis = millis();
  bool movingForward = true;

  while (millis() - startMillis < totalMillis) {
    if (movingForward) {
      digitalWrite(MOVE_FWD, RELAY_ON);
      digitalWrite(MOVE_BWD, RELAY_OFF);
      if (digitalRead(LMS_FWD) == LOW) {
        movingForward = false;
      }
    } else {
      digitalWrite(MOVE_FWD, RELAY_OFF);
      digitalWrite(MOVE_BWD, RELAY_ON);
      if (digitalRead(LMS_BWD) == LOW) {
        movingForward = true;
      }
    }

    // Update LCD time
    unsigned long remaining = totalMillis - (millis() - startMillis);
    int hours = remaining / 3600000UL;
    int minutes = (remaining % 3600000UL) / 60000UL;
    int seconds = (remaining % 60000UL) / 1000UL;

    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    if (hours < 10) lcd.print("0"); lcd.print(hours); lcd.print(":");
    if (minutes < 10) lcd.print("0"); lcd.print(minutes); lcd.print(":");
    if (seconds < 10) lcd.print("0"); lcd.print(seconds); lcd.print("  ");

    delay(50); // small delay for LCD refresh, not blocking
  }

  // Stop all movement
  digitalWrite(MOVE_FWD, RELAY_OFF);
  digitalWrite(MOVE_BWD, RELAY_OFF);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("    Time Expired!");
  delay(1500);

  // Return to LMS_BWD (home)
  digitalWrite(MOVE_BWD, RELAY_ON);
  while (digitalRead(LMS_BWD) == HIGH) {
    // Add timeout logic if needed
    delay(5);
  }
  digitalWrite(MOVE_BWD, RELAY_OFF);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("    Pressing");
  lcd.setCursor(0, 2);
  lcd.print("    Complete!");

  digitalWrite(BUZZER, RELAY_OFF);
  delay(5000);
  digitalWrite(BUZZER, RELAY_ON);
  
  lcd.clear();
  displayMenu();
}

void setupHeater(int heatingHours, int heatingMinutes, int heatingSeconds) {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("      Setup");
  lcd.setCursor(0, 2);
  lcd.print("      Heater");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Heater ON");

  int totalTime = (heatingHours * 3600) + (heatingMinutes * 60) + heatingSeconds;
  int elapsedTime = 0;

  digitalWrite(FAN, RELAY_ON);
  digitalWrite(HEATER, RELAY_OFF); // Turn on the heater

  while (elapsedTime < totalTime) {
    char key = keypad.getKey();
    if (key == 'B') {
      Serial.print("Heater Stopped");
      // lcd.clear();
      // lcd.setCursor(0, 1);
      // lcd.print("Heater Stopped!");
      break;
    }

    delay(1000);  // Delay 1 second
    elapsedTime++;

    // Calculate remaining time
    int remainingTime = totalTime - elapsedTime;
    int hours = remainingTime / 3600;
    int minutes = (remainingTime % 3600) / 60;
    int seconds = remainingTime % 60;

    // Display on LCD
    lcd.setCursor(0, 1);
    lcd.print("Time Left: ");
    if (hours < 10) lcd.print("0");
    lcd.print(hours); lcd.print(":");
    if (minutes < 10) lcd.print("0");
    lcd.print(minutes); lcd.print(":");
    if (seconds < 10) lcd.print("0");
    lcd.print(seconds); lcd.print(" ");
  }

  // Turn off heater
  digitalWrite(FAN, RELAY_OFF);
  digitalWrite(HEATER, RELAY_ON);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("     Heater OFF");
  delay(2000);

  lcd.clear();
  displayMenu();
}

void setupPressing(int pHours, int pMinutes, int pSeconds) {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("        Setup");
  lcd.setCursor(0, 2);
  lcd.print("       Pressing");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pressing ON");

  unsigned long totalMillis = ((unsigned long)pHours * 3600UL + pMinutes * 60UL + pSeconds) * 1000UL;
  unsigned long startMillis = millis();
  bool movingForward = true;

  while (millis() - startMillis < totalMillis) {
    if (movingForward) {
      digitalWrite(MOVE_FWD, RELAY_ON);
      digitalWrite(MOVE_BWD, RELAY_OFF);
      if (digitalRead(LMS_FWD) == LOW) {
        movingForward = false;
      }
    } else {
      digitalWrite(MOVE_FWD, RELAY_OFF);
      digitalWrite(MOVE_BWD, RELAY_ON);
      if (digitalRead(LMS_BWD) == LOW) {
        movingForward = true;
      }
    }

    // Update LCD time
    unsigned long remaining = totalMillis - (millis() - startMillis);
    int hours = remaining / 3600000UL;
    int minutes = (remaining % 3600000UL) / 60000UL;
    int seconds = (remaining % 60000UL) / 1000UL;

    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    if (hours < 10) lcd.print("0"); lcd.print(hours); lcd.print(":");
    if (minutes < 10) lcd.print("0"); lcd.print(minutes); lcd.print(":");
    if (seconds < 10) lcd.print("0"); lcd.print(seconds); lcd.print("  ");

    delay(50); // small delay for LCD refresh, not blocking
  }

  // Stop all movement
  digitalWrite(MOVE_FWD, RELAY_OFF);
  digitalWrite(MOVE_BWD, RELAY_OFF);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("    Time Expired!");
  delay(1500);

  // Return to LMS_BWD (home)
  digitalWrite(MOVE_BWD, RELAY_ON);
  while (digitalRead(LMS_BWD) == HIGH) {
    // Add timeout logic if needed
    delay(5);
  }
  digitalWrite(MOVE_BWD, RELAY_OFF);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("    Pressing");
  lcd.setCursor(0, 2);
  lcd.print("    Complete!");

  digitalWrite(BUZZER, RELAY_OFF);
  delay(5000);
  digitalWrite(BUZZER, RELAY_ON);

  lcd.clear();
  displayMenu();
}