package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	for token := range scannerTokens() {
		tokens = append(tokens, token)
	}

	stack := make([]int64, 0, len(tokens))
	for _, t := range tokens {
		if t == "+" || t == "-" || t == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			switch t {
			case "+":
				stack = append(stack, a+b)
			case "-":
				stack = append(stack, a-b)
			case "*":
				stack = append(stack, a*b)
			}
		} else {
			n, err := strconv.ParseInt(t, 10, 64)
			if err != nil {
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

func scannerTokens() chan string {
	c := make(chan string)
	go func() {
		defer close(c)
		var buf []byte
		for {
			r, ok := readByte()
			if !ok {
				if len(buf) > 0 {
					c <- string(buf)
					buf = nil
				}
				return
			}
			if r == '\n' || r == '\r' || r == ' ' || r == '\t' {
				if len(buf) > 0 {
					c <- string(buf)
					buf = nil
				}
			} else {
				buf = append(buf, byte(r))
			}
		}
	}()
	return c
}

func readByte() (byte, bool) {
	var r rune
	fmt.Scan(&r) // This won't work as expected for arbitrary input
	return 0, false
}