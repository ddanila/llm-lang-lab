package main

import (
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
	var line1, line2 string
	
	// Read all input until EOF or newline
	fmt.Scanln(&line1)
	
	if err := fmt.Scanln(&line2); err != nil {
		// If second line read fails, treat as empty
		line2 = ""
	}

	dist := editDistance(line1, line2)
	fmt.Println(dist)
}