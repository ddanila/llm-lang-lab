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
	var tokens []string
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}
		tokens = append(tokens, strings.Fields(line)...)
	}

	result := evaluateRPN(tokens)
	fmt.Println(result)
}

func evaluateRPN(tokens []string) string {
	stack := make([]int64, 0, len(tokens))

	for _, token := range tokens {
		val, err := strconv.ParseInt(token, 10, 64)
		if err != nil {
			return "ERROR"
		}
		switch token {
		case "+":
			if len(stack) < 2 {
				return "ERROR"
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack[len(stack)-1] = a + b
		case "-":
			if len(stack) < 2 {
				return "ERROR"
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack[len(stack)-1] = a - b
		case "*":
			if len(stack) < 2 {
				return "ERROR"
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack[len(stack)-1] = a * b
		default:
			if token != "+" && token != "-" && token != "*" {
				return "ERROR"
			}
		}
	}

	if len(stack) != 1 {
		return "ERROR"
	}

	return fmt.Sprintf("%d", stack[0])
}