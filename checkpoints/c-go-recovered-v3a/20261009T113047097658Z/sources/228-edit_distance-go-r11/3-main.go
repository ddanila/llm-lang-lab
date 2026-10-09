package main

import "fmt"

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

	for i := 0; i < n; i++ {
		curr[0] = i + 1
		for j := 0; j < m; j++ {
			if s1[i] == s2[j] {
				curr[j+1] = prev[j]
			} else {
				insertion := curr[j]
				deletion := prev[j+1]
				substitution := prev[j] + 1

				if insertion <= deletion && insertion <= substitution {
					curr[j+1] = insertion
				} else if deletion <= substitution {
					curr[j+1] = deletion
				} else {
					curr[j+1] = substitution
				}
			}
		}
		prev, curr = curr, prev
	}

	return prev[m]
}

func main() {
	var line string
	fmt.Scanln(&line)
	s1 := line

	fmt.Scanln(&line)
	s2 := line

	fmt.Println(editDistance(s1, s2))
}