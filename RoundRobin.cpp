#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Process {
    int id, arrival_time, burst_time, remaining_time, completion_time, turnaround_time, waiting_time, response_time;
};

void roundRobinScheduling(Process processes[], int n, int time_quantum) {
    queue<int> q;
    vector<pair<int, int>> gantt_chart; // Stores (process_id, execution_time)
    int current_time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].response_time = -1; // Initialize response time as -1 (not yet started)
    }

    q.push(0);
    bool visited[n] = {false};
    visited[0] = true;

    while (completed < n) {
        int index = q.front();
        q.pop();

        // Calculate response time
        if (processes[index].response_time == -1) {
            processes[index].response_time = current_time - processes[index].arrival_time;
        }

        int execution_time = min(time_quantum, processes[index].remaining_time);
        gantt_chart.push_back({processes[index].id, execution_time}); // Add to Gantt chart
        processes[index].remaining_time -= execution_time;
        current_time += execution_time;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                q.push(i);
                visited[i] = true;
            }
        }

        if (processes[index].remaining_time > 0) {
            q.push(index);
        } else {
            completed++;
            processes[index].completion_time = current_time;
            processes[index].turnaround_time = processes[index].completion_time - processes[index].arrival_time;
            processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;
        }
    }

    // Print Gantt chart
    cout << "\nGantt Chart:\n";
    for (auto &entry : gantt_chart) {
        cout << "P" << entry.first << " [" << entry.second << "] ";
    }
    cout << "\n";
}

void printProcesses(Process processes[], int n) {
    cout << "\nID  AT  BT  CT  TAT  WT  RT\n";
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "   " << processes[i].arrival_time << "   " << processes[i].burst_time << "   "
             << processes[i].completion_time << "   " << processes[i].turnaround_time << "   " << processes[i].waiting_time << "   " 
             << processes[i].response_time << "\n";
    }
}

int main() {
    int n, time_quantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
    }

    cout << "Enter time quantum: ";
    cin >> time_quantum;

    roundRobinScheduling(processes, n, time_quantum);
    printProcesses(processes, n);

    return 0;
}
