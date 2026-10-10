package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	var line1, line2 string
	
	// Read first line including empty lines
	line1, err1 := reader.ReadString('\n')
	if err1 != nil && err1.Error() != "EOF" {
		return
	}
	line1 = line1[:len(line1)-1] // Remove newline if present
	
	// Read second line including empty lines
	line2, err2 := reader.ReadString('\n')
	if err2 != nil && err2.Error() != "EOF" {
		return
	}
	line2 = line2[:len(line2)-1] // Remove newline if present

	s1 := line1
	s2 := line2

	n := len(s1)
	m := len(s2)

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
				curr[j] = min(prev[j]+1, curr[j-1]+1, prev[j-1]+1)
			}
		}
		copy(prev, curr)
	}

	fmt.Println(prev[m])
}

func min(a, b, c int) int {
	if a < b {
		a = b
	}
	if a < c {
		a = c
	}
	return a
}