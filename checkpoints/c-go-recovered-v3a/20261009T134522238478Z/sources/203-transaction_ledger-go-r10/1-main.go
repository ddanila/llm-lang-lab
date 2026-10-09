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
	line, err := reader.ReadString('\n')
	if err != nil && line == "" {
		return
	}
	
	// Handle empty input (N=0 case with no lines)
	line = strings.TrimSpace(line)
	if line == "" {
		return
	}
	
	n, _ := strconv.Atoi(strings.TrimSpace(line))
	
	balance := 0
	stack := []int{}
	
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		
		parts := strings.Fields(line)
		if len(parts) == 0 {
			continue
		}
		
		cmd := parts[0]
		
		switch cmd {
		case "ADD":
			val, _ := strconv.Atoi(parts[1])
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