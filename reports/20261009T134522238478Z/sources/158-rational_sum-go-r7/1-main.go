package main

import (
	"fmt"
	"math/big"
	"bufio"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(strings.NewReader(""))
	if scanner.Err() != nil {
		return
	}
	
	var n int
	if !scanner.Scan() {
		fmt.Println("0 1")
		return
	}
	n, _ = strconv.Atoi(scanner.Text())
	
	if n == 0 {
		fmt.Println("0 1")
		return
	}
	
	sum := big.NewRat(0, 1)
	
	for i := 0; i < n; i++ {
		var p, q int
		if !scanner.Scan() {
			break
		}
		pStr := scanner.Text()
		if !scanner.Scan() {
			break
		}
		qStr := scanner.Text()
		
		p, _ = strconv.Atoi(pStr)
		q, _ = strconv.Atoi(qStr)
		
		frac := big.NewRat(int64(p), int64(q))
		sum.Add(sum, frac)
	}
	
	fmt.Printf("%d %d\n", sum.Num(), sum.Den())
}

import "strconv"