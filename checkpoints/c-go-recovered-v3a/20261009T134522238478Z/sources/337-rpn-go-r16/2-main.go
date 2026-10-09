package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	input, err := readAllFromStdin()
	if err != nil {
		fmt.Println("ERROR")
		return
	}

	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		fmt.Println("ERROR")
		return
	}

	stack := []int64{}

	for _, token := range tokens {
		if isOperator(token) {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			a := stack[len(stack)-2]
			stack = stack[:len(stack)-2]

			switch token {
			case "+":
				stack = append(stack, a+b)
			case "-":
				stack = append(stack, a-b)
			case "*":
				stack = append(stack, a*b)
			}
		} else {
			val, err := strconv.ParseInt(token, 10, 64)
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

func isOperator(token string) bool {
	return token == "+" || token == "-" || token == "*"
}

func readAllFromStdin() (string, error) {
	var sb strings.Builder
	buf := make([]byte, 1024)
	n, err := read(buf)
	if n > 0 {
		sb.Write(buf[:n])
	}
	if err != nil && err.Error() != "EOF" {
		return sb.String(), err
	}
	return sb.String(), nil
}

func read(buf []byte) (int, error) {
	var n int
	var err error
	for i := 0; i < len(buf); i++ {
		c := buf[i]
		if c == '\n' || c == '\r' {
			n = i
			break
		} else if c == ' ' || c == '\t' {
			continue
		} else {
			n = i + 1
			break
		}
	}
	if n > 0 {
		return n, nil
	}
	return 0, fmt.Errorf("EOF")
}