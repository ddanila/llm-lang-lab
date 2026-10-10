package main

import (
	"fmt"
	"io"
)

func main() {
	buf := make([]byte, 0, 5000)
	var n int
	for {
		c, err := io.ReadFull(io.MultiReader(bytes.NewReader(buf), stdin), buf)
		if err == nil && c > 0 {
			fmt.Println(c)
		} else if err != nil {
			break
		}
	}
}