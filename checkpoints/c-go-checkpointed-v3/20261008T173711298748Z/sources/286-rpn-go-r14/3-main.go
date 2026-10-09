package main

import (
	"fmt"
	"io"
	"strconv"
	"strings"
)

func main() {
	var input strings.Builder
	buf := make([]byte, 1<<20)
	for {
		n, err := io.ReadFull(&input, buf)
		if err != nil {
			break
		}
	}
	
	tokens := strings.Fields(input.String())
	
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

func main2() {
	input, _ := io.ReadAll(io.NopCloser(&strings.Reader{}))
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