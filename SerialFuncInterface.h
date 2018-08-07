// SerialFuncInterface.h

#ifndef _SERIALFUNCINTERFACE_h
#define _SERIALFUNCINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "wprogram.h"
#else
	#include "WProgram.h"
#endif


struct NameFuncCombo
{
	String Identifier;	
	String(*Func)(String *);
	String(*GetFunc)(String *);	
};

typedef struct NameFuncCombo NameFuncCombo;

union ParameterUnion
{
	int ival;
	float fval;
};

enum ParameterTypes
{
	FloatVar = 0,
	IntVar = 1
};

struct TypedParameter
{
	ParameterUnion Param;
	ParameterTypes Type;
	bool Required;
};

typedef struct TypedParameter TypedParameter;

/**
 * @brief Class to handle serial interface commands
 * 
 *   Commands ("Funcionts") take the form of:
 * Set commands:
 *  [Identifier] [Param];
 * 	Ex: Value 100;\n
 * Get commands
 *  [Identifier]?;
 * 	Ex: Value?;\n
 * Command with more than one parameter:
 * 	Ex: Value 100,200;\n
 * Multiple commands can be sent in a line:
 *  Ex: Value1 100;Value2 200;Value1?;\n
 */
class SerialFuncInterfaceClass
{
 protected:
	 static const char RequestChar = '?';
	 static const char Terminator = ';';
	 static const char Delimiter = ',';

	 const String ConnectString = "Hi computer!\n";
	 static String ID ;

	 const String IDPrefix = "ID";
	 const String ErrorPrefix = "Error";

	 unsigned int MAX_NUM_FUNC = 16;
	 unsigned int CurrentLen = 0;
	 NameFuncCombo * FuncList;

	 unsigned int Baud = 115200;
	 unsigned int Timeout = 5;



 public:
 /**
  * @brief Construct a new Serial Func Interface Class object
  *  
  */
	SerialFuncInterfaceClass();
	/**
	 * @brief Construct a new Serial Func Interface Class object
	 * 
	 * @param maxfuncnum need to set up the max number of functions before starting
	 */
	SerialFuncInterfaceClass(unsigned int maxfuncnum);
	/**
	 * @brief Construct a new Serial Func Interface Class object
	 * 
	 * @param maxfuncnum need to set up the max number of functions before starting
	 * @param id You can overwrite the default ID
	 */
	SerialFuncInterfaceClass(unsigned int maxfuncnum, String id);

	/**
	 * @brief Set the Baud rate
	 * 
	 * @param baud Baud rate
	 */
	void SetBaud(unsigned int baud);

	/**
	 * @brief Register a new function
	 * 
	 * @param nfc New funcion combination
	 * @return true It worked
	 * @return false It failed
	 */
	bool AddFunc(NameFuncCombo nfc);

	/**
	 * @brief Add an array of funcions
	 * 
	 * @param nfc New funcion combination
	 * @param length Number of new funcions added
	 * @return true It worked
	 * @return false It failed
	 */
	bool AddFunc(NameFuncCombo nfc[],unsigned int length);

	/**
	 * @brief Deal with any undealed with messages
	 * 
	 * @return true 
	 * @return false 
	 */
	bool ParseSerial();

	/**
	 * @brief The class always will have an ID function which returns an ID
	 * 
	 * @param val Input string
	 * @return String ID
	 */
	static String IDFunc(String * val);

	/**
	 * @brief Helper funcion to deal with parameters
	 * 
	 * @param out Parameter list out
	 * @param outlen length of list
	 * @param In Input string
	 * @return true 
	 * @return false 
	 */
	static bool ParseArguments(TypedParameter * out, int outlen, String * In);

};


#endif

