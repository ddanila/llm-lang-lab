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
	
	s := strings.TrimSpace(line)
	if s == "" {
		return
	}
	
	n, _ := strconv.Atoi(s)
	
	balance := 0
	stack := []int{}
	
	for i := 0; i < n; i++ {
		line, err = reader.ReadString('\n')
		if err != nil {
			break
		}
		
		s = strings.TrimSpace(line)
		if s == "" {
			continue
		}
		
		parts := strings.Fields(s)
		cmd := parts[0]
		
		switch cmd {
		case "ADD":
			x, _ := strconv.Atoi(parts[1])
			balance += x
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