package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	for token := range scanTokens() {
		tokens = append(tokens, token)
		if len(tokens) > 200 {
			fmt.Println("ERROR")
			return
		}
	}

	stack := make([]int64, 0, 10)

	for _, tok := range tokens {
		switch tok {
		case "+":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack[len(stack)-1] = a + b

		case "-":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack[len(stack)-1] = a - b

		case "*":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack[len(stack)-1] = a * b

		default:
			val, err := strconv.ParseInt(tok, 10, 64)
			if err != nil {
				fmt.Println("ERROR")
				return
			}
			stack = append(stack, val)
		}
	}

	if len(stack) != 1 {
		fmt.Println("ERROR")
		return
	}

	fmt.Println(stack[0])
}

func scanTokens() chan string {
	ch := make(chan string)
	go func() {
		var line, tok string
		for {
			line, _ = fmt.Scanln()
			if line == "" {
				break
			}
			fmt.Sscanf(line, "%s", &tok)
			for len(tok) > 0 {
				i := 0
				for i < len(tok) && tok[i] != ' ' && tok[i] != '\t' && tok[i] != '\r' && tok[i] != '\n' {
					i++
				}
				if i > 0 {
					ch <- tok[:i]
				}
				tok = tok[i:]
			}
		}
		close(ch)
	}()
	return ch
}