package main

import (
	"bufio"
	"fmt"
	"io"
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
	reader := bufio.NewReader(os.Stdin)
	
	var nStr string
	if _, err := reader.ReadString('\n'); err == nil || err != io.EOF {
		// Read first line
		line1, _ := reader.ReadString('\n')
		nStr = strings.TrimSpace(line1)
		
		if nStr == "" {
			fmt.Println("0 1")
			return
		}
		
		n, _ := strconv.ParseInt(nStr, 10, 64)
		
		var num, den int64 = 0, 1
		
		for i := 0; i < n; i++ {
			line2, _ := reader.ReadString('\n')
			parts := strings.Fields(line2)
			if len(parts) >= 2 {
				p, _ := strconv.ParseInt(parts[0], 10, 64)
				q, _ := strconv.ParseInt(parts[1], 10, 64)
				
				// num/den + p/q = (num*q + p*den) / (den*q)
				newNum := num*q + p*den
				newDen := den*q
				
				g := gcd(newNum, newDen)
				if g < 0 {
					g = -g
				}
				
				num = newNum / g
				den = newDen / g
				
				// Ensure denominator is positive
				if den < 0 {
					num = -num
					den = -den
				}
			}
		}
		
		fmt.Printf("%d %d\n", num, den)
		return
	}
	
	// Handle empty input case
	fmt.Println("0 1")
}