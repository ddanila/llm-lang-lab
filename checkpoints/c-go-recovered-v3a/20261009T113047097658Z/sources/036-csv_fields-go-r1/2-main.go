package main

import (
	"io"
)

func main() {
	var buf [5001]byte
	n := 0
	
	for {
		b, err := io.ReadFull(io.NopCloser(nil), nil) // placeholder - need actual reading
		
		// Read from stdin until newline or EOF
	}
	
	_ = buf
}