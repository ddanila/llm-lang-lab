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
	if err != nil && err.Error() != "EOF" {
		return
	}
	
	// Trim and parse N
	line = strings.TrimSpace(line)
	if line == "" {
		// No commands, just EOF after N=0 or empty input
		return
	}
	
	n, err := strconv.Atoi(strings.Fields(line)[0])
	if err != nil {
		return
	}
	
	balance := 0
	savedBalances := []int{}
	
	for i := 0; i < n; i++ {
		line, err = reader.ReadString('\n')
		if err != nil && err.Error() != "EOF" {
			return
		}
		
		fields := strings.Fields(line)
		if len(fields) == 0 {
			continue
		}
		
		cmd := fields[0]
		
		switch cmd {
		case "ADD":
			if len(fields) < 2 {
				continue
			}
			val, err := strconv.Atoi(fields[1])
			if err != nil {
				continue
			}
			balance += val
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