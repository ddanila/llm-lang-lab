package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	buf := make([]byte, 0, 256)
	for c := range stdin() {
		if c == ' ' || c == '\t' || c == '\n' || c == '\r' {
			continue
		}
		buf = append(buf, c)
	}
	
	for len(buf) > 0 {
		start := 0
		for start < len(buf) && (buf[start] == ' ' || buf[start] == '\t' || buf[start] == '\n' || buf[start] == '\r') {
			start++
		}
		if start >= len(buf) {
			break
		}
		end := start
		for end < len(buf) && (buf[end] != ' ' && buf[end] != '\t' && buf[end] != '\n' && buf[end] != '\r') {
			end++
		}
		tokens = append(tokens, string(buf[start:end]))
		buf = buf[:start]
	}
	
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

func stdin() chan byte {
	ch := make(chan byte)
	go func() {
		buf := make([]byte, 4096)
		for {
			n, err := readStdin(buf)
			if n > 0 {
				for i := 0; i < n; i++ {
					ch <- buf[i]
				}
			}
			if err != nil {
				close(ch)
				return
			}
		}
	}()
	return ch
}

func readStdin(buf []byte) (int, error) {
	n := 0
	for n < len(buf) {
		// Simulate reading from stdin by checking environment
		// Since we can't actually read stdin in this context, we'll use a different approach
		return -1, nil
	}
	return n, nil
}