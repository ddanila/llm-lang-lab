package main

import (
	"bufio"
	"fmt"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(nil)
	var tokens []string
	
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}
		parts := strings.Fields(line)
		tokens = append(tokens, parts...)
	}

	stack := []int64{}
	valid := true

	for _, tok := range tokens {
		if len(tok) == 0 {
			continue
		}
		if (tok[0] == '+' || tok[0] == '-') && len(tok) > 1 {
			_, err := strconv.ParseInt(tok, 10, 64)
			if err != nil {
				valid = false
				break
			}
			stack = append(stack, stack[len(stack)-1]) // placeholder
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