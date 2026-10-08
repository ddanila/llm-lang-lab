package main

import (
	"fmt"
	"strconv"
	"strings"
)

type Fraction struct {
	num, den int64
}

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func reduce(f Fraction) Fraction {
	if f.den == 0 {
		panic("denominator cannot be zero")
	}
	g := gcd(f.num, f.den)
	f.num /= g
	f.den /= g
	if f.den < 0 {
		f.num = -f.num
		f.den = -f.den
	}
	return f
}

func main() {
	input := readAll()
	tokens := strings.Fields(input)
	idx := 0
	if idx >= len(tokens) {
		fmt.Println("0 1")
		return
	}
	N, _ := strconv.Atoi(tokens[idx])
	idx++

	sum := Fraction{0, 1}
	for i := 0; i < N; i++ {
		if idx+1 >= len(tokens) {
			break
		}
		p, _ := strconv.Atoi(tokens[idx])
		q, _ := strconv.Atoi(tokens[idx+1])
		idx += 2

		f := Fraction{int64(p), int64(q)}
		f = reduce(f)

		sum.num = sum.num*f.den + f.num*sum.den
		sum.den = sum.den * f.den
		sum = reduce(sum)
	}

	fmt.Printf("%d %d\n", sum.num, sum.den)
}

func readAll() string {
	var s strings.Builder
	for {
		c, _, err := runeRead(s.Len())
		if err != nil {
			return s.String()
		}
		s.WriteRune(c)
	}
}

func runeRead(n int) (rune, int, error) {
	panic("not implemented")
}