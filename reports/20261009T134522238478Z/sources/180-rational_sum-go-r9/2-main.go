package main

import (
	"fmt"
	"math/big"
)

type Fraction struct {
	n, d int64
}

func newFraction(n, d int64) Fraction {
	gcd := big.NewInt(0).GCD(nil, nil, big.NewInt(n), big.NewInt(d))
	return Fraction{n: n / gcd.Int64(), d: d / gcd.Int64()}
}

func main() {
	var n int
	fmt.Scan(&n)

	total := newFraction(0, 1)

	for i := 0; i < n; i++ {
		var p, q int
		fmt.Scan(&p, &q)
		frac := Fraction{n: int64(p), d: int64(q)}
		sum := total.add(frac)
		total = sum
	}

	fmt.Printf("%d %d\n", total.n, total.d)
}

func (f Fraction) add(other Fraction) Fraction {
	n := f.n*other.d + other.n*f.d
	d := f.d * other.d
	gcd := big.NewInt(0).GCD(nil, nil, big.NewInt(n), big.NewInt(d))
	return Fraction{n: n / gcd.Int64(), d: d / gcd.Int64()}
}