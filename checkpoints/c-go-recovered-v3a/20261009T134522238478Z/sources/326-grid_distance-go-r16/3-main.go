package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	sc := bufio.NewScanner(os.Stdin)
	var H, W, sr, scVal, tr, tc int

	if !sc.Scan() {
		return
	}
	val := sc.Text()
	parts := strings.Fields(val)
	H = 0
	W = 0
	sr = 0
	scVal = 0
	tr = 0
	tc = 0
	for i, p := range parts {
		if i == 0 {
			H, _ = strconv.Atoi(p)
		} else if i == 1 {
			W, _ = strconv.Atoi(p)
		} else if i == 2 {
			sr, _ = strconv.Atoi(p)
		} else if i == 3 {
			scVal, _ = strconv.Atoi(p)
		} else if i == 4 {
			tr, _ = strconv.Atoi(p)
		} else if i == 5 {
			tc, _ = strconv.Atoi(p)
		}
	}

	grid := make([][]byte, H)
	for i := 0; i < H; i++ {
		if !sc.Scan() {
			break
		}
		line := sc.Text()
		if len(line) == 0 {
			line = "\n"
		}
		grid[i] = []byte(line[:min(len(line), W)])
	}

	startBlocked := grid[sr][scVal] == '#'
	endBlocked := grid[tr][tc] == '#'

	if startBlocked || endBlocked {
		fmt.Println("-1")
		return
	}

	if sr == tr && scVal == tc {
		fmt.Println("0")
		return
	}

	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	q := [][2]int{}
	dist[sr][scVal] = 0
	q = append(q, [2]int{sr, scVal})

	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	head := 0
	for head < len(q) {
		curr := q[head]
		head++
		r, c := curr[0], curr[1]
		d := dist[r][c]

		if r == tr && c == tc {
			fmt.Println(d)
			return
		}

		for k := 0; k < 4; k++ {
			nr, nc := r+dr[k], c+dc[k]
			if nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && dist[nr][nc] == -1 {
				dist[nr][nc] = d + 1
				q = append(q, [2]int{nr, nc})
			}
		}
	}

	fmt.Println("-1")
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}