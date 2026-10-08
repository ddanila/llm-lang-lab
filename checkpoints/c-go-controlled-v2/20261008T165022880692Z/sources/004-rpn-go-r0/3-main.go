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
		if line == "" {
			continue
		}
		for _, c := range line {
			if c == ' ' || c == '\t' || c == '\n' || c == '\r' {
				continue
			}
			tokens = append(tokens, string(c))
		}
	}

	if len(tokens) > 200 {
		fmt.Println("ERROR")
		return
	}

	stack := make([]int64, 0, 10)
	for _, tok := range tokens {
		switch tok {
		case "+", "-", "*":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, apply(a, b, tok))
		default:
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
		panic("unknown op")
	}
}