package main

import (
	"bufio"
	"fmt"
	"os"
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

	prev := make([]int, m+1)
	curr := make([]int, m+1)

	for j := 0; j <= m; j++ {
		prev[j] = j
	}

	for i := 1; i <= n; i++ {
		curr[0] = i
		for j := 1; j <= m; j++ {
			if s1[i-1] == s2[j-1] {
				curr[j] = prev[j]
			} else {
				insertion := curr[j-1] + 1
				deletion := prev[j] + 1
				substitution := prev[j-1] + 1
				if insertion < deletion && insertion < substitution {
					curr[j] = insertion
				} else if deletion < substitution {
					curr[j] = deletion
				} else {
					curr[j] = substitution
				}
			}
		}
		copy(prev, curr)
	}

	return prev[m]
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	if !scanner.Scan() {
		return
	}
	s1 := scanner.Text()
	
	if !scanner.Scan() {
		return
	}
	s2 := scanner.Text()
	
	fmt.Println(editDistance(s1, s2))
}