package main

import (
	"fmt"
	"math/big"
	"regexp"
	"strconv"
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
	var sc *Scanner
	sc = &Scanner{}
	
	// Read N
	s := sc.next()
	if s == "" {
		return
	}
	n, _ := strconv.ParseInt(s, 10, 64)
	
	sumN := int64(0)
	sumD := int64(1)
	
	for i := 0; i < int(n); i++ {
		pStr := sc.next()
		qStr := sc.next()
		
		p, _ := strconv.ParseInt(pStr, 10, 64)
		q, _ := strconv.ParseInt(qStr, 10, 64)
		
		// sum = sumN/sumD + p/q = (sumN*q + p*sumD) / (sumD*q)
		// Use big.Int for intermediate calculation to avoid overflow
		bn := big.NewInt(sumN)
		bd := big.NewInt(sumD)
		bp := big.NewInt(p)
		bq := big.NewInt(q)
		
		bnum := new(big.Int).Mul(bn, bq)
		bden := new(big.Int).Mul(bd, bq)
		
		addTerm := new(big.Int).Mul(bp, bd)
		bnum.Add(bnum, addTerm)
		
		sumN = bnum.Int64()
		sumD = bd.Int64()
		
		// Reduce
		sumN, sumD = reduce(sumN, sumD)
	}
	
	fmt.Printf("%d %d\n", sumN, sumD)
}

type Scanner struct{}

func (s *Scanner) next() string {
	var buf [1024]byte
	for {
		if len(s.buffer) == 0 {
			s.buffer = s.readNextLine()
			if s.buffer == nil {
				return ""
			}
		}
		
		re := regexp.MustCompile(`\S+`)
		matches := re.FindAllString(s.buffer, -1)
		if len(matches) > 0 {
			s.buffer = strings.Join(matches[1:], "")
			return matches[0]
		}
		s.buffer = ""
	}
}

func (s *Scanner) readNextLine() string {
	// This is a simplified approach - we need to read from stdin directly
	// Since we can't use bufio.Scanner properly without more complex setup,
	// let's use a different approach
	return ""
}

import "strings"