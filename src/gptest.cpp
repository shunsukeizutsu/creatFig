#include <stdio.h>
#include <signal.h>
#include <stdexcept>
#include <stdlib.h>
#include <iostream>
#include "creatfig.hpp"
#include <cstring>

using namespace std;

static int gShutOff = 0;
static void setSigInt(void);
static void Terminate(void);

int main(void)
{
    PlotData PD2;//defalut
    //PlotData PD(100.0,0.0,100.0,0.0);//範囲指定
    

    try
    {
        setSigInt();
        double y=0.0;
        double y2=0.0;
        double y3=0.0;
        double x=2.0;
        double z=0.0;
        while (!gShutOff)
        {
            y=x;
            y2=3*x;
            y3=4*x;
            z=x+y;
            //PD.saveData2D(x,y);
            PD2.saveData2D(x,y);
            x++;
            if(y==100)
            {
                break;
            }
            
        }
        //PD.PrintFig2D();
        PD2.PrintFig2D();
        
        while (!gShutOff)
        {
            usleep(1000);
        }
    }
    catch (std::runtime_error const &error)
    {
        std::cout << error.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "An unknown fatal error has occured. Aborting." << std::endl;
    }
    Terminate();
    return EXIT_SUCCESS;
}

static void ctrlC(int aStatus)
{
    signal(SIGINT, NULL);
    gShutOff = 1;
}
static void setSigInt()
{
    struct sigaction sig;
    memset(&sig, 0, sizeof(sig));
    sig.sa_handler = ctrlC;
    sigaction(SIGINT, &sig, NULL);
}
static void Terminate(void)
{
    printf("\nend\n");
}