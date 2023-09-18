### Solve linear equations using Householder transformation

Build
```bash
$ make
```
Seek help
```bash
$ ./SolveLinearEquations.out -h
Usage: ./SolveLinearEquations.out
	Solve linear equations Ax=y using Householder transformations.

	Expected input format:
		N
		a11	a12	...	a1N	y1
		a21	a22	...	a2N	y2
		...	...	...	...	...
		aN1	aN2	...	aNN	yN

	Output format of solution to equation if matrix is not degenerate:
		x1	x2	...	xN
```
Save your linear equations to a file, for example `input.txt`
```
3
1 2 3 3
3 1 2 6
2 3 1 9
```
Run
```bash
$ ./SolveLinearEquations.out < input.txt
2.000000e+00 2.000000e+00 -1.000000e+00
```
