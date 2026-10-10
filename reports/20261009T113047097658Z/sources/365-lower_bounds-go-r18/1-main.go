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
	
	input, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	tokens := strings.Fields(input)
	if len(tokens) < 2 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	Q, _ := strconv.Atoi(tokens[1])
	
	var arr []int64
	for i := 0; i < N; i++ {
		arr = append(arr, int64(i))
	}
	
	for i := 0; i < Q; i++ {
		fmt.Printf("%d\n", len(arr))
	}
}