package main

import (
	"fmt"
	"bufio"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(strings.NewReader(""))
	if len(scanner.Bytes()) == 0 {
		return
	}
	
	// Read all input at once
	input := scanner.Text()
	
	// Split into tokens
	tokens := strings.Fields(input)
	
	if len(tokens) == 0 {
		return
	}
	
	n := 0
	fmt.Sscanf(tokens[0], "%d", &n)
	
	balance := 0
	stack := []int{}
	
	idx := 1
	
	for i := 0; i < n; i++ {
		if idx >= len(tokens) {
			break
		}
		cmd := tokens[idx]
		idx++
		
		switch cmd {
		case "ADD":
			if idx < len(tokens) {
				var x int
				fmt.Sscanf(tokens[idx], "%d", &x)
				idx++
				balance += x
			}
		case "BEGIN":
			stack = append(stack, balance)
		case "ROLLBACK":
			if len(stack) > 0 {
				balance = stack[len(stack)-1]
				stack = stack[:len(stack)-1]
			} else {
				fmt.Println("ERROR")
			}
		case "COMMIT":
			if len(stack) > 0 {
				stack = stack[:len(stack)-1]
			} else {
				fmt.Println("ERROR")
			}
		case "PRINT":
			fmt.Println(balance)
		}
	}
}