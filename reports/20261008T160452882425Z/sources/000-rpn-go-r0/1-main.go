package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	for {
		var token string
		fmt.Scanln(&token)
		if token == "" {
			break
		}
		tokens = append(tokens, token)
	}

	stack := make([]int64, 0, len(tokens))

	for _, t := range tokens {
		switch t {
		case "+":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a+b)
		case "-":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a-b)
		case "*":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a*b)
		default:
			if t == "" {
				fmt.Println("ERROR")
				return
			}
			val, err := strconv.ParseInt(t, 10, 64)
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