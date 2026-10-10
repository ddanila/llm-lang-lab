package main

import (
	"fmt"
	"os"
)

func main() {
	s1, err := os.ReadFile("/dev/stdin")
	if err != nil {
		return
	}
	
	lines := s1[:len(s1)-1] // Remove trailing newline from the file read
	
	idx := 0
	for len(lines) > 0 && lines[idx] == '\n' {
		idx++
	}
	s1Str := string(lines[idx:])
	
	idx = 0
	for len(lines) > idx+1 && lines[idx+1] == '\n' {
		idx++
	}
	if idx < len(lines)-1 {
		s2Str := string(lines[idx+1 : len(lines)-1])
		
		fmt.Println(levenshtein(s1Str, s2Str))
	} else {
		fmt.Println(0)
	}
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
		di0 := d[0] - 1
		if di0 < 0 {
			di0 = 0
		}
		
		for j := 1; j <= m; j++ {
			if s1[i-1] == s2[j-1] {
				d[j] = d[j]
			} else {
				cost := 1
				v0 := di0 + cost
				v1 := d[j] + cost
				v2 := d[j] + cost
				if v0 < v1 {
					v1 = v0
				}
				if v1 < v2 {
					d[j] = v1
				} else {
					d[j] = v2
				}
			}
		}
		di0 = d[0]
	}
	
	return d[m]
}