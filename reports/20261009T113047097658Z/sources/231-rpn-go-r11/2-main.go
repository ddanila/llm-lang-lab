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
	stack := []int64{}
	
	for scanner.Scan() {
		line := scanner.Text()
		tokens := strings.Fields(line)
		
		for _, token := range tokens {
			if len(token) == 0 {
				continue
			}
			
			// Check if it's an operator
			if token == "+" || token == "-" || token == "*" {
				if len(stack) < 2 {
					fmt.Println("ERROR")
					return
				}
				
				b := stack[len(stack)-1]
				a := stack[len(stack)-2]
				stack = stack[:len(stack)-2]
				
				if token == "+" {
					stack = append(stack, a+b)
				} else if token == "-" {
					stack = append(stack, a-b)
				} else if token == "*" {
					stack = append(stack, a*b)
				}
			} else {
				// It's an integer
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