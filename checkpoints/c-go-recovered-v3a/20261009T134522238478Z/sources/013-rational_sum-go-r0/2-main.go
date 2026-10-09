package main

import (
	"fmt"
)

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func reduce(n, d int64) (int64, int64) {
	if d == 0 {
		return n, 1
	}
	g := gcd(n, d)
	return n / g, d / g
}

func main() {
	var n int
	fmt.Scan(&n)

	num := int64(0)
	den := int64(1)

	for i := 0; i < n; i++ {
		var p, q int64
		fmt.Scan(&p, &q)

		newNum := num*q + p*den
		newDen := den * q

		g := gcd(newNum, newDen)
		num = newNum / g
		den = newDen / g
	}

	if num == 0 {
		fmt.Println("0 1")
	} else if num > 0 {
		fmt.Printf("%d %d\n", num, den)
	} else {
		fmt.Printf("%d %d\n", num, den)
	}
}