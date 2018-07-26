# SerialFuncInterface

Creates a serial interface for arduino projects. It provides an iterface designed for commands or changing some variable. Note that this uses the String class for dealing with commands and so is best suited for things with plenty of speed and RAM (I targeted the teensy LC or teensy 3.2 boards originally) but will work for anything.

Commands ("Funcions") take the form of:  
  Set commands:  
   [Identifier] [Param];  
  	Ex: Value 100;\n  
  Get commands  
   [Identifier]?;  
  	Ex: Value?;\n  
  Command with more than one parameter (there is a function included to help parse these):  
  	Ex: Value 100,200;\n  
  Multiple commands can be sent in a line:  
   Ex: Value1 100;Value2 200;Value1?;\n  

