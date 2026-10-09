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
	if err != nil {
		return
	}
	line = strings.TrimSpace(line)
	if line == "" {
		return
	}
	n, err := strconv.Atoi(line)
	if err != nil {
		return
	}

	balance := 0
	stack := make([]int, 0, n+1)

	for i := 0; i < n; i++ {
		line, err = reader.ReadString('\n')
		if err != nil && line == "" {
			break
		}
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}

		parts := strings.Fields(line)
		if len(parts) == 0 {
			continue
		}

		cmd := parts[0]
		switch cmd {
		case "ADD":
			if len(parts) < 2 {
				continue
			}
			val, _ := strconv.Atoi(parts[1])
			balance += val
		case "BEGIN":
			stack = append(stack, balance)
		case "ROLLBACK":
			if len(stack) == 0 {
				fmt.Fprintln(os.Stdout, "ERROR")
			} else {
				balance = stack[len(stack)-1]
				stack = stack[:len(stack)-1]
			}
		case "COMMIT":
			if len(stack) == 0 {
				fmt.Fprintln(os.Stdout, "ERROR")
			} else {
				stack = stack[:len(stack)-1]
			}
		case "PRINT":
			fmt.Fprintln(os.Stdout, balance)
		}
	}
}