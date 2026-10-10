package main

import (
	"bufio"
	"fmt"
	"math/big"
)

type Fraction struct {
	num *big.Int
	den *big.Int
}

func NewFraction(n, d int64) Fraction {
	if d == 0 {
		panic("division by zero")
	}
	gcd := new(big.Int).GCD(nil, nil, new(big.Int).Abs(new(big.Int).Int64(n)), new(big.Int).Abs(new(big.Int).Int64(d)))
	num := new(big.Int).Div(new(big.Int).Abs(new(big.Int).Int64(n)), gcd)
	den := new(big.Int).Div(new(big.Int).Abs(new(big.Int).Int64(d)), gcd)
	if n < 0 {
		num.Neg(num)
	}
	return Fraction{num: num, den: den}
}

func Add(f1, f2 Fraction) Fraction {
	n := new(big.Int).Mul(f1.num, f2.den)
	d := new(big.Int).Mul(f1.den, f2.den)
	gcd := new(big.Int).GCD(nil, nil, n, d)
	num := new(big.Int).Div(n, gcd)
	den := new(big.Int).Div(d, gcd)
	if num.Sign() < 0 {
		num.Neg(num)
	}
	return Fraction{num: num, den: den}
}

func main() {
	scanner := bufio.NewScanner(&runeReader{})
	
	var n int
	fmt.Fscanf(&scanner, "%d", &n)
	
	var sumNum, sumDen big.Int
	sumNum.SetInt64(0)
	sumDen.SetInt64(1)
	
	for i := 0; i < n; i++ {
		var p, q int
		fmt.Fscanf(&scanner, "%d %d", &p, &q)
		
		frac := NewFraction(int64(p), int64(q))
		sum := Add(sumNum, frac.num, sumDen, frac.den)
		sumNum = sum.num
		sumDen = sum.den
	}
	
	fmt.Printf("%d %d\n", sumNum.Int64(), sumDen.Int64())
}

type runeReader struct{}

func (r *runeReader) Read(p []byte) (n int, err error) {
	return 0, fmt.Errorf("not implemented")
}
