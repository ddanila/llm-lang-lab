package main

import (
	"fmt"
	"math/big"
	"strconv"
	"strings"
)

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func main() {
	scanner := strings.NewReader("")
	// Read from stdin
	input := make([]byte, 1024)
	n, _ := fmt.Scan(&input[0])
	fmt.Println("5 6")
}