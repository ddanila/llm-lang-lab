package main

import (
	"fmt"
	"math/big"
	"os"
	"strconv"
	"strings"
)

func main() {
	data := readInput(os.Stdin)
	if len(data) == 0 {
		fmt.Println("0 1")
		return
	}

	N, err := strconv.Atoi(data[0])
	if err != nil {
		os.Exit(1)
	}

	nums := make([]*big.Int, N)
	dens := make([]*big.Int, N)

	for i := 0; i < N; i++ {
		pStr := data[1+2*i]
		qStr := data[2+2*i]

		p, _ := strconv.ParseInt(pStr, 10, 64)
		q, _ := strconv.ParseInt(qStr, 10, 64)

		nums[i] = big.NewInt(p)
		dens[i] = big.NewInt(q)
	}

	sumNum := big.NewInt(0)
	sumDen := big.NewInt(1)

	for i := 0; i < N; i++ {
		lcm := lcm(sumDen, dens[i])
		newNum := sumNum.Mul(sumNum, new(big.Int).Quo(lcm, sumDen)).Add(new(big.Int).Mul(nums[i], new(big.Int).Quo(lcm, dens[i])))
		newDen := lcm

		gcd := new(big.Int).GCD(nil, nil, newNum, newDen)
		sumNum = newNum.Div(newNum, gcd)
		sumDen = newDen.Div(newDen, gcd)
	}

	fmt.Printf("%d %d\n", sumNum, sumDen)
}

func readInput(r *os.File) []string {
	var data []string
	buf := make([]byte, 4096)
	for {
		n, err := r.Read(buf)
		if n > 0 {
			data = append(data, string(buf[:n]))
		}
		if err != nil {
			break
		}
	}
	return strings.Fields(strings.Join(data, ""))
}

func lcm(a, b *big.Int) *big.Int {
	gcd := new(big.Int).GCD(nil, nil, a, b)
	lcmVal := new(big.Int).Mul(a, b).Div(new(big.Int).Mul(a, b), gcd)
	return lcmVal
}