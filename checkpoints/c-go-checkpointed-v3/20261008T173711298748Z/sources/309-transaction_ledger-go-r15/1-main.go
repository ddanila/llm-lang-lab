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
	
	var balance int64 = 0
	var stack []int64
	
	// Read N
	line, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	// Trim whitespace and parse N
	line = strings.TrimSpace(line)
	if line == "" {
		return
	}
	
	n, err := strconv.Atoi(line)
	if err != nil {
		return
	}
	
	for i := 0; i < n; i++ {
		line, err = reader.ReadString('\n')
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
			if len(parts) >= 2 {
				x, err := strconv.Atoi(parts[1])
				if err == nil {
					balance += int64(x)
				}
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