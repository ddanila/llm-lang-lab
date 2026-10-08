package main

import (
	"bufio"
	"fmt"
	"math/big"
	"os"
	"strconv"
	"strings"
)

type Fraction struct {
	numerator   *big.Int
	denominator *big.Int
}

func NewFraction(n, d int64) Fraction {
	return Fraction{
		numerator:   big.NewInt(n),
		denominator: big.NewInt(d),
	}
}

func (f Fraction) Reduce() Fraction {
	if f.denominator.Sign() == 0 {
		panic("division by zero")
	}

	neg := false
	if f.numerator.Sign() < 0 {
		neg = !neg
		f.numerator.Neg(f.numerator)
	}
	if f.denominator.Sign() < 0 {
		neg = !neg
		f.denominator.Neg(f.denominator)
	}

	if neg {
		f.numerator.Neg(f.numerator)
		f.denominator.Neg(f.denominator)
	}

	gcd := new(big.Int).GCD(nil, nil, f.numerator, f.denominator)
	f.numerator.Div(f.numerator, gcd)
	f.denominator.Div(f.denominator, gcd)

	return f
}

func (f Fraction) Add(other Fraction) Fraction {
	n1, d1 := f.numerator, f.denominator
	n2, d2 := other.numerator, other.denominator

	// a/b + c/d = (ad + bc) / bd
	num := new(big.Int).Mul(n1, d2)
	den := new(big.Int).Mul(d1, d2)
	sumNum := new(big.Int).Add(num, new(big.Int).Mul(n2, d1))

	return Fraction{numerator: sumNum, denominator: den}.Reduce()
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	// Read all input from stdin
	var s strings.Builder
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		s.WriteString(line[:len(line)-1])
		s.WriteRune('\n')
	}

	tokens := strings.Fields(s.String())

	if len(tokens) == 0 {
		fmt.Println("0 1")
		return
	}

	N, _ := strconv.ParseInt(tokens[0], 10, 64)
	idx := 1

	var sumFrac Fraction = NewFraction(0, 1)

	for i := int64(0); i < N; i++ {
		if idx >= len(tokens) {
			break
		}
		p, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++
		if idx >= len(tokens) {
			break
		}
		q, _ := strconv.ParseInt(tokens[idx], 10, 64)
		idx++

		frac := NewFraction(p, q)
		sumFrac = sumFrac.Add(frac)
	}

	fmt.Printf("%d %d\n", sumFrac.numerator.Int64(), sumFrac.denominator.Int64())
}