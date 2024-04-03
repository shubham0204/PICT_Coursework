class Job:
    def __init__(self, id: int, profit: int, deadline: int):
        self.id = id
        self.deadline = deadline
        self.profit = profit

    def __str__(self) -> str:
        return f"Job: id={self.id}, deadline={self.deadline}, profit={self.profit}"


def greedy_scheduling(jobs: list[Job]):
    # Sort the jobs in decreasing order of their profits
    for i in range(len(jobs)):
        j = i
        while jobs[j].profit > jobs[j - 1].profit and j > 0:
            temp = jobs[j - 1]
            jobs[j - 1] = jobs[j]
            jobs[j] = temp
            j -= 1

    # Calculate max permissible time to complete the jobs
    # Reference: https://youtu.be/zPtI8q9gvX8?si=8mHVmh4-q4T_d234
    max_deadline = max([job.deadline for job in jobs])
    slot_status = [True for _ in range(max_deadline)]
    max_profit_seq = []
    for job in jobs:
        for i in range(job.deadline - 1, -1, -1):
            if slot_status[i]:
                slot_status[i] = False
                max_profit_seq.append(job)
                break
    for job in max_profit_seq:
        print(job)

    max_profit = sum([job.profit for job in max_profit_seq])
    return max_profit


jobs = [Job(1, 20, 2), Job(2, 15, 2), Job(3, 10, 1), Job(4, 5, 3), Job(5, 1, 3)]
max_profit = greedy_scheduling(jobs)
print(f"Max profit is {max_profit}")
