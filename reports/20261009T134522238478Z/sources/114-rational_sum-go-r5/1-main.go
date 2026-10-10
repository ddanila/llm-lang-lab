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
	var n int
	if _, err := fmt.Fscanf(scanner, "%d", &n); err != nil {
		return
	}

	// Use big.Int for arbitrary precision to avoid overflow during intermediate steps
	num := new(big.Int)
	den := new(big.Int)
	one := big.NewInt(1)

	for i := 0; i < n; i++ {
		var pStr, qStr string
		fmt.Fscanf(scanner, "%s %s", &pStr, &qStr)
		
		p, _ := strconv.ParseInt(pStr, 10, 64)
		q, _ := strconv.ParseInt(qStr, 10, 64)

		// Add p/q to num/den: (num*p + den*q) / (den*q)
		newNum := new(big.Int).Mul(num, big.NewInt(q))
		newDen := new(big.Int).Mul(den, big.NewInt(q))
		
		addTerm := new(big.Int).Mul(big.NewInt(p), den)
		newNum.Add(newNum, addTerm)

		num = newNum
		den = newDen

		// Reduce the fraction
		g := num.Abs(num) // Absolute value for gcd calculation
		if den.Sign() < 0 {
			g = g.Mul(g, big.NewInt(-1))
		} else {
			g = g.Abs(den)
		}
		
		common := new(big.Int).GCD(nil, nil, num, den)
		num.Div(num, common)
		den.Div(den, common)

		// Ensure denominator is positive
		if den.Sign() < 0 {
			num.Neg(num)
			den.Neg(den)
		}
	}

	fmt.Printf("%d %d\n", num.Int64(), den.Int64())
}