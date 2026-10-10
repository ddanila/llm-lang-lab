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
	s1 = lines[idx:]
	idx = 0
	for len(s1) > 0 && s1[idx] == '\n' {
		idx++
	}
	s1 = s1[idx:]
	
	if len(lines) > idx+1 {
		s2 := lines[idx+1 : len(lines)-1]
		
		idx = 0
		for len(s2) > 0 && s2[idx] == '\n' {
			idx++
		}
		s2 = s2[idx:]
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
		di0 := d[0] - 1
		if di0 < 0 {
			di0 = 0
		}
		di1 := d[0] + 1
		
		for j := 1; j <= m; j++ {
			old := di1
			if s1[i-1] == s2[j-1] {
				di1 = d[j]
			} else {
				cost := 1
				v0 := di0 + cost
				v1 := d[j] + cost
				v2 := di1 + cost
				if v0 < v1 {
					v1 = v0
				}
				if v1 < v2 {
					di1 = v1
				} else {
					di1 = v2
				}
			}
			di0 = di1
		}
		d[0] = di0
	}
	
	return d[m]
}