package main

import (
	"bufio"
	"fmt"
	"os"
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
	scanner := bufio.NewScanner(os.Stdin)
	var n int
	if !scanner.Scan() {
		fmt.Println("0 1")
		return
	}
	n, _ = strconv.Atoi(scanner.Text())

	sum := newFraction(0, 1)
	for i := 0; i < n; i++ {
		scanner.Scan()
		parts := strings.Fields(scanner.Text())
		if len(parts) >= 2 {
			p, _ := strconv.Atoi(parts[0])
			q, _ := strconv.Atoi(parts[1])
			sum = sum.add(newFraction(int64(p), int64(q)))
		}
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}