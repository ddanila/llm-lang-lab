package main

import (
	"fmt"
	"math/big"
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
	// Read all input from stdin
	var s strings.Builder
	for {
		line, err := readLine()
		if err != nil || line == "" {
			break
		}
		s.WriteString(line)
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

func readLine() (string, error) {
	var buf [65536]byte
	n, err := read(buf[:])
	if n > 0 && buf[n-1] == '\n' {
		return string(buf[:n]), nil
	}
	if n > 0 && buf[n-1] == '\r' {
		return string(buf[:n-1]), nil
	}
	if n > 0 {
		return string(buf[:n]), nil
	}
	return "", err
}

func read(b []byte) (int, error) {
	n := 0
	for {
		select {
		case <-readStdinChan:
			n = len(readBuf)
			copy(b, readBuf[:n])
			readBuf = readBuf[n:]
			return n, nil
		default:
			// Try to read one byte at a time using syscall or just use bufio
			// Since we can't use blocking reads easily without proper setup,
			// let's use a simpler approach with os.Stdin
		}
	}
}

func init() {
	// Use a simple buffered reader for stdin
}