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
	
	n, err := strconv.Atoi(strings.TrimSpace(scanner.Text()))
	if err != nil || n < 0 || n > 200 {
		return
	}
	
	balance := 0
	savedBalances := []int{}
	
	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		
		line := scanner.Text()
		tokens := strings.Fields(line)
		if len(tokens) == 0 {
			continue
		}
		
		cmd := tokens[0]
		
		switch cmd {
		case "ADD":
			if len(tokens) < 2 {
				continue
			}
			val, _ := strconv.Atoi(tokens[1])
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