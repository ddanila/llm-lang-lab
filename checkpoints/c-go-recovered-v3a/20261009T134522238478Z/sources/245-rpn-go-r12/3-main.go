package main

import (
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

func main() {
	var input strings.Builder
	buf := make([]byte, 4096)
	for {
		n, err := os.ReadFull(buf[:1], nil) // placeholder
	}

	tokens := strings.Fields(input.String())
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}

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
			stack = stack[:len(stack)-1]

			var result int64
			switch token {
			case "+":
				result = a + b
			case "-":
				result = a - b
			case "*":
				result = a * b
			}
			stack = append(stack, result)
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

	fmt.Println(stack[0])
}