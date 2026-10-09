package main

import (
	"fmt"
)

func editDistance(s1, s2 string) int {
	n := len(s1)
	m := len(s2)
	if n == 0 {
		return m
	}
	if m == 0 {
		return n
	}

	d := make([][]int, n+1)
	for i := range d {
		d[i] = make([]int, m+1)
	}

	for i := 0; i <= n; i++ {
		d[i][0] = i
	}
	for j := 0; j <= m; j++ {
		d[0][j] = j
	}

	for i := 1; i <= n; i++ {
		for j := 1; j <= m; j++ {
			cost := 0
			if s1[i-1] != s2[j-1] {
				cost = 1
			}
			d[i][j] = min(d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1]+cost)
		}
	}

	return d[n][m]
}

func min(a, b, c int) int {
	if a <= b && a <= c {
		return a
	}
	if b <= a && b <= c {
		return b
	}
	return c
}

func main() {
	s1 := ""
	s2 := ""
	fmt.Fscanln(&s1)
	fmt.Fscanln(&s2)
	fmt.Println(editDistance(s1, s2))
}