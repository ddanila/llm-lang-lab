package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Fraction struct {
	num   int64
	den   int64
}

func newFraction(p, q int64) Fraction {
	gcd := gcd(abs(p), q)
	return Fraction{p / gcd, q / gcd}
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

func (f Fraction) add(other Fraction) Fraction {
	num := f.num*other.den + other.num*f.den
	den := f.den * other.den
	gcdVal := gcd(abs(num), den)
	return Fraction{num / gcdVal, den / gcdVal}
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	var n int64
	fmt.Sscanf(reader.ReadString('\n'), "%d", &n)
	// Remove any trailing spaces/newlines from the line before parsing N pairs
	input := reader.ReadString('\n')
	input = strings.TrimSpace(input)
	if input != "" {
		fmt.Sscanf(input, "%d", &n)
	}

	var total Fraction
	total = newFraction(0, 1)

	for i := int64(0); i < n; i++ {
		line, err := reader.ReadString('\n')
		if err != nil || line == "" {
			break
		}
		fields := strings.Fields(line)
		if len(fields) >= 2 {
			p, _ := strconv.ParseInt(fields[0], 10, 64)
			q, _ := strconv.ParseInt(fields[1], 10, 64)
			frac := newFraction(p, q)
			total = total.add(frac)
		}
	}

	fmt.Printf("%d %d\n", total.num, total.den)
}