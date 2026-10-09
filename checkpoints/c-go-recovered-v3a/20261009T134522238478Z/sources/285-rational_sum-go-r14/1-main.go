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
	var s strings.Reader
	fmt.Sscanf(&s, "%d", &n)

	num := big.NewInt(0)
	den := big.NewInt(1)

	for i := 0; i < n; i++ {
		var p, q int64
		fmt.Fscanf(&s, "%d %d", &p, &q)

		pBig := big.NewInt(p)
		qBig := big.NewInt(q)

		num = num.Mul(num, qBig)
		num = num.Add(num, pBig)

		den = den.Mul(den, qBig)

		g := gcd(num.Int64(), den.Int64())
		if g != 0 {
			num.Div(num, big.NewInt(g))
			den.Div(den, big.NewInt(g))
		}
	}

	fmt.Println(num.String(), den.String())
}