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

type Fraction struct {
	num   int64
	den   int64
}

func newFraction(n, d int64) Fraction {
	if d == 0 {
		panic("division by zero")
	}
	g := gcd(n, d)
	if g < 0 {
		g = -g
	}
	n /= g
	d /= g
	if d < 0 {
		n = -n
		d = -d
	}
	return Fraction{n: n, den: d}
}

func add(f1, f2 Fraction) Fraction {
	num := f1.num*f2.den + f2.num*f1.den
	den := f1.den * f2.den
	return newFraction(num, den)
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var n int
	if !scanner.Scan() {
		fmt.Println("0 1")
		return
	}
	n = scanner.Text()
	if n == "" {
		fmt.Println("0 1")
		return
	}

	sum := newFraction(0, 1)
	for i := 0; i < n; i++ {
		var p, q int64
		scanner.Scan()
		parts := scanner.Text()
		fields := []string{}
		for _, c := range parts {
			if c != ' ' && c != '\t' && c != '\n' && c != '\r' {
				fields = append(fields, string(c))
			}
		}
		if len(fields) >= 2 {
			p, _ = strconv.ParseInt(fields[0], 10, 64)
			q, _ = strconv.ParseInt(fields[1], 10, 64)
			sum = add(sum, newFraction(p, q))
		}
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}