#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iomanip>
using namespace std;
 
struct process {
    char name[10];
    int timeRL, timeCPU, priority;
    int timeOUT, timeIN, timewait, timesave;
    int index; //the index of pr[i]
};
 
typedef process *ListP;
 
int quantum;
int set;
 
void input(ListP &pr, int &n, int &timeOUT) {
    timeOUT = 0;
    ifstream in("input.txt");
    in >> n;
    in >> set;
    in >> quantum;
    pr = new process[n];
    for (int i = 0; i < n; i++) {
        in >> pr[i].name;
        in >> pr[i].timeRL;
        in >> pr[i].timeCPU;
        in >> pr[i].priority;
        if (timeOUT < pr[i].timeRL)
            timeOUT = pr[i].timeRL + pr[i].timeCPU;
        else
            timeOUT += pr[i].timeCPU;
        pr[i].index = i;
    }
}
 
void output_input(ListP pr, int n) {
    cout << endl << "---------------INPUT---------------" << endl << endl;
    cout << "Name" << setw(10) << "TimeRL" << setw(10) << "TimeCPU" << setw(10)
            << "Priority" << endl;
    for (int i = 0; i < n; i++)
        cout << pr[i].name << setw(10) << pr[i].timeRL << setw(10)
                << pr[i].timeCPU << setw(10) << pr[i].priority << endl;
    cout << "quantum = " << quantum << endl;
    cout << endl << "---------------OUTPUT---------------" << endl << endl;
}
 
void output_FIFO(ListP pr, int n, int timeOUT) {
    cout << "FIFO" << endl << endl << "PROCESS" << endl << endl;
    cout << "Name" << setw(10) << "TimeRL" << setw(10) << "TimeCPU" << setw(10)
            << "Priority" << setw(10) << "TimeIN" << setw(10) << "TimeOUT"
            << setw(10) << "Timewait" << setw(10) << "Timesave" << endl;
    double avg = 0;
    for (int i = 0; i < n; i++){
        cout << pr[i].name << setw(10) << pr[i].timeRL << setw(10)
                << pr[i].timeCPU << setw(10) << pr[i].priority << setw(10)
                << pr[i].timeIN << setw(10) << pr[i].timeOUT << setw(10)
                << pr[i].timewait << setw(10) << pr[i].timesave << endl;
        avg +=  pr[i].timewait;        
    }
    avg = avg/n;
    printf("Average Timewait: %.2f",avg);
}
 
void output_RoundRobin(ListP pr, ListP RL, int n, int m, int timeOUT) {
    cout << "ROUND ROBIN" << endl << endl << "OUTPUT" << endl << endl;
    cout << "Name" << setw(10) << "TimeOUT" << setw(10) << "Timewait"
            << setw(10) << "Timesave" << endl;

    double avg = 0;       
    for (int i = 0; i < n; i++){
        cout << pr[i].name << setw(10) << pr[i].timeOUT << setw(10)
                << pr[i].timewait << setw(10) << pr[i].timesave << endl;
        avg += pr[i].timewait;
    }
    
    cout << endl << endl << "---PROCESS---" << endl << endl;
 
    cout << "Name" << setw(10) << "TimeRL" << setw(10) << "TimeCPU" << setw(10)
            << "Priority" << setw(10) << "TimeIN" << setw(10) << "TimeOUT"
            << endl;

    
    for (int i = 0; i < m; i++){
        cout << RL[i].name << setw(10) << RL[i].timeRL << setw(10)
                << RL[i].timeCPU << setw(10) << RL[i].priority << setw(10)
                << RL[i].timeIN << setw(10) << RL[i].timeOUT << endl;
    }

    avg = avg/n;
    printf("Average Timewait: %.2f",avg);
}
 
void output_Priority_preemptive(ListP pr, int n, int timeOUT) {
    cout << "Priority preemptive" << endl << endl << "PROCESS" << endl << endl;
    cout << "Name" << setw(10) << "TimeRL" << setw(10) << "TimeCPU" << setw(10)
            << "Priority" << setw(10) << "TimeIN" << setw(10) << "TimeOUT"
            << setw(10) << "Timewait" << setw(10) << "Timesave" << endl;
    double avg = 0;
    for (int i = 0; i < n; i++){
        cout << pr[i].name << setw(10) << pr[i].timeRL << setw(10)
                << pr[i].timeCPU << setw(10) << pr[i].priority << setw(10)
                << pr[i].timeIN << setw(10) << pr[i].timeOUT << setw(10)
                << pr[i].timewait << setw(10) << pr[i].timesave << endl;
        avg += pr[i].timewait;
    }
    avg = avg/n;
    printf("Average Timewait: %.2f",avg);
}
 
