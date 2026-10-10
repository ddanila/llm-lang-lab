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
	line := strings.TrimSpace(scanner.Text())
	if line == "" {
		return
	}
	n, err := strconv.Atoi(line)
	if err != nil {
		return
	}

	balance := 0
	stack := []int{}

	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		line = strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}
		parts := strings.Fields(line)
		cmd := parts[0]

		switch cmd {
		case "ADD":
			if len(parts) < 2 {
				continue
			}
			x, _ := strconv.Atoi(parts[1])
			balance += x
		case "BEGIN":
			stack = append(stack, balance)
		case "ROLLBACK":
			if len(stack) == 0 {
				fmt.Println("ERROR")
				continue
			}
			balance = stack[len(stack)-1]
			stack = stack[:len(stack)-1]
		case "COMMIT":
			if len(stack) == 0 {
				fmt.Println("ERROR")
				continue
			}
			stack = stack[:len(stack)-1]
		case "PRINT":
			fmt.Println(balance)
		}
	}
}