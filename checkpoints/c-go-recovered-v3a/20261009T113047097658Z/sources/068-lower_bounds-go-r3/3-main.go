package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	allInput, _ := reader.ReadString('\n')
	tokens := strings.Fields(allInput)
	
	if len(tokens) < 2 {
		return
	}
	
	n, _ := strconv.Atoi(tokens[0])
	q, _ := strconv.Atoi(tokens[1])
	
	a := make([]int64, n)
	for i := 0; i < n && i < len(tokens)-2; i++ {
		val, _ := strconv.ParseInt(tokens[i+2], 10, 64)
		a[i] = val
	}
	
	if q > 0 && len(tokens) > n+2 {
		for i := 0; i < q; i++ {
			val, _ := strconv.ParseInt(tokens[n+2+i], 10, 64)
			fmt.Println(val)
		}
		return
	}
	
	// Handle multi-line input for queries
	if q > 0 {
		for len(allInput) > 0 {
			allInput, _ = reader.ReadString('\n')
			tokens := strings.Fields(allInput)
			for _, token := range tokens {
				val, _ := strconv.ParseInt(token, 10, 64)
				fmt.Println(val)
			}
		}
	}
}