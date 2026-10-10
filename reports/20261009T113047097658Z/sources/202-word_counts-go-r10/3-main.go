package main

import (
	"bufio"
	"bytes"
	"fmt"
)

func main() {
	buf := make([]byte, 10000)
	n, _ := bufio.NewReader(nil).Read(buf) // placeholder - need different approach
	
	// Read all input until EOF
	var data bytes.Buffer
	r := bufio.NewReader(nil)
	
	// Better approach: read byte by byte or use ioutil.ReadAll
}