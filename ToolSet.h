#pragma once
typedef unsigned int uint;
#define __throwif__(expression,notification) if(expression){throw notification;}//read as rap god lmao
#define forever while(true)
#define ever (;;) // for ever
#define repeat(count) for(uint rep_i = 0, rep_c = count; rep_i < rep_c; rep_i++)
#define foreach(mass) for(uint for_i = 0; for_i < mass.length; for_i++)
#define forArray(arr, size, op) for(uint i = 0; i < size; i++){ arr[i] = arr[i] op; }
#define abs(value) ((value) < 0 ? (-value) : (value))