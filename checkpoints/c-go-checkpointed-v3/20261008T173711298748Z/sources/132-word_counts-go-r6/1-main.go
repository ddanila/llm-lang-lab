package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	// Read at most 10000 bytes from stdin
	data := make([]byte, 0, 10000)
	bufio.ReadFull(os.Stdin, data) // This is not correct, need to read until EOF with limit

	// Actually, let's read byte by byte or use bufio.Scanner with ReadBytes
	// But we need to limit to 10000 bytes
	// Let's use a simpler approach: read all input into a buffer up to 10000 bytes
	
	input := make([]byte, 0)
	reader := bufio.NewReader(os.Stdin)
	
	for {
		p, err := reader.ReadBytes('\n') // This is wrong, we want raw bytes
		// Actually, let's just read all available input with a limit
	}
	
	// Let me rewrite this properly
}