def solve1():
    with open('input.txt', 'r') as file:
        lines = file.readlines()
    
    list = []

    for line in lines:
        num = int(line)

        if len(list) is 25:
            is_valid = False

            for i, numOuter in enumerate(list):
                for j, numInner in enumerate(list, start=(i + 1)):
                    if numOuter + numInner == num:
                        is_valid = True
                        break
                if is_valid:
                    break
            
            if not is_valid:
                return num

            list.pop(0)

        list.append(num)

def solve2(INVALID_NUM):
    with open('input.txt', 'r') as file:
        lines = file.readlines()
    
    list = []
    cumulative_list = []
    sum = 0

    for line in lines:
        num = int(line)
        list.append(num)

        sum += num
        cumulative_list.append(sum)

    for i in range(len(cumulative_list)):
        for j in range(i - 1):
            if cumulative_list[i] - cumulative_list[j] == INVALID_NUM:
                min = INVALID_NUM
                max = 0
                for k in range(j + 1, i + 1):
                    if list[k] < min:
                        min = list[k]
                    elif list[k] > max:
                        max = list[k]
                return min + max

print(solve1())
print(solve2(solve1()))