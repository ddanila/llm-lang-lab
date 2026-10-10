package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
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
	
	var n int64
	_, err := fmt.Fscan(scanner, &n)
	if err != nil || scanner.Err() != nil {
		fmt.Println("0 1")
		return
	}

	var sum Fraction
	for i := int64(0); i < n; i++ {
		var p, q int64
		_, err = fmt.Fscan(scanner, &p, &q)
		if err != nil || scanner.Err() != nil {
			break
		}
		frac := newFraction(p, q)
		sum = sum.Add(frac)
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}