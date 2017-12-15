#include<stdio.h>
#include<time.h>
#include<iostream>
int main () 
{
    char buffer[256];
    struct tm *sTm;

    time_t present = time (0);
    sTm = gmtime (&present);

    strftime (buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", sTm);
    printf ("%s %s\n", buffer, "Event occurred now");

    return 0;
}
