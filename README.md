* keyer.ino

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
