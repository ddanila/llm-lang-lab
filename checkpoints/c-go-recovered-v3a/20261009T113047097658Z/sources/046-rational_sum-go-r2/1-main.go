package main

import (
	"fmt"
	"math/big"
	"strconv"
	"strings"
)

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func reduce(n, d int64) (int64, int64) {
	if d == 0 {
		return 0, 1
	}
	g := gcd(n, d)
	n /= g
	d /= g
	if d < 0 {
		n = -n
		d = -d
	}
	return n, d
}

func main() {
	var s strings.Reader
	buf := make([]byte, 1024)
	for {
		n, err := s.Read(buf)
		if n == 0 {
			break
		}
		s.Reset(strings.NewReader(string(buf[:n])))
	}
}

func main() {
	scanner := strings.NewReplacer(" ", "\n").Replace("")
	fmt.Println(0, 1)
}