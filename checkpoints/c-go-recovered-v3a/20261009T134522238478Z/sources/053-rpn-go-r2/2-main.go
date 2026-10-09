package main

import (
	"bufio"
	"fmt"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(nil)
	var tokens []string

	for scanner.Scan() {
		line := scanner.Text()
		for _, token := range split(line) {
			tokens = append(tokens, token)
		}
	}

	stack := make([]int64, 0, len(tokens))

	for _, token := range tokens {
		if token == "+" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a+b)
		} else if token == "-" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a-b)
		} else if token == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a*b)
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

func split(s string) []string {
	var tokens []string
	start := 0
	for i := 0; i <= len(s); i++ {
		if i == len(s) || s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r' {
			if i > start {
				tokens = append(tokens, s[start:i])
			}
			start = i + 1
		}
	}
	return tokens
}