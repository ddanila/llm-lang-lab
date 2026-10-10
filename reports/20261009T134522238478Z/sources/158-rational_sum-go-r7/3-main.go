package main

import (
	"bufio"
	"fmt"
	"math/big"
)

func main() {
	reader := bufio.NewReader("")
	
	var n int
	if _, err := fmt.Fscanf(reader, "%d", &n); err != nil {
		fmt.Println("0 1")
		return
	}
	
	if n == 0 {
		fmt.Println("0 1")
		return
	}
	
	sum := big.NewRat(0, 1)
	
	for i := 0; i < n; i++ {
		var p, q int
		fmt.Fscanf(reader, "%d %d", &p, &q)
		
		frac := big.NewRat(int64(p), int64(q))
		sum.Add(sum, frac)
	}
	
	fmt.Printf("%d %d\n", sum.Num(), sum.Den())
}