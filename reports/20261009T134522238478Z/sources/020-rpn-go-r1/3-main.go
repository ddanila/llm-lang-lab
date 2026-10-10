package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(bufio.NewReader(os.Stdin))
	var tokens []string
	
	for scanner.Scan() {
		line := scanner.Text()
		for len(line) > 0 {
			i := 0
			for i < len(line) && isSpace(line[i]) {
				i++
			}
			if i >= len(line) {
				break
			}
			j := i
			for j < len(line) && !isSpace(line[j]) {
				j++
			}
			tokens = append(tokens, line[i:j])
		}
	}

	if len(tokens) > 200 {
		fmt.Println("ERROR")
		return
	}

	stack := make([]int64, 0, 10)

	for _, tok := range tokens {
		if tok == "+" || tok == "-" || tok == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			if tok == "+" {
				stack = append(stack, a+b)
			} else if tok == "-" {
				stack = append(stack, a-b)
			} else {
				stack = append(stack, a*b)
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

func isSpace(c byte) bool {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r'
}