// log.cpp
#include "log.h"




namespace explore
{
	namespace log
	{







		/* open */
		bool open(std::string filename)
		{

			// close the log file if it's open
			close();

			LOG_FILE.open(filename.c_str());
			if(LOG_FILE.fail())
				return false;
			else
				return true;


		}










		/* close */
		void close()
		{
			if(LOG_FILE.is_open())
				LOG_FILE.close();
		}











		/* log */
		void log(std::string message)
		{
			log_iostream(message);
			log_file(message);
		}



		/* log_iostream */
		void log_iostream(std::string message)
		{
			// only log to iostream in debug mode
			#ifndef EG_DEBUG_MODE
			return;
			#endif

			std::cout << message << std::endl;
		}



		/* log_file */
		void log_file(std::string message)
		{
			if(!LOG_FILE.is_open())
				return;

			LOG_FILE << message << std::endl;
			LOG_FILE.flush();
		}











		/* warning */
		void warning(std::string message)
		{
			warning_iostream(message);
			warning_file(message);
		}




		/* warning_iostream */
		void warning_iostream(std::string message)
		{
			// only log to iostream in debug mode
			#ifndef EG_DEBUG_MODE
			return;
			#endif

			std::cout << std::endl;
			std::cout << " --- Warning ---" << std::endl;
			std::cout << message << std::endl;
			std::cout << " ---------------" << std::endl;
		}




		/* warning_file */
		void warning_file(std::string message)
		{
			if(!LOG_FILE.is_open())
				return;

			LOG_FILE << std::endl;
			LOG_FILE << " --- Warning ---" << std::endl;
			LOG_FILE << message << std::endl;
			LOG_FILE << " ---------------" << std::endl;
		}










		/* error */
		void error(std::string message)
		{
			error_iostream(message);
			error_file(message);
		}




		/* error_iostream */
		void error_iostream(std::string message)
		{
			// only log to iostream in debug mode
			#ifndef EG_DEBUG_MODE
			return;
			#endif

			std::cout << std::endl;
			std::cout << " ~~~~~~~~~~~ ERROR ~~~~~~~~~~~" << std::endl;
			std::cout << message << std::endl;
			std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		}




		/* error_file */
		void error_file(std::string message)
		{
			if(!LOG_FILE.is_open())
				return;

			LOG_FILE << std::endl;
			LOG_FILE << " ~~~~~~~~~~~ ERROR ~~~~~~~~~~~" << std::endl;
			LOG_FILE << message << std::endl;
			LOG_FILE << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
		}







		/* PRIVATE VARIABLES */
		std::ofstream LOG_FILE;




	}
}