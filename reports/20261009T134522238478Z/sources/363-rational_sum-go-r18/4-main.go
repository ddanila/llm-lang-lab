package main

import (
	"fmt"
	"io"
	"math/big"
	"os"
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
	content, _ := io.ReadAll(os.Stdin)
	
	// Parse the input
	tokens := strings.Fields(string(content))
	if len(tokens) == 0 {
		fmt.Println("0 1")
		return
	}
	
	n, err := strconv.ParseInt(tokens[0], 10, 64)
	if err != nil {
		fmt.Println("0 1")
		return
	}
	
	// Use big.Int for exact arithmetic
	numerator := new(big.Int).SetInt64(0)
	denominator := new(big.Int).SetInt64(1)
	
	for i := 1; i < len(tokens); i += 2 {
		p, err := strconv.ParseInt(tokens[i], 10, 64)
		if err != nil {
			continue
		}
		
		q, err := strconv.ParseInt(tokens[i+1], 10, 64)
		if err != nil {
			continue
		}
		
		// Add p/q to the sum: new_numerator = numerator*q + p*denominator
		// new_denominator = denominator * q
		numerator.Mul(numerator, big.NewInt(q))
		numerator.Add(numerator, big.NewInt(p))
		denominator.Mul(denominator, big.NewInt(q))
		
		// Reduce the fraction
		g := gcd(numerator.Int64(), denominator.Int64())
		if g != 0 {
			numerator.Div(numerator, big.NewInt(g))
			denominator.Div(denominator, big.NewInt(g))
		}
	}
	
	fmt.Printf("%d %d\n", numerator.Int64(), denominator.Int64())
}