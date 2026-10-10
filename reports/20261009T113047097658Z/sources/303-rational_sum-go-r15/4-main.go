package main

import (
	"bufio"
	"fmt"
	"math/big"
	"os"
	"strconv"
	"strings"
)

func gcd(a, b *big.Int) *big.Int {
	for b.Cmp(big.NewInt(0)) != 0 {
		a, b = b, a.Mod(a, b)
	}
	return a
}

func abs(i *big.Int) *big.Int {
	if i.Sign() < 0 {
		return i.Neg(i)
	}
	return i
}

type Fraction struct {
	num *big.Int
	den *big.Int
}

func NewFraction(n, d int64) Fraction {
	if d == 0 {
		panic("division by zero")
	}
	gcdVal := gcd(new(big.Int).Abs(big.NewInt(n)), new(big.Int).Abs(big.NewInt(d)))
	num := big.NewInt(0).Div(abs(big.NewInt(n)), gcdVal)
	den := big.NewInt(0).Div(abs(big.NewInt(d)), gcdVal)
	if n < 0 {
		num.Neg(num)
	}
	return Fraction{num: num, den: den}
}

func Add(f1, f2 Fraction) Fraction {
	n := new(big.Int).Mul(f1.num, f2.den)
	d := new(big.Int).Mul(f1.den, f2.den)
	gcdVal := gcd(n, d)
	num := new(big.Int).Div(n, gcdVal)
	den := new(big.Int).Div(d, gcdVal)
	if num.Sign() < 0 {
		num.Neg(num)
	}
	return Fraction{num: num, den: den}
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	var s strings.Builder
	buf := make([]byte, 1024)
	
	for {
		n, err := reader.Read(buf)
		if n > 0 {
			s.Write(buf[:n])
		}
		if err != nil {
			break
		}
	}
	
	input := s.String()
	parts := strings.Fields(input)
	if len(parts) == 0 {
		fmt.Println("0 1")
		return
	}
	
	n, _ := strconv.Atoi(parts[0])
	
	var sumNum big.Int
	sumDen := big.NewInt(1)
	
	idx := 1
	for i := 0; i < n; i++ {
		if idx+1 >= len(parts) {
			break
		}
		p, _ := strconv.Atoi(parts[idx])
		q, _ := strconv.Atoi(parts[idx+1])
		idx += 2
		
		fracNum := big.NewInt(int64(p))
		fracDen := big.NewInt(int64(q))
		
		sum := new(big.Int)
		sum.Mul(sum, fracDen)
		sum.Add(sum, fracNum)
		
		gcdVal := gcd(sum, fracDen)
		sum.Div(sum, gcdVal)
		fracDen.Div(fracDen, gcdVal)
		
		sumNum = *sum
		sumDen = *fracDen
	}
	
	fmt.Printf("%d %d\n", sumNum.Int64(), sumDen.Int64())
}
