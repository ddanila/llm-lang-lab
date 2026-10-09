package main

import (
	"fmt"
	"scan"
)

func main() {
	s := scan.NewScanner()
	if !s.Scan() {
		return
	}
	var H, W, sr, sc, tr, tc int
	fmt.Fscanf(s.r, "%d %d %d %d %d %d", &H, &W, &sr, &sc, &tr, &tc)

	grid := make([]string, H)
	for i := 0; i < H; i++ {
		s.Scan()
		grid[i] = s.Text()
	}

	if grid[sr][sc] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	if sr == tr && sc == tc {
		fmt.Println("0")
		return
	}

	d := make([][]int, H)
	for i := range d {
		d[i] = make([]int, W)
		for j := range d[i] {
			d[i][j] = -1
		}
	}

	qx := make([]int, 0, H*W)
	qy := make([]int, 0, H*W)
	qx = append(qx, sr)
	qy = append(qy, sc)
	d[sr][sc] = 0

	dx := []int{-1, 1, 0, 0}
	dy := []int{0, 0, -1, 1}

	head := 0
	for head < len(qx) {
		x, y := qx[head], qy[head]
		head++
		dist := d[x][y]

		for i := 0; i < 4; i++ {
			nx, ny := x+dx[i], y+dy[i]
			if nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] == '.' && d[nx][ny] == -1 {
				d[nx][ny] = dist + 1
				qx = append(qx, nx)
				qy = append(qy, ny)
			}
		}
	}

	fmt.Println(d[tr][tc])
}