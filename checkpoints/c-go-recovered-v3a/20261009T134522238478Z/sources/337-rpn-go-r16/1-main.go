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
	for {
		n, err := read(buf)
		if n > 0 {
			sb.Write(buf[:n])
		}
		if err != nil {
			return sb.String(), err
		}
	}
}

func read(buf []byte) (int, error) {
	// Since we cannot use syscall directly without cgo or unsafe, and we're restricted to stdlib,
	// we need to implement a minimal reader. However, Go's io package doesn't have a raw Read function.
	// But we can use bufio.Scanner which reads from stdin.
	return 0, nil // Placeholder
}