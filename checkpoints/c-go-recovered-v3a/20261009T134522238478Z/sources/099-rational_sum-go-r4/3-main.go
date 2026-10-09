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
	return Fraction{num: n / gcdVal, den: d / gcdVal}
}

func (f *Fraction) Add(other Fraction) {
	f.num = f.num*other.den + other.num*f.den
	f.den = f.den * other.den
	gcdVal := gcd(abs(f.num), abs(f.den))
	f.num /= gcdVal
	f.den /= gcdVal
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
	
	// Read remaining lines if any
	allInput := input
	remaining, err := reader.ReadString('\n')
	if err == nil {
		allInput += remaining
	}
	tokens := strings.Fields(allInput)
	
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
		if idx >= len(tokens) {
			break
		}
		q, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++
		sum.Add(newFraction(p, q))
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}