void output_SJF_preemptive(ListP pr, int n, int timeOUT) {
    cout << "SJF preemptive" << endl << endl << "PROCESS" << endl << endl;
    cout << "Name" << setw(10) << "TimeRL" << setw(10) << "TimeCPU" << setw(10)
            << "Priority" << setw(10) << "TimeIN" << setw(10) << "TimeOUT"
            << setw(10) << "Timewait" << setw(10) << "Timesave" << endl;
    double avg = 0;
    for (int i = 0; i < n; i++){
        cout << pr[i].name << setw(10) << pr[i].timeRL << setw(10)
                << pr[i].timeCPU << setw(10) << pr[i].priority << setw(10)
                << pr[i].timeIN << setw(10) << pr[i].timeOUT << setw(10)
                << pr[i].timewait << setw(10) << pr[i].timesave << endl;
        avg += pr[i].timewait;
    }
    avg = avg/n;
    printf("Average Timewait: %.2f",avg);
}
 
void output_Priority_nopreemptive(ListP pr, ListP RL, int n, int m, int timeOUT) {
    cout << "Priority nopreemptive" << endl << endl << "OUTPUT" << endl << endl;
    cout << "Name" << setw(10) << "TimeOUT" << setw(10) << "Timewait"
            << setw(10) << "Timesave" << endl;
    
    double avg = 0;
    for (int i = 0; i < n; i++){
        cout << pr[i].name << setw(10) << pr[i].timeOUT << setw(10)
                << pr[i].timewait << setw(10) << pr[i].timesave << endl;
        avg +=  pr[i].timewait;
    }

    cout << endl << endl << "---PROCESS---" << endl << endl;
 
    cout << "Name" << setw(10) << "TimeRL" << setw(10) << "TimeCPU" << setw(10)
            << "Priority" << setw(10) << "TimeIN" << setw(10) << "TimeOUT" << endl;
    for (int i = 0; i < m; i++)
        cout << RL[i].name << setw(10) << RL[i].timeRL << setw(10)
                << RL[i].timeCPU << setw(10) << RL[i].priority << setw(10)
                << RL[i].timeIN << setw(10) << RL[i].timeOUT << endl;
   
    avg = avg/n;
    printf("Average Timewait: %.2f",avg);
}
 
void output_SJF_nopreemptive(ListP pr, ListP RL, int n, int m, int timeOUT) {
    cout << "SJF nopreemptive" << endl << endl << "OUTPUT" << endl << endl;
    cout << "Name" << setw(10) << "TimeOUT" << setw(10) << "Timewait"
            << setw(10) << "Timesave" << endl;
        
    double avg = 0;
    for (int i = 0; i < n; i++){
        cout << pr[i].name << setw(10) << pr[i].timeOUT << setw(10)
                << pr[i].timewait << setw(10) << pr[i].timesave << endl;
        avg +=  pr[i].timewait;
    }

    cout << endl << endl << "---PROCESS---" << endl << endl;
 
    cout << "Name" << setw(10) << "TimeRL" << setw(10) << "TimeCPU" << setw(10)
            << "Priority" << setw(10) << "TimeIN" << setw(10) << "TimeOUT" << endl;
    for (int i = 0; i < m; i++)
        cout << RL[i].name << setw(10) << RL[i].timeRL << setw(10)
                << RL[i].timeCPU << setw(10) << RL[i].priority << setw(10)
                << RL[i].timeIN << setw(10) << RL[i].timeOUT << endl;

    avg = avg/n;
    printf("Average Timewait: %.2f",avg);
}
 
void process_FIFO(ListP &pr, int n, int timeOUT) {
    ListP RL = new process[n];
    int m = -1;
    for (int t = 0; t < timeOUT; t++) {
        for (int i = 0; i < n; i++)
            if (t == pr[i].timeRL)
                RL[++m] = pr[i];
    }
    timeOUT = 0;
    for (int i = 0; i <= m; i++) {
        if (timeOUT <= RL[i].timeRL) {
            timeOUT = RL[i].timeRL + RL[i].timeCPU;
            RL[i].timeIN = RL[i].timeRL;
        } else {
            timeOUT += RL[i].timeCPU;
            RL[i].timeIN = RL[i - 1].timeOUT;
        }
        RL[i].timeOUT = timeOUT;
        RL[i].timewait = RL[i].timeOUT - (RL[i].timeRL + RL[i].timeCPU);
        RL[i].timesave = RL[i].timeOUT - RL[i].timeRL;
    }
    pr = RL;
}
 
