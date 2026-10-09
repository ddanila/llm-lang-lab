package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Fraction struct {
	num   int64
	den   int64
}

func newFraction(n, d int64) Fraction {
	if d == 0 {
		panic("division by zero")
	}
	gcd := gcd(abs(n), abs(d))
	return Fraction{num: n / gcd, den: d / gcd}
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
	num := f.num*other.den + other.num*f.den
	den := f.den * other.den
	return newFraction(num, den)
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		return
	}
	nStr := strings.TrimSpace(scanner.Text())
	n, err := strconv.ParseInt(nStr, 10, 64)
	if err != nil || n < 0 || n > 20 {
		return
	}

	var sum Fraction = newFraction(0, 1)

	for i := int64(0); i < n; i++ {
		if !scanner.Scan() {
			break
		}
		line := scanner.Text()
		tokens := strings.Fields(line)
		if len(tokens) != 2 {
			continue
		}

		p, err1 := strconv.ParseInt(tokens[0], 10, 64)
		q, err2 := strconv.ParseInt(tokens[1], 10, 64)
		if err1 != nil || err2 != nil || q <= 0 {
			continue
		}

		frac := newFraction(p, q)
		sum = sum.add(frac)
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}