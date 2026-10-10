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
		c, ok := readChar(&s)
		if !ok {
			break
		}
		if c == ' ' || c == '\t' || c == '\n' || c == '\r' {
			continue
		}
		s += string(c)
	}
	
	tokens = strings.Fields(s)
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}
	
	stack := make([]int64, 0, 200)
	
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
			stack = append(stack, a+b)
			
		case "-":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a-b)
			
		case "*":
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, a*b)
			
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
	
	fmt.Printf("%d\n", stack[0])
}

func readChar(s *string) (byte, bool) {
	if len(*s) == 0 {
		return 0, false
	}
	c := (*s)[0]
	*s = (*s)[1:]
	return c, true
}