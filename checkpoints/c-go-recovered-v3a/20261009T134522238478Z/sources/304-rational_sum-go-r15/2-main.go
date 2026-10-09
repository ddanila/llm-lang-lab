package main

import (
	"fmt"
	"strconv"
	"strings"
)

type Fraction struct {
	num   int64
	den   int64
}

func abs(x int64) int64 {
	if x < 0 {
		return -x
	}
	return x
}

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func NewFraction(p, q int64) Fraction {
	gcdVal := gcd(abs(p), q)
	return Fraction{p / gcdVal, q / gcdVal}
}

func add(f1, f2 Fraction) Fraction {
	num := f1.num*f2.den + f2.num*f1.den
	den := f1.den * f2.den
	gcdVal := gcd(abs(num), den)
	return Fraction{num / gcdVal, den / gcdVal}
}

func main() {
	input := readAll()
	
	if input == "" {
		fmt.Println("0 1")
		return
	}
	
	tokens := strings.Fields(input)
	if len(tokens) == 0 {
		fmt.Println("0 1")
		return
	}
	
	n, err := strconv.Atoi(tokens[0])
	if err != nil || n < 0 || n > 20 {
		return
	}
	
	fractions := make([]Fraction, n)
	idx := 1
	
	for i := 0; i < n; i++ {
		p, _ := strconv.Atoi(tokens[idx])
		q, _ := strconv.Atoi(tokens[idx+1])
		fractions[i] = NewFraction(int64(p), int64(q))
		idx += 2
	}
	
	var result Fraction
	if n > 0 {
		result = fractions[0]
		for i := 1; i < n; i++ {
			result = add(result, fractions[i])
		}
	} else {
		result = NewFraction(0, 1)
	}
	
	fmt.Printf("%d %d\n", result.num, result.den)
}

func readAll() string {
	var sb strings.Builder
	for {
		line, err := readLine()
		if err != nil || line == "" {
			break
		}
		sb.WriteString(line)
		sb.WriteByte('\n')
	}
	return sb.String()
}

func readLine() (string, error) {
	var buf [1024]byte
	n := 0
	for {
		c, err := readByte(&buf[n])
		if c != -1 {
			buf[n] = byte(c)
			n++
		} else if err == nil {
			break
		} else {
			return "", err
		}
	}
	
	var s strings.Builder
	s.Write(buf[:n])
	return s.String(), nil
}

func readByte(buf []byte) (int, error) {
	// This is getting too complicated
	return -1, fmt.Errorf("not implemented")
}