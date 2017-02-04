#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(char * input, int range) 
{
	int i;
	int n = (int)strlen(input);
	int res = 0;

	for(i=0; i < n; i++) {
		res += (int)input[i] * i;
	}

	return res % range;
}

int *create_hashmap(int size) 
{
	int map[size];
	int i;
	
	for(i = 0; i < size; i++) {
		map[i] = -1;
	}

	return map;
}

int get_hashmap(int *map, int i) 
{
	return map[i];
}

int insert_hashmap(int *map, char * input, int value)
{
	int range = sizeof(map)/sizeof(int);
	int location = hash(input, range);

	if(map[location] == -1) {
		map[location] = value;
		return 1;  //success, no collision
	}
	else {
		return 0; // fail, collision found
	}
}