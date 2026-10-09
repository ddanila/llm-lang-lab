package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	buf := make([]byte, 5000)
	
	var n int
	for i := range buf {
		c, err := r.ReadByte()
		if err != nil {
			break
		}
		buf[i] = c
		n++
	}

	start := 0
	i := 0
	for i < n {
		c := buf[i]
		if c == '"' && start == 0 {
			i++ // skip the opening quote
			continue
		} else if c == '"' && start > 0 {
			end := i + 1
			fields := split(buf[:end], ',')
			count := len(fields)
			var lengths []int
			for _, f := range fields {
				lengths = append(lengths, len(f))
			}
			fmt.Printf("%d", count)
			for _, l := range lengths {
				fmt.Printf(" %d", l)
			}
			fmt.Println()
			return
		} else if c == ',' && start == 0 {
			end := i + 1
			fields := split(buf[:end], ',')
			count := len(fields)
			var lengths []int
			for _, f := range fields {
				lengths = append(lengths, len(f))
			}
			fmt.Printf("%d", count)
			for _, l := range lengths {
				fmt.Printf(" %d", l)
			}
			fmt.Println()
			return
		} else if c == '\n' || c == '\r' {
			end := i + 1
			fields := split(buf[:end], ',')
			count := len(fields)
			var lengths []int
			for _, f := range fields {
				lengths = append(lengths, len(f))
			}
			fmt.Printf("%d", count)
			for _, l := range lengths {
				fmt.Printf(" %d", l)
			}
			fmt.Println()
			return
		}
		start++
		i++
	}

	fields := split(buf, ',')
	count := len(fields)
	var lengths []int
	for _, f := range fields {
		lengths = append(lengths, len(f))
	}
	fmt.Printf("%d", count)
	for _, l := range lengths {
		fmt.Printf(" %d", l)
	}
	fmt.Println()
}

func split(b []byte, sep byte) [][]byte {
	var fields [][]byte
	start := 0
	for i := range b {
		if b[i] == sep {
			fields = append(fields, b[start:i])
			start = i + 1
		}
	}
	fields = append(fields, b[start:])
	return fields
}