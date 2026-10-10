package main

import (
	"fmt"
	"math/big"
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
	input := strings.TrimSpace(fmt.Fscan(&input)) // placeholder, will use different approach
	// Actually, let's read from stdin properly
	reader := bufio.NewReader(os.Stdin)
	
	var nStr string
	if _, err := reader.ReadString('\n'); err != nil && err == io.EOF {
		// Handle case with no input
	}
	
	// Better approach: read all tokens
	data := make([]string, 0)
	buf := make([]byte, 1024)
	for {
		n, _ := reader.Read(buf)
		if n == 0 {
			break
		}
		data = append(data, string(buf[:n]))
	}
	
	// Actually simpler: use fmt.Scan directly
	var input []string
	_, err := fmt.Fscan(os.Stdin, &input...)
	if err != nil {
		fmt.Println("0 1")
		return
	}
	
	if len(input) == 0 {
		fmt.Println("0 1")
		return
	}
	
	n, _ := strconv.ParseInt(input[0], 10, 64)
	
	var num, den int64 = 0, 1
	
	for i := 1; i <= n*2; i += 2 {
		p, _ := strconv.ParseInt(input[i], 10, 64)
		q, _ := strconv.ParseInt(input[i+1], 10, 64)
		
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
	
	fmt.Printf("%d %d\n", num, den)
}