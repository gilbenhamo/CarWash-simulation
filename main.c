///// Gil ben hamo  /////

#include "funcs.c"

int main()
{  
    //init variables
    int cars_amount=0;
    double SimulationTime,wash_time,time_save;
    double n_time=0;
    Car* car;

    //override interrupt signals (kill) - if signal occurs 
    signal(SIGTERM, overrideSignal);
    signal(SIGINT, overrideSignal);
    signal(SIGHUP, overrideSignal);
    signal(SIGQUIT, overrideSignal);
    signal(SIGTSTP, overrideSignal);

    //init the seed for rand func
    srand(time(NULL)); 

    //init shared memory
    key_t key = ftok("headers.h",2);
    int time_shmid = createSharedMemo(key,TIME_SIZE);
    double* clockTime = (double*)shmat(time_shmid,0,0);
    double* waitTime = clockTime+1;
    *waitTime = 0;
    *clockTime = 0;

    printf("~Starting Car-Wash simulation~\n");
    int stations_amount = getStationsAmount ();    //get the desired stations size

    //init Semaphores
    sem_t *car_wash_queue = createSemaphore(WASH_SEM_NAME,stations_amount);
    if(car_wash_queue == SEM_FAILED)
    {
        perror("Create queue semaphore error!");
        exit(1);
    }
    sem_t *clock_time_mutex = createSemaphore(TIME_MUTEX_SEM_NAME,1);
    if(clock_time_mutex == SEM_FAILED)
    {
        sem_close(car_wash_queue);
        perror("Create mutex semaphore error!");
        exit(1);
    }
    sem_t *print_mutex = createSemaphore(PRINT_MUTEX_SEM_NAME,1);
    if(print_mutex == SEM_FAILED)
    {
        sem_close(car_wash_queue);
        sem_close(clock_time_mutex);
        perror("Create mutex semaphore error!");
        exit(1);
    }

    //CARWASH RUN CODE
    int i = 0;
    SimulationTime = nextTime(SIMULATION_AVG_RATE);
    printf("Estimated simulation time: %lf\n",SimulationTime);
    for(n_time = nextTime(ARRIVE_AVG_RATE) ; workingFlag && *clockTime <= SimulationTime; )
    {
        sem_wait(clock_time_mutex);
        (*clockTime) = (*clockTime) + n_time; //change  to starttime
        time_save = *clockTime;
        sem_post(clock_time_mutex);

        if(*clockTime <= SimulationTime)
        {
            cars_amount++;
            if(fork()==0)
            {
                car = createCar(getpid(),time_save);

                sem_wait(print_mutex);
                printf("car : %d , Arrived at time %lf\n",car->pid,car->arrivedTime);
                sem_post(print_mutex);

                ////////CAR WASH QUEUE////////////
                sem_wait(car_wash_queue);

                sem_wait(clock_time_mutex);
                car->startTime = *(clockTime);
                *waitTime= *waitTime + (car->startTime-car->arrivedTime);
                sem_post(clock_time_mutex);

                sem_wait(print_mutex);
                printf("car : %d , in the washing machine! ,%lf\n",car->pid,car->startTime);
                sem_post(print_mutex);

                wash_time = nextTime(WASHING_AVG_RATE);
                car->endTime=car->startTime+wash_time;
                sleep(wash_time);

                sem_post(car_wash_queue);
                //////////////////////////////////

                //updated the clocktime only one proccess at time
                sem_wait(clock_time_mutex);
                if(car->endTime > *(clockTime))
                    *(clockTime) = car->endTime;
                sem_post(clock_time_mutex);

                sem_wait(print_mutex);
                printf("car : %d , leaving the washing machine! %f\n",car->pid,car->endTime);
                sem_post(print_mutex);

                if(car)
                    free(car);

                exit(1);
            }
            else{
                n_time = nextTime(ARRIVE_AVG_RATE);
                int temp = n_time;
                sleep(n_time);           //Main proccess sleeps until the next car should arrive
            }
        }
    }

    while(wait(NULL)>0);            //wait for all the childs to finish
    printf("Time taken = %lf seconds, car washed = %d, AVG waiting time = %lf\n",*clockTime,cars_amount,*waitTime/cars_amount);
    
    //free shared memeory
    sem_close(car_wash_queue);
    sem_close(clock_time_mutex);
    sem_close(print_mutex);
    shmctl(time_shmid,IPC_RMID,0);
    shmdt(clockTime);
    shmdt(waitTime);

    return 0;
}
