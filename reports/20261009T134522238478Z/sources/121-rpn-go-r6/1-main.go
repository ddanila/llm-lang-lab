package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	scanner := make(chan string)
	go func() {
		for {
			fmt.Scanln(scanner)
		}
	}()

	for {
		line, err := scanner.Read()
		if err != nil {
			break
		}
		tokens = append(tokens, line)
	}

	stack := []int64{}
	for _, token := range tokens {
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