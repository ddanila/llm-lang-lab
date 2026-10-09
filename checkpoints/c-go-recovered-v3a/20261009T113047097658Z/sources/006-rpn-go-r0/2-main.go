package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	tokens := []string{}

	for scanner.Scan() {
		line := scanner.Text()
		// Split by whitespace
		fields := strings.Fields(line)
		tokens = append(tokens, fields...)
	}

	stack := make([]int64, 0, 200)

	for _, tok := range tokens {
		if len(tok) == 0 {
			continue
		}

		// Check if operator
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
			continue
		}

		// Check if valid integer token
		if len(tok) < 1 || (tok[0] != '+' && tok[0] != '-' && (tok[0] < '0' || tok[0] > '9')) {
			fmt.Println("ERROR")
			return
		}

		// Parse integer
		val, err := strconv.ParseInt(tok, 10, 64)
		if err != nil {
			fmt.Println("ERROR")
			return
		}

		stack = append(stack, val)
	}

	if len(stack) != 1 {
		fmt.Println("ERROR")
		return
	}

	fmt.Printf("%d\n", stack[0])
}