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
	var tokens []string
	
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Fields(line)
		tokens = append(tokens, parts...)
	}
	
	stack := make([]int64, 0)
	
	for _, token := range tokens {
		if token == "+" || token == "-" || token == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a)
			if token == "+" {
				stack[len(stack)-1] = a + b
			} else if token == "-" {
				stack[len(stack)-1] = a - b
			} else if token == "*" {
				stack[len(stack)-1] = a * b
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