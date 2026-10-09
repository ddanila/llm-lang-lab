package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	
	// Read all input from stdin
	input := make([]byte, 0, 1024)
	buf := make([]byte, 1024)
	for {
		n, err := fmt.Fscanf(&input, "%c", nil)
		if n == 0 && err != nil {
			break
		}
	}

	tokens = strings.Fields(string(input))
	
	stack := make([]int64, 0, len(tokens))

	for _, token := range tokens {
		if token == "+" || token == "-" || token == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			a := stack[len(stack)-2]
			stack = stack[:len(stack)-2]

			switch token {
			case "+":
				stack = append(stack, a+b)
			case "-":
				stack = append(stack, a-b)
			case "*":
				stack = append(stack, a*b)
			}
		} else {
			val, err := strconv.ParseInt(token, 10, 64)
			if err != nil {
				fmt.Println("ERROR")
				return
			}
			stack = append(stack, val)
		}
	}

	if len(stack) != 1 {
		fmt.Println("ERROR")
	} else {
		fmt.Println(stack[0])
	}
}