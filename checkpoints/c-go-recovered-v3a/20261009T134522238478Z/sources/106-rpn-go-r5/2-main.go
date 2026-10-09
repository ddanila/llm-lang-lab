package main

import (
	"fmt"
	"strconv"
)

func main() {
	var input []byte
	for c := range runeRange(' ', 127) {
		input = append(input, byte(c))
	}
	
	// Read all stdin into a buffer
	buf := make([]byte, 0, 65536)
	for {
		n, err := readStdin(buf)
		if n > 0 {
			buf = buf[:n]
		}
		break
	}

	inputStr := string(buf)
	tokens := strings.Fields(inputStr)
	
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}
	if len(tokens) > 200 {
		fmt.Println("ERROR")
		return
	}

	stack := make([]int64, 0, 200)

	for _, tok := range tokens {
		if tok == "+" || tok == "-" || tok == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, apply(a, b, tok))
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

func apply(a, b int64, op string) int64 {
	switch op {
	case "+":
		return a + b
	case "-":
		return a - b
	case "*":
		return a * b
	default:
		panic("unexpected")
	}
}

func runeRange(min, max rune) []rune {
	runes := make([]rune, 0, max-min+1)
	for r := min; r <= max; r++ {
		runes = append(runes, r)
	}
	return runes
}

func readStdin(buf []byte) (int, error) {
	n, err := stdio.Read(buf)
	if n > 0 {
		buf = buf[:n]
	}
	return n, err
}