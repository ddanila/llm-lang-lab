package main

import (
	"bufio"
	"fmt"
)

func editDistance(s1, s2 string) int {
	if len(s1) == 0 {
		return len(s2)
	}
	if len(s2) == 0 {
		return len(s1)
	}

	n := len(s1)
	m := len(s2)

	// Use two rows for space optimization
	dpPrev := make([]int, m+1)
	dpCurr := make([]int, m+1)

	for j := 0; j <= m; j++ {
		dpPrev[j] = j
	}

	for i := 1; i <= n; i++ {
		dpCurr[0] = i
		for j := 1; j <= m; j++ {
			if s1[i-1] == s2[j-1] {
				dpCurr[j] = dpPrev[j]
			} else {
				insert := dpCurr[j-1] + 1
				delete_ := dpPrev[j] + 1
				subst := dpPrev[j-1] + 1
				if insert <= delete_ && insert <= subst {
					dpCurr[j] = insert
				} else if delete_ <= insert && delete_ <= subst {
					dpCurr[j] = delete_
				} else {
					dpCurr[j] = subst
				}
			}
		}
		// Swap rows
		dpPrev, dpCurr = dpCurr, dpPrev
	}

	return dpPrev[m]
}

func main() {
	reader := bufio.NewReader(nil)

	var s1, s2 string

	// Read first line
	line1, err1 := reader.ReadString('\n')
	if err1 != nil && err1.Error() == "EOF" {
		return
	}
	s1 = line1[:len(line1)-1] // Remove newline

	// Read second line
	line2, err2 := reader.ReadString('\n')
	if err2 != nil && err2.Error() == "EOF" {
		return
	}
	s2 = line2[:len(line2)-1] // Remove newline

	dist := editDistance(s1, s2)
	fmt.Println(dist)
}