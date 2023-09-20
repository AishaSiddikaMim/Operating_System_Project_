#include<stdio.h>
#include<stdlib.h>

//First come first serve
float FCFS()
{
    int Arrival_time[10], Burst_time[10], Waiting_time[10], Turnaround_time[10];
    int n, Compilation_time, burst = 0;
    float Averagewaiting_time = 0, Averageturnaround_time = 0, Total_time = 0;

    printf("You have chosen First Come First Serve Algorithm\n");
    printf("\nEnter the number of process\n");
    scanf("%d", &n);

    printf("Enter Arrival & Burst time\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d%d", &Arrival_time[i], &Burst_time[i]);
    }

    for(int i = 0; i < n; i++)
    {
        if(i == 0)

            Waiting_time[i] = Arrival_time[i];


        else

            Waiting_time[i] = burst - Arrival_time[i];
            burst = burst + Burst_time[i];
            Total_time = Total_time + Waiting_time[i];

    }

    Averagewaiting_time = Total_time / n;

    Compilation_time = 0;
    Total_time = 0;

    for(int i = 0; i < n; i++)
    {
        Compilation_time = Compilation_time + Burst_time[i];
        Turnaround_time[i] = Compilation_time - Arrival_time[i];
        Total_time = Total_time + Turnaround_time[i];
    }

    Averageturnaround_time = Total_time / n;

    printf("Process, Waiting Time, TurnAround Time\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\n", i + 1, Waiting_time[i], Turnaround_time[i]);
    }

    printf("Average Waiting Time is : %f\n", Averagewaiting_time);
    return Averagewaiting_time;
}


//Shortest Job First
float SJF()

{
   struct process
    {
        int id, Waiting_time, Arrival_time, Burst_time, Turnaround_time;
    };
    struct process a[10];

    void swap(int *b, int *c)
    {
        int temp;
        temp = *c;
        *c = *b;
        *b = temp;
    }

    int n, check_AT = 0, Compilation_time = 0;
    float Total_waitingtime = 0, Total_turnaroundtime = 0, Averagewaiting_time = 0, Averageturnaround_time = 0;

    printf("You have chosen Shortest Job First Algorithm\n");
    printf("\nEnter the number of process\n");
    scanf("%d", &n);

    printf("Enter Arrival & Burst time\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d%d", &a[i].Arrival_time, &a[i].Burst_time);
        a[i].id = i + 1;


        //checking if the arrival time of the processes are same or not
        if(i == 0)

            check_AT = a[i].Arrival_time;

        else if (check_AT != a[i].Arrival_time)

            check_AT = 1;
    }

    //if arrival time of the processes are different, then we're sorting the processes based on arrival time
    if(check_AT != 0)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n - i -1; j++)
            {
                if(a[j].Arrival_time > a[j + 1].Arrival_time)
                {
                    swap(&a[j].id, &a[j + 1].id);
                     swap(&a[j].Arrival_time, &a[j + 1].Arrival_time);
                      swap(&a[j].Burst_time, &a[j + 1].Burst_time);
                }
            }
        }
    }


    //if the arrival time of the processes are different swap, (small to large)
    if(check_AT != 0)
    {
        a[0].Waiting_time = a[0].Arrival_time;
        a[0].Turnaround_time = a[0].Burst_time - a[0].Arrival_time;
        Compilation_time = a[0].Turnaround_time;
        Total_waitingtime = Total_waitingtime + a[0].Waiting_time;
        Total_turnaroundtime = Total_turnaroundtime + a[0].Turnaround_time;

        for(int i = 1; i < n; i++)
        {
            int minimum = a[i].Burst_time;

            for(int j = i + 1 ; j < n; j++)
            {
                if(minimum > a[j].Burst_time && a[j].Arrival_time <= Compilation_time)
                {
                    minimum = a[j]. Burst_time;
                    swap(&a[i].id, &a[j].id);
                     swap(&a[i].Arrival_time, &a[j].Arrival_time);
                      swap(&a[i].Burst_time, &a[j].Burst_time);
                }
            }

            a[i].Waiting_time = Compilation_time - a[i].Arrival_time;
            Total_waitingtime = Total_waitingtime + a[i].Waiting_time;
            Compilation_time = Compilation_time + a[i].Burst_time;
            a[i].Turnaround_time = Compilation_time - a[i].Arrival_time;
            Total_turnaroundtime = Total_turnaroundtime + a[i].Turnaround_time;
        }

    }


    //if the arrival time of the processes are same
    else
    {
        for(int i = 0; i < n; i++)
        {
            int minimum = a[i].Burst_time;
            for(int j = i + 1; j < n; j++)
            {
                if(minimum > a[j].Burst_time && a[j].Arrival_time <= Compilation_time)
                {
                    minimum =a[j].Burst_time;
                    swap(&a[i].id, &a[j].id);
                     swap(&a[i].Arrival_time, &a[j].Arrival_time);
                      swap(&a[i].Burst_time, &a[j].Burst_time);

                }

            }
            a[i].Waiting_time = Compilation_time - a[i].Arrival_time;
            Compilation_time = Compilation_time + a[i].Burst_time;

            a[i].Turnaround_time = Compilation_time - a[i].Arrival_time;
            Total_waitingtime= Total_waitingtime + a[i].Waiting_time;
            Total_turnaroundtime = Total_turnaroundtime + a[i].Turnaround_time;
        }
    }

    Averagewaiting_time = Total_waitingtime / n;
    Averageturnaround_time = Total_turnaroundtime/n;

    printf("The process are\n");
    printf("Process-ID Waiting Time Turnaround Time\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\n",a[i].id, a[i].Waiting_time, a[i].Turnaround_time);
    }

    printf("Average Waiting Time is: %f\n", Averagewaiting_time);
    return Averagewaiting_time;

}


