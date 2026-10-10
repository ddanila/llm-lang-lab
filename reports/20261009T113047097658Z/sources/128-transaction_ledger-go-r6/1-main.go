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

	var nStr string
	if token, err := reader.ReadString('\n'); err == nil && strings.TrimSpace(token) != "" {
		nStr = strings.TrimSpace(token)
	}

	var n int
	if nStr == "" {
		n = 0
	} else {
		var err error
		n, err = strconv.Atoi(nStr)
		if err != nil {
			return
		}
	}

	balance := 0
	savedBalances := []int{}

	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}
		parts := strings.Fields(line)
		cmd := parts[0]

		switch cmd {
		case "ADD":
			var x int
			fmt.Sscanf(parts[1], "%d", &x)
			balance += x
		case "BEGIN":
			savedBalances = append(savedBalances, balance)
		case "ROLLBACK":
			if len(savedBalances) == 0 {
				fmt.Println("ERROR")
			} else {
				balance = savedBalances[len(savedBalances)-1]
				savedBalances = savedBalances[:len(savedBalances)-1]
			}
		case "COMMIT":
			if len(savedBalances) == 0 {
				fmt.Println("ERROR")
			} else {
				savedBalances = savedBalances[:len(savedBalances)-1]
			}
		case "PRINT":
			fmt.Println(balance)
		}
	}
}