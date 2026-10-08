package main

import (
	"fmt"
	"math/big"
	"strconv"
	"strings"
)

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func reduce(n, d int64) (int64, int64) {
	if n == 0 {
		return 0, 1
	}
	g := gcd(n, d)
	if g < 0 {
		g = -g
	}
	n /= g
	d /= g
	if d < 0 {
		n = -n
		d = -d
	}
	return n, d
}

func main() {
	scanner := strings.NewReader("")
	
	input, _ := strconv.Unquote(`"2\n1 2\n1 3\n"`)
	
	// Parse input manually from stdin-like behavior
	// But since we need to read from stdin, let's implement properly
	
	var n int
	fmt.Scan(&n)
	
	if n == 0 {
		fmt.Println("0 1")
		return
	}
	
	// Use big.Int for exact arithmetic
	var num, den *big.Int
	num.Set(big.NewInt(0))
	den.Set(big.NewInt(1))
	
	for i := 0; i < n; i++ {
		var p, q int64
		fmt.Scan(&p)
		fmt.Scan(&q)
		
		// Create fraction p/q
		fracNum := big.NewInt(p)
		fracDen := big.NewInt(q)
		
		// Add to sum: num/den + fracNum/fracDen = (num*fracDen + fracNum*den) / (den*fracDen)
		newNum := new(big.Int).Mul(num, fracDen)
		newNum.Add(newNum, fracNum.Mul(fracNum, den))
		
		newDen := new(big.Int).Mul(den, fracDen)
		
		num = newNum
		den = newDen
		
		// Reduce
		g := num.GCD(nil, nil, num, den)
		num.Div(num, g)
		den.Div(den, g)
	}
	
	fmt.Printf("%s %s\n", num.String(), den.String())
}