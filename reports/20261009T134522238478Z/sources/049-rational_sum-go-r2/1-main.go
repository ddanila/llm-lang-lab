package main

import (
	"fmt"
	"strconv"
	"strings"
)

type Fraction struct {
	num   int64
	den   int64
}

func newFraction(p, q int64) Fraction {
	if q == 0 {
		panic("denominator cannot be zero")
	}
	gcd := gcd(abs(p), q)
	return Fraction{p / gcd, q / gcd}
}

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

func (f Fraction) add(other Fraction) Fraction {
	n := f.num*other.den + other.num*f.den
	d := f.den * other.den
	gcdVal := gcd(abs(n), d)
	return Fraction{n / gcdVal, d / gcdVal}
}

func main() {
	var input string
	fmt.Scanln(&input)
	if input == "" {
		fmt.Println("0 1")
		return
	}
	parts := strings.Fields(input)
	idx := 0
	n, _ := strconv.ParseInt(parts[idx], 10, 64)
	idx++

	var sum Fraction = newFraction(0, 1)

	for i := int64(0); i < n; i++ {
		if idx >= len(parts) {
			break
		}
		p, _ := strconv.ParseInt(parts[idx], 10, 64)
		idx++
		q, _ := strconv.ParseInt(parts[idx], 10, 64)
		idx++

		frac := newFraction(p, q)
		sum = sum.add(frac)
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}