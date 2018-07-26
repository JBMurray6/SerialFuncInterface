#include "SerialFuncInterface.h"

SerialFuncInterfaceClass SerialFuncInterface = SerialFuncInterfaceClass(3);//Starts with an ID class

//Define a couple serial funcions
const String FreqPrefix = "Freq";
String GetFreq(String * S);
String SetFreq(String * S);
NameFuncCombo FreqFuncs = { FreqPrefix,SetFreq,GetFreq };
float Freq = 1;

const String AmplitudePrefix = "Amp";
String GetAmplitude(String * S);
String SetAmplitude(String * S);
NameFuncCombo AmplitudeFuncs = { AmplitudePrefix,SetAmplitude,GetAmplitude };
float Amplitude = 1;

void setup() {
  // Register your serial funcions
  SerialFuncInterface.AddFunc(FreqFuncs);
  SerialFuncInterface.AddFunc(AmplitudeFuncs);
}

void loop() {
  // Parse your inputs (nothing happens if there are none
  SerialFuncInterface.ParseSerial();
}

//Start of Serial functions
String GetFreq(String *)
{
  return String(Freq);
}

String SetFreq(String * S)
{
  float F = S->toFloat();
  Freq=F;
  return "Set to " + String(Freq);
}

String GetAmplitude(String *)
{
  return String(Amplitude);
}

String SetAmplitude(String * S)
{
  Amplitude = S->toFloat();
  if (Amplitude > 1)
  {
    Amplitude = 1;
  }
  else if (Amplitude < 0)
  {
    Amplitude = 0;
  }

  return "Set to " + String(Amplitude);
}

