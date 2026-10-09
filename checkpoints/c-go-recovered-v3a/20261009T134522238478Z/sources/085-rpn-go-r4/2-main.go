package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	var tokens []string
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			continue
		}
		tokens = append(tokens, strings.Fields(line)...)
	}
	
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}
	
	stack := []int64{}
	
	for _, token := range tokens {
		if isOperator(token) {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			right := stack[len(stack)-1]
			left := stack[len(stack)-2]
			stack = stack[:len(stack)-2]
			
			switch token {
			case "+":
				stack = append(stack, left+right)
			case "-":
				stack = append(stack, left-right)
			case "*":
				stack = append(stack, left*right)
			}
		} else {
			val, err := strconv.ParseInt(token, 10, 64)
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

func isOperator(s string) bool {
	return s == "+" || s == "-" || s == "*"
}