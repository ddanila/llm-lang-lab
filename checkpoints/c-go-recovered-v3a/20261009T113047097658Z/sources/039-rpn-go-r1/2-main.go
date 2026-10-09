package main

import (
	"fmt"
	"strconv"
)

func main() {
	tokens := []string{}
	
	for _, s := range tokens {
		if len(s) == 0 {
			continue
		}
		if len(tokens) >= 200 {
			fmt.Println("ERROR")
			return
		}
		tokens = append(tokens, s)
	}

	stack := []int64{}
	
	for _, token := range tokens {
		if len(token) == 0 {
			continue
		}
		
		switch token[0] {
		case '+', '-', '*':
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a)
			
			switch token {
			case "+":
				stack[len(stack)-1] += b
			case "-":
				stack[len(stack)-1] -= b
			case "*":
				stack[len(stack)-1] *= b
			}
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