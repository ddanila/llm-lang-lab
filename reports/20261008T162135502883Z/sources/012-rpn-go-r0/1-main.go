package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	tokens := []string{}
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}
		parts := strings.Fields(line)
		tokens = append(tokens, parts...)
	}

	stack := []int64{}
	valid := true

	for _, token := range tokens {
		if token == "+" || token == "-" || token == "*" {
			if len(stack) < 2 {
				valid = false
				break
			}
			b := stack[len(stack)-1]
			a := stack[len(stack)-2]
			stack = stack[:len(stack)-2]
			switch token {
			case "+":
				stack = append(stack, a+b)
			case "-":
				stack = append(stack, a-b)
			case "*":
				stack = append(stack, a*b)
			}
		} else {
			val, err := strconv.ParseInt(token, 10, 64)
			if err != nil {
				valid = false
				break
			}
			stack = append(stack, val)
		}
	}

	if !valid || len(stack) != 1 {
		fmt.Println("ERROR")
	} else {
		fmt.Printf("%d\n", stack[0])
	}
}