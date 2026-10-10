package main

import (
	"bytes"
	"io"
)

func main() {
	var buf bytes.Buffer
	buf.ReadFrom(nil) // dummy to init, actually we read from stdin
}