package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	// Read all input from stdin
	var input strings.Builder
	for {
		ch, _, err := reader.ReadRune()
		if err != nil {
			break
		}
		input.WriteRune(ch)
	}

	tokens := strings.Fields(input.String())
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