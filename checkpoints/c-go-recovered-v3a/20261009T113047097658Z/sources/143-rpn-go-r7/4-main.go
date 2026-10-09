package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var tokens []string
	for scanner.Scan() {
		line := scanner.Text()
		fields := strings.Fields(line)
		if len(fields) == 0 {
			continue
		}
		tokens = append(tokens, fields...)
	}

	allTokens := strings.Join(tokens, " ")
	parts := strings.Fields(allTokens)

	if len(parts) == 0 {
		fmt.Println("ERROR")
		return
	}

	stack := []int64{}
	for _, token := range parts {
		if token == "+" || token == "-" || token == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = stack[:len(stack)]
			var res int64
			if token == "+" {
				res = a + b
			} else if token == "-" {
				res = a - b
			} else {
				res = a * b
			}
			stack = append(stack, res)
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