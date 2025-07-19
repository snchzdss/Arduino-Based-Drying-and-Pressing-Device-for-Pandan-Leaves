void setupProcess() {
  int sheatingHours = 0, sheatingMinutes = 0, sheatingSeconds = 0;
  int pressingHours = 0, pressingMinutes = 0, pressingSeconds = 0;

  getTimeInput("Heating Time:", sheatingHours, sheatingMinutes, sheatingSeconds);
  getTimeInput("Pressing Time:", pressingHours, pressingMinutes, pressingSeconds);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press A to Start");

  while (true) {
    char key = keypad.getKey();
    if (key == 'A') {
      while (true) {
        startHeating(sheatingHours, sheatingMinutes, sheatingSeconds);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("A: Continue");
        lcd.setCursor(0, 1);
        lcd.print("B: Reheat");

        while (true) {
          key = keypad.getKey();
          if (key == 'A') {
            startPressing(pressingHours, pressingMinutes, pressingSeconds);
            return;
          } else if (key == 'B') {
            getTimeInput("Reheat Time:", sheatingHours, sheatingMinutes, sheatingSeconds);
            break; // Go back to reheating
          }
        }
      }
    }
  }
}


void displayMenu() {
  const int menuLength = 3;
  String menuItems[menuLength] = {"SETUP PROCESS", "SETUP HEATER", "SETUP PRESSING"};
  int selectedIndex = 0;

  while (true) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("      PANDAIKU");
    lcd.setCursor(0, 2);
    lcd.print("  > ");
    lcd.print(menuItems[selectedIndex]);

    char key = keypad.getKey();
    if (key == 'C') { // Scroll up
      selectedIndex--;
      if (selectedIndex < 0) selectedIndex = menuLength - 1;
    } else if (key == 'D') { // Scroll down
      selectedIndex++;
      if (selectedIndex >= menuLength) selectedIndex = 0;
    } else if (key == 'A') { // Select
      if (selectedIndex == 0) {
        setupProcess();
      } else if (selectedIndex == 1) {
        // Ask for only heating time for standalone heater setup
        int hH = 0, hM = 0, hS = 0;
        getTimeInput("Heater Time:", hH, hM, hS);
        setupHeater(hH, hM, hS);
      } else if (selectedIndex == 2) {
        int pH = 0, pM = 0, pS = 0;
        getTimeInput("Pressing Time:", pH, pM, pS);
        setupPressing(pH, pM, pS);
      }
      return; // Exit menu after selection
    }
    delay(200);
  }
}

void getTimeInput(const char* label, int &hours, int &minutes, int &seconds) {
  char timeStr[9] = "--:--:--"; // Format for HH:MM:SS, initialize with placeholders
  int pos = 0; // Position tracker for digits input
  char key;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(label);
  lcd.setCursor(0, 1);
  lcd.print(timeStr);  // Display the initial placeholder
  lcd.setCursor(0, 3);
  lcd.print("# - Save");

  while (true) {
    key = keypad.getKey();
    
    if (key >= '0' && key <= '9') {
      if (pos < 8) {  // Ensure that we do not overwrite the colon positions
        timeStr[pos] = key;
        lcd.setCursor(pos, 1);
        lcd.print(key);  // Display the digit at the current position
        pos++;

        // Ensure colons stay fixed at positions 2 and 5
        if (pos == 2 || pos == 5) {
          pos++;  // Skip the colon positions
        }
      }
    } else if (key == '#') { // Confirm Input
      // Parse the time from the entered string
      hours = (timeStr[0] - '0') * 10 + (timeStr[1] - '0');
      minutes = (timeStr[3] - '0') * 10 + (timeStr[4] - '0');
      seconds = (timeStr[6] - '0') * 10 + (timeStr[7] - '0');
      break;  // Exit input loop after valid entry
    } else if (key == '*') { // Clear input
      pos = 0;
      strcpy(timeStr, "--:--:--");
      lcd.setCursor(0, 1);
      lcd.print(timeStr);  // Reset time display to placeholders
    }
  }
}