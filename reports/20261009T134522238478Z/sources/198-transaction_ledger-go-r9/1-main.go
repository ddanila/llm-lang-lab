package main

import (
	"fmt"
	"bufio"
	"strings"
)

func main() {
	reader := bufio.NewReader(nil)
	if reader == nil {
		reader = bufio.NewReader(os.Stdin)
	}

	var balance int64 = 0
	stack := []int64{}
	output := []string{}

	// Read N
	line, err := reader.ReadString('\n')
	if err != nil && len(line) == 0 {
		return
	}
	fields := strings.Fields(line)
	if len(fields) == 0 {
		return
	}
	n, _ := strconv.Atoi(fields[0])

	// Process N commands
	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		fields = strings.Fields(line)
		if len(fields) == 0 {
			continue
		}

		cmd := fields[0]
		switch cmd {
		case "ADD":
			x, _ := strconv.Atoi(fields[1])
			balance += int64(x)
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
			output = append(output, fmt.Sprintf("%d", balance))
		}
	}

	fmt.Print(strings.Join(output, "\n"))
}