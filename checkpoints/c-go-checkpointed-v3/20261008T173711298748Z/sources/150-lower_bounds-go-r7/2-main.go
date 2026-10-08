package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	// Read N and Q
	n, q, err := readTwoInts(reader)
	if err != nil {
		return
	}

	// Read N integers
	arr := make([]int64, n)
	for i := int64(0); i < n; i++ {
		arr[i], _ = readInt(reader)
	}

	// Process Q queries
	for i := int64(0); i < q; i++ {
		x, _ := readInt(reader)
		idx := lowerBound(arr, x)
		fmt.Println(idx)
	}
}

func readTwoInts(r *bufio.Reader) (int64, int64, error) {
	line, err := r.ReadString('\n')
	if err != nil {
		return 0, 0, err
	}
	parts := split(line)
	if len(parts) < 2 {
		return 0, 0, fmt.Errorf("expected N Q")
	}
	n, _ := strconv.ParseInt(parts[0], 10, 64)
	q, _ := strconv.ParseInt(parts[1], 10, 64)
	return n, q, nil
}

func readInt(r *bufio.Reader) (int64, error) {
	line, err := r.ReadString('\n')
	if err != nil {
		return 0, err
	}
	parts := split(line)
	for _, p := range parts {
		p = trim(p)
		if p == "" {
			continue
		}
		val, _ := strconv.ParseInt(p, 10, 64)
		return val, nil
	}
	return 0, fmt.Errorf("no integer found")
}

func split(s string) []string {
	var parts []string
	start := 0
	for i, c := range s {
		if c == ' ' || c == '\t' || c == '\n' || c == '\r' {
			if start < i {
				parts = append(parts, s[start:i])
			}
			start = i + 1
		}
	}
	if start < len(s) {
		parts = append(parts, s[start:])
	}
	return parts
}

func trim(s string) string {
	start := 0
	end := len(s)
	for start < end && (s[start] == ' ' || s[start] == '\t') {
		start++
	}
	for end > start && (s[end-1] == ' ' || s[end-1] == '\t' || s[end-1] == '\n' || s[end-1] == '\r') {
		end--
	}
	return s[start:end]
}

func lowerBound(arr []int64, x int64) int {
	l, r := 0, len(arr)
	for l < r {
		mid := l + (r-l)/2
		if arr[mid] >= x {
			r = mid
		} else {
			l = mid + 1
		}
	}
	return l
}