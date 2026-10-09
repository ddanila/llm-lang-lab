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
	tokens := []string{}
	
	for scanner.Scan() {
		line := scanner.Text()
		for _, tok := range strings.Fields(line) {
			tokens = append(tokens, tok)
		}
	}
	
	if len(tokens) == 0 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	tokens = tokens[1:]
	
	balance := int64(0)
	stack := make([]int64, 0, N+1)
	output := []string{}
	
	for i := 0; i < len(tokens); i++ {
		cmd := tokens[i]
		
		switch cmd {
		case "ADD":
			valStr := tokens[i+1]
			val, _ := strconv.ParseInt(valStr, 10, 64)
			balance += val
			i++ // skip the value token
		case "BEGIN":
			stack = append(stack, balance)
		case "ROLLBACK":
			if len(stack) == 0 {
				output = append(output, "ERROR")
			} else {
				balance = stack[len(stack)-1]
				stack = stack[:len(stack)-1]
			}
		case "COMMIT":
			if len(stack) == 0 {
				output = append(output, "ERROR")
			} else {
				stack = stack[:len(stack)-1]
			}
		case "PRINT":
			output = append(output, fmt.Sprintf("%d", balance))
		}
	}
	
	for _, v := range output {
		fmt.Println(v)
	}
}