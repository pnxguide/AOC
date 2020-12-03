package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	row, col := 0, 0
	x := 3
	cnt := 0

	for {
		line, _, _ := reader.ReadLine()
		if len(line) == 0 {
			break
		}

		/*
			if row%2 != 0 {
				row++
				continue
			}
		*/

		str := string(line)
		rowLength := len(str)

		if str[col+(row*x)%rowLength] == '#' {
			cnt++
		}

		/*
			if str[col+(row/2)%rowLength] == '#' {
				cnt++
			}
		*/

		row++
	}

	fmt.Println(cnt)
}
