package main

import (
	"fmt"
	"math/big"
)

func main() {
	var n int64
	fmt.Fscan(&n)
	if n < 0 || n > 20 {
		return
	}

	num := big.NewInt(0)
	den := big.NewInt(1)

	for i := int64(0); i < n; i++ {
		var p, q int64
		fmt.Fscan(&p, &q)

		// Add p/q to num/den: new_num = num*q + p*den, new_den = den*q
		newDen := big.NewInt(int64(q))
		newNum := new(big.Int).Mul(num, newDen)
		newNum.Add(newNum, new(big.Int).Mul(big.NewInt(p), den))

		// Reduce the fraction by dividing both by their GCD
		gcd := new(big.Int).Gcd(nil, num, newDen) // This is incorrect; need to compute gcd of newNum and newDen
		gcd = new(big.Int).Gcd(nil, newNum, newDen)

		newNum.Div(newNum, gcd)
		newDen.Div(newDen, gcd)

		num.Set(newNum)
		den.Set(newDen)
	}

	fmt.Println(num.String(), den.String())
}