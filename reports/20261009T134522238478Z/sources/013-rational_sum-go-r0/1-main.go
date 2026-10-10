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

func reduce(n, d int64) (int64, int64) {
	if d == 0 {
		return n, 1
	}
	g := gcd(n, d)
	return n / g, d / g
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

		numBig := num
		denBig := den

		newNum := new(big.Int).Mul(numBig, qBig)
		newDen := new(big.Int).Mul(denBig, qBig)

		addTerm := new(big.Int).Add(newNum, pBig)

		newNum = addTerm
		newDen = newDen

		gcdVal := new(big.Int).GCD(nil, nil, newNum, newDen)
		newNum.Div(newNum, gcdVal)
		newDen.Div(newDen, gcdVal)

		num.Set(newNum)
		den.Set(newDen)
	}

	fmt.Println(num.String(), den.String())
}