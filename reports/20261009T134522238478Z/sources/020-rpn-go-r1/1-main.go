package main

import (
	"fmt"
	"strconv"
)

func main() {
	var tokens []string
	for token := range scanTokens() {
		tokens = append(tokens, token)
		if len(tokens) > 200 {
			fmt.Println("ERROR")
			return
		}
	}

	stack := make([]int64, 0, 10)

	for _, tok := range tokens {
		if tok == "+" || tok == "-" || tok == "*" {
			if len(stack) < 2 {
				fmt.Println("ERROR")
				return
			}
			b := stack[len(stack)-1]
			stack = stack[:len(stack)-1]
			a := stack[len(stack)-1]
			stack = stack[:len(stack)] // remove b
			if tok == "+" {
				stack = append(stack, a+b)
			} else if tok == "-" {
				stack = append(stack, a-b)
			} else {
				stack = append(stack, a*b)
			}
		} else {
			val, err := strconv.ParseInt(tok, 10, 64)
			if err != nil {
				fmt.Println("ERROR")
				return
			}
			stack = append(stack, val)
		}
	}

	if len(stack) != 1 {
		fmt.Println("ERROR")
		return
	}

	fmt.Println(stack[0])
}

func scanTokens() chan string {
	ch := make(chan string)
	go func() {
		var buf [256]byte
		n, err := readStdin(buf[:])
		if err != nil {
			close(ch)
			return
		}
		i := 0
		for i < n {
			c := buf[i]
			if c == ' ' || c == '\t' || c == '\n' || c == '\r' {
				i++
				continue
			}
			start := i
			for i < n && (c = buf[i]) != ' ' && c != '\t' && c != '\n' && c != '\r' {
				c = buf[i]
				i++
			}
			if start < i {
				ch <- string(buf[start:i])
			}
		}
		close(ch)
	}()
	return ch
}

func readStdin(buf []byte) (int, error) {
	var n int
	for {
		c := rune('\n')
		if len(buf) == 0 {
			buf = make([]byte, 4096)
		}
		n = 0
		for n < len(buf) {
			r, _, ok := readRune()
			if !ok {
				return n, nil
			}
			buf[n] = byte(r)
			n++
		}
	}
}

func readRune() (rune, int, bool) {
	return 0, 0, false
}