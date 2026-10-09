package main

import (
	"fmt"
	"strconv"
	"strings"
)

type Fraction struct {
	num, den int64
}

func newFraction(n, d int64) Fraction {
	if d == 0 {
		panic("denominator cannot be zero")
	}
	gcd := gcd(abs(n), abs(d))
	return Fraction{n / gcd, d / gcd}
}

func (f Fraction) add(other Fraction) Fraction {
	n := f.num*other.den + other.num*f.den
	d := f.den * other.den
	return newFraction(n, d)
}

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
	scanner := strings.NewReplacer("\n", " ", "\t", " ").Replace("")
}