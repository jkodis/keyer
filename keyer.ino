//
// keyer.ino -- use an Arduino as a fixed speed two-paddle iambic keyer.
//

// Wikipedia says that the length of a dot in milliseconds is 1200 over
// the words per minute rate when using "PARIS" as the standard word.
const int wpm = 10;
const int ditTime = 1200 / wpm;

const int ditPin  = 7;
const int dahPin  = 8;
const int tonePin = 12;

enum states {
  IDLE, NEED_DIT, NEED_DIT_PAUSE, NEED_DAH, NEED_DAH_PAUSE
};
enum states state = IDLE;

void setup() {
  pinMode(tonePin, OUTPUT);
  pinMode(ditPin, INPUT_PULLUP);
  pinMode(dahPin, INPUT_PULLUP);
  Serial.begin(9600);
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
