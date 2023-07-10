# Car Wash Simulation

## Description
This project is a Car Wash simulation that utilizes shared memory, communication, and synchronization between processes and system signals. It provides an estimation of the simulation time based on a Poisson distribution.

## Environment
- OS: Ubuntu (Linux)

### Requirements
- gcc compiler


## How to compile and run
1. Compile the program:

```shell
gcc -o main main.c -lpthread -lm
```

2. Run the program:

```shell
./main
```

3. Compile and run in a single command:

```shell
gcc -o main main.c -lpthread -lm; ./main
```

## Example
1. When starting the Car Wash simulation, you will be prompted to enter the number of washing stations that will take part in the simulation.

   Example:
   
   ```
   ~Starting Car-Wash simulation~
   Please enter the amount of washing stations [1-5]: 3
   ```

2. The program will output the following information:

   ```
   Estimated simulation time: 12.058350
   car : 12531 , Arrived at time 2.114107
   car : 12531 , in the washing machine! ,2.114107
   car : 12531 , leaving the washing machine! 2.566689
   car : 12532 , Arrived at time 2.340398
   car : 12532 , in the washing machine! ,2.566689
   car : 12567 , Arrived at time 5.915173
   car : 12567 , in the washing machine! ,5.915173
   car : 12568 , Arrived at time 6.249813
   car : 12568 , in the washing machine! ,6.598179
   car : 12569 , Arrived at time 6.598179
   car : 12569 , in the washing machine! ,6.598179
   car : 12568 , leaving the washing machine! 6.625635
   car : 12567 , leaving the washing machine! 6.584452
   car : 12532 , leaving the washing machine! 9.263658
   car : 12569 , leaving the washing machine! 13.001491
   Time taken = 13.001491 seconds, car washed = 5, AVG waiting time = 0.114932
   ```

## Author
- [Gil Ben Hamo](https://github.com/gilbenhamo)

