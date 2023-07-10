///// Gil ben hamo  /////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>

//define semphores name
#define WASH_SEM_NAME "CW"
#define TIME_MUTEX_SEM_NAME "TMU"
#define PRINT_MUTEX_SEM_NAME "PMU"

//shared memo size
#define TIME_SIZE sizeof(double)*2

//poisson distribution AVGS
#define ARRIVE_AVG_RATE 1/1.5
#define WASHING_AVG_RATE 1/3.0
#define SIMULATION_AVG_RATE 1/30.0

//flag for signals interrupt 
static int workingFlag = 1;

//car represnt by procces
typedef struct Car
{
    pid_t pid;
    double arrivedTime;
    double startTime;
    double endTime;

}Car;

//funcs
void overrideSignal();
int getStationsAmount();
int createSharedMemo(key_t key,int size);
double nextTime(double rateParameter);
sem_t* createSemaphore(char* sem_name,int size);
Car* createCar(int id,double time);