//Shortest Remaining Time First
float SRTF()

{
    struct process
{
    int Waiting_time, Arrival_time, Burst_time, Turnaround_time;
};

struct process a[10];

    int n, temp[10];
    int count = 0, t = 0, short_process;
    float Total_waitingtime = 0, Total_turnaroundtime = 0, Averagewaiting_time = 0, Averageturnaround_time = 0;

    printf("You have chosen Shortest Remaining Time First Algorithm\n");
    printf("\nEnter the number of the process\n");
    scanf("%d",&n);

    printf("Enter Arrival & Burst time\n");

   for(int i = 0; i < n; i++)
    {
        scanf("%d%d", &a[i].Arrival_time, &a[i].Burst_time);
        temp[i] = a[i].Burst_time;
    }

    //initializing burst time of a process with maximum
    a[9].Burst_time = 10000;

    for(t = 0; count !=n ; t++)
    {
        short_process = 9;

        for(int i = 0; i < n; i++)
        {
            if(a[i].Burst_time < a[short_process].Burst_time && (a[i].Arrival_time <= t && a[i].Burst_time > 0))
            {
                short_process = i;
            }

        }

        a[short_process].Burst_time = a[short_process].Burst_time - 1;

        if(a[short_process].Burst_time == 0)
        {
            count++;
            a[short_process].Waiting_time = t + 1 - a[short_process].Arrival_time - temp[short_process];
            a[short_process].Turnaround_time = t + 1 - a[short_process].Arrival_time;

           Total_waitingtime = Total_waitingtime + a[short_process].Waiting_time;
            Total_turnaroundtime = Total_turnaroundtime + a[short_process].Turnaround_time;
        }
    }

    Averagewaiting_time = Total_waitingtime/n;
   Averageturnaround_time = Total_turnaroundtime/n;

    printf("Process-Id Waiting Time Turnaround Time\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\n", i + 1, a[i].Waiting_time, a[i].Turnaround_time);
    }

    printf("Average Waiting Time is: %f\n", Averagewaiting_time);
    return Averagewaiting_time;
}


//Priority scheduling - Non preemptive
float PS()

