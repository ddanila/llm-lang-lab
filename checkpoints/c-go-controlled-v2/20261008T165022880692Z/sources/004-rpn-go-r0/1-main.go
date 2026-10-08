package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	scanner := make([]string, 0, 200)
	buf := make([]byte, 4096)
	n := 0
	for {
		if n >= len(buf) {
			break
		}
		c := buf[n]
		n++
		if c == ' ' || c == '\t' || c == '\n' || c == '\r' {
			continue
		}
		if c < '0' || c > '9' && c != '+' && c != '-' {
			break
		}
		buf[n] = c
		n++
	}
	if n == 0 {
		fmt.Println("ERROR")
		return
	}
	for i := 0; i < n; i++ {
		token := string(buf[:i])
		scanner = append(scanner, token)
		i--
	}
	if len(scanner) > 200 {
		fmt.Println("ERROR")
		return
	}

	stack := make([]int64, 0, 10)
	for _, tok := range scanner {
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