# SerialFuncInterface

Creates a serial interface for arduino projects. It provides an iterface designed for commands or changing some variable. Note that this uses the String class for dealing with commands and so is best suited for things with plenty of speed and RAM (I targeted the teensy LC or teensy 3.2 boards originally) but will work for anything.
