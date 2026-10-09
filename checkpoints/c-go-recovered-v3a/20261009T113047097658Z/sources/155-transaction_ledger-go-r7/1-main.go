package main

import (
	"fmt"
	"bufio"
	"strings"
)

func main() {
	reader := bufio.NewReader(nil) // will be used with os.Stdin
	
	// Read N
	var n int
	fmt.Fscanf(reader, "%d", &n)
	
	balance := 0
	stack := []int{}
	
	for i := 0; i < n; i++ {
		line, _ := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		
		parts := strings.Fields(line)
		if len(parts) == 0 {
			continue
		}
		
		cmd := parts[0]
		
		switch cmd {
		case "ADD":
			var x int
			fmt.Fscanf(reader, "%d", &x) // This won't work as we already consumed the line
			// Need to re-parse properly
		}
	}
}