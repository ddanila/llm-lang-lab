package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	line1, err := reader.ReadString('\n')
	if err != nil {
		return
	}
	fields := strings.Fields(line1)
	if len(fields) < 4 {
		return
	}

	H, _ := strconv.Atoi(fields[0])
	W, _ := strconv.Atoi(fields[1])
	sr, _ := strconv.Atoi(fields[2])
	sc, _ := strconv.Atoi(fields[3])
	tr, _ := strconv.Atoi(fields[4])
	tc, _ := strconv.Atoi(fields[5])

	gridLines := make([]string, H)
	for i := 0; i < H; i++ {
		line, _ := reader.ReadString('\n')
		line = strings.TrimRight(line, "\r\n")
		gridLines[i] = line
	}

	if sr < 0 || sr >= H || sc < 0 || sc >= W || tr < 0 || tr >= H || tc < 0 || tc >= W {
		fmt.Println("-1")
		return
	}

	startCell := gridLines[sr][sc]
	targetCell := gridLines[tr][tc]

	if startCell == '#' || targetCell == '#' {
		fmt.Println("-1")
		return
	}

	if sr == tr && sc == tc {
		fmt.Println("0")
		return
	}

	dx := []int{0, 0, 1, -1}
	dy := []int{1, -1, 0, 0}
	dist := make([][]int, H)
	for i := range dist {
		dist[i] = make([]int, W)
		for j := range dist[i] {
			dist[i][j] = -1
		}
	}

	q := [][2]int{}
	rHead := 0
	dist[sr][sc] = 0
	q = append(q, [2]int{sr, sc})

	for rHead < len(q) {
		curr := q[rHead]
	rHead++
		x, y := curr[0], curr[1]
		d := dist[x][y]
		for k := 0; k < 4; k++ {
			nx, ny := x+dx[k], y+dy[k]
			if nx >= 0 && nx < H && ny >= 0 && ny < W && gridLines[nx][ny] == '.' && dist[nx][ny] == -1 {
				dist[nx][ny] = d + 1
				q = append(q, [2]int{nx, ny})
			}
		}
	}

	if dist[tr][tc] != -1 {
		fmt.Println(dist[tr][tc])
	} else {
		fmt.Println("-1")
	}
}