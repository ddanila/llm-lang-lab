package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 10000)
	counts := make(map[string]int)
	
	buf := make([]byte, 1024)
	totalRead := 0
	
	for {
		n, err := reader.Read(buf)
		if n > 0 {
			totalRead += n
			
			for i := 0; i < n; i++ {
				b := buf[i]
				if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
					// Accumulate word in a buffer
					// We need to handle words up to 10000 letters, so we can't use a fixed small buffer for the word itself
					// Instead, we'll process byte by byte and build words
				} else {
					// Non-letter separator - if we have a pending word, output it
				}
			}
		} else if err != nil {
			break
		}
	}
	
	// Let's rewrite with a simpler approach: read all bytes into a slice and process
}