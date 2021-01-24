* keyer.ino

For those who might wonder, a keyer is a bit of hardware and software
used primarily by amateur radio operators to send morse code faster
and more accurately than can be done using a simple manual key.  Also,
as a way for me to play around with and learn about an Arduino.

Here are a few notes...

The various versions aren't so much steady improvements as they are
different ways to control the speed of the keyer.  Version used a
fixed speed; Version 2 uses a potentiometer to control the speed; and
Version 3 will likely use a combination of a button used in
conjunction with the keyer paddles to control the speed.  Because of
this, the hardware requirements and the pin assignments will vary
somewhat between versions.  You have been warned.

There are active buzzers, which buzz when a voltage is applied.  This
is the kind I've used here.  They are polarized, and won't work if the
polarity is incorrect.  There are also passive buzzer, which require
an AC signal.  These won't work with this circut.

** Version 2.0 -- the potentiometer speed controlled version

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

