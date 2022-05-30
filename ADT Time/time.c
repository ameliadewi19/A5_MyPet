#include <stdio.h>
#include <stdlib.h>
#include "time.h"

void CreateTIME (TIME *J, int HH, int MM)
{
    (*J).Hour = HH;
    (*J).Minute = MM;
}

int GetHour(TIME J)
{
    return J.Hour;
}

int GetMinute(TIME J)
{
    return J.Minute;
}

void SetHour(TIME *J, int newHour)
{
    (*J).Hour = newHour;
}

void SetMinute(TIME *J, int newMinute)
{
    (*J).Minute = newMinute;
}

void PrintTIME (TIME J)
{
    printf("%d:%d\n", J.Hour, J.Minute);
}

boolean IsJamValid (TIME J)
{
    return ((J.Hour >= 0) && (J.Hour <= 23)) && ((J.Minute >= 0) && (J.Minute <= 59));
}

long int TimeToMenit (TIME J)
{
    return (60 * J.Hour) + J.Minute;
}

TIME MenitToTime (long int N)
{
    TIME J;
	
    J.Hour = N/60;
    N %= 60;
	
    J.Minute = N;
	
	return J;
}

void PrintJam(TIME J){
	printf("%02d:%02d", J.Hour, J.Minute);
}

TIME NextNMenit (TIME J, int N)
{
    int menit = TimeToMenit(J) + N;
    return MenitToTime(menit);
}
