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

	for i := 1; i <= n; i++ {
		curr[0] = i
		s1Char := s1[i-1]
		for j := 1; j <= m; j++ {
			s2Char := s2[j-1]
			if s1Char == s2Char {
				curr[j] = prev[j-1]
			} else {
				insert := curr[j-1] + 1
				deleteOp := prev[j] + 1
				subst := prev[j-1] + 1
				if insert < deleteOp && insert < subst {
					curr[j] = insert
				} else if deleteOp < subst {
					curr[j] = deleteOp
				} else {
					curr[j] = subst
				}
			}
		}
		copy(prev, curr)
	}

	return prev[m]
}

func main() {
	var line1, line2 string
	fmt.Scanln(&line1)
	fmt.Scanln(&line2)
	
	result := editDistance(line1, line2)
	fmt.Println(result)
}