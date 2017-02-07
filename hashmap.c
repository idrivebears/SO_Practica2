#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash(char * input, int range) 
{
	int i;
	int n = (int)strlen(input);
	int res = 5381;

	for(i=0; i < n; i++) {
		res = ((res << 5) + res) + input[i];
	}

	return res % range;
}

int *create_hashmap(int size) 
{
	int *map = (int *) malloc(sizeof(int)*size);
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
	unsigned int location = hash(input, range);

	printf("Inserting val:%d into loc:%d\n", value,location);

	if(map[location] == -1) {
		map[location] = value;
		return 1;  //success, no collision
	}
	else {
		return 0; // fail, collision found
	}
}

int main()
{
	int MAP_SIZE = 20;
	int *my_map = create_hashmap(MAP_SIZE);

	int i;
	for(i = 0; i < MAP_SIZE; i++) 
	{
		printf("%d,", my_map[i]);
	}
	printf("\n");

	insert_hashmap(my_map, "thisisatest",hash("birds", MAP_SIZE));
	
	if(insert_hashmap(my_map, "thisisbtest", hash("birds", MAP_SIZE)) == 0) {
		printf("insert failure\n");
	}

	for(i = 0; i < MAP_SIZE; i++) 
	{
		printf("%d,", my_map[i]);
	}
	printf("\n");

	printf("Retrieving 'user': %d\n", get_hashmap(my_map, hash("user", MAP_SIZE)));

	return 0;
}