package main

import (
	"fmt"
	"math/big"
)

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
	scanner := bufio.NewReader(os.Stdin)
	
	var n int
	fmt.Fscan(scanner, &n)
	
	var sumN, sumD big.Int
	sumN.SetInt64(0)
	sumD.SetInt64(1)
	
	for i := 0; i < n; i++ {
		var p, q int
		fmt.Fscan(scanner, &p, &q)
		
		// Convert to big.Int for calculation
		pBig := big.NewInt(int64(p))
		qBig := big.NewInt(int64(q))
		
		// sum = sum + p/q => sumN/sumD + p/q = (sumN*q + p*sumD) / (sumD*q)
		tmp1 := new(big.Int).Mul(&sumN, qBig)
		tmp2 := new(big.Int).Mul(pBig, &sumD)
		tmp1.Add(tmp1, tmp2)
		
		den := new(big.Int).Mul(&sumD, qBig)
		
		gcdVal := gcd(sumN.Int64(), den.Int64())
		if gcdVal == 0 {
			gcdVal = 1
		}
		
		sumN.Div(tmp1, big.NewInt(gcdVal))
		sumD.Div(den, big.NewInt(gcdVal))
	}
	
	fmt.Println(sumN.String(), sumD.String())
}