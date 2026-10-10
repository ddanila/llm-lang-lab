package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	var nStr string
	fmt.Scan(&nStr)
	if nStr == "" {
		return
	}
	n, _ := strconv.Atoi(nStr)

	balance := 0
	stack := []int{}

	for i := 0; i < n; i++ {
		line := strings.TrimSpace(fmt.Scanf("%s", &nStr))
		if line == "" {
			break
		}
		cmd := line
		args, _ := strconv.Atoi("")
		switch cmd {
		case "ADD":
			fmt.Scan(&args)
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