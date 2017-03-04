#!/usr/bin/ruby

require "rational"

n = ARGV[0].to_i # number of output files
o = ARGV[1].to_i # output file

f = -1 # output file counter

# Generates all triples of shifts such that a + b <= 64 and a,b are coprime
for a in 1..63 do 
        for b in 1..(64-a) do 
		if a.gcd(b) != 1; then next; end
                for c in 1..63 do 
			f = ( f + 1 ) % n
			if f == o; then
                              printf("[m]:=[1]*(x^2) + ([1]+[r]^%d) + ([1]+[rl]^%d+[rr]^%d)*x;\n", c, a, b)
				printf("p:=Det[m];\n");
				printf("irr:=Irred(p);\n")
				printf("!!('%d-%d-%d ', p, ' ', irr);\n", a, b, c)
			end
		end
	end
end
