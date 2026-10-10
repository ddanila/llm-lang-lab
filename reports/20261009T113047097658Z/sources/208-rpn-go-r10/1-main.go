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

	stack := make([]int64, 0, len(tokens))

	for _, tok := range tokens {
		if tok == "+" || tok == "-" || tok == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = stack[:len(stack)-1]

			if tok == "+" {
				stack = append(stack, a+b)
			} else if tok == "-" {
				stack = append(stack, a-b)
			} else if tok == "*" {
				stack = append(stack, a*b)
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