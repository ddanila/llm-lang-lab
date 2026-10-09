package main

import (
	"bufio"
	"fmt"
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
	sc := bufio.NewScanner(strings.NewReader(""))
	
	var sumN int64 = 0
	var sumD int64 = 1
	
	if !sc.Scan() {
		fmt.Println("0 1")
		return
	}
	
	n, _ := strconv.ParseInt(sc.Text(), 10, 64)
	
	for i := 0; i < int(n); i++ {
		sc.Scan()
		p, _ := strconv.ParseInt(sc.Text(), 10, 64)
		sc.Scan()
		q, _ := strconv.ParseInt(sc.Text(), 10, 64)
		
		// sum = sumN/sumD + p/q = (sumN*q + p*sumD) / (sumD*q)
		sumN = sumN*q + p*sumD
		sumD = sumD * q
		
		sumN, sumD = reduce(sumN, sumD)
	}
	
	fmt.Printf("%d %d\n", sumN, sumD)
}

import "strconv"