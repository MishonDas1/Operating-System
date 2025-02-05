#include <bits/stdc++.h>

using namespace std;

struct Process {
    int id, arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime, responseTime;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

   
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                swap(processes[j], processes[j + 1]);
            }
        }
    }

    int currentTime = 0;
    int completed = 0;
    bool isCompleted[n] = {false};
    vector<int> executionOrder;

    while (completed < n) {
        int shortestBurst = INT_MAX;
        int selected = -1;

       
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < shortestBurst) {
                    shortestBurst = processes[i].burstTime;
                    selected = i;
                }
            }
        }

        if (selected == -1) {
           
            int earliestArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!isCompleted[i] && processes[i].arrivalTime < earliestArrival) {
                    earliestArrival = processes[i].arrivalTime;
                    selected = i;
                }
            }
            currentTime = processes[selected].arrivalTime;
        }

    
        processes[selected].completionTime = currentTime + processes[selected].burstTime;
        processes[selected].turnAroundTime = processes[selected].completionTime - processes[selected].arrivalTime;
        processes[selected].waitingTime = processes[selected].turnAroundTime - processes[selected].burstTime;
        processes[selected].responseTime = processes[selected].waitingTime; // For non-preemptive, RT = WT

        currentTime = processes[selected].completionTime;
        isCompleted[selected] = true;
        executionOrder.push_back(selected);
        completed++;
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT" << endl;
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << processes[i].arrivalTime << "\t" << processes[i].burstTime
             << "\t" << processes[i].completionTime << "\t" << processes[i].turnAroundTime
             << "\t" << processes[i].waitingTime << "\t" << processes[i].responseTime << endl;
    }

   
    cout << "\nGantt Chart:\n";
    cout << " |";
    for (int idx : executionOrder) {
        cout << " P" << processes[idx].id << " |";
    }
    cout << "\n";

    cout << "0";
    int prevCT = 0;
    for (int idx : executionOrder) {
        cout << setw(5) << processes[idx].completionTime;
    }
    cout << "\n";

    return 0;
}
