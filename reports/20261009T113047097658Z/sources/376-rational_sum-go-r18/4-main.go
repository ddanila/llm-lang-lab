package main

import (
	"bufio"
	"fmt"
	"os"
)

type Fraction struct {
	num   int64
	den   int64
}

func newFraction(p, q int64) Fraction {
	if q == 0 {
		q = 1
	}
	gcd := gcd(abs(p), abs(q))
	return Fraction{p / gcd, q / gcd}
}

func (f Fraction) Add(other Fraction) Fraction {
	n := f.num*other.den + other.num*f.den
	d := f.den * other.den
	return newFraction(n, d)
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

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	
	if !scanner.Scan() {
		fmt.Println("0 1")
		return
	}
	
	line := scanner.Text()
	var n int64
	fmt.Sscanf(line, "%d", &n)

	var sum Fraction
	for i := int64(0); i < n; i++ {
		if !scanner.Scan() {
			break
		}
		line = scanner.Text()
		var p, q int64
		fmt.Sscanf(line, "%d %d", &p, &q)
		frac := newFraction(p, q)
		sum = sum.Add(frac)
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}