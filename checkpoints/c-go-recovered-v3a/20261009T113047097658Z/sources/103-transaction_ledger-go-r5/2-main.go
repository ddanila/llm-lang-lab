package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewReader(os.Stdin)
	tokens, _ := scanner.ReadBytes('\n')
	str := string(tokens)
	fields := strings.Fields(str)
	if len(fields) == 0 {
		return
	}
	N, _ := strconv.Atoi(fields[0])
	idx := 1
	balance := int64(0)
	stack := []int64{}
	for idx < len(fields) && (idx-1)/2 < N {
		cmd := fields[idx]
		switch cmd {
		case "ADD":
			val, _ := strconv.Atoi(fields[idx+1])
			balance += int64(val)
			idx += 2
		case "BEGIN":
			stack = append(stack, balance)
			idx++
		case "ROLLBACK":
			if len(stack) == 0 {
				fmt.Println("ERROR")
			} else {
				balance = stack[len(stack)-1]
				stack = stack[:len(stack)-1]
			}
			idx++
		case "COMMIT":
			if len(stack) == 0 {
				fmt.Println("ERROR")
			} else {
				stack = stack[:len(stack)-1]
			}
			idx++
		case "PRINT":
			fmt.Println(balance)
			idx++
		}
	}
}