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
	var err error
	if nStr, err = reader.ReadString('\n'); err != nil {
		return
	}
	nStr = strings.TrimSpace(nStr)
	if nStr == "" {
		return
	}
	n, _ := strconv.Atoi(nStr)

	balance := 0
	savedBalances := []int{}

	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
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
			val, _ := strconv.Atoi(parts[1])
			balance += val
		case "BEGIN":
			savedBalances = append(savedBalances, balance)
		case "ROLLBACK":
			if len(savedBalances) == 0 {
				fmt.Fprintln(os.Stdout, "ERROR")
			} else {
				balance = savedBalances[len(savedBalances)-1]
				savedBalances = savedBalances[:len(savedBalances)-1]
			}
		case "COMMIT":
			if len(savedBalances) == 0 {
				fmt.Fprintln(os.Stdout, "ERROR")
			} else {
				savedBalances = savedBalances[:len(savedBalances)-1]
			}
		case "PRINT":
			fmt.Fprintln(os.Stdout, balance)
		}
	}
}