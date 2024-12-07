"""
function ActivitySelection(A, n) {
    sort activities 'A' in increasing order of their finish times
    S := { A[0] }
    f := A[0].finish_time
    for i := 0 to (n - 1) {
        if A[i].start_time >= f {
            S += { A[i] }
            f = A[i].finish_time
        }
    }
    print S
}
"""

from dataclasses import dataclass

start_times = [1, 2, 3, 4, 7, 8, 9, 9, 11, 12]
finish_times = [3, 5, 4, 7, 10, 9, 11, 13, 12, 14]

@dataclass
class Activity:
    start_time: int = 0
    finish_time: int = 0
    
activities = [Activity(si, fi) for si, fi in zip(start_times, finish_times)]
n = len(activities)

def ActivitySelection(A, n):
    A = list(sorted(A, key=lambda a: a.finish_time))
    selected_activities = [A[0]]
    finish_time = A[0].finish_time
    for i in range(1, n):
        if A[i].start_time >= finish_time:
            selected_activities.append(A[i])
            finish_time = A[i].finish_time
    return selected_activities

selected_activities = ActivitySelection(activities, n)
for activity in selected_activities:
    print(activity)