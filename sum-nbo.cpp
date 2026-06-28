
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char* argv[]){
	uint32_t total_sum =0;
	for (int i = 1; i < argc; i+=1){
		
		FILE* pFile = fopen(argv[i],"rb");
		
		if(pFile == NULL) 
		{
			fprintf(stderr, "Error opening file: %s\n",argv[i]);
			return 1;
		}
		fseek(pFile, 0, SEEK_END);
		long file_size = ftell(pFile);
		rewind(pFile);
		// 4byte 보다 작을 때 오류 처리
		if (file_size <4){
			fprintf(stderr,"Error: %s is less than 4 bytes\n",argv[i]);
			fclose(pFile);
			return 1;
		}
		uint32_t value;
		fread(&value, sizeof(uint32_t), 1, pFile);
		uint32_t part_1 = value & 0xFF000000;
		part_1 = part_1 >> 24;
		uint32_t part_2 = value & 0x00FF0000;
		part_2 = part_2 >> 8;
		uint32_t part_3 = value & 0x0000FF00;
		part_3 = part_3 << 8;
		uint32_t part_4 = value & 0x000000FF;
	        part_4 = part_4 << 24;
		
		value = part_1 | part_2 | part_3 | part_4;

		fclose(pFile);
		total_sum += value;
		printf("%s : 0x%08x (%u)\n" ,argv[i], value, value);
	}
	printf("Total : 0x%08x (%u)\n", total_sum, total_sum);
	return 0;

}

