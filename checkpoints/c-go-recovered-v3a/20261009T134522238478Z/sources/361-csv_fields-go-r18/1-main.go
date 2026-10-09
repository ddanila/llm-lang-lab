package main

import (
	"fmt"
)

func main() {
	data := make([]byte, 5001)
	n, _ := fmt.Fread(&data[0], os.Stdin) // Note: This is pseudo-code, need actual implementation
	fmt.Println(n)
}