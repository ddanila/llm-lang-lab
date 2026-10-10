package main

import (
	"fmt"
	"io"
	"os"
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
		n, err := os.Read(buf)
		if n > 0 {
			sb.Write(buf[:n])
		}
		if err != nil && err != io.EOF {
			return sb.String(), err
		}
		if err == io.EOF {
			break
		}
	}
	return sb.String(), nil
}