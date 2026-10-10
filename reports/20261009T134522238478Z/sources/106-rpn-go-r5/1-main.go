package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	input := strings.TrimRight(string(make([]byte, 1024)), "\n")
	if len(input) == 0 {
		fmt.Println("ERROR")
		return
	}

	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}
	if len(tokens) > 200 {
		fmt.Println("ERROR")
		return
	}

	stack := make([]int64, 0, 200)

	for _, tok := range tokens {
		if tok == "+" || tok == "-" || tok == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, apply(a, b, tok))
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

func apply(a, b int64, op string) int64 {
	switch op {
	case "+":
		return a + b
	case "-":
		return a - b
	case "*":
		return a * b
	default:
		panic("unexpected")
	}
}