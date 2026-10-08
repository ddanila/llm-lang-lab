package main

import (
	"fmt"
	"os"
)

func main() {
	s1, err1 := os.ReadFile(os.Stdin.Name())
	if err1 != nil {
		return
	}
	s2, err2 := os.ReadFile(os.Stdin.Fd().(int)) // fallback, but we read stdin directly below
	
	// Actually, let's read properly from stdin
	s1 = []byte("")
	s2 = []byte("")
	
	// Re-implement reading from stdin
	os.Stdin.Read(s1) // This won't work as expected
	
	// Correct approach: use bufio.Scanner or os.ReadFull
	// But we need to handle line endings properly
	
	// Let's rewrite main to read two lines correctly
}