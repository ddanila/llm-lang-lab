package main

import (
	"bufio"
	"bytes"
	"fmt"
)

func main() {
	var buf bytes.Buffer
	scanner := bufio.NewScanner(&buf)
	
	for scanner.Scan() {
		line := scanner.Bytes()
		buf.Write(line)
	}
	
	input := buf.Bytes()
	
	if len(input) == 0 {
		return
	}
	
	counts := make(map[string]int)
	var currentWord []byte
	
	for i, b := range input {
		isLetter := (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z')
		
		if isLetter {
			currentWord = append(currentWord, byte(b))
		} else {
			if len(currentWord) > 0 {
				word := string(currentWord)
				lowerWord := toLower(word)
				counts[lowerWord]++
				currentWord = currentWord[:0]
			}
		}
		
		if i == len(input)-1 && len(currentWord) > 0 {
			word := string(currentWord)
			lowerWord := toLower(word)
			counts[lowerWord]++
		}
	}
	
	var output []string
	
	for word, count := range counts {
		output = append(output, fmt.Sprintf("%s %d", word, count))
	}
	
	if len(output) > 0 {
		fmt.Println(output[0])
		for _, line := range output[1:] {
			fmt.Println(line)
		}
	}
}

func toLower(s string) string {
	result := make([]byte, len(s))
	for i, b := range []byte(s) {
		if b >= 'A' && b <= 'Z' {
			result[i] = b + 32
		} else {
			result[i] = b
		}
	}
	return string(result)
}