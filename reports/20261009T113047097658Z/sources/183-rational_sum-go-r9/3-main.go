package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Fraction struct {
	numerator   int64
	denominator int64
}

func newFraction(n, d int64) Fraction {
	if d == 0 {
		panic("division by zero")
	}
	gcd := gcd(abs(n), abs(d))
	return Fraction{
		numerator:   n / gcd,
		denominator: d / gcd,
	}
}

func (f *Fraction) add(other Fraction) {
	n1, d1 := f.numerator, f.denominator
	n2, d2 := other.numerator, other.denominator

	lcm := lcm(d1, d2)
	f.numerator = n1 * (lcm / d1) + n2 * (lcm / d2)
	f.denominator = lcm
	// Reduce after addition
	gcdVal := gcd(abs(f.numerator), abs(f.denominator))
	if gcdVal != 0 {
		f.numerator /= gcdVal
		f.denominator /= gcdVal
	}
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

func lcm(a, b int64) int64 {
	if a == 0 || b == 0 {
		return 0
	}
	return abs(a / gcd(a, b)) * b
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		return
	}
	nStr := strings.TrimSpace(scanner.Text())
	if nStr == "" {
		fmt.Println("0 1")
		return
	}
	n, _ := strconv.Atoi(nStr)

	total := newFraction(0, 1)

	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		line := scanner.Text()
		tokens := strings.Fields(line)
		if len(tokens) != 2 {
			continue
		}
		p, _ := strconv.Atoi(tokens[0])
		q, _ := strconv.Atoi(tokens[1])
		frac := newFraction(int64(p), int64(q))
		total.add(frac)
	}

	fmt.Printf("%d %d\n", total.numerator, total.denominator)
}