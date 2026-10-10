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

func NewFraction(p, q int64) Fraction {
	gcd := gcd(abs(p), q)
	return Fraction{p / gcd, q / gcd}
}

func (f *Fraction) Add(other Fraction) {
	n := f.num*other.den + other.num*f.den
	d := f.den * other.den
	gcd := gcd(abs(n), d)
	f.num = n / gcd
	f.den = d / gcd
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
	reader := bufio.NewReader(os.Stdin)
	tokens := []string{}
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		tokens = append(tokens, strings.Fields(line)...)
	}

	if len(tokens) == 0 {
		fmt.Println("0 1")
		return
	}

	N, _ := strconv.ParseInt(tokens[0], 10, 64)
	idx := 1

	var sum Fraction = NewFraction(0, 1)

	for i := int64(0); i < N; i++ {
		if idx+1 >= len(tokens) {
			break
		}
		p, _ := strconv.ParseInt(tokens[idx], 10, 64)
		q, _ := strconv.ParseInt(tokens[idx+1], 10, 64)
		sum.Add(NewFraction(p, q))
		idx += 2
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}