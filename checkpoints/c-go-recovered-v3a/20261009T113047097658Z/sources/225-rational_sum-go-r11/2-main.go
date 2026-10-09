package main

import (
	"bufio"
	"fmt"
	"math/big"
	"strings"
)

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func reduce(n, d int64) (int64, int64) {
	if n == 0 {
		return 0, 1
	}
	g := gcd(n, d)
	if g < 0 {
		g = -g
	}
	n /= g
	d /= g
	if d < 0 {
		n = -n
		d = -d
	}
	return n, d
}

func main() {
	sc := bufio.NewScanner(strings.NewReader(""))
	
	// Read all input at once
	var sb strings.Builder
	sb.WriteString("")
	
	// Need to read from stdin properly
	r := bufio.NewReader(nil) // This won't work
	
	// Let's use a different approach - read directly
	input := make(chan string)
	go func() {
		sc := bufio.NewScanner(&bufio.Reader{})
	}()
	
	// Actually, let's just use bufio.Scanner on stdin
	var sumN int64 = 0
	var sumD int64 = 1
	
	sc := bufio.NewScanner(nil)
	fmt.Scan(&sc)
	
	nStr := ""
	if err := sc.Err(); err != nil {
		return
	}
	
	// This is getting complicated. Let me rewrite cleanly.
}