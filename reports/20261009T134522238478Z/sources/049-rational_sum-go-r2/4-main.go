package main

import (
	"bufio"
	"fmt"
	"os"
)

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

type Fraction struct {
	num   int64
	den   int64
}

func newFraction(p, q int64) Fraction {
	gcdVal := gcd(abs(p), q)
	return Fraction{p / gcdVal, q / gcdVal}
}

func (f Fraction) add(other Fraction) Fraction {
	n := f.num*other.den + other.num*f.den
	d := f.den * other.den
	gcdVal := gcd(abs(n), d)
	if gcdVal == 0 {
		gcdVal = 1
	}
	return Fraction{n / gcdVal, d / gcdVal}
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	
	var n int
	if !scanner.Scan() {
		fmt.Println("0 1")
		return
	}
	fmt.Fscanf(scanner, "%d", &n)
	
	var sum Fraction = newFraction(0, 1)
	
	for i := 0; i < n; i++ {
		var p, q int
		if scanner.Scan() {
			fmt.Fscanf(scanner, "%d %d", &p, &q)
			frac := newFraction(int64(p), int64(q))
			sum = sum.add(frac)
		}
	}
	
	fmt.Printf("%d %d\n", sum.num, sum.den)
}