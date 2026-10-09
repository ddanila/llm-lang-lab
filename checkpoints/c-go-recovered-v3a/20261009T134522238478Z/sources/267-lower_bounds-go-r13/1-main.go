package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	input, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	tokens := strings.Fields(input)
	if len(tokens) < 2 {
		return
	}
	
	N, _ := strconv.Atoi(tokens[0])
	Q, _ := strconv.Atoi(tokens[1])
	
	if N == 0 || Q == 0 {
		return
	}
	
	var arr [200]int
	idx := 0
	for idx < N {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		tokens := strings.Fields(line)
		for _, tok := range tokens {
			if idx >= N {
				break
			}
			val, _ := strconv.Atoi(tok)
			arr[idx] = val
			idx++
		}
	}
	
	for i := 0; i < Q; i++ {
		line, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		tokens := strings.Fields(line)
		for _, tok := range tokens {
			x, _ := strconv.Atoi(tok)
			
			lowerBound := N
			left, right := 0, N-1
			
			for left <= right {
				mid := left + (right-left)/2
				if arr[mid] >= x {
					lowerBound = mid
					right = mid - 1
				} else {
					left = mid + 1
				}
			}
			
			fmt.Println(lowerBound)
		}
	}
}