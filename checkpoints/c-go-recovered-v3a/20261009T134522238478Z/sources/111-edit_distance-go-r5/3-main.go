package main

import (
	"fmt"
	"os"
)

func main() {
	data, err := os.ReadFile("/dev/stdin")
	if err != nil {
		return
	}
	
	// Split by newlines, taking exactly 2 lines
	var s1, s2 string
	n := len(data)
	if n == 0 {
		fmt.Println(0)
		return
	}
	
	// Find first newline
	firstNL := -1
	for i := 0; i < n; i++ {
		if data[i] == '\n' {
			firstNL = i
			break
		}
	}
	
	if firstNL == -1 {
		// No newline, single line input (second line empty)
		s1 = string(data)
		s2 = ""
	} else {
		s1 = string(data[:firstNL])
		remaining := data[firstNL+1:]
		
		// Find second newline
		secondNL := -1
		for i := 0; i < len(remaining); i++ {
			if remaining[i] == '\n' {
				secondNL = i
				break
			}
		}
		
		if secondNL == -1 {
			s2 = string(remaining)
		} else {
			s2 = string(remaining[:secondNL])
		}
	}
	
	fmt.Println(levenshtein(s1, s2))
}

func levenshtein(s1, s2 string) int {
	n := len(s1)
	m := len(s2)
	
	if n == 0 {
		return m
	}
	if m == 0 {
		return n
	}
	
	d := make([]int, m+1)
	
	for j := 0; j <= m; j++ {
		d[j] = j
	}
	
	for i := 1; i <= n; i++ {
		prev := d[0]
		for j := 1; j <= m; j++ {
			old := d[j]
			if s1[i-1] == s2[j-1] {
				d[j] = prev
			} else {
				cost := 1 + min(prev, min(d[j], old))
				d[j] = cost
			}
			prev = old
		}
		d[0]++
	}
	
	return d[m]
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}