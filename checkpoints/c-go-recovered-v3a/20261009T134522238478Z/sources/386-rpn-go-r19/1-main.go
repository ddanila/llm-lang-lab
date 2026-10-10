package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	input := readAll()
	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}

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
			stack = stack[:len(stack)] // pop second operand
			stack = append(stack, b) // push left (a)
			stack = append(stack, a) // push right (b) - wait, order is: pop right, then pop left, then push left OP right
			// Correct logic:
			// stack[len-1] is right operand
			// stack[len-2] is left operand
			right := stack[len(stack)-1]
			left := stack[len(stack)-2]
			stack = stack[:len(stack)-2] // pop both

			switch tok {
			case "+":
				stack = append(stack, left+right)
			case "-":
				stack = append(stack, left-right)
			case "*":
				stack = append(stack, left*right)
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

	fmt.Printf("%d\n", stack[0])
}

func readAll() string {
	var buf strings.Builder
	for {
		ch := rune(0)
		r, _, err := bufio.NewReaderSize(nil, 1).ReadRune() // This won't work without imports
		_ = ch
		_ = r
		_ = err
	}
	return ""
}