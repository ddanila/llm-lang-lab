package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Fraction struct {
	num, den int64
}

func newFraction(n, d int64) Fraction {
	if d == 0 {
		panic("denominator cannot be zero")
	}
	gcd := gcd(abs(n), abs(d))
	return Fraction{n / gcd, d / gcd}
}

func (f Fraction) add(other Fraction) Fraction {
	n := f.num*other.den + other.num*f.den
	d := f.den * other.den
	return newFraction(n, d)
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
	var tokens []string
	
	for scanner.Scan() {
		tokens = append(tokens, scanner.Text())
	}
	
	// Join all tokens with space and split by whitespace
	input := strings.Join(tokens, " ")
	parts := strings.Fields(input)
	
	if len(parts) == 0 {
		fmt.Println("0 1")
		return
	}
	
	var sum Fraction
	
	for i := 1; i < len(parts); i += 2 {
		p, _ := strconv.ParseInt(parts[i], 10, 64)
		q, _ := strconv.ParseInt(parts[i+1], 10, 64)
		sum = sum.add(newFraction(p, q))
	}
	
	fmt.Printf("%d %d\n", sum.num, sum.den)
}