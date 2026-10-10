package main

import (
	"bytes"
	"fmt"
)

func main() {
	var buf bytes.Buffer
	buf.Grow(5000)

	if _, err := buf.ReadFrom(nil); err != nil {
		fmt.Fprintln(buf, "1 0")
		return
	}

	n, err := buf.Read(make([]byte, 1))
	if err != nil || n == 0 {
		fmt.Fprintln(buf, "1 0")
		return
	}

	start := 0
	for i := 0; i < len(buf.Bytes()); i++ {
		c := buf.Bytes()[i]
		if c == '"' {
			if start == 0 {
				// Start of a quoted field
				i++ // skip the opening quote
				continue
			}
			// End of a quoted field
			end := i + 1
			buf.Truncate(end)

			fields := bytes.Split(buf.Bytes(), []byte{','})
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
			// Empty field at the beginning
			end := i + 1
			buf.Truncate(end)
			fields := bytes.Split(buf.Bytes(), []byte{','})
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
			buf.Truncate(end)
			fields := bytes.Split(buf.Bytes(), []byte{','})
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
	}

	// No special characters found - single field (possibly empty or unquoted)
	fields := bytes.Split(buf.Bytes(), []byte{','})
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