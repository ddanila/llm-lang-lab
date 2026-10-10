package main

import (
	"fmt"
	"strconv"
)

func main() {
	stack := []int64{}
	var tokens []string
	for token := range fmt.Scanln() {
		tokens = append(tokens, token)
	}
	// Re-read properly since Scanln doesn't handle EOF cleanly in a loop
	// We need to read all input first
}

func main() {
	input := ""
	fmt.Scanf("%s", &input) // This won't work for multiline
	
	// Better approach: read line by line and tokenize
	var tokens []string
	for {
		line, err := fmt.Scanln("")
		if err != nil {
			break
		}
		tokens = append(tokens, line)
	}
	
	// Actually, let's use a different approach - read all from stdin
}

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
		// Split by whitespace
		parts := strings.Fields(line)
		tokens = append(tokens, parts...)
	}
	
	// Process RPN
	stack := make([]int64, 0)
	
	for _, token := range tokens {
		if token == "+" || token == "-" || token == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = append(stack, b) // Pop right operand first
			if token == "+" {
				stack[len(stack)-1] = a + b
			} else if token == "-" {
				stack[len(stack)-1] = a - b
			} else if token == "*" {
				stack[len(stack)-1] = a * b
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