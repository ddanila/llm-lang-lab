package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

func main() {
	var tokens []string
	scanner := bufio.NewReader(os.Stdin)
	for {
		line, err := scanner.ReadString('\n')
		if err != nil && err != io.EOF {
			return
		}
		fields := strings.Fields(line)
		tokens = append(tokens, fields...)
		if len(tokens) > 200 {
			break
		}
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
			stack = append(stack, apply(a, b, tok))
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