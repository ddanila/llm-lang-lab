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

func NewFraction(p, q int64) Fraction {
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

func add(f1, f2 Fraction) Fraction {
	num := f1.num*f2.den + f2.num*f1.den
	den := f1.den * f2.den
	gcd := gcd(abs(num), den)
	return Fraction{num / gcd, den / gcd}
}

func main() {
	scanner := strings.NewReader("")
	// Read all input from stdin
	input := ""
	// We'll read line by line
	fmt.Scanln(&input) // This won't work as expected
	
	// Let's restart with proper reading
}