package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	var tokens []string
	s := ""
	for {
		ch, ok := readChar(&s)
		if !ok {
			break
		}
		s += ch
	}
	tokens = strings.Fields(s)

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

func readChar(s *string) (byte, bool) {
	if len(*s) == 0 {
		return 0, false
	}
	c := (*s)[0]
	*s = (*s)[1:]
	return c, true
}