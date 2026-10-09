package main

import (
	"fmt"
	"strconv"
)

func main() {
	stack := []int64{}
	var token string
	for {
		token, _ = fmt.Scanln("")
		if token == "" {
			break
		}
		token = token[:len(token)-1] // remove newline if present
		
		val, err := strconv.ParseInt(token, 10, 64)
		if err != nil {
			fmt.Println("ERROR")
			return
		}
		
		stack = append(stack, val)
	}
	
	if len(stack) == 0 {
		fmt.Println("ERROR")
		return
	}
	
	if len(stack) != 1 {
		fmt.Println("ERROR")
		return
	}
	
	fmt.Println(stack[0])
}