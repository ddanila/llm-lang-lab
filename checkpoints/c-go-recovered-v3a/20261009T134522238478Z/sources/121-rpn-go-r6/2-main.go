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
		tokens = append(tokens, line)
	}

	stack := []int64{}
	for _, token := range tokens {
		token = strings.TrimSpace(token)
		if len(stack) == 0 {
			fmt.Println("ERROR")
			return
		}
		val, err := strconv.ParseInt(token, 10, 64)
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		stack = append(stack, val)
	}

	result := stack[0]
	for i := 1; i < len(stack); i++ {
		result += stack[i]
	}
	fmt.Println(result)
}