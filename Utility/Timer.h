/************************************************************************************************************************* 
 * COURSE: DATA STRUCTURE and ALGORITHMS
 *
 * TOPIC:   TIME CLASS
 * DESCRIPTION: 
 * CREATED ON : Sat May 19 2018
 *************************************************************************************************************************/

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
/* ============================================== Header includes ====================================================== */
#include "utility.h"
#include <Windows.h>
/* ============================================== Type definition ====================================================== */

class Timer
{
private:
    clock_t start_time;
public:
    /**
     * @brief Constructor
     */
    Timer();

    /**
     * @brief Retrieves the number of miliseconds that have elapsed sime the system was started
     * @return The number of milliseconds that have elapsed sine the system was started
     */
    double getTicks();

    /**
     * @brief Retrieves the difference between the specific system ticks 'tm1' and 'tm2'
     * @param[in] 'tm1' the specific system ticks
     * @param[in] 'tm2' the specific system ticks
     * @return The difference between two system ticks
     */
    double getDiff(double tm1, double tm2);

    /**
     * @brief Retrieves the difference between the current system ticks and the specific system ticks
     * @param[in] tm the specific system ticks
     * @return The differnece between two system ticks
     */
    double getElapsed(double tm);

    /**
     * @brief Suspends execution for millisecond intervals
     * @param[in] msec The millisecond intervals which want to be suspended.
     */
    void msleep(double msec);

    /**
     * @brief Retrieves the difference between the start time and end time 
     * @return The difference between two system ticks
     */
    double elapsed_time();

    /**
     * @brief Gets current times as string type
     * @param[out] buf The pointer to get the current data. It mus already be allocated memory
     * @param[in] bufsize The size of the pointer to get the current data.
     * @return Return string that contains current date if it is successful, else return nullptr.
     */
    char *getCurrentTimeString(char *buf, int bufsize);

    /**
     * @brief Initilize the start time again
     */
    void reset();

    /**
     * @brief Destructor
     */
    ~Timer();
};

