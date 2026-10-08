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
	gcdVal := gcd(abs(n), abs(d))
	return Fraction{
		num: n / gcdVal,
		den: d / gcdVal,
	}
}

func add(a, b Fraction) Fraction {
	num := a.num*b.den + b.num*a.den
	den := a.den * b.den
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
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)

	if len(tokens) == 0 {
		fmt.Println("0 1")
		return
	}

	n, err := strconv.ParseInt(tokens[0], 10, 64)
	if err != nil {
		fmt.Println("0 1")
		return
	}

	sum := newFraction(0, 1)

	for i := 0; i < n; i++ {
		idx := 2 + 2*i
		if idx+1 >= len(tokens) {
			break
		}
		p, err := strconv.ParseInt(tokens[idx], 10, 64)
		if err != nil {
			continue
		}
		q, err := strconv.ParseInt(tokens[idx+1], 10, 64)
		if err != nil {
			continue
		}
		sum = add(sum, newFraction(p, q))
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}