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

func newFraction(p, q int64) Fraction {
	if q == 0 {
		q = 1
	}
	gcd := gcd(abs(p), abs(q))
	return Fraction{p / gcd, q / gcd}
}

func (f Fraction) Add(other Fraction) Fraction {
	n := f.num*other.den + other.num*f.den
	d := f.den * other.den
	gcd := gcd(abs(n), abs(d))
	return Fraction{n / gcd, d / gcd}
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
	if !scanner.Scan() {
		fmt.Println("0 1")
		return
	}
	
	input := scanner.Text()
	tokens := strings.Fields(input)
	
	idx := 0
	if len(tokens) == 0 {
		fmt.Println("0 1")
		return
	}
	
	n, err := strconv.Atoi(tokens[idx])
	if err != nil {
		fmt.Println("0 1")
		return
	}
	idx++
	
	var sum Fraction
	
	for i := 0; i < n; i++ {
		if idx >= len(tokens) {
			break
		}
		p, err := strconv.Atoi(tokens[idx])
		if err != nil {
			fmt.Println("0 1")
			return
		}
		idx++
		
		q, err := strconv.Atoi(tokens[idx])
		if err != nil {
			fmt.Println("0 1")
			return
		}
		idx++
		
		frac := newFraction(int64(p), int64(q))
		sum = sum.Add(frac)
	}
	
	fmt.Printf("%d %d\n", sum.num, sum.den)
}