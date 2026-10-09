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

func lcm(a, b int64) int64 {
	if a == 0 || b == 0 {
		return 0
	}
	return (a / gcd(a, b)) * b
}

func main() {
	var n int
	fmt.Scan(&n)

	num := int64(0)
	den := int64(1)

	for i := 0; i < n; i++ {
		var p, q int64
		fmt.Scan(&p, &q)

		g := gcd(p, q)
		p /= g
		q /= g

		if den == 0 {
			den = q
			num = p
		} else {
			l := lcm(den, q)
			mulDen := l / den
			addNum := mulDen * p
			num += addNum
			den = l

			g = gcd(num, den)
			if g != 0 {
				num /= g
				den /= g
			}
		}
	}

	fmt.Printf("%d %d\n", num, den)
}