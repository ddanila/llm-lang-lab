package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var tokens []string
	for scanner.Scan() {
		line := scanner.Text()
		for len(line) > 0 {
			start := 0
			for start < len(line) && (line[start] == ' ' || line[start] == '\t') {
				start++
			}
			if start >= len(line) {
				break
			}
			end := start
			for end < len(line) && line[end] != ' ' && line[end] != '\t' && line[end] != '\n' {
				end++
			}
			tokens = append(tokens, line[start:end])
			line = line[end:]
		}
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