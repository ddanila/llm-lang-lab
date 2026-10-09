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
	g := gcd(abs(n), abs(d))
	return Fraction{num: n / g, den: d / g}
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
	reader := bufio.NewReader(os.Stdin)
	input, err := reader.ReadString('\n')
	if err != nil {
		os.Exit(1)
	}

	parts := strings.Fields(input)
	if len(parts) == 0 {
		fmt.Println("0 1")
		return
	}

	n, err := strconv.ParseInt(parts[0], 10, 64)
	if err != nil {
		os.Exit(1)
	}

	var sum Fraction = newFraction(0, 1)

	idx := 1
	for i := int64(0); i < n; i++ {
		if idx >= len(parts) {
			break
		}
		p, err := strconv.ParseInt(parts[idx], 10, 64)
		if err != nil {
			os.Exit(1)
		}
		idx++

		q, err := strconv.ParseInt(parts[idx], 10, 64)
		if err != nil {
			os.Exit(1)
		}
		idx++

		frac := newFraction(p, q)
		sum = sum.Add(frac)
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}

func (f Fraction) Add(other Fraction) Fraction {
	num := f.num*other.den + other.num*f.den
	den := f.den * other.den
	return newFraction(num, den)
}