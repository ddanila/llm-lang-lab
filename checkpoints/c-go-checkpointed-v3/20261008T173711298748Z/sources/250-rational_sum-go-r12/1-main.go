package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Fraction struct {
	n, d int64
}

func reduce(f Fraction) Fraction {
	if f.d == 0 {
		return Fraction{1, 1}
	}
	gcd := gcdAbs(f.n, f.d)
	f.n /= gcd
	f.d /= gcd
	if f.d < 0 {
		f.n = -f.n
		f.d = -f.d
	}
	return f
}

func gcdAbs(a, b int64) int64 {
	a = abs(a)
	b = abs(b)
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
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		fmt.Println("0 1")
		return
	}
	s := strings.TrimSpace(scanner.Text())
	if s == "" {
		fmt.Println("0 1")
		return
	}
	n, _ := strconv.Atoi(s)

	var sum Fraction = Fraction{0, 1}

	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		tokens := strings.Fields(scanner.Text())
		if len(tokens) < 2 {
			break
		}
		p, _ := strconv.Atoi(tokens[0])
		q, _ := strconv.Atoi(tokens[1])

		f := Fraction{int64(p), int64(q)}
		sum = add(sum, f)
	}

	fmt.Printf("%d %d\n", sum.n, sum.d)
}

func add(a, b Fraction) Fraction {
	num := a.n*b.d + b.n*a.d
	den := a.d * b.d
	return reduce(Fraction{num, den})
}