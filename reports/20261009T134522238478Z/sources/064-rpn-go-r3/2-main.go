package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	var tokens []string
	input := readAll()
	tokens = strings.Fields(input)

	stack := []int64{}

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

			switch tok {
			case "+":
				stack = append(stack, a+b)
			case "-":
				stack = append(stack, a-b)
			case "*":
				stack = append(stack, a*b)
			}
		} else {
			v, err := strconv.ParseInt(tok, 10, 64)
			if err != nil {
				fmt.Println("ERROR")
				return
			}
			stack = append(stack, v)
		}
	}

	if len(stack) != 1 {
		fmt.Println("ERROR")
		return
	}

	fmt.Println(stack[0])
}

func readAll() string {
	var s strings.Builder
	for {
		c := rune(0)
		fmt.Scan(&c)
		if c == -1 {
			break
		}
		s.WriteRune(c)
	}
	return s.String()
}