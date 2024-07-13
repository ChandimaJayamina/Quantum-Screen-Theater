#include <stdio.h>
#include <time.h>
#include "validations.h"

int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int isValidDate(char *date)
{
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3)
    {
        return 0; // Unable to parse the date
    }

    //time_t now = time(NULL);

    // Convert it to local time representation
    //struct tm *local = localtime(&now);

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        return 0; // Invalid values
    }

    int daysInMonth;
    switch (month)
    {
    case 2:
        daysInMonth = isLeapYear(year) ? 29 : 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        daysInMonth = 30;
        break;
    default:
        daysInMonth = 31;
        break;
    }

    if (day > daysInMonth)
    {
        return 0; // Invalid day for the given month
    }

    return 1; // Valid date
}
