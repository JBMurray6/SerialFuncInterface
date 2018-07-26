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

//Example of a command with several parameters
const String FreqSweepPrefix = "Sweep";
String GetFreqSweep(String * S);
String SetFreqSweep(String * S);
NameFuncCombo FreqSweepFuncs = { FreqSweepPrefix,SetFreqSweep,GetFreqSweep };
enum SweepTypes
{
  LIN = 0,
  LOG = 1
};
const int NumSweepParams = 4;
const float initfloat = 0;
const TypedParameter FreqSweepParams[NumSweepParams] = {
  { initfloat , FloatVar,  true },//Start
{ initfloat , FloatVar, true },//Stop
{ (int)1000 , IntVar, false },//Num of milliseconds
{ (int)0 , IntVar, false }//SweepType enum
};

void setup() {
  // Register your serial funcions
  SerialFuncInterface.AddFunc(FreqFuncs);
  SerialFuncInterface.AddFunc(AmplitudeFuncs);
  SerialFuncInterface.AddFunc(SweepFuncs);
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


String SetFreqSweep(String * S)
{
  memcpy(&LastSetSweep, &FreqSweepParams, sizeof FreqSweepParams);

  if (!SerialFuncInterface.ParseArguments(LastSetSweep, NumSweepParams, &(S->append(';'))))
  {
    Serial.println("Failed");
  }

  float SweepMillis = LastSetSweep[2].Param.ival;
  float SweepDelta = (float)(LastSetSweep[1].Param.fval - LastSetSweep[0].Param.fval);

  switch (LastSetSweep[3].Param.ival)
  {
  case (SweepTypes::LIN):
    //Not implemented
    break;
  case (SweepTypes::LOG):
    SweepRate = ((float)(log10(LastSetSweep[1].Param.fval) - log10(LastSetSweep[0].Param.fval))) / ((float)LastSetSweep[2].Param.ival);//delta freq/time
    break;
  default:
    return "Not a sweep type";
  }

  CurrSetFreq = LastSetSweep[0].Param.fval;
  memcpy(&CurrentSweep, &LastSetSweep, sizeof FreqSweepParams);
  return "Runing sweep";

}

String GetFreqSweep(String * S)
{
  return String(CurrentSweep[0].Param.fval);
}

