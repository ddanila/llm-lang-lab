package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func isDigit(c byte) bool {
	return c >= '0' && c <= '9'
}

func parseNumber(s string) (int64, bool) {
	if len(s) == 0 {
		return 0, false
	}
	sign := 1
	start := 0
	if s[0] == '+' {
		start = 1
	} else if s[0] == '-' {
		sign = -1
		start = 1
	}
	if start >= len(s) {
		return 0, false
	}
	for i := start; i < len(s); i++ {
		if !isDigit(s[i]) {
			return 0, false
		}
	}
	val, err := strconv.ParseInt(s, 10, 64)
	return sign * val, err == nil
}

func main() {
	var tokens []string
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			continue
		}
		fields := strings.Fields(line)
		tokens = append(tokens, fields...)
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
			switch tok {
			case "+":
				stack = append(stack, a+b)
			case "-":
				stack = append(stack, a-b)
			case "*":
				stack = append(stack, a*b)
			}
		} else {
			n, ok := parseNumber(tok)
			if !ok {
				fmt.Println("ERROR")
				return
			}
			stack = append(stack, n)
		}
	}

	if len(stack) != 1 {
		fmt.Println("ERROR")
		return
	}

	fmt.Println(stack[0])
}