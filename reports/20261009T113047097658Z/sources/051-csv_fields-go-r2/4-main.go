package main

func main() {
	buf := make([]byte, 0, 5000)
	
	// Read all input from stdin
	for {
		b, err := readByte(&buf)
		if err != nil {
			break
		}
	}
	
	input := string(buf)
	
	// If input is empty (len == 0), treat as one empty field
	if len(input) == 0 {
		println("1 0")
		return
	}
	
	// Parse CSV fields
	fields := parseCSV(input)
	
	// Output number of fields and their lengths
	print(len(fields))
	for _, f := range fields {
		print(" ", len(f))
	}
	println()
}

func readByte(buf *[]byte) (byte, error) {
	r := make([]byte, 1)
	n, err := readStdin(r)
	if n == 0 && err != nil {
		return 0, err
	}
	if n > 0 {
		*buf = append(*buf, r[0])
	}
	return r[0], nil
}

func parseCSV(input string) []string {
	var fields []string
	start := 0
	
	i := 0
	n := len(input)
	
	for i < n {
		if input[i] == '"' {
			// Quoted field
			start = i + 1
			i++
			
			fieldBytes := make([]byte, 0, n-start)
			
			for i < n {
				if input[i] == '"' {
					// Check if this is an escaped quote or end of field
					if i+1 < n && input[i+1] == '"' {
						// Escaped quote: include one quote in the decoded value
						fieldBytes = append(fieldBytes, '"')
						i += 2
					} else {
						// End of quoted field
						i++ // skip closing quote
						break
					}
				} else {
					fieldBytes = append(fieldBytes, input[i])
					i++
				}
			}
			
			fields = append(fields, string(fieldBytes))
		} else if input[i] == ',' {
			// Unquoted field ends at comma
			field := input[start:i]
			fields = append(fields, field)
			start = i + 1
			i++
		} else {
			i++
		}
	}
	
	// Add the last field if there is any content after the last comma or quote
	if start < len(input) {
		field := input[start:]
		fields = append(fields, field)
	}
	
	return fields
}