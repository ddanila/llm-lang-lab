package main

import (
	"fmt"
	"math/big"
	"strconv"
)

func main() {
	var n int
	fmt.Scan(&n)

	// Initialize fraction as 0/1
	num := big.NewInt(0)
	den := big.NewInt(1)

	for i := 0; i < n; i++ {
		var pStr, qStr string
		fmt.Scan(&pStr, &qStr)
		
		p, _ := strconv.ParseInt(pStr, 10, 64)
		q, _ := strconv.ParseInt(qStr, 10, 64)

		// Add p/q to num/den: (num*p + den*q) / (den*q)
		newNum := new(big.Int).Mul(num, big.NewInt(int64(q)))
		newDen := new(big.Int).Mul(den, big.NewInt(int64(q)))
		
		addTerm := new(big.Int).Mul(big.NewInt(p), den)
		newNum.Add(newNum, addTerm)

		num = newNum
		den = newDen

		// Reduce the fraction
		common := num.GCD(nil, nil, num, den)
		if common.Sign() != 0 {
			num.Div(num, common)
			den.Div(den, common)
		}

		// Ensure denominator is positive
		if den.Sign() < 0 {
			num.Neg(num)
			den.Neg(den)
		}
	}

	fmt.Printf("%d %d\n", num.Int64(), den.Int64())
}