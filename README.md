# EEPROM Burner Mega

Burn/validate 28c256 EEPROMs with an Arduino Mega.

See pinout at top of sketch.  Place bytes in `data` array—they will be written sequentially starting from address 0.  Be sure to fill in the reset vector address, and if applicable, any interrupts.

