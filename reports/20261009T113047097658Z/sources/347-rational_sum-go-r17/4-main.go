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
		return Fraction{num: 0, den: 1}
	}
	gcd := gcd(abs(n), abs(d))
	return Fraction{num: n / gcd, den: d / gcd}
}

func (f Fraction) add(other Fraction) Fraction {
	num := f.num*other.den + other.num*f.den
	den := f.den * other.den
	return newFraction(num, den)
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
	nStr := strings.TrimSpace(scanner.Text())
	var n int
	if nStr == "" {
		fmt.Println("0 1")
		return
	} else {
		n, _ = strconv.Atoi(nStr)
	}

	sum := newFraction(0, 1)
	for i := 0; i < n; i++ {
		line := scanner.Text()
		tokens := strings.Fields(line)
		if len(tokens) >= 2 {
			p, _ := strconv.ParseInt(tokens[0], 10, 64)
			q, _ := strconv.ParseInt(tokens[1], 10, 64)
			sum = sum.add(newFraction(p, q))
		}
	}

	if sum.num == 0 {
		fmt.Println("0 1")
	} else {
		fmt.Printf("%d %d\n", sum.num, sum.den)
	}
}