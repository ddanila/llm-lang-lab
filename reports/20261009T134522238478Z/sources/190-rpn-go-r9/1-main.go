package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	for {
		var token string
		_, err := fmt.Scan(&token)
		if err != nil {
			break
		}
		tokens = append(tokens, token)
	}

	stack := []int64{}
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
	} else {
		fmt.Println(stack[0])
	}
}