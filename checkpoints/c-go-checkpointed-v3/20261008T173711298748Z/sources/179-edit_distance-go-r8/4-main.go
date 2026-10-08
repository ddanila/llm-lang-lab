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
	reader := bufio.NewReader(os.Stdin)
	line1, err1 := reader.ReadString('\n')
	if err1 != nil && err1.Error() == "EOF" {
		line1 = ""
	} else if err1 != nil {
		fmt.Println("0")
		return
	}
	
	line2, err2 := reader.ReadString('\n')
	if err2 != nil && err2.Error() == "EOF" {
		line2 = ""
	} else if err2 != nil {
		fmt.Println("0")
		return
	}

	s1 := line1
	s2 := line2

	dist := levenshtein(s1, s2)
	fmt.Println(dist)
}