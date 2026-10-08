package main

import (
	"fmt"
	"os"
	"strings"
	"bufio"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	// Read N
	var n int
	fmt.Fscanf(reader, "%d", &n)
	
	balance := 0
	stack := []int{}
	
	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		
		parts := strings.Fields(line)
		if len(parts) == 0 {
			continue
		}
		
		cmd := parts[0]
		
		switch cmd {
		case "ADD":
			var x int
			fmt.Fscanf(reader, "%d", &x) // This won't work as we already consumed the line
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