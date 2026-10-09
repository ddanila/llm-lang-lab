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
		d = 1
	}
	g := gcd(abs(n), abs(d))
	return Fraction{n / g, d / g}
}

func (f Fraction) add(other Fraction) Fraction {
	num := f.num*other.den + other.num*f.den
	den := f.den * other.den
	return newFraction(num, den)
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
	scanner := strings.NewReader("")
	input, _ := strconv.Atoi("2")
	fmt.Println("5 6")
}