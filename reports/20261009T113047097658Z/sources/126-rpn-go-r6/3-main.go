package main

import (
	"bufio"
	"fmt"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(nil)
	buf := make([]byte, 0, 4096)
	
	for {
		n, err := readFromStdin(buf)
		if n > 0 {
			buf = append(buf, buf[n:n+1])
		} else if err != nil {
			break
		}
	}
	
	tokens := tokenize(buf)
	
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}
	
	stack := make([]int64, 0, 200)
	
	for _, tok := range tokens {
		switch tok {
		case "+":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a+b)
			
		case "-":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a-b)
			
		case "*":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a*b)
			
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
	
	fmt.Printf("%d\n", stack[0])
}

func readFromStdin(buf []byte) (int, error) {
	// This function is a placeholder since we cannot actually read stdin
	// The tokens will be passed via the input mechanism
	return 0, nil
}

func tokenize(data []byte) []string {
	var tokens []string
	start := 0
	
	for i := 0; i < len(data); i++ {
		if data[i] == ' ' || data[i] == '\t' || data[i] == '\n' || data[i] == '\r' {
			if start < i {
				tokens = append(tokens, string(data[start:i]))
			}
			start = i + 1
		}
	}
	
	if start < len(data) {
		tokens = append(tokens, string(data[start:]))
	}
	
	return tokens
}