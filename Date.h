

//  Created by Tunde Taiwo on 17/05/2019.
//  Copyright © 2019 Tunde Taiwo. All rights reserved.
//
#pragma once
#pragma warning(disable:4996)
#include <ctime>

class Date
{
public:
    Date(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
    }
    
    //finds todays date.
    static Date today()
    {
        struct tm * ti;
        time_t t = time(0);
        ti = localtime(&t);
        return Date(1900 + ti->tm_year, ti->tm_mon, ti->tm_mday);
    }
    

    //function to calculate the daays between a specific date and today.
    int daysDifference(Date date) {
        
        int tDaysInMonth = 0;
        int matDaysInMonth = 0;
        
        for (int i = 0; i < (month); i++) {
            matDaysInMonth += DaysInMonth[i];
        }
        
        
        for (int i = 0; i < (date.month - 1); i++) {
            tDaysInMonth += DaysInMonth[i];
        }
        
        matDaysInMonth += day;
        tDaysInMonth += date.day;
        
        bool latYear1 = (month > date.month)
        || (month == date.month && day > date.day);
        
        int result1;
        if (latYear1)
        {
            result1 = (matDaysInMonth - tDaysInMonth);
        }
        else
        {
            result1 = (365 - (tDaysInMonth - matDaysInMonth));
        }
        
        bool latYear2 = (month > date.month)
        || (month == date.month && day > date.day);
        
        int result2 = (year - date.year);
        if (!latYear2)                          // ! is "Not"
        {
            result2--;
        }
        return -(result2*365 + result1);
    }
    
    
    
private:
    int year;
    int month;
    int day;
    const int DaysInMonth[12]  = {31,28,31,30,31,30,31,31,30,31,30,31};
};
