#include "LoggerFunctions.h"

bool Logger_Log(Logger* logger, const char* type, const char* message)
{
	if(logger == NULL || logger->filename == NULL)
	{
		return false;
	}
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	FILE* logfile = fopen(logger->filename, "a");
	fprintf(logfile, "[%d-%d-%d@%d:%d:%d] %s: %s\n", tm.tm_year + 1900, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, type, message);
	fclose(logfile);
	
	return true;
}
