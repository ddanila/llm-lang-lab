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
	
	// Read N and Q
	line1, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	
	// Parse first line for N and Q
	fields := strings.Fields(line1)
	if len(fields) < 2 {
		return
	}
	
	n, err := strconv.Atoi(fields[0])
	if err != nil {
		return
	}
	
	q, err := strconv.Atoi(fields[1])
	if err != nil {
		return
	}
	
	// If Q is 0, output nothing and exit
	if q == 0 {
		return
	}
	
	// Read the array elements
	array := make([]int64, n)
	for i := 0; i < n; i++ {
		line2, err := reader.ReadString('\n')
		if err != nil {
			return
		}
		
		fields = strings.Fields(line2)
		// Handle case where array elements might be on multiple lines or same line
		idx := 0
		for idx < len(fields) && i < n {
			val, _ := strconv.ParseInt(fields[idx], 10, 64)
			array[i] = val
			i++
			idx++
		}
		
		// If we didn't get enough elements on this line, read more lines
		for i < n {
			line2, err := reader.ReadString('\n')
			if err != nil {
				break
			}
			fields = strings.Fields(line2)
			for idx := 0; idx < len(fields) && i < n; idx++ {
				val, _ := strconv.ParseInt(fields[idx], 10, 64)
				array[i] = val
				i++
			}
		}
	}
	
	// Read Q queries
	for j := 0; j < q; j++ {
		line3, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		
		fields = strings.Fields(line3)
		for _, field := range fields {
			x, _ := strconv.ParseInt(field, 10, 64)
			
			// Find first element >= x using binary search (since array is sorted)
			// Using linear scan since N <= 200 is small enough
			index := -1
			for k := 0; k < n; k++ {
				if array[k] >= x {
					index = k
					break
				}
			}
			
			if index == -1 {
				fmt.Println(n)
			} else {
				fmt.Println(index)
			}
		}
	}
}