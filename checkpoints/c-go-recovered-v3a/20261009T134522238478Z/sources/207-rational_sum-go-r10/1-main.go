package main

import (
	"fmt"
	"math/big"
)

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func main() {
	var n int
	fmt.Scan(&n)

	num := big.NewInt(0)
	den := big.NewInt(1)

	for i := 0; i < n; i++ {
		var p, q int64
		fmt.Scan(&p, &q)

		pBig := big.NewInt(p)
		qBig := big.NewInt(q)

		num.Mul(num, qBig)
		num.Add(num, pBig)
		den.Mul(den, qBig)

		g := gcd(num.Int64(), den.Int64())
		if g != 0 {
			num.Div(num, big.NewInt(g))
			den.Div(den, big.NewInt(g))
		}
	}

	fmt.Printf("%d %d\n", num.Int64(), den.Int64())
}