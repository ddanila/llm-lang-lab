package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	// Read all input line by line until EOF
	var tokens []string
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		tokens = append(tokens, strings.Fields(line)...)
	}
	
	if len(tokens) == 0 {
		return
	}
	
	idx := 0
	
	// Read N
	n, _ := strconv.Atoi(tokens[idx])
	idx++
	
	// Read Q
	q, _ := strconv.Atoi(tokens[idx])
	idx++
	
	// If Q is 0, output nothing and exit
	if q == 0 {
		return
	}
	
	// Read N integers into a slice
	a := make([]int, n)
	for i := 0; i < n; i++ {
		a[i], _ = strconv.Atoi(tokens[idx])
		idx++
	}
	
	// Process Q queries
	for i := 0; i < q; i++ {
		x, _ := strconv.Atoi(tokens[idx])
		idx++
		
		// Binary search for the first element >= x
		low := 0
		high := n - 1
		result := n // Default if not found
		
		for low <= high {
			mid := low + (high-low)/2
			if a[mid] >= x {
				result = mid
				high = mid - 1
			} else {
				low = mid + 1
			}
		}
		
		fmt.Println(result)
	}
}