package main

import (
	"fmt"
	"bufio"
	"strings"
)

func main() {
	reader := bufio.NewReader(nil) // We'll read from stdin directly via os.Stdin
	if reader == nil {
		return
	}
	
	// Use a custom scanner to handle whitespace-separated tokens
	scanner := bufio.NewScanner(reader)
	tokens := []string{}
	var token string
	
	// Read all input and split into tokens
	buf := make([]byte, 0, 65536)
	for {
		line, err := reader.ReadBytes('\n')
		if err != nil {
			break
		}
		buf = append(buf, line...)
	}
	
	inputStr := string(buf)
	tokenizer := strings.NewReader(inputStr)
	
	var currentBalance int64 = 0
	var savedBalances []int64
	
	type Token struct {
		Value string
	}
	
	var nextToken func() *Token
	
	nextToken = func() *Token {
		for {
			if _, err := fmt.Fscanf(tokenizer, "%s", &token); err != nil {
				break
			}
			if token == "" {
				continue
			}
			return &Token{Value: token}
		}
		return nil
	}
	
	var peekNext func() string
	peekNext = func() string {
		t := nextToken()
		if t != nil {
			return t.Value
		}
		return ""
	}
	
	// Actually, let's just read all tokens into a slice first
	allTokens := []string{}
	for scanner.Scan() {
		line := scanner.Text()
		tokens = append(tokens, strings.Fields(line)...)
	}
	
	if len(tokens) == 0 {
		return
	}
	
	N := 0
	i := 0
	if i < len(tokens) {
		N, _ = fmt.Sscanf(tokens[i], "%d", &N)
		i++
	}
	
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