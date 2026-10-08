package main

import (
	"fmt"
	"math/big"
)

func main() {
	var n int
	fmt.Scan(&n)
	
	if n == 0 {
		fmt.Println("0 1")
		return
	}
	
	// Use big.Int for exact arithmetic
	num := big.NewInt(0)
	den := big.NewInt(1)
	
	for i := 0; i < n; i++ {
		var p, q int64
		fmt.Scan(&p)
		fmt.Scan(&q)
		
		// Create fraction p/q
		fracNum := big.NewInt(p)
		fracDen := big.NewInt(q)
		
		// Add to sum: num/den + fracNum/fracDen = (num*fracDen + fracNum*den) / (den*fracDen)
		newNum := new(big.Int).Mul(num, fracDen)
		newNum.Add(newNum, fracNum.Mul(fracNum, den))
		
		newDen := new(big.Int).Mul(den, fracDen)
		
		num = newNum
		den = newDen
		
		// Reduce by GCD
		g := num.GCD(nil, nil, num, den)
		num.Div(num, g)
		den.Div(den, g)
	}
	
	fmt.Printf("%s %s\n", num.String(), den.String())
}