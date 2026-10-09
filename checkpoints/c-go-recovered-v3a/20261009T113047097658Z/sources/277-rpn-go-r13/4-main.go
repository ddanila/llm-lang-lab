package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var tokens []string
	for scanner.Scan() {
		line := scanner.Text()
		for len(line) > 0 {
			i := 0
			if line[0] == ' ' || line[0] == '\t' {
				for i < len(line) && (line[i] == ' ' || line[i] == '\t') {
					i++
				}
			}
			j := i
			for j < len(line) && line[j] != ' ' && line[j] != '\t' {
				j++
			}
			if j > i {
				tokens = append(tokens, line[i:j])
			}
			line = line[j:]
		}
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
			stack = append(stack, a)

			switch tok {
			case "+":
				stack[len(stack)-1] = b + a
			case "-":
				stack[len(stack)-1] = a - b
			case "*":
				stack[len(stack)-1] = a * b
			}
		} else {
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