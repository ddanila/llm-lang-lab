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
	n, err := strconv.Atoi(line)
	if err != nil || n < 0 || n > 200 {
		return
	}

	var balance int64 = 0
	var saved []int64

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
			val, _ := strconv.Atoi(parts[1])
			balance += int64(val)
		case "BEGIN":
			saved = append(saved, balance)
		case "ROLLBACK":
			if len(saved) == 0 {
				fmt.Fprintln(os.Stdout, "ERROR")
			} else {
				balance = saved[len(saved)-1]
				saved = saved[:len(saved)-1]
			}
		case "COMMIT":
			if len(saved) == 0 {
				fmt.Fprintln(os.Stdout, "ERROR")
			} else {
				saved = saved[:len(saved)-1]
			}
		case "PRINT":
			fmt.Fprintln(os.Stdout, balance)
		}
	}
}