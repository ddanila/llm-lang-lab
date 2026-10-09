package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	var tokens []string
	scanner := bufio.NewScanner(os.Stdin)
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
	if len(tokens) == 0 {
		return "ERROR"
	}

	stack := make([]int64, 0, 200)

	for _, token := range tokens {
		if token == "+" || token == "-" || token == "*" {
			if len(stack) < 2 {
				return "ERROR"
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, applyOp(a, b, token))
		} else if isValidNumber(token) {
			val, err := strconv.ParseInt(token, 10, 64)
			if err != nil {
				return "ERROR"
			}
			stack = append(stack, val)
		} else {
			return "ERROR"
		}
	}

	if len(stack) != 1 {
		return "ERROR"
	}

	return fmt.Sprintf("%d", stack[0])
}

func isValidNumber(s string) bool {
	if len(s) == 0 {
		return false
	}
	if s[0] == '+' || s[0] == '-' {
		return len(s) > 1
	}
	for _, c := range s {
		if c < '0' || c > '9' {
			return false
		}
	}
	return true
}

func applyOp(a, b int64, op string) int64 {
	switch op {
	case "+":
		return a + b
	case "-":
		return a - b
	case "*":
		return a * b
	default:
		return 0
	}
}