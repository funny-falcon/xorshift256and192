&t;
&E;
&a;
&(_d=10000);
Array l[64,64], r[64,64], m[64,64];
&(p=2);
&(J=x);
[l]:=0;
[r]:=0;
for i = 0,62 do l[i+1,i]:=1; r[i,i+1]:=1; od;
[rl]:=[l];
[rr]:=[r];
rl[0,63]:=1;
rr[63,0]:=1;
