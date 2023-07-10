///// Gil ben hamo  /////

#include "headers.h"

void overrideSignal()
{
    workingFlag = 0;
}

int getStationsAmount()
{
    int amount;
    printf("Please enter amount of washing stations [1-5]: ");
    scanf("%d",&amount);
    while(amount<=0 || amount>5)
    {
        printf("Please enter a valid number betwen 1-5\n");
        scanf("%d",&amount);
    }
    return amount;
}

double nextTime(double rateParameter)
{
    return -logf(1.0f - (double)rand() / ((double)RAND_MAX + 1)) / rateParameter;
}

int createSharedMemo(key_t key,int size)
{  
    return shmget(key,size,IPC_CREAT|0666);
}

sem_t* createSemaphore(char* sem_name,int size)
{
    sem_unlink(sem_name);
    return sem_open(sem_name, O_CREAT | O_EXCL ,0660,size);
}

Car* createCar(int id,double time)
{
    Car* c = (Car*)malloc(sizeof(Car));
    c->pid = id;
    c->startTime = 0;
    c->arrivedTime = time;
    c->endTime = 0;
    return c;
}
