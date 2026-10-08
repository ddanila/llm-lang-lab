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

func abs(x int64) int64 {
	if x < 0 {
		return -x
	}
	return x
}

func main() {
	var n int
	fmt.Scan(&n)

	sum := big.NewInt(0)
	den := big.NewInt(1)

	for i := 0; i < n; i++ {
		var p, q int64
		fmt.Scan(&p, &q)

		pBig := big.NewInt(p)
		qBig := big.NewInt(q)

		num := new(big.Int).Mul(pBig, den)
		denom := new(big.Int).Mul(den, qBig)

		sum.Add(sum, num)
		den = denom

		g := new(big.Int)
		g.GCD(nil, nil, sum, den)

		sum.Div(sum, g)
		den.Div(den, g)
	}

	fmt.Println(sum.String(), den.String())
}