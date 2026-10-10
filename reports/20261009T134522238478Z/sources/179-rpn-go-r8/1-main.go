package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	var tokens []string
	scanner := strings.NewReplacer(" ", " ").Replace(strings.TrimSpace(""))
	
	// Read all input and split by whitespace
	input := ""
	var buf [1024]byte
	n, err := readAll(&buf)
	if err != nil && err.Error() != "EOF" {
		fmt.Println("ERROR")
		return
	}
	input = string(buf[:n])

	// Split into tokens
	tokens = strings.Fields(input)
	
	stack := make([]int64, 0, len(tokens))

	for _, token := range tokens {
		if token == "+" || token == "-" || token == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			a := stack[len(stack)-2]
			stack = stack[:len(stack)-2]

			switch token {
			case "+":
				stack = append(stack, a+b)
			case "-":
				stack = append(stack, a-b)
			case "*":
				stack = append(stack, a*b)
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
	} else {
		fmt.Println(stack[0])
	}
}

func readAll(buf *[1024]byte) (int, error) {
	for {
		n, err := fmt.Scan(buf)
		if n > 0 {
			return n, nil
		}
		if err == nil {
			return n, fmt.Errorf("EOF")
		}
	}
}