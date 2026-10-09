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

	var n int
	line, err := reader.ReadString('\n')
	if err != nil || len(strings.TrimSpace(line)) == 0 {
		return
	}
	n, _ = strconv.Atoi(strings.TrimSpace(line))

	balance := 0
	savedBalances := []int{}

	output := []string{}

	for i := 0; i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		fields := strings.Fields(line)
		if len(fields) == 0 {
			continue
		}
		cmd := fields[0]

		switch cmd {
		case "ADD":
			x, _ := strconv.Atoi(fields[1])
			balance += x
		case "BEGIN":
			savedBalances = append(savedBalances, balance)
		case "ROLLBACK":
			if len(savedBalances) == 0 {
				output = append(output, "ERROR")
			} else {
				balance = savedBalances[len(savedBalances)-1]
				savedBalances = savedBalances[:len(savedBalances)-1]
			}
		case "COMMIT":
			if len(savedBalances) == 0 {
				output = append(output, "ERROR")
			} else {
				savedBalances = savedBalances[:len(savedBalances)-1]
			}
		case "PRINT":
			output = append(output, strconv.Itoa(balance))
		}
	}

	fmt.Println(strings.Join(output, "\n"))
}