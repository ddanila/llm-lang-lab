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
	nStr := scanner.Text()
	if nStr == "" {
		return
	}
	n, _ := strconv.Atoi(nStr)

	balance := 0
	stack := []int{}

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
			args, _ := strconv.Atoi(parts[1])
			balance += args
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