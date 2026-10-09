package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	for {
		var token string
		fmt.Scan(&token)
		tokens = append(tokens, token)
		if len(tokens) > 200 {
			break
		}
	}

	stack := []int64{}

	for _, t := range tokens {
		if t == "+" || t == "-" || t == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			a := stack[len(stack)-2]
			stack = stack[:len(stack)-2]
			if t == "+" {
				stack = append(stack, a+b)
			} else if t == "-" {
				stack = append(stack, a-b)
			} else if t == "*" {
				stack = append(stack, a*b)
			}
		} else {
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