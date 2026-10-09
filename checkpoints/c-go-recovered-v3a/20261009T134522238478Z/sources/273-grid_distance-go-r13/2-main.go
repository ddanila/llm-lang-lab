package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	sc := bufio.NewScanner(os.Stdin)
	if !sc.Scan() {
		return
	}
	var H, W, sr, sc_int, tr, tc int
	fmt.Fscanf(sc, "%d %d %d %d %d %d", &H, &W, &sr, &sc_int, &tr, &tc)

	grid := make([]string, H)
	for i := 0; i < H; i++ {
		sc.Scan()
		grid[i] = sc.Text()
	}

	if grid[sr][sc_int] == '#' || grid[tr][tc] == '#' {
		fmt.Println("-1")
		return
	}

	if sr == tr && sc_int == tc {
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
	qy = append(qy, sc_int)
	d[sr][sc_int] = 0

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