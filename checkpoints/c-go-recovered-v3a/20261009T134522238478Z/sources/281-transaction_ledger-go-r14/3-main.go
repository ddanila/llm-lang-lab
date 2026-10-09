package main

import (
	"fmt"
	"bufio"
	"strings"
)

func main() {
	reader := bufio.NewReader(nil)
	
	buf := make([]byte, 0, 65536)
	for {
		line, err := reader.ReadBytes('\n')
		if err != nil {
			break
		}
		buf = append(buf, line...)
	}
	
	inputStr := string(buf)
	tokens := strings.Fields(inputStr)
	
	if len(tokens) == 0 {
		return
	}
	
	N := 0
	i := 0
	if i < len(tokens) {
		fmt.Sscanf(tokens[i], "%d", &N)
		i++
	}
	
	var currentBalance int64 = 0
	var savedBalances []int64
	
	for i < N && i < len(tokens) {
		cmd := tokens[i]
		i++
		
		switch cmd {
		case "ADD":
			if i < len(tokens) {
				val, _ := fmt.Sscanf(tokens[i], "%d", &val)
				currentBalance += val
				i++
			}
		case "BEGIN":
			savedBalances = append(savedBalances, currentBalance)
		case "ROLLBACK":
			if len(savedBalances) == 0 {
				fmt.Println("ERROR")
			} else {
				currentBalance = savedBalances[len(savedBalances)-1]
				savedBalances = savedBalances[:len(savedBalances)-1]
			}
		case "COMMIT":
			if len(savedBalances) == 0 {
				fmt.Println("ERROR")
			} else {
				savedBalances = savedBalances[:len(savedBalances)-1]
			}
		case "PRINT":
			fmt.Println(currentBalance)
		}
	}
}