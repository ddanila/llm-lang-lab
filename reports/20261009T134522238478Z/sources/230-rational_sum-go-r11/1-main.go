package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		fmt.Println("0 1")
		return
	}
	line := strings.TrimSpace(scanner.Text())
	if line == "" {
		fmt.Println("0 1")
		return
	}
	n, err := strconv.Atoi(line)
	if err != nil || n < 0 {
		fmt.Println("0 1")
		return
	}

	numerator := int64(0)
	denominator := int64(1)

	for i := 0; i < n; i++ {
		if !scanner.Scan() {
			break
		}
		fields := strings.Fields(scanner.Text())
		if len(fields) < 2 {
			break
		}
		p, err := strconv.ParseInt(fields[0], 10, 64)
		if err != nil {
			continue
		}
		q, err := strconv.ParseInt(fields[1], 10, 64)
		if err != nil {
			continue
		}

		g := gcd(q, denominator)
		denominator = denominator / g
		numerator = numerator*q + p*denominator

		g = gcd(numerator, denominator)
		numerator /= g
		denominator /= g
	}

	if numerator == 0 {
		fmt.Println("0 1")
	} else if denominator < 0 {
		numerator = -numerator
		denominator = -denominator
	}
	fmt.Printf("%d %d\n", numerator, denominator)
}