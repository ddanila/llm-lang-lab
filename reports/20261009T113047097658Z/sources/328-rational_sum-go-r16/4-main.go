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
	input := scanner.Text()
	if input == "" {
		fmt.Println("0 1")
		return
	}
	parts := strings.Fields(input)
	if len(parts) == 0 {
		fmt.Println("0 1")
		return
	}

	n, _ := strconv.ParseInt(parts[0], 10, 64)

	num := int64(0)
	den := int64(1)

	idx := 1
	for i := int64(0); i < n; i++ {
		if idx >= len(parts) {
			break
		}
		p, _ := strconv.ParseInt(parts[idx], 10, 64)
		q, _ := strconv.ParseInt(parts[idx+1], 10, 64)
		idx += 2

		fmt.Printf("DEBUG: Adding %d/%d to %d/%d\n", p, q, num, den)
		
		// Add p/q to num/den: new_num = num*q + p*den, new_den = den*q
		newNum := num*q + p*den
		newDen := den * q

		fmt.Printf("DEBUG: newNum=%d, newDen=%d\n", newNum, newDen)

		g := gcd(newNum, newDen)
		if g < 0 {
			g = -g
		}

		num = newNum / g
		den = newDen / g

		fmt.Printf("DEBUG: Result num=%d, den=%d\n", num, den)
	}

	fmt.Printf("%d %d\n", num, den)
}