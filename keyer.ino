//
// keyer.ino -- use an Arduino as an adjustable speed two-paddle iambic keyer.
//

const int wpmMin     = 3;
const int wpmMax     = 30; // these values set the range of speeds available
const int wpmFixed   = 0;    // zero to use a pot, higher for a fixed speed

const int ditPin     = 7;  // traditionally, the left hand keyer paddle
const int dahPin     = 8;  // traditionally, the right hand keyer paddle
const int tonePin    = 2;  // long pin to 2, shorter pin to ground
const int speedPot   = A0;

enum states {
  IDLE, NEED_DIT, NEED_DIT_PAUSE, NEED_DAH, NEED_DAH_PAUSE
};
enum states state = IDLE;

void setup() {
  Serial.begin(9600);
  pinMode(tonePin,OUTPUT);
  pinMode(ditPin, INPUT_PULLUP);
  pinMode(dahPin, INPUT_PULLUP);
}

// getWpm -- gets the appropriate words per minute value based on a
// setting of the speed potentiometer.  If you'd rather not bother
// with this, just set wpmDefault to your preferred fixed speed.
float getWpm() {
  if (wpmFixed > 0)
    return wpmFixed;
  int potValue = analogRead(speedPot); // returns 0..1023
  float wpm = wpmMin + (potValue * (wpmMax - wpmMin)) / 1024.;
  return wpm;
}

void loop() {

  bool ditRequested = false, dahRequested = false;
  unsigned long int timeNow, timeNext;
  timeNow = timeNext = millis();

  while (true) {
    ditRequested = ditRequested || (digitalRead(ditPin) == LOW);
    dahRequested = dahRequested || (digitalRead(dahPin) == LOW);

    timeNow = millis();
    if (timeNow >= timeNext) {
      // The length of a dot in milliseconds is 1200 over the words
      // per minute rate, when using "PARIS" as the standard word.
      float wpm = getWpm();
      int ditTime = 1200 / wpm;
      switch (state) {
      case IDLE:
        if (ditRequested) {
          state = NEED_DIT;
        }
        if (dahRequested) {
          state = NEED_DAH;
        }
        continue;
      case NEED_DIT:
        digitalWrite(tonePin, HIGH);
        timeNext = millis() + ditTime;
        state = NEED_DIT_PAUSE;
        continue;
      case NEED_DIT_PAUSE:
        digitalWrite(tonePin, LOW);
        timeNext = millis() + ditTime;
        ditRequested = false;
        state = dahRequested ? NEED_DAH : IDLE;
        continue;
      case NEED_DAH:
        digitalWrite(tonePin, HIGH);
        timeNext = millis() + 3 * ditTime;
        state = NEED_DAH_PAUSE;
        continue;
      case NEED_DAH_PAUSE:
        digitalWrite(tonePin, LOW);
        timeNext = millis() + ditTime;
        dahRequested = false;
        state = ditRequested ? NEED_DIT : IDLE;
        continue;
      }
      delay(1);
    }
  }
}
