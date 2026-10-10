package main

import (
	"bytes"
	"fmt"
)

func main() {
	var buf bytes.Buffer
	buf.ReadFrom(nil) // dummy to init, actually we read from stdin
}