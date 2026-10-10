package main

import (
	"bufio"
	"fmt"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(bufio.NewReader(nil))
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			continue
		}
		tokens := split(line)
		stack := []int64{}

		for _, t := range tokens {
			if t == "+" || t == "-" || t == "*" {
				if len(stack) < 2 {
					fmt.Println("ERROR")
					return
				}
				b := stack[len(stack)-1]
				a := stack[len(stack)-2]
				stack = stack[:len(stack)-2]
				if t == "+" {
					stack = append(stack, a+b)
				} else if t == "-" {
					stack = append(stack, a-b)
				} else if t == "*" {
					stack = append(stack, a*b)
				}
			} else {
				val, err := strconv.ParseInt(t, 10, 64)
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
}

func split(s string) []string {
	var tokens []string
	start := 0
	for i, c := range s {
		if c == ' ' || c == '\t' || c == '\n' || c == '\r' {
			if i > start {
				tokens = append(tokens, s[start:i])
			}
			start = i + 1
		}
	}
	if start < len(s) {
		tokens = append(tokens, s[start:])
	}
	return tokens
}