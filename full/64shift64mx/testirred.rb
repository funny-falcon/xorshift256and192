#!/usr/bin/ruby

n = ARGV[0].to_i # number of output files
o = ARGV[1].to_i # output file

f = -1 # output file counter

# Generates all triples of shifts such that a < c
for a in 1..63
  for b in 1..63
    next if a.gcd(b) != 1
    for c in 1..63	
      next if a.gcd(c) != 1
      next if b.gcd(c) != 1
      f = ( f + 1 ) % n
      if f == o; then
        printf("[m]:=([1]+[rr]^%d+[l]^%d)*(1+[r]^%d);\n", a, b, c)
        printf("p:=Chpoly([m]);\n")
        printf("irr:=Irred(p);\n")
        printf("!!('%d-%d-%d ', p, ' ', irr);\n", a, b, c)
      end
    end
  end
end
