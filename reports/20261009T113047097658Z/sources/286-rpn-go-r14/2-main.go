package main

import (
	"fmt"
	"io"
	"strconv"
	"strings"
)

func main() {
	input, err := io.ReadAll(io.NopCloser(&readCloser{}))
	if err != nil {
		fmt.Println("ERROR")
		return
	}
	tokens := strings.Fields(string(input))
	
	stack := make([]int64, 0, len(tokens))
	
	for _, tok := range tokens {
		if tok == "+" || tok == "-" || tok == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			var res int64
			if tok == "+" {
				res = a + b
			} else if tok == "-" {
				res = a - b
			} else if tok == "*" {
				res = a * b
			}
			stack = append(stack, res)
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

type readCloser struct{}

func (readCloser) Read(p []byte) (int, error) {
	return io.ReadFull(io.NopCloser(&strings.NewReader(""))), nil
}