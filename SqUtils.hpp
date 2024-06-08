#pragma once


#define CHECK_ARG_COUNT(v, count) \
    if (sq_gettop(v) != count + 1) return sq_throwerror(v, _SC("Invalid argument count"));

#define REGISTER_SQ_FUNC(sqvm, name, func) { \
    sq_pushstring(sqvm, name, -1); \
    sq_newclosure(sqvm, func, 0); \
    sq_newslot(sqvm, -3, SQFalse); \
}



#ifdef SYSTEM_WINDOWS

#define CONSOLE_COLOR_RESET ""
#define CONSOLE_COLOR_GREEN ""
#define CONSOLE_COLOR_RED ""
#define CONSOLE_COLOR_PURPLE ""
#define CONSOLE_COLOR_CYAN ""


#else

#define CONSOLE_COLOR_RESET "\033[0m"
#define CONSOLE_COLOR_GREEN "\033[1;32m"
#define CONSOLE_COLOR_RED "\033[1;31m"
#define CONSOLE_COLOR_PURPLE "\033[1;35m"
#define CONSOLE_COLOR_CYAN "\033[0;36m"

#endif 






inline void Log(int severity, const char* fmt, ...)
{




		const char* type="info";
        const char* color = CONSOLE_COLOR_GREEN;
		switch (severity) 
        {
			case  0:
				type = "info";
				color = CONSOLE_COLOR_GREEN;
				break;
			case 1:
				type = "warning";
				color = CONSOLE_COLOR_PURPLE;
				break;
            case 2:
				type = "error";
				color = CONSOLE_COLOR_RED;
				break;
			default:
				break;
		}

		time_t rawTime;
		struct tm* timeInfo;
		char timeBuffer[80];

		time(&rawTime);
		timeInfo = localtime(&rawTime);

		strftime(timeBuffer, sizeof(timeBuffer), "[%H:%M:%S]", timeInfo);

		char consoleFormat[1024];
		snprintf(consoleFormat, 1024, "%s%s %s%s%s: %s\n", CONSOLE_COLOR_CYAN,
				timeBuffer, color, type, CONSOLE_COLOR_RESET, fmt);


		char fileFormat[1024];
		snprintf(fileFormat, 1024, "%s %s: %s\n", timeBuffer, type, fmt);

		va_list argptr;

		va_start(argptr, fmt);
		vprintf(consoleFormat, argptr);
		va_end(argptr);

		char buf[4096];

		va_start(argptr, fmt);
		vsprintf(buf, fmt, argptr);
		va_end(argptr);

        #ifdef SYSTEM_WINDOWS
        

        #else
   
        #endif


       
}



#define ERROR0(msg) Log(2,__FILE__, __LINE__, msg)
#define ERROR(msg, ...) Log(2,__FILE__, __LINE__, msg, __VA_ARGS__)


inline void printfunc(HSQUIRRELVM , const SQChar* s, ...) 
{
    va_list vl;
    va_start(vl, s);
    vprintf(s, vl);
    va_end(vl);
}

inline void errorfunc(HSQUIRRELVM , const SQChar* s, ...) 
{
    va_list vl;
    va_start(vl, s);
    vfprintf(stderr, s, vl);
    va_end(vl);
}