void process_RoundRobin(ListP &pr, ListP &RL, int n, int &m, int timeOUT, int quantum) //Round Robin
{
    RL = new process[n];
    m = 0; // the number of element in RL
    int count = 0; //count time quantum
    int j = 0;
    int temptime = 0;
    for (int t = 0; t <= timeOUT; t++) {
        if (m > 0 && j < m) {
            count++;
            if (count <= quantum && RL[j].timeCPU - temptime > 0)
                temptime++;
            if (count == quantum && RL[j].timeCPU - temptime > 0) {
                m++;
                RL[m - 1] = RL[j];
                RL[m - 1].timeCPU -= temptime;
            }
            if (RL[j].timeCPU - temptime == 0) {
 
                pr[RL[j].index].timeOUT = t;
                pr[RL[j].index].timewait = pr[RL[j].index].timeOUT
                        - (pr[RL[j].index].timeRL + pr[RL[j].index].timeCPU);
                pr[RL[j].index].timesave = pr[RL[j].index].timeOUT - pr[RL[j].index].timeRL;
            }
            if (count == quantum || RL[j].timeCPU - temptime == 0) {
                RL[j].timeOUT = t;
                RL[j].timeCPU = temptime;
                RL[j].timeIN = t - RL[j].timeCPU;
                j++;
                temptime = 0;
                count = 0;
            }
        }
 
        for (int i = 0; i < n; i++)
            if (t == pr[i].timeRL) {
                  m++;
                RL[m - 1] = pr[i];
            }
    }
}
 
void process_Priority_preemptive(ListP &pr, int n, int timeOUT) {
    ListP RL = new process[n];
    ListP pr1 = pr; 
    int j = 0, m = 0;
    int temptime = 0;
    for (int t = 0; t <= timeOUT; t++) {
        if (m > 0 && j < m) {
            if (temptime < RL[j].timeCPU)
                temptime++;
            if (temptime == RL[j].timeCPU) {
                RL[j].timeIN = t - RL[j].timeCPU;
                RL[j].timeOUT = RL[j].timeIN + RL[j].timeCPU;
                RL[j].timewait = RL[j].timeOUT - (RL[j].timeRL + RL[j].timeCPU);
                RL[j].timesave = RL[j].timeOUT - RL[j].timeRL;
                temptime = 0;
                j++;
            }
        }
        for (int i = 0; i < n; i++)
            if (t == pr1[i].timeRL) {
                int k = m;
                while (k > j + 1 && pr1[i].priority < RL[k - 1].priority) {
                    RL[k] = RL[k - 1];
                    k--;
                }
                RL[k] = pr1[i];
                m++;
            }
    }
    pr = RL;
}
 
void process_Priority_nopreemptive(ListP &pr, ListP &RL, int n, int &m, int timeOUT) {
    RL = new process[n];
    ListP pr1 = pr;
    int j = 0;
    m = 0;
    int temptime = 0;
    for (int t = 0; t <= timeOUT; t++) {
        if (m > 0 && j < m) {
            if (temptime < RL[j].timeCPU)
                temptime++;
            if (temptime == RL[j].timeCPU) {
                RL[j].timeIN = t - RL[j].timeCPU;
                RL[j].timeOUT = RL[j].timeIN + RL[j].timeCPU;
                RL[j].timewait = RL[j].timeOUT - (RL[j].timeRL + RL[j].timeCPU);
                RL[j].timesave = RL[j].timeOUT - RL[j].timeRL;
 
                pr1[RL[j].index].timeOUT = t;
                pr1[RL[j].index].timewait = pr1[RL[j].index].timeOUT
                        - (pr1[RL[j].index].timeRL + pr1[RL[j].index].timeCPU);
                pr1[RL[j].index].timesave = pr1[RL[j].index].timeOUT - pr1[RL[j].index].timeRL;
                temptime = 0;
                j++;
            }
        }
        for (int i = 0; i < n; i++)
            if (t == pr1[i].timeRL) {
                m++;
                int k = m - 1;
                if (temptime > 0 && pr1[i].priority < RL[j].priority) {
                    m++;
                    k = m - 1;
                    for (k = m - 1; k > j + 1; k--)
                        RL[k] = RL[k - 2];
                    RL[j + 1] = pr1[i];
 
                    RL[j + 2] = RL[j];
                    RL[j + 2].timeCPU -= temptime;
 
                    RL[j].timeIN = t - temptime;
                    RL[j].timeOUT = t;
                    RL[j].timeCPU = temptime;
                    temptime = 0;
                    j++;
                } else {
                    while (k > j && pr1[i].priority < RL[k - 1].priority) {
                        RL[k] = RL[k - 1];
                        k--;
                    }
                    RL[k] = pr1[i];
                }
            }
    }
}
 
