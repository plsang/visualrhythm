#ifndef LOG_INCLUDE
#define LOG_INCLUDE

/**
* Class provides methods for logging
*************************************************************************
* History:
* Original version: Thiago Mizutani & Fabricio Lopes de Souza
*   c.f. http://code.google.com/p/m-fit/
* 26/05/2011 - Sang L. Phan
*   + Translate docs into English
*   + Remove unused code that works with QT Nokia framework
*   + Modify for experiments
************************************************************************/
class Log
{
public:
    static int writeLog(const char *fmt, ...);
};

#endif
