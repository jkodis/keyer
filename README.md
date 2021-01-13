* keyer.ino

For those who might wonder, a keyer is a bit of hardware and software
used primarily by amateur radio operators to send morse code faster
and more accurately than can be done using a simple manual key.  Also,
as a way for me to play around with and learn about an Arduino.

** Version 1.0 -- the fixed speed version

The keyer program allows the use of an Arduino as a simple fixed speed
iambic two paddle keyer.

As currently configured, the program is set up for use with an Arduino
Uno board, and may need to be changed for a different Arduino board.
It only requires three pins: two digital input pins for the two
paddles and one digital output pin to drive a small buzzer.  Two
ground pins are also required, one for the buzzer and one for the
common connection to the keyer paddles.  The speed is fixed at 10
words per minute.  If necessary, all of this can be adjusted by
changing a few constant values at the beginning of the program.

** Version 1.1 -- the potentiometer speed controlled version

This version adds a few new values and another input to configure.
Rather than a single fixed speed, there is now a range of speeds,
currently set to between 3 and 30 WPM (because anything below 3 WPM
puts me to sleep and anything over 30WPM is way too fast for my poor
old brain to register), but like anything else here there are a few
constants that can be changed if you so desire.  You'll also have to
connect a potentiometer for speed control.  This is easy -- the two
outer legs go to Vcc (+5V or +3.3V, depending on the board you're
using) while the "slider" or "wiper" contact has to go on one of the
analog input pins, by default, A0.

