package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	tokens := []string{}
	
	for scanner.Scan() {
		line := scanner.Text()
		tokens = append(tokens, strings.Fields(line)...)
	}
	
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