package main

import (
	"fmt"
	"math/big"
)

func abs(x int64) int64 {
	if x < 0 {
		return -x
	}
	return x
}

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func main() {
	var n int
	fmt.Scan(&n)

	sumNum := big.NewInt(0)
	den := big.NewInt(1)

	for i := 0; i < n; i++ {
		var p, q int64
		fmt.Scan(&p, &q)

		pBig := big.NewInt(p)
		qBig := big.NewInt(q)

		num := new(big.Int).Mul(pBig, den)
		denom := new(big.Int).Mul(den, qBig)

		sumNum.Add(sumNum, num)
		den = denom

		g := new(big.Int)
		g.GCD(nil, nil, sumNum, den)

		sumNum.Div(sumNum, g)
		den.Div(den, g)
	}

	fmt.Println(sumNum.String(), den.String())
}