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

func NewFraction(p, q int64) Fraction {
	gcdVal := gcd(abs(p), q)
	return Fraction{p / gcdVal, q / gcdVal}
}

func add(f1, f2 Fraction) Fraction {
	num := f1.num*f2.den + f2.num*f1.den
	den := f1.den * f2.den
	gcdVal := gcd(abs(num), den)
	return Fraction{num / gcdVal, den / gcdVal}
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	
	// Read all tokens
	var allTokens []string
	for scanner.Scan() {
		line := scanner.Text()
		allTokens = append(allTokens, strings.Fields(line)...)
	}
	
	if len(allTokens) == 0 {
		fmt.Println("0 1")
		return
	}
	
	n, err := strconv.Atoi(allTokens[0])
	if err != nil || n < 0 || n > 20 {
		return
	}
	
	fractions := make([]Fraction, n)
	idx := 1
	
	for i := 0; i < n; i++ {
		p, _ := strconv.Atoi(allTokens[idx])
		q, _ := strconv.Atoi(allTokens[idx+1])
		fractions[i] = NewFraction(int64(p), int64(q))
		idx += 2
	}
	
	var result Fraction
	if n > 0 {
		result = fractions[0]
		for i := 1; i < n; i++ {
			result = add(result, fractions[i])
		}
	} else {
		result = NewFraction(0, 1)
	}
	
	fmt.Printf("%d %d\n", result.num, result.den)
}