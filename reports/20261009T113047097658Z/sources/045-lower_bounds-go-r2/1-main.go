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
	
	// Read all input into a single string and tokenize
	input, _ := reader.ReadString('\n')
	tokens := strings.Fields(input)
	
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
	a := make([]int64, n)
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