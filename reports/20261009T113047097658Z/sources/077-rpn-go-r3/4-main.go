package main

import (
	"bufio"
	"fmt"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(nil)
	var tokens []string
	
	for {
		if _, err := fmt.Scanln(&scanner); err != nil {
			break
		}
		
		tokens = append(tokens, scanner)
	}

	stack := make([]int64, 0, len(tokens))

	for _, tok := range tokens {
		if tok == "+" || tok == "-" || tok == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = stack[:len(stack)-1]

			var res int64
			switch tok {
			case "+":
				res = a + b
			case "-":
				res = a - b
			case "*":
				res = a * b
			}
			stack = append(stack, res)
		} else if len(tok) > 0 {
			val, err := strconv.ParseInt(tok, 10, 64)
			if err != nil {
				fmt.Println("ERROR")
				return
			}
			stack = append(stack, val)
		} else {
			fmt.Println("ERROR")
			return
		}
	}

	if len(stack) != 1 {
		fmt.Println("ERROR")
		return
	}

	fmt.Println(stack[0])
}