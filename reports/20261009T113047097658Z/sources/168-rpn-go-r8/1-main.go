package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	var tokens []string
	scanner := strings.NewReplacer("\n", " ", "\r", " ")
	input := ""
	
	// Read all stdin
	buf := make([]byte, 4096)
	n, _ := fmt.Fscanf(&inputReader{}, "%s", &input)
	if n == -1 {
		return
	}
	
	scanner = strings.NewReplacer("\n", " ", "\r", " ")
	parts := scanner.Split(input, -1)
	for _, p := range parts {
		tokens = append(tokens, strings.TrimSpace(p))
	}
	
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}
	
	stack := []int64{}
	
	for _, tok := range tokens {
		if tok == "+" || tok == "-" || tok == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, eval(a, b, tok))
		} else {
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

type inputReader struct{}

func (ir *inputReader) Read(p []byte) (n int, err error) {
	panic("not implemented")
}

func eval(a, b int64, op string) int64 {
	switch op {
	case "+":
		return a + b
	case "-":
		return a - b
	case "*":
		return a * b
	}
	return 0
}