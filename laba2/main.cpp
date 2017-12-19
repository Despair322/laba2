#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>

#include "threads.h"

using namespace std;


DWORD WINAPI myFunc( LPVOID param );

Semaphore smp( 5 );

FILE *f;

int creating_thread = 0;

int main(int argc, char *argv[])
{
    LPVOID a;
    DWORD id;

    f = fopen( "out.txt", "wt" );

    for ( int i = 0; i < 3; i++ )
    {
        a = new int( i );
        HANDLE h = CreateThread( NULL, 0, myFunc, a, 0, &id );
    }

    creating_thread = 1;

    while( 1 )
        if ( smp.ret_Count_dbg() > 5 )
        {
            cout << "Error"; return 0 ;
        }

    return 0;
}

DWORD WINAPI myFunc( LPVOID param )
{
    while (!creating_thread);


    while(1)
    {
        smp.Enter();
        fprintf( f, "Active\n" );

        int calc = 0;
        for ( int i = 0; i < 200; i++ )
        {
            calc += i + 20*i;
            Sleep(0);
        }

        fprintf( f, "Deactive\n" );
        smp.Leave();

    }
}
