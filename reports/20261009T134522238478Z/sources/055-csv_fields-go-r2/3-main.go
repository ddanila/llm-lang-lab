package main

import (
	"bytes"
	"fmt"
)

func main() {
	var buf bytes.Buffer
	
	data := make([]byte, 0, 5000)
	n, err := io.ReadFull(os.Stdin, data)
	if err != nil && len(data) == 0 {
		fmt.Println("1 0")
		return
	}
	
	count, lengths := parseCSV(data[:n])
	
	for i := range count {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(lengths[i])
	}
	fmt.Println()
}

import (
	"io"
	"os"
)