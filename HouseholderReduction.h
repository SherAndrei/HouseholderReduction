#pragma once

// Solve Ax=y
// A is expected to be stored by rows
int HouseholderReduction(double *A, unsigned N, const double *y, double *x);
