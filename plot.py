import matplotlib.pyplot as plt
import math

with open('time_algs.txt', 'r') as f:
    cnt = 0
    n = []
    merge_time = []
    quick_time = []
    bubble_time = []
    for line in f.readlines():
        if cnt == 0:
            n.append(float(line))
        elif cnt == 1:
            merge_time.append(float(line))
        elif cnt == 2:
            quick_time.append(float(line))
        elif cnt == 3:
            res = float(line)
            if res < 1e9:
                bubble_time.append(res)
            else:
                bubble_time.append(float('inf'))
        cnt = (cnt + 1)%4
    plt.scatter(n, merge_time, label='Merge Sort')
    plt.scatter(n, quick_time, label='Quick Sort')
    plt.scatter(n, bubble_time, label='Bubble Sort')

    plt.xlabel('n')
    plt.xscale('log') 
    plt.ylabel('Time')
    plt.yscale('log') 
    plt.title('Sorting Algorithm Performance')
    plt.legend()

    plt.show()