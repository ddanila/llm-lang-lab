package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	if !scanner.Scan() {
		return
	}
	
	fields := []string{}
	for _, s := range scanner.Split("") {
		fields = append(fields, s)
	}
	
	// Read all tokens from stdin
	tokens := []string{}
	scanner2 := bufio.NewScanner(os.Stdin)
	if scanner2 == nil {
		return
	}
	
	// Re-read everything properly
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString(0) // This won't work well
	
	// Let's use a simpler approach with io.Reader
	data := make([]byte, 1<<20)
	n, _ := os.Stdin.Read(data)
	if n == 0 {
		return
	}
	
	// Parse tokens from the byte slice
	pos := 0
	tokens = []string{}
	for pos < n {
		if data[pos] <= ' ' && pos > 0 {
			// Skip whitespace
			pos++
			continue
		}
		start := pos
		for pos < n && data[pos] > ' ' {
			pos++
		}
		if start < pos {
			tokens = append(tokens, string(data[start:pos]))
		} else {
			pos++
		}
	}
	
	if len(tokens) == 0 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	Q, _ := strconv.Atoi(tokens[1])
	
	arr := make([]int64, N)
	for i := 0; i < N; i++ {
		arr[i], _ = strconv.ParseInt(tokens[2+i], 10, 64)
	}
	
	for i := 0; i < Q; i++ {
		x, _ := strconv.ParseInt(tokens[2+N+i], 10, 64)
		
		// Binary search for first element >= x
		l, r := 0, N-1
		idx := -1
		
		for l <= r {
			mid := (l + r) / 2
			if arr[mid] >= x {
				idx = mid
				r = mid - 1
			} else {
				l = mid + 1
			}
		}
		
		if idx == -1 {
			fmt.Println(N)
		} else {
			fmt.Println(idx)
		}
	}
}