Array q[65];
q[0] := x;
q[1] := q[0] * q[0];
q[2] := q[1] * q[1];
q[3] := q[2] * q[2];
q[4] := q[3] * q[3];
q[5] := q[4] * q[4];
q[6] := q[5] * q[5];
q[7] := q[6] * q[6];
q[8] := q[7] * q[7];
q[9] := q[8] * q[8];
q[10] := q[9] * q[9];
q[11] := q[10] * q[10];
q[12] := q[11] * q[11];
q[13] := q[12] * q[12];
q[14] := q[13] * q[13];
q[15] := q[14] * q[14];
q[16] := q[15] * q[15];
q[17] := q[16] * q[16];
q[18] := q[17] * q[17];
q[19] := q[18] * q[18];
q[20] := q[19] * q[19];
q[21] := q[20] * q[20];
q[22] := q[21] * q[21];
q[23] := q[22] * q[22];
q[24] := q[23] * q[23];
q[25] := q[24] * q[24];
q[26] := q[25] * q[25];
q[27] := q[26] * q[26];
q[28] := q[27] * q[27];
q[29] := q[28] * q[28];
q[30] := q[29] * q[29];
q[31] := q[30] * q[30];
q[32] := q[31] * q[31];
q[33] := q[32] * q[32];
q[34] := q[33] * q[33];
q[35] := q[34] * q[34];
q[36] := q[35] * q[35];
q[37] := q[36] * q[36];
q[38] := q[37] * q[37];
q[39] := q[38] * q[38];
q[40] := q[39] * q[39];
q[41] := q[40] * q[40];
q[42] := q[41] * q[41];
q[43] := q[42] * q[42];
q[44] := q[43] * q[43];
q[45] := q[44] * q[44];
q[46] := q[45] * q[45];
q[47] := q[46] * q[46];
q[48] := q[47] * q[47];
q[49] := q[48] * q[48];
q[50] := q[49] * q[49];
q[51] := q[50] * q[50];
q[52] := q[51] * q[51];
q[53] := q[52] * q[52];
q[54] := q[53] * q[53];
q[55] := q[54] * q[54];
q[56] := q[55] * q[55];
q[57] := q[56] * q[56];
q[58] := q[57] * q[57];
q[59] := q[58] * q[58];
q[60] := q[59] * q[59];
q[61] := q[60] * q[60];
q[62] := q[61] * q[61];
q[63] := q[62] * q[62];
q[64] := q[63] * q[63];
!!('Check: ', if q[64] = x then 1 else 0; &q fi);
p := 1;
p := *p * q[0];
p := *p * q[2];
p := *p * q[4];
p := *p * q[6];
p := *p * q[8];
p := *p * q[10];
p := *p * q[12];
p := *p * q[14];
p := *p * q[16];
p := *p * q[18];
p := *p * q[20];
p := *p * q[22];
p := *p * q[24];
p := *p * q[26];
p := *p * q[28];
p := *p * q[30];
p := *p * q[32];
p := *p * q[34];
p := *p * q[36];
p := *p * q[38];
p := *p * q[40];
p := *p * q[42];
p := *p * q[44];
p := *p * q[46];
p := *p * q[48];
p := *p * q[50];
p := *p * q[52];
p := *p * q[54];
p := *p * q[56];
p := *p * q[58];
p := *p * q[60];
p := *p * q[62];
!!('Result: ', if p = 1 then 0; &q else 1 fi);
p := 1;
p := *p * q[0];
p := *p * q[1];
p := *p * q[4];
p := *p * q[5];
p := *p * q[8];
p := *p * q[9];
p := *p * q[12];
p := *p * q[13];
p := *p * q[16];
p := *p * q[17];
p := *p * q[20];
p := *p * q[21];
p := *p * q[24];
p := *p * q[25];
p := *p * q[28];
p := *p * q[29];
p := *p * q[32];
p := *p * q[33];
p := *p * q[36];
p := *p * q[37];
p := *p * q[40];
p := *p * q[41];
p := *p * q[44];
p := *p * q[45];
p := *p * q[48];
p := *p * q[49];
p := *p * q[52];
p := *p * q[53];
p := *p * q[56];
p := *p * q[57];
p := *p * q[60];
p := *p * q[61];
!!('Result: ', if p = 1 then 0; &q else 1 fi);
p := 1;
p := *p * q[0];
p := *p * q[1];
p := *p * q[2];
p := *p * q[3];
p := *p * q[8];
p := *p * q[9];
p := *p * q[10];
p := *p * q[11];
p := *p * q[16];
p := *p * q[17];
p := *p * q[18];
p := *p * q[19];
p := *p * q[24];
p := *p * q[25];
p := *p * q[26];
p := *p * q[27];
p := *p * q[32];
p := *p * q[33];
p := *p * q[34];
p := *p * q[35];
p := *p * q[40];
p := *p * q[41];
p := *p * q[42];
p := *p * q[43];
p := *p * q[48];
p := *p * q[49];
p := *p * q[50];
p := *p * q[51];
p := *p * q[56];
p := *p * q[57];
p := *p * q[58];
p := *p * q[59];
!!('Result: ', if p = 1 then 0; &q else 1 fi);
p := 1;
p := *p * q[0];
p := *p * q[1];
p := *p * q[2];
p := *p * q[3];
p := *p * q[4];
p := *p * q[5];
p := *p * q[6];
p := *p * q[7];
p := *p * q[16];
p := *p * q[17];
p := *p * q[18];
p := *p * q[19];
p := *p * q[20];
p := *p * q[21];
p := *p * q[22];
p := *p * q[23];
p := *p * q[32];
p := *p * q[33];
p := *p * q[34];
p := *p * q[35];
p := *p * q[36];
p := *p * q[37];
p := *p * q[38];
p := *p * q[39];
p := *p * q[48];
p := *p * q[49];
p := *p * q[50];
p := *p * q[51];
p := *p * q[52];
p := *p * q[53];
p := *p * q[54];
p := *p * q[55];
!!('Result: ', if p = 1 then 0; &q else 1 fi);
p := 1;
p := *p * q[0];
p := *p * q[1];
p := *p * q[2];
p := *p * q[3];
p := *p * q[4];
p := *p * q[5];
p := *p * q[6];
p := *p * q[7];
p := *p * q[8];
p := *p * q[9];
p := *p * q[10];
p := *p * q[11];
p := *p * q[12];
p := *p * q[13];
p := *p * q[14];
p := *p * q[15];
p := *p * q[32];
p := *p * q[33];
p := *p * q[34];
p := *p * q[35];
p := *p * q[36];
p := *p * q[37];
p := *p * q[38];
p := *p * q[39];
p := *p * q[40];
p := *p * q[41];
p := *p * q[42];
p := *p * q[43];
p := *p * q[44];
p := *p * q[45];
p := *p * q[46];
p := *p * q[47];
!!('Result: ', if p = 1 then 0; &q else 1 fi);
p := 1;
p := *p * q[0];
p := *p * q[1];
p := *p * q[2];
p := *p * q[3];
p := *p * q[4];
p := *p * q[5];
p := *p * q[6];
p := *p * q[9];
p := *p * q[14];
p := *p * q[15];
p := *p * q[16];
p := *p * q[19];
p := *p * q[20];
p := *p * q[23];
p := *p * q[24];
p := *p * q[25];
p := *p * q[26];
p := *p * q[27];
p := *p * q[28];
p := *p * q[29];
p := *p * q[30];
p := *p * q[31];
p := *p * q[39];
p := *p * q[40];
p := *p * q[42];
p := *p * q[43];
p := *p * q[44];
p := *p * q[45];
p := *p * q[49];
p := *p * q[50];
p := *p * q[53];
p := *p * q[54];
!!('Result: ', if p = 1 then 0; &q else 1 fi);
p := 1;
p := *p * q[0];
p := *p * q[1];
p := *p * q[2];
p := *p * q[3];
p := *p * q[4];
p := *p * q[5];
p := *p * q[6];
p := *p * q[8];
p := *p * q[10];
p := *p * q[11];
p := *p * q[12];
p := *p * q[13];
p := *p * q[14];
p := *p * q[15];
p := *p * q[16];
p := *p * q[17];
p := *p * q[18];
p := *p * q[19];
p := *p * q[20];
p := *p * q[21];
p := *p * q[22];
p := *p * q[23];
p := *p * q[24];
p := *p * q[25];
p := *p * q[26];
p := *p * q[27];
p := *p * q[28];
p := *p * q[29];
p := *p * q[30];
p := *p * q[31];
p := *p * q[39];
p := *p * q[41];
!!('Result: ', if p = 1 then 0; &q else 1 fi);