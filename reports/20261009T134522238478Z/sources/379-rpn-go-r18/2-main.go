package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	stack := []int64{}
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line := scanner.Text()
		tokens := strings.Fields(line)
		for _, token := range tokens {
			if len(tokens) > 200 {
				fmt.Println("ERROR")
				return
			}
			if token == "+" {
				if len(stack) < 2 {
					fmt.Println("ERROR")
					return
				}
				b := stack[len(stack)-1]
				stack = stack[:len(stack)-1]
				a := stack[len(stack)-1]
				stack = append(stack, a+b)
			} else if token == "-" {
				if len(stack) < 2 {
					fmt.Println("ERROR")
					return
				}
				b := stack[len(stack)-1]
				stack = stack[:len(stack)-1]
				a := stack[len(stack)-1]
				stack = append(stack, a-b)
			} else if token == "*" {
				if len(stack) < 2 {
					fmt.Println("ERROR")
					return
				}
				b := stack[len(stack)-1]
				stack = stack[:len(stack)-1]
				a := stack[len(stack)-1]
				stack = append(stack, a*b)
			} else {
				val, err := strconv.ParseInt(token, 10, 64)
				if err != nil {
					fmt.Println("ERROR")
					return
				}
				stack = append(stack, val)
			}
		}
	}

	if len(stack) != 1 {
		fmt.Println("ERROR")
		return
	}

	fmt.Println(stack[0])
}