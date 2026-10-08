package main

import (
	"bufio"
	"fmt"
	"os"
)

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func reduce(n, d int64) (int64, int64) {
	if d == 0 {
		return 0, 1
	}
	g := gcd(n, d)
	n /= g
	d /= g
	if d < 0 {
		n = -n
		d = -d
	}
	return n, d
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var numPairs int
	if !scanner.Scan() {
		fmt.Println("0 1")
		return
	}
	numPairs, _ = strconv.Atoi(scanner.Text())

	var num, den int64 = 0, 1

	for i := 0; i < numPairs; i++ {
		if !scanner.Scan() {
			break
		}
		p, err := strconv.ParseInt(scanner.Text(), 10, 64)
		if err != nil {
			continue
		}
		if !scanner.Scan() {
			break
		}
		q, err := strconv.ParseInt(scanner.Text(), 10, 64)
		if err != nil {
			continue
		}

		newNum := p*den + num*q
		newDen := den * q
		num, den = reduce(newNum, newDen)
	}

	fmt.Printf("%d %d\n", num, den)
}