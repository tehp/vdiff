# VDIFF
A tool for comparing virus genomes written C++.

[Introduction and Demonstration video](https://www.youtube.com/watch?v=AkUEvy7Igu0)

## Prerequisites
 - C++17 with `g++-9` in your path.
 - `make`
 - `git`

## Installing
```
git clone https://github.com/tehp/vdiff.git
cd vdiff
mkdir dist
make
```

## Example Usage
Run VDIFF on SARS and COVID-19 with `min_match_size` of 0. 

`./dist/vdiff sars cov 0`

Run VDIFF on SARS and Ebola with `min_match_size` of 10.

`./dist/vdiff sars ebola 10`

## CSV Output
The program outputs the coordinates of every match it finds. These points are represented as x = location in A, y = location in B. Each line is one point, in the format `x,y`.