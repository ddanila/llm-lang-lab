package main

import (
	"bufio"
	"bytes"
	"fmt"
)

func main() {
	var buf bytes.Buffer
	r := bufio.NewReader(nil)
	
	// Read all input from stdin
	data, _ := bufio.NewReader(nil).ReadBytes(0) // This won't work
	
	// Use io.ReadAll equivalent
	buf = make([]byte, 10000)
	n, err := bufio.NewReader(nil).Read(buf)
}