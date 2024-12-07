"""
function JobScheduling(J, n) {
    sort jobs 'J' in decreasing order of their profits
    
    slots := [false] * n
    schedule := [null] * n
    profit := 0
    
    for i := 0 to (n - 1) {
        for k := 0 to (J[i].deadline - 1) {
            if not slots[k] {
                schedule[k] = J[i]
                profit += J[i].profit
                slots[k] = true
            }
        }
    }
    
    return schedule, profit
}
"""

from dataclasses import dataclass

deadlines = [2, 2, 1, 3, 3]
profits = [20, 15, 10, 5, 1]

@dataclass
class Job:
    deadline: int = 0
    profit: int = 0

jobs = [Job(di, pi) for di, pi in zip(deadlines, profits)]
n = len(jobs)

def JobScheduling(J, n):
    J = list(sorted(J, key=lambda job: job.profit, reverse=True))
    slots = [False] * n
    schedule = [None] * n
    for i in range(n):
        for k in range(0, J[i].deadline):
            if not slots[k]:
                schedule[k] = J[i]
                slots[k] = True
                break
    return schedule

schedule = JobScheduling(jobs, n)   
for job in schedule:
    if job is not None:
        print(job)