void process_SJF_preemptive(ListP &pr, int n, int timeOUT) {
    ListP RL = new process[n];
    ListP pr1 = pr; //list temp of pr
    int j = 0, m = 0;
    int temptime = 0;
    for (int t = 0; t <= timeOUT; t++) {
        if (m > 0 && j < m) {
            if (temptime < RL[j].timeCPU)
                temptime++;
            if (temptime == RL[j].timeCPU) {
                RL[j].timeIN = t - RL[j].timeCPU;
                RL[j].timeOUT = RL[j].timeIN + RL[j].timeCPU;
                RL[j].timewait = RL[j].timeOUT - (RL[j].timeRL + RL[j].timeCPU);
                RL[j].timesave = RL[j].timeOUT - RL[j].timeRL;
                temptime = 0;
                j++;
            }
        }
        for (int i = 0; i < n; i++)
            if (t == pr1[i].timeRL) {
                int k = m;
                while (k > j + 1 && pr1[i].timeCPU < RL[k - 1].timeCPU) {
                    RL[k] = RL[k - 1];
                    k--;
                }
                RL[k] = pr1[i];
                m++;
            }
    }
    pr = RL;
}
 
void process_SJF_nopreemptive(ListP &pr, ListP &RL, int n, int &m, int timeOUT) {
    RL = new process[n];
    ListP pr1 = pr; //list temp of pr
    int j = 0;
    m = 0;
    int temptime = 0;
    for (int t = 0; t <= timeOUT; t++) {
        if (m > 0 && j < m) {
            if (temptime < RL[j].timeCPU)
                temptime++;
            if (temptime == RL[j].timeCPU) {
                RL[j].timeIN = t - RL[j].timeCPU;
                RL[j].timeOUT = RL[j].timeIN + RL[j].timeCPU;
                RL[j].timewait = RL[j].timeOUT - (RL[j].timeRL + RL[j].timeCPU);
                RL[j].timesave = RL[j].timeOUT - RL[j].timeRL;
 
                pr1[RL[j].index].timeOUT = t;
                pr1[RL[j].index].timewait = pr1[RL[j].index].timeOUT
                        - (pr1[RL[j].index].timeRL + pr1[RL[j].index].timeCPU);
                pr1[RL[j].index].timesave = pr1[RL[j].index].timeOUT - pr1[RL[j].index].timeRL;
 
                temptime = 0;
                j++;
            }
        }
        for (int i = 0; i < n; i++)
            if (t == pr1[i].timeRL) {
                m++;
                int k = m - 1;
                if (temptime > 0 && pr1[i].timeCPU < RL[j].timeCPU - temptime) {
                    m++;
                    k = m - 1;
                    for (k = m - 1; k > j + 1; k--)
                        RL[k] = RL[k - 2];
                    RL[j + 1] = pr1[i];
 
                    RL[j + 2] = RL[j];
                    RL[j + 2].timeCPU -= temptime;
 
                    RL[j].timeIN = t - temptime;
                    RL[j].timeOUT = t;
                    RL[j].timeCPU = temptime;
                    temptime = 0;
                    j++;
                } else {
                    while (k > j + 1 && pr1[i].timeCPU < RL[k - 1].timeCPU) {
                        RL[k] = RL[k - 1];
                        k--;
                        if (k == j + 1
                                && pr1[i].timeCPU < RL[k - 1].timeCPU - temptime) {
                            RL[k] = RL[k - 1];
                            k--;
                        }
                    }
                    RL[k] = pr1[i];
                }
            }
    }
}
 
void PROCESS(ListP &pr, ListP &RL, int n, int &m, int timeOUT, int select) {
    switch (select) {
    case 1:
        process_FIFO(pr, n, timeOUT);
        break;
    case 2:
        process_RoundRobin(pr, RL, n, m, timeOUT, quantum);
        break;
    case 3:
        process_Priority_preemptive(pr, n, timeOUT);
        break;
    case 4:
        process_Priority_nopreemptive(pr, RL, n, m, timeOUT);
        break;
    case 5:
        process_SJF_preemptive(pr, n, timeOUT);
        break;
    case 6:
        process_SJF_nopreemptive(pr, RL, n, m, timeOUT);
        break;
    }
}
 
void OUTPUT(ListP pr, ListP RL, int n, int m, int timeOUT, int select) {
    switch (select) {
    case 1:
        output_FIFO(pr, n, timeOUT);
        break;
    case 2:
        output_RoundRobin(pr, RL, n, m, timeOUT);
        break;
    case 3:
        output_Priority_preemptive(pr, n, timeOUT);
        break;
    case 4:
        output_Priority_nopreemptive(pr, RL, n, m, timeOUT);
        break;
    case 5:
        output_SJF_preemptive(pr, n, timeOUT);
        break;
    case 6:
        output_SJF_nopreemptive(pr, RL, n, m, timeOUT);
        break;
    }
    cout << endl << "-----------------END-----------------" << endl << endl;
}
 
int main() {
    ListP pr, RL;
    int n, m, timeOUT;
    input(pr, n, timeOUT);
    output_input(pr, n);
    PROCESS(pr, RL, n, m, timeOUT, set);
    OUTPUT(pr, RL, n, m, timeOUT, set);
    return 0;
}