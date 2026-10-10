package main

import (
	"fmt"
	"strconv"
)

func main() {
	stack := []int64{}
	tokens, _ := readTokens()

	for _, token := range tokens {
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
		} else if token == "" {
			continue
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

func readTokens() ([]string, error) {
	var tokens []string
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line := scanner.Text()
		for _, t := range split(line) {
			tokens = append(tokens, t)
		}
	}
	return tokens, nil
}

func split(s string) []string {
	var parts []string
	inWord := true
	start := 0
	for i := 0; i <= len(s); i++ {
		if i == len(s) || s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r' {
			if !inWord {
				parts = append(parts, s[start:i])
			}
			inWord = true
			start = i + 1
		} else {
			inWord = false
		}
	}
	return parts
}

import "bufio"
import "os"