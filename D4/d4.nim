import strutils
import re

proc countScore1(arr: seq[string]): int =
    var score = 0

    for key in arr:
        if match(key, re"(byr|iyr|eyr|hgt|hcl|ecl|pid)$"):
            inc(score)

    return score

proc solve1() =
    let file = open("input.txt")
    defer: file.close()

    var entry: string = ""
    var cnt: int32 = 0

    while not file.endOfFile():
        var line = file.readLine()
        if(line != ""):
            entry.add(" ")
            entry.add(line)
        else:
            if countScore1(entry.replace(re":(\S+)").split(' ')) == 7:
                inc(cnt)

            entry = ""
    
    if countScore1(entry.replace(re":(\S+)").split(' ')) == 7:
        inc(cnt)

    echo cnt

proc countScore2(pairs: seq[string]): int =
    var score = 0

    for pair in pairs:
        if pair == "":
            continue

        var keyValue = pair.split(':')

        let key = keyValue[0]
        let value = keyValue[1]

        case key:
            of "byr": 
                let birthYear = parseInt(value)
                if (birthYear >= 1920) and (birthYear <= 2002):
                    inc(score)
            of "iyr":
                let issueYear = parseInt(value)
                if (issueYear >= 2010) and (issueYear <= 2020):
                    inc(score)
            of "eyr":
                let expirationYear = parseInt(value)
                if (expirationYear >= 2020) and (expirationYear <= 2030):
                    inc(score)
            of "hgt":
                if match(value, re"(\d+)cm$"):
                    let height = parseInt(value.replace("cm"))
                    if (height >= 150) and (height <= 193):
                        inc(score)
                elif match(value, re"(\d+)in$"):
                    let height = parseInt(value.replace("in"))
                    if (height >= 59) and (height <= 76):
                        inc(score)
            of "hcl":
                if match(value, re"#[0-9|a-f]{6}$"):
                    inc(score)
            of "ecl":
                if match(value, re"(amb|blu|brn|gry|grn|hzl|oth)$"):
                    inc(score)
            of "pid":
                if match(value, re"[0-9]{9}$"):
                    inc(score)
    
    return score

proc solve2() =
    let file = open("input.txt")
    defer: file.close()

    var entry: string = ""
    var cnt: int32 = 0

    while not file.endOfFile():
        var line = file.readLine()
        if(line != ""):
            entry.add(line)
            entry.add(" ")
        else:
            if countScore2(entry.split(' ')) == 7:
                inc(cnt)
            
            entry = ""

    if countScore2(entry.split(' ')) == 7:
        inc(cnt)

    echo cnt

# solve1()
solve2()