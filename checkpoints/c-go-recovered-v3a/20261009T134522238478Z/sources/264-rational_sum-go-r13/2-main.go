package main

import (
	"fmt"
	"strconv"
	"strings"
)

func gcd(a, b int64) int64 {
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

func reduce(num, den int64) (int64, int64) {
	if num == 0 {
		return 0, 1
	}
	g := gcd(num, den)
	return num / g, den / g
}

func main() {
	var input string
	fmt.Scanln(&input)
	
	tokens := strings.Fields(input)
	idx := 0
	
	if idx >= len(tokens) {
		fmt.Println("0 1")
		return
	}
	
	n, _ := strconv.ParseInt(tokens[idx], 10, 64)
	idx++
	
	var num, den int64 = 0, 1
	
	for i := 0; i < int(n); i++ {
		if idx+1 >= len(tokens) {
			break
		}
		
		p, _ := strconv.ParseInt(tokens[idx], 10, 64)
		q, _ := strconv.ParseInt(tokens[idx+1], 10, 64)
		idx += 2
		
		// Add p/q to num/den: new_num = num*q + p*den, new_den = den*q
		newNum := num*q + p*den
		newDen := den*q
		
		num, den = reduce(newNum, newDen)
	}
	
	fmt.Println(num, den)
}