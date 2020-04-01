void processCalibrationKeys(int key) {
  switch (key) {
    case btnUP: {
        inputcal += 1;  //0.0001;
        speedCalibration = speed + inputcal / 10000;
        delay(calDelay);
        calDelay = max(5, 0.96 * calDelay);
        waitForButtonRelease = false;
      }
      break;

    case btnDOWN: {
        inputcal -= 1 ; //0.0001;
        speedCalibration = speed + inputcal / 10000;
        delay(calDelay);
        calDelay = max(5, 0.96 * calDelay);
        waitForButtonRelease = false;
      }
      break;

    case btnSELECT: {
        EEPROM.update(0, inputcal);
        speedCalibration = speed + inputcal / 10000;
      }
      break;

    case btnRIGHT: {
        lcdMenu.setNextActive();
      }
      break;

    case btnNONE:
      {
        calDelay = 150;
      }
      break;
  }
}

void printCalibrationSubmenu() {
  sprintf(scratchBuffer, "SpdFctr: ");
  dtostrf(speedCalibration, 6, 4, &scratchBuffer[9]);
  lcdMenu.printMenu(scratchBuffer);
}
