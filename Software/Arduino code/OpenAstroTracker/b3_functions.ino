
int read_LCD_buttons() {
  adc_key_in = analogRead(0);
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 240)  return btnUP;
  if (adc_key_in < 400)  return btnDOWN;
  if (adc_key_in < 600)  return btnLEFT;
  if (adc_key_in < 920)  return btnSELECT;
}

// Adjust the given number by the given adjustment, wrap around the limits.
// Limits are inclusive, so they represent the lowest and highest valid number.
int adjustWrap(int current, int adjustBy, int minVal, int maxVal)
{
  current += adjustBy;
  if (current > maxVal) current -= (maxVal + 1 - minVal);
  if (current < minVal) current += (maxVal + 1 - minVal);
  return current;
}

// Adjust the given number by the given adjustment, clamping to the limits.
// Limits are inclusive, so they represent the lowest and highest valid number.
int adjustClamp(int current, int adjustBy, int minVal, int maxVal)
{
  current += adjustBy;
  if (current > maxVal) current = maxVal;
  if (current < minVal) current = minVal;
  return current;
}

// Adjust the given seconds by the given adjustment, wrapping around.
int adjustSecond(int current, int adjustBy) {
  return adjustWrap(current, adjustBy, 0, 59);
}

// Adjust the given minutes by the given adjustment, wrapping around.
int adjustMinute(int current, int adjustBy) {
  return adjustWrap(current, adjustBy, 0, 59);
}

// Adjust the given hour by the given adjustment, wrapping around.
int adjustHour(int current, int adjustBy) {
  return adjustWrap(current, adjustBy, 0, 23);
}

// Clamp the given number to the limits.
// Limits are inclusive, so they represent the lowest and highest valid number.
long clamp(long current, long minVal, long maxVal)
{
  if (current > maxVal) current = maxVal;
  if (current < minVal) current = minVal;
  return current;
}

// Clamp the given number to the limits.
// Limits are inclusive, so they represent the lowest and highest valid number.
float clamp(float current, float minVal, float maxVal)
{
  if (current > maxVal) current = maxVal;
  if (current < minVal) current = minVal;
  return current;
}

#ifdef DEBUG_MODE
void log(const char* input) {
  Serial.println(input);
  Serial.flush();
}

void log(String input) {
  Serial.println(input);
  Serial.flush();
}
#endif

String formatRA(DayTime* ratime, int act = -1); // The Arduino IDEs auto generation does not handle custom datatypes
String formatRA(DayTime* ratime, int act = -1) {
  sprintf(scratchBuffer, " %02dh %02dm %02ds", ratime->getHours(), ratime->getMinutes(), ratime->getSeconds());
  switch (act) {
    case 0: scratchBuffer[0] = GREATER_THAN; break;
    case 1: scratchBuffer[4] = GREATER_THAN; break;
    case 2: scratchBuffer[8] = GREATER_THAN; break;
  }
  return String(scratchBuffer);
}
String formatDEC(int degree, int minute, int second, int act = -1) {
  sprintf(scratchBuffer, "%c%02d@ %02d' %02d\"", degree > 0 ? '+' : '-', int(fabs(degree)), minute, second);
  switch (act) {
    case 0: scratchBuffer[0] = GREATER_THAN; break;
    case 1: scratchBuffer[4] = GREATER_THAN; break;
    case 2: scratchBuffer[8] = GREATER_THAN; break;
  }
  return String(scratchBuffer);
}
