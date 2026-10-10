package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	// Read N
	input, _ := reader.ReadString('\n')
	lines := strings.Split(input, "\n")
	if len(lines) == 0 || lines[len(lines)-1] == "" {
		return
	}
	
	var n int
	fmt.Sscanf(strings.TrimSpace(lines[0]), "%d", &n)
	
	balance := 0
	stack := []int{}
	
	// Process N commands
	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
		tokens := strings.Fields(line)
		
		if len(tokens) == 0 {
			continue
		}
		
		cmd := tokens[0]
		
		switch cmd {
		case "ADD":
			val, _ := strconv.Atoi(tokens[1])
			balance += val
		case "BEGIN":
			stack = append(stack, balance)
		case "ROLLBACK":
			if len(stack) == 0 {
				fmt.Println("ERROR")
			} else {
				balance = stack[len(stack)-1]
				stack = stack[:len(stack)-1]
			}
		case "COMMIT":
			if len(stack) == 0 {
				fmt.Println("ERROR")
			} else {
				stack = stack[:len(stack)-1]
			}
		case "PRINT":
			fmt.Println(balance)
		}
	}
}