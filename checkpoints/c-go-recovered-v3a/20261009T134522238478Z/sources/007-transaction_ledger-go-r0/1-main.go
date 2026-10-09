package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var n int
	if !scanner.Scan() {
		return
	}
	n, _ = strconv.Atoi(strings.TrimSpace(scanner.Text()))

	balance := 0
	stack := []int{}

	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		line := strings.Fields(scanner.Text())
		if len(line) == 0 {
			continue
		}
		cmd := line[0]

		switch cmd {
		case "ADD":
			if len(line) >= 2 {
				x, _ := strconv.Atoi(line[1])
				balance += x
			}
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