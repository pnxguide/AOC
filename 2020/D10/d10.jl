function solve1()
    lines = readlines("input.txt")
    numbers = [parse(Int, x) for x in lines]
    sorted = sort(numbers)
    sorted = prepend!(sorted, 0)
    sorted = push!(sorted, sorted[size(sorted)[1]] + 3)

    ones = 0
    threes = 0

    for i = 2:size(sorted)[1]
        diff = sorted[i] - sorted[i - 1]

        if diff == 1
            ones += 1
        elseif diff == 3
            threes += 1
        end
    end

    println(ones * threes)
end

function solve2()
    lines = readlines("input.txt")
    numbers = [parse(Int, x) for x in lines]
    sorted = sort(numbers)
    sorted = prepend!(sorted, 0)
    sorted = push!(sorted, sorted[size(sorted)[1]] + 3)

    ones = 0
    arrangement = 1

    # A000073 Tribonacci numbers: a(n) = a(n − 1) + a(n − 2) + a(n − 3) 
    multiple = [1, 2, 4, 7, 13]

    for i = 2:size(sorted)[1]
        diff = sorted[i] - sorted[i - 1]

        if diff == 1
            ones += 1
        elseif diff == 3 && ones > 0
            arrangement *= multiple[ones]
            ones = 0
        end
    end

    println(arrangement)
end

solve1()
solve2()