{
    struct process
{
    int id, Waiting_time, Arrival_time, Burst_time, Turnaround_time, Priority;
};

struct process a[10];

void swap(int *b, int *c)
{
    int temp;
    temp = *c;
    *c = *b;
    *b = temp;
}

    int n, check_AT = 0, Compilation_time = 0;
    float Total_waitingtime = 0, Total_turnaroundtime = 0, Averagewaiting_time = 0, Averageturnaround_time = 0;

    printf("You have chosen Priority scheduling-Non preemptive Algorithm\n");
    printf("\nEnter the number of process\n");
    scanf("%d", &n);

    printf("Enter Arrival, Burst time & Priority\n");

    for(int i = 0; i < n; i++)
    {

        scanf("%d%d%d", &a[i].Arrival_time, &a[i].Burst_time, &a[i].Priority);
        a[i].id = i + 1;


         //checking if the arrival time of the processes are same or not
        if(i == 0)
        check_AT = a[i].Arrival_time;

        if(check_AT != a[i].Arrival_time)
        check_AT = 1;
   }


    //if arrival time of the processes are different, then we're sorting the processes based on arrival time
    if(check_AT != 0)
    {
        for(int i = 0; i < n; i++)
        {
           for(int j = 0; j < n - i -1; j++)
            {
                if(a[j].Arrival_time > a[j + 1].Arrival_time)
                {
                    swap(&a[j].id, &a[j + 1].id);
                     swap(&a[j].Arrival_time, &a[j + 1].Arrival_time);
                      swap(&a[j].Burst_time, &a[j + 1].Burst_time);
                       swap(&a[j].Priority, &a[j+1].Priority);
                }
            }
        }
    }


    //if the arrival time of the processes are different swap, (small to large)
    if(check_AT != 0)
    {
        a[0].Waiting_time = a[0].Arrival_time;
        a[0].Turnaround_time = a[0].Burst_time - a[0].Arrival_time;

        Compilation_time = a[0].Turnaround_time;
        Total_waitingtime = Total_waitingtime + a[0].Waiting_time;
        Total_turnaroundtime = Total_turnaroundtime + a[0].Turnaround_time;

         for(int i = 1; i < n; i++)
        {
            int minimum = a[i].Priority;

            for(int j = i + 1 ; j < n; j++)
            {
                if(minimum > a[j].Priority && a[j].Arrival_time <= Compilation_time)
                {
                      minimum = a[j].Priority;
                      swap(&a[i].id, &a[j].id);
                       swap(&a[i].Arrival_time, &a[j].Arrival_time);
                        swap(&a[i].Burst_time, &a[j].Burst_time);
                         swap(&a[i].Priority, &a[j].Priority);
                     }

            }

            a[i].Waiting_time = Compilation_time - a[i].Arrival_time;
            Total_waitingtime = Total_waitingtime + a[i].Waiting_time;

            Compilation_time = Compilation_time + a[i].Burst_time;

            a[i].Turnaround_time = Compilation_time - a[i].Arrival_time;
            Total_turnaroundtime = Total_turnaroundtime + a[i].Turnaround_time;
        }
    }


    //if the arrival time of the processes are same
    else
    {
          for(int i = 0; i < n; i++)
        {
            int minimum = a[i].Priority;
            for(int j = i + 1; j < n; j++)
            {
                if(minimum > a[j].Priority && a[j].Arrival_time <= Compilation_time)
                {

                 minimum = a[j].Priority;
                    swap(&a[i].id, &a[j].id);
                     swap(&a[i].Arrival_time, &a[j].Arrival_time);
                     swap(&a[i].Burst_time, &a[j].Burst_time);
                      swap(&a[i].Priority, &a[j].Priority);
                }
            }

            a[i].Waiting_time = Compilation_time - a[i].Arrival_time;

            Compilation_time = Compilation_time + a[i].Burst_time;

            a[i].Turnaround_time = Compilation_time - a[i].Arrival_time;
            Total_waitingtime = Total_waitingtime + a[i].Waiting_time;
            Total_turnaroundtime = Total_turnaroundtime + a[i].Turnaround_time;

        }

    }

     Averagewaiting_time = Total_waitingtime / n;
     Averageturnaround_time = Total_turnaroundtime / n;

    printf("The process are\n");
    printf("Process-ID Waiting Time Turnaround Time\n");

    for(int i = 0; i < n; i++)
    {

    printf("%d\t\t%d\t\t%d\n",a[i].id, a[i].Waiting_time, a[i].Turnaround_time);

    }

    printf("Average Waiting Time is: %f\n", Averagewaiting_time);
    return Averagewaiting_time;
}


//Round Robin Scheduling
float RRS ()

{
   struct process
{
    int id, Waiting_time, Arrival_time, Burst_time, Turnaround_time;
};

struct process a[10];

//ready queue
int queue[100];
int front = -1;
int rear = -1;

//inserting elements in queue
void insert(int n)
{
    if(front == -1)

    front = 0;
    rear = rear + 1;
    queue[rear] = n;

}


//deleting elements from queue
int delete()
{
    int n;
    n = queue[front];
    front = front+1;
    return n;
}

    int n, Time_quantam, m, TIME = 0;
    int temp[10], exist[10] = {0};
    float Total_waitingtime = 0, Total_turnaroundtime = 0, Averagewaiting_time = 0, Averageturnaround_time = 0;

    printf("You have chosen Round Robin Scheduling Algorithm\n");
    printf("\nEnter the number of process\n");
    scanf("%d", &n);

    printf("Enter Arrival & Burst time\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d%d", &a[i].Arrival_time, &a[i].Burst_time);
        a[i].id = i;
        temp[i] = a[i].Burst_time;
    }

    printf("Enter the Time Quantum\n");
    scanf("%d", &Time_quantam);


    insert(0);
    exist[0] = 1;


    //until queue is empty
    while(front <= rear)
    {
        m = delete();

        if(a[m].Burst_time >= Time_quantam)
        {
            a[m].Burst_time = a[m].Burst_time - Time_quantam;
            TIME = TIME + Time_quantam;
        }
        else
        {
            TIME = TIME + a[m].Burst_time;
            a[m].Burst_time = 0;
        }


        for(int i = 0; i < n; i++)
        {
            if(exist[i] == 0 && a[i].Arrival_time <= TIME)
            {
                insert(i);
                exist[i] = 1;
            }
        }

        if(a[m].Burst_time == 0)
        {
            a[m].Turnaround_time = TIME - a[m].Arrival_time;
            a[m].Waiting_time = a[m].Turnaround_time - temp[m];
            Total_waitingtime = Total_waitingtime + a[m].Waiting_time;
            Total_turnaroundtime = Total_turnaroundtime + a[m].Turnaround_time;

        }

        else
        {
            insert(m);
        }
    }

    Averagewaiting_time = Total_waitingtime / n;
    Averageturnaround_time = Total_turnaroundtime / n;

    printf("Process-ID Waiting Time Turnaround Time\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\n", a[i].id, a[i].Waiting_time, a[i].Turnaround_time);
    }

    printf("Average Waiting Time is: %f\n", Averagewaiting_time);
    //printf("Average Turnaround Time is: %f", Averageturnaround_time);
    return Averagewaiting_time;
}

int main ()
{

    printf("Choose the Algorithm\n");

    printf("\nEnter 1 to select First Come First Serve Algorithm");
    printf("\nEnter 2 to select Shortest Job First Algorithm");
    printf("\nEnter 3 to select Shortest Remaining Time First Algorithm");
    printf("\nEnter 4 to select Priority Scheduling-Non preemptive Algorithm");
    printf("\nEnter 5 to select Round Robin Scheduling Algorithm");
    printf("\nEnter 6 to compare the Scheduling Algorithms\n");


    int input;
    printf("\nEnter the number to choose: \n");
    scanf("%d", &input);

    switch (input)
    {
        case 1:
           FCFS();
        break;

        case 2:
            SJF();
            break;
        case 3:
            SRTF();
            break;
        case 4:
            PS();
            break;
        case 5:
            RRS();
            break;

        case 6:
            {

                float a = FCFS();
                float b = SJF();
                float c = SRTF();
                float d = PS();
                float e = RRS();

                printf("Average Waiting Time of All algorithms are :\n");
                printf("%f\t%f\t%f\t%f\t%f\n", a, b, c, d, e);


      if(a < b && a < c && a < d && a < e)
      {
         printf("FCFS Algorithm is better");
      }

      else if(b < a && b < c&& b < d && b < e)
      {
         printf("SJF Algorithm is better");
      }

      else if(c < a && c < b && c < d && c < e)
       {
         printf("SRTF Algorithm is better");
       }

      else if(d < a && d < b && e < c && d < e)
       {
          printf("Priority Scheduling Algorithm is better");
       }

      else if(e < a && e < b && e < c && e < d)
        {
          printf("Round Rabin Algorithm is better");
        }


        else if(a == b == c == d == e)
            {
                printf("All of the Algorithms are better");
            }


        else if(a == b && a < c && a< d && a < e)
        {
            printf("FCFS & SJF are better");
        }

        else if(a == c && c < a && c < b && c < d && c < e)
        {
           printf("FCFS & SRTF are better");
        }

        else if(a == d && d < a && d < b && d < c && d < e)
        {
           printf("FCFS & Priority Scheduling are better");
        }

        else if(a == e && e < b && e < c && e < d)
        {
           printf("FCFS & Round Robin are better");
        }


        else if(b == c && c < a && c < d && c < e)
        {
           printf("SJF & SRTF are better");
        }

        else if(b == d && d < a && d < c && d < e)
        {
            printf("SJF & Priority Scheduling are better");
        }

        else if(b == e && e < a && e < b && e < c)
        {
            printf("SJF & Round Robin are better");
        }

        else if(c == d && d < a && d < b && d < e)
        {
           printf("SRTF & Priority Scheduling are better");
        }

        else if(c == e && e < a && e < b && e < d)
        {
           printf("SRTF & Round Robin are better");
        }

        else if(d == e && e < a && e < b && e < c)
        {
            printf("Priority Scheduling & Round Robin are better");
        }

        else if(a == b == c && a < d && a < e)
        {
            printf("FCFS, SJF and SRTF  are better");
        }

        else if(c == d == e && c < a && c < b)
        {
            printf("SRTF, Priority Scheduling and Round Robin are better");
        }

            }
            break;
    }

}










