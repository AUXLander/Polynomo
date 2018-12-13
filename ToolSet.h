#pragma once
typedef unsigned int uint;
#define __throwif__(expression,notification) if(expression){throw notification;}//read as rap god lmao
#define forever while(true)
#define ever (;;) // for ever
#define repeat(count) for(uint p3xe_i = 0; p3xe_i < (count); ++p3xe_i)
#define foreach(mass) for(uint i = 0; i < mass.length; i++)
#define forArray(arr, size, op) for(uint i = 0; i < size; i++){ arr[i] = arr[i] op; }
#define abs(value) ((value) < 0 ? (-1 * value) : (value))