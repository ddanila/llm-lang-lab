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

func addFractions(p1, q1, p2, q2 int64) (int64, int64) {
	num := p1*q2 + p2*q1
	den := q1 * q2
	g := gcd(num, den)
	if g < 0 {
		g = -g
	}
	return num / g, den / g
}

func main() {
	var n int
	fmt.Scan(&n)

	var p, q int64
	var num, den int64 = 0, 1

	for i := 0; i < n; i++ {
		fmt.Scan(&p, &q)
		num, den = addFractions(num, den, p, q)
	}

	fmt.Printf("%d %d\n", num, den)
}