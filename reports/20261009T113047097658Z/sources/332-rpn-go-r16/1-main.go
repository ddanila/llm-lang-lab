package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	input := os.Stdin.String()
	tokens := strings.Fields(input)

	stack := []int64{}

	for _, token := range tokens {
		if token == "+" || token == "-" || token == "*" {
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
				stack[len(stack)-1] = a + b
			case "-":
				stack[len(stack)-1] = a - b
			case "*":
				stack[len(stack)-1] = a * b
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
		return
	}

	fmt.Printf("%d\n", stack[0])
}