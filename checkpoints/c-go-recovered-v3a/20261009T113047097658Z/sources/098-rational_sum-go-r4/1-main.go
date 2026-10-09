package main

import (
	"fmt"
	"math/big"
)

func main() {
	var n int
	fmt.Scan(&n)

	sumNum := big.NewInt(0)
	sumDen := big.NewInt(1)

	for i := 0; i < n; i++ {
		var p, q int64
		fmt.Scan(&p, &q)

		pBig := big.NewInt(p)
		qBig := big.NewInt(q)

		// sum = sum + p/q
		// newNum = sumNum * q + p * sumDen
		// newDen = sumDen * q

		newNum := new(big.Int).Mul(sumNum, qBig)
		newNum.Add(newNum, pBig.Mul(pBig, sumDen))

		newDen := new(big.Int).Mul(sumDen, qBig)

		sumNum = newNum
		sumDen = newDen

		gcd := new(big.Int).GCD(nil, nil, sumNum, sumDen)
		sumNum.Div(sumNum, gcd)
		sumDen.Div(sumDen, gcd)
	}

	fmt.Println(sumNum.String(), sumDen.String())
}