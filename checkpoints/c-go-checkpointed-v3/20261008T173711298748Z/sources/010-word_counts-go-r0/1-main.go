package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"strings"
)

func main() {
	reader := bufio.NewReader(io.NopCloser(&bytes.NewBuffer(nil))) // placeholder, will be replaced
	// Actually, we need to read from stdin. Let's use bufio.Scanner or io.ReadFull style loop.
	
	// Read all input from stdin into a buffer (max 10000 bytes)
	buf := make([]byte, 10000)
	n, err := io.ReadFull(io.NopCloser(&dummyReader{}), buf) // This won't work directly
	
	// Better approach: read byte by byte or use bufio.Reader with ReadByte in a loop
	reader = bufio.NewReaderSize(nil, 0) // nil reader? No.
	
	// Let's just use io.ReadFull properly with stdin
	var input bytes.Buffer
	buf := make([]byte, 1024)
	for {
		n, err := io.ReadFull(io.NopCloser(&dummyReader{}), buf)
		if n > 0 {
			input.Write(buf[:n])
		}
		if err != nil {
			break
		}
	}
	
	// Hmm, this is getting complicated. Let's use a simpler approach with bufio.Reader
	reader = bufio.NewReaderSize(nil, 0) // This doesn't work
	
	// Correct approach:
	r := bufio.NewReaderSize(nil, 0) // Can't create reader from nil
	
	// Actually, let's just read from stdin directly using io.Copy or similar
	var data bytes.Buffer
	buf := make([]byte, 1024)
	for {
		n, err := io.ReadFull(io.NopCloser(&dummyReader{}), buf)
		if n > 0 {
			data.Write(buf[:n])
		}
		if err != nil {
			break
		}
	}
	
	// This is wrong. Let me rewrite properly.
	
	_ = reader
	_ = data
	_ = buf
}

type dummyReader struct{}

func (d *dummyReader) Read(p []byte) (int, error) {
	return 0, io.EOF
}

// Actually, I need to read from os.Stdin. Let me rewrite the entire program properly.