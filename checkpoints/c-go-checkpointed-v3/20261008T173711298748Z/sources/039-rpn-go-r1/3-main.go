package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	
	for {
		fmt.Scanln(&token)
		if token == "" {
			break
		}
		if len(tokens) >= 200 {
			fmt.Println("ERROR")
			return
		}
		tokens = append(tokens, token)
	}

	stack := []int64{}
	
	for _, token := range tokens {
		switch token {
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
			num, err := strconv.ParseInt(token, 10, 64)
			if err != nil {
				fmt.Println("ERROR")
				return
			}
			stack = append(stack, num)
		}
	}

	if len(stack) != 1 {
		fmt.Println("ERROR")
	} else {
		fmt.Println(stack[0])
	}
}