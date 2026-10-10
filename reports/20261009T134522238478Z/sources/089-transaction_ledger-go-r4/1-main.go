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
	if !scanner.Scan() {
		return
	}
	
	nStr := strings.TrimSpace(scanner.Text())
	var n int
	fmt.Sscanf(nStr, "%d", &n)
	
	balance := 0
	stack := []int{}
	output := []string{}
	
	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		line := strings.TrimSpace(scanner.Text())
		parts := strings.Fields(line)
		
		if len(parts) == 0 {
			continue
		}
		
		cmd := parts[0]
		
		switch cmd {
		case "ADD":
			var x int
			fmt.Sscanf(parts[1], "%d", &x)
			balance += x
		case "BEGIN":
			stack = append(stack, balance)
		case "ROLLBACK":
			if len(stack) == 0 {
				output = append(output, "ERROR")
			} else {
				balance = stack[len(stack)-1]
				stack = stack[:len(stack)-1]
			}
		case "COMMIT":
			if len(stack) == 0 {
				output = append(output, "ERROR")
			} else {
				stack = stack[:len(stack)-1]
			}
		case "PRINT":
			output = append(output, strconv.Itoa(balance))
		}
	}
	
	for _, s := range output {
		fmt.Println(s)
	}
}