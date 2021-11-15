heap = []


def insert(x):
    global heap
    heap.append(x)
    pos = len(heap) - 1
    while pos != 0 and heap[pos] > heap[pos // 2]:
        heap[pos], heap[pos // 2] = heap[pos // 2], heap[pos]
        pos //= 2


def extract():
    global heap
    heap[0], heap[-1] = heap[-1], heap[0]
    ret = heap[-1]
    del heap[-1]
    pos = 0
    while 2 * pos < len(heap):
        if 2 * pos + 1 == len(heap) or heap[2 * pos] > heap[2 * pos + 1]:
            if heap[2 * pos] > heap[pos]:
                heap[pos], heap[2 * pos] = heap[2 * pos], heap[pos]
                pos = 2 * pos
            else:
                break
        else:
            if heap[2 * pos + 1] > heap[pos]:
                heap[pos], heap[2 * pos + 1] = heap[2 * pos + 1], heap[pos]
                pos = 2 * pos + 1
            else:
                break
    return ret


def solve():
    for _ in range(int(input())):
        data = input().split()
        if len(data) == 1:
            print(extract())
        else:
            insert(int(data[1]))


solve()
