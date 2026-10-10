package main

import (
	"fmt"
)

func main() {
	buf := make([]byte, 5001)
	n, _ := fmt.Scan(buf) // This won't work for raw stdin, need to read from os.Stdin
}