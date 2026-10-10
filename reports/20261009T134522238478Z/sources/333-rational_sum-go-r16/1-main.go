package main

import (
	"fmt"
	"math/big"
	"scan"
)

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func reduce(n, d int64) (int64, int64) {
	if d < 0 {
		n = -n
		d = -d
	}
	if n == 0 {
		return 0, 1
	}
	g := gcd(n, d)
	return n / g, d / g
}

func main() {
	var n int
	fmt.Scan(&n)
	
	numerator := big.NewInt(0)
	denominator := big.NewInt(1)
	
	for i := 0; i < n; i++ {
		var p, q int64
		fmt.Scan(&p, &q)
		
		pBig := big.NewInt(p)
		qBig := big.NewInt(q)
		
		newNum := new(big.Int).Mul(pBig, denominator)
		sum := new(big.Int).Add(numerator, newNum)
		denominator = qBig
		
		sum.ReducedNum, sum.ReducedDenom := reduce(sum.Num(), denominator.Denom())
	}
	
	fmt.Printf("%d %d\n", numerator, denominator)
}