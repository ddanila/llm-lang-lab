package main

import (
	"fmt"
	"strconv"
)

func main() {
	tokens := make([]string, 0, 200)
	for {
		var line string
		_, err := fmt.Scan(&line)
		if err != nil {
			break
		}
		for _, c := range line {
			if c == ' ' || c == '\t' || c == '\r' || c == '\n' {
				continue
			}
			tokens = append(tokens, string(c))
		}
	}

	stack := make([]int64, 0, 10)

	for _, tok := range tokens {
		switch tok {
		case "+":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack[len(stack)-1] = a + b

		case "-":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack[len(stack)-1] = a - b

		case "*":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack[len(stack)-1] = a * b

		default:
			val, err := strconv.ParseInt(tok, 10, 64)
			if err != nil {
				fmt.Println("ERROR")
				return
			}
			stack = append(stack, val)
		}
	}

	if len(stack) != 1 {
		fmt.Println("ERROR")
		return
	}

	fmt.Println(stack[0])
}