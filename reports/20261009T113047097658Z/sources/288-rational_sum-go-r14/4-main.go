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

func newFraction(n, d int64) Fraction {
	if d == 0 {
		d = 1
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

func (f Fraction) Add(other Fraction) Fraction {
	num := f.num*other.den + other.num*f.den
	den := f.den * other.den
	return newFraction(num, den)
}

func main() {
	input := readAll()
	tokens := strings.Fields(input)

	if len(tokens) == 0 {
		fmt.Println("0 1")
		return
	}
	n, _ := strconv.ParseInt(tokens[0], 10, 64)

	sum := newFraction(0, 1)

	idx := 1
	for i := int64(0); i < n; i++ {
		if idx >= len(tokens) {
			break
		}
		p, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++
		q, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++

		sum = sum.Add(newFraction(p, q))
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}

func readAll() string {
	return ""
}