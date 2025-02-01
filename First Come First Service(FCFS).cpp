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

    // Sorting processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                swap(processes[j], processes[j + 1]);
            }
        }
    }

    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime;

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
        processes[i].responseTime = processes[i].waitingTime;

        currentTime = processes[i].completionTime;
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT" << endl;
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t" << processes[i].arrivalTime << "\t" << processes[i].burstTime
             << "\t" << processes[i].completionTime << "\t" << processes[i].turnAroundTime
             << "\t" << processes[i].waitingTime << "\t" << processes[i].responseTime << endl;
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << " |";
    for (int i = 0; i < n; i++) {
        cout << " P" << processes[i].id << " |";
    }
    cout << "\n";

    cout << "0";
    for (int i = 0; i < n; i++) {
        cout << setw(5) << processes[i].completionTime;
    }
    cout << "\n";

    return 0;
}


