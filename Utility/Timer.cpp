/************************************************************************************************************************* 
 * COURSE: DATA STRUCTURE and ALGORITHMS
 *
 * TOPIC:   TIMER CLASS
 * DESCRIPTION: 
 * CREATED ON : Sat May 19 2018
 *************************************************************************************************************************/

/* ============================================== Header includes ====================================================== */
#include "Timer.h"

/* ============================================== Type definition ====================================================== */

Timer::Timer()
{
    start_time = clock();
}

Timer::~Timer()
{
    /* Do nothing */
}

double Timer::elapsed_time()
{
    clock_t end_time = clock();
    return ((double)(end_time - start_time)) / ((double)CLK_TCK);
}

void Timer::reset()
{
    start_time = clock();
}

double Timer::getTicks()
{
    return clock();
}

double Timer::getDiff(double tm1, double tm2)
{
    return tm2 >= tm1 ? tm2 - tm1 : 0xFFFFFFFFUL - (tm1 - tm2);
}

double Timer::getElapsed(double tm)
{
    return getDiff(tm, getTicks());
}

void Timer::msleep(double msec)
{
    Sleep(msec);
}

char *Timer::getCurrentTimeString(char *buf, int bufsize)
{
    time_t tm = time(0);
    struct tm *ptm = localtime(&tm);
    int n = snprintf(buf, bufsize, "%04d-%02d-%02d %02d:%02d:%02d",
                     1900 + ptm->tm_year, 1 + ptm->tm_mon, ptm->tm_mday,
                     ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    if (n == -1)
        buf[bufsize - 1] = '\0';

    return buf;
}
