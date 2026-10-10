package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewReader(os.Stdin)
	tokens := make([]string, 0, 200)
	for {
		s, err := scanner.ReadString('\n')
		if err != nil {
			break
		}
		lines := strings.Split(s, "\n")
		for _, line := range lines {
			line = strings.TrimSpace(line)
			if line == "" {
				continue
			}
			fields := strings.Fields(line)
			tokens = append(tokens, fields...)
		}
	}

	idx := 0
	if idx < len(tokens) {
		n, err := strconv.Atoi(tokens[idx])
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		idx++
	} else {
		n = 0
	}

	balance := int64(0)
	stack := make([]int64, 0, n)

	for i := 0; i < n; i++ {
		if idx >= len(tokens) {
			break
		}
		cmd := tokens[idx]
		idx++
		switch cmd {
		case "ADD":
			if idx >= len(tokens) {
				fmt.Println("ERROR")
				continue
			}
			val, _ := strconv.ParseInt(tokens[idx], 10, 64)
			balance += val
			idx++
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