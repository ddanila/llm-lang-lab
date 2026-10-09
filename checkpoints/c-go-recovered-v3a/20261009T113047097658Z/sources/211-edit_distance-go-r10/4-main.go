package main

import (
	"bufio"
	"fmt"
	"os"
)

func levenshtein(s1, s2 string) int {
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
		ci := s1[i-1]
		curr[0] = i
		for j := 1; j <= m; j++ {
			if ci == s2[j-1] {
				curr[j] = prev[j]
			} else {
				insert := curr[j-1] + 1
				deleteOp := prev[j] + 1
				subst := prev[j-1] + 1
				if insert < deleteOp {
					if insert < subst {
						curr[j] = insert
					} else if subst < deleteOp {
						curr[j] = subst
					} else {
						curr[j] = deleteOp
					}
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
	reader := bufio.NewReader(os.Stdin)
	line1, err := reader.ReadString('\n')
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	
	line2, err := reader.ReadString('\n')
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}

	s1 := line1[:len(line1)-1]
	s2 := line2[:len(line2)-1]

	dist := levenshtein(s1, s2)
	fmt.Println(dist)
}