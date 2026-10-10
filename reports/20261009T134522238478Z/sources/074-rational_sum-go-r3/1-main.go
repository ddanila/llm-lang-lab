package main

import (
	"fmt"
	"math/big"
	"strconv"
	"strings"
)

type Fraction struct {
	num   *big.Int
	den   *big.Int
}

func NewFraction(n, d int64) Fraction {
	g := big.NewInt(0).Gcd(nil, big.NewInt(d), big.NewInt(n))
	n = n / g
	d = d / g
	if d < 0 {
		n = -n
		d = -d
	}
	return Fraction{big.NewInt(n), big.NewInt(d)}
}

func Add(f1, f2 Fraction) Fraction {
	num := new(big.Int).Mul(f1.num, f2.den)
	den := new(big.Int).Mul(f1.den, f2.den)
	g := big.NewInt(0).Gcd(nil, den, num)
	num.Div(num, g)
	den.Div(den, g)
	return Fraction{num, den}
}

func formatFraction(f Fraction) string {
	if f.num.Cmp(big.NewInt(0)) == 0 {
		return "0 1"
	}
	return fmt.Sprintf("%d %d", f.num.Int64(), f.den.Int64())
}

func main() {
	scanner := strings.NewReader("")
	// Use bufio for tokenization
	import "bufio"
	bufioScanner := bufio.NewScanner(strings.NewReader(""))
	if !bufioScanner.Scan() {
		return
	}
	s := bufioScanner.Text()
	
	var n int64
	fmt.Sscanf(s, "%d", &n)
	
	var sum Fraction
	for i := int64(0); i < n; i++ {
		bufioScanner.Scan()
		tokens := strings.Fields(bufioScanner.Text())
		if len(tokens) >= 2 {
			p, _ := strconv.ParseInt(tokens[0], 10, 64)
			q, _ := strconv.ParseInt(tokens[1], 10, 64)
			sum = Add(sum, NewFraction(p, q))
		}
	}
	
	fmt.Println(formatFraction(sum))
}