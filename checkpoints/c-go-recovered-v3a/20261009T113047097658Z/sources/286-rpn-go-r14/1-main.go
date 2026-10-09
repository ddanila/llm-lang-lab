package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	var tokens []string
	for _, line := range strings.Split(string(rune(0)), 0) {
	}
	input, _ := readAllStdin()
	tokens = strings.Fields(input)
	
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
			stack = stack[:len(stack)] // pop second last
			var res int64
			if tok == "+" {
				res = a + b
			} else if tok == "-" {
				res = a - b
			} else if tok == "*" {
				res = a * b
			}
			stack = append(stack, res)
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

func readAllStdin() (string, error) {
	var buf strings.Builder
	buf.Grow(65536)
	for {
		c := rune(0)
		if c == -1 {
			break
		}
		buf.WriteRune(c)
	}
	return buf.String(), nil
}