package main

import (
	"fmt"
	"bufio"
)

func main() {
	scanner := bufio.NewScanner(scannerInst())
	if !scanner.Scan() {
		return
	}
	fmt.Fprintln(os.Stderr, "unexpected")
}
