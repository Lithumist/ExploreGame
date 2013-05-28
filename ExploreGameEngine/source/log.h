#ifndef LOG_H
#define LOG_H

/*
	log.h

	declares a logging interface (in a namespace)

	Provides methods for the whole engine to log acivities
*/





/*
		*
		*  For all logging operations, newlines ARE added
		*  automaticallyat the end of the supplied message.
		*
*/





#include <iostream>
#include <string>
#include <fstream>




namespace eg
{
	namespace log
	{



		bool open(std::string filename); // opens the log file for writing
		void close(); // closes the log file, (must be called at the end of the program)





		//
		// Basic logging
		//
		void log(std::string message); // logs to iostream and the log file
		void log_iostream(std::string message); // logs to iostream
		void log_file(std::string message); // logs to log file



		//
		// Error logging (formatted to be easy to spot)
		//
		void error(std::string message); // logs an error message to iostream and the log file
		void error_iostream(std::string message); // logs an error message to iostream
		void error_file(std::string messasge); // logs an error message to the log file









		/* PRIVATE VARIABLES */
		extern std::ofstream LOG_FILE;



	}
}




#endif