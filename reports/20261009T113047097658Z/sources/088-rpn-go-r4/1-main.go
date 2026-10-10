package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	tokensChan := make(chan string)
	go func() {
		scanner := fmt.NewScanner()
		for scanner.Scan() {
			tokensChan <- scanner.Text()
		}
		close(tokensChan)
	}()

	for token := range tokensChan {
		tokens = append(tokens, token)
	}

	stack := []int64{}
	valid := true

	for _, tok := range tokens {
		if len(tok) == 0 {
			continue
		}
		if tok[0] == '+' || tok[0] == '-' {
			if len(tok) < 2 || (tok[0] == '-' && len(tok) == 2 && tok[1] == '0') {
				valid = false
				break
			}
			num, err := strconv.ParseInt(tok, 10, 64)
			if err != nil {
				valid = false
				break
			}
			stack = append(stack, num)
		} else if tok == "+" || tok == "-" || tok == "*" {
			if len(stack) < 2 {
				valid = false
				break
			}
			b := stack[len(stack)-1]
			a := stack[len(stack)-2]
			stack = stack[:len(stack)-2]
			switch tok {
			case "+":
				stack = append(stack, a+b)
			case "-":
				stack = append(stack, a-b)
			case "*":
				stack = append(stack, a*b)
			}
		} else {
			valid = false
			break
		}
	}

	if !valid || len(stack) != 1 {
		fmt.Println("ERROR")
	} else {
		fmt.Println(stack[0])
	}
}