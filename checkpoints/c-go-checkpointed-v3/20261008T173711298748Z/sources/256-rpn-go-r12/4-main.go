package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	fmt.Scan(&tokens[0])
	stack := make([]int64, 0)
	for _, tok := range tokens {
		if tok == "+" || tok == "-" || tok == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			left := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			right := stack[len(stack)-1]
			stack = append(stack, left)
			switch tok {
			case "+":
				stack[len(stack)-1] = right + left
			case "-":
				stack[len(stack)-1] = right - left
			case "*":
				stack[len(stack)-1] = right * left
			}
		} else {
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