
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char* argv[]){
	uint32_t total sum =0;
	for (int i = 1; i < argc; i+=1){
		
		FILE* pFile = fopen(argv[i],"rb");
		
		if(pFile == NULL) // 4byte 보다 작을때 -> 오류 처리
		{
			fprintf(stderr, "Error opening file: %s\n",argv[i]);
			return 1;
		}
		fseek(pFile, 0, SEEK_END);
		long file_size = ftell(pFile);
		rewind(pFile);

		if (file_size <4){
			fprintf(stderr,"Error: %s is less than 4 bytes\n",argv[i]);
			fclose(pFile);
			return 1;
		}
		uint32_t value;
		fread(&value, sizeof(uint32_t), 1, pFile);
		fclose(pFile);
		total_sum += value;
		printf("%s : 0x%08x (%u)\n" ,argv[i], value, value);
	}
	printf("Total : 0x%08x (%u)\n", total_sum, total_sum);
	return 0;

}

