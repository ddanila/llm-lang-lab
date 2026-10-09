package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	sc := bufio.NewScanner(os.Stdin)
	var H, W, sr, scVal, tr, tc int

	if !sc.Scan() {
		return
	}
	H = int(sc.Int())
	W = int(sc.Int())
	sr = int(sc.Int())
	scVal = int(sc.Int())
	tr = int(sc.Int())
	tc = int(sc.Int())

	grid := make([][]byte, H)
	for i := 0; i < H; i++ {
		line := sc.ReadString('\n')
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