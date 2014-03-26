#ifndef PARSER_HH
#define PARSER_HH
/**
 * @file Parser.hh
 * @brief The header of the static Parser class
 */

 // System includes
 #include <iostream>
 #include <fstream>
 #include <string>
 #include <vector>
 #include <map>

 // Local includes
 #include "Brain.hh"
 #include "ArgumentType.hh"

 class Brain;

/** @class Parser.hh
 * Class that reads a program into a brain. It also parses the arguments given
 * to functions.
 */
 class Parser {

 public:
   /**
      @breif Function that loads the instructions from a brainfile into a brain
      @param brainptr The brain where the instructions will be stored
      @param brainfile The path to the brain file
      @param arguments Uneccesary argument for the moment
      @return Zero on success or an error number
    */
 	static int parseFile(Brain** brainptr, std::string brainfile, int arguments);
 	static int parseImmediate(void* value, std::string imed);
   	static int parseGetTypeImmediate(ArgumentType* type,std::string imed);
 	
 };

#endif
