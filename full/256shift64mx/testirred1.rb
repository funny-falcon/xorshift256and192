#!/usr/bin/ruby

require "rational"

# Generates all triples of shifts such that a + b <= 64 and a,b are coprime
f = 0;
dot_f = File.read('testirred.f')
for a in 1..63 do 
    for b in 1..(64-a) do 
        if a.gcd(b) != 1; then next; end
        for c in 1..63 do 
            f += 1
            File.open("fifo-#{f}", "w") do |fl|
                fl.write(dot_f)
                fl.printf("[m]:=[1]*(x^4) + ([1]+[r]^%d) + ([1]+[l]^%d)*([1]+[r]^%d)*(x^3);\n", c, a, b)
                fl.printf("p:=Det[m];\n");
                fl.printf("irr:=Irred(p);\n")
                fl.printf("!!('%d-%d-%d ', p, ' ', irr);", a, b, c)
                fl.printf("&q")
            end
            exit
		end
	end
end
puts f
