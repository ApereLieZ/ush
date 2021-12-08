#include"../inc/ush.h"

int parse_flag(char** args, bool *flag_a) {
    int z = 1;
    for(int i = 0; args[i] != NULL; i++) {
        if(args[i][0] == '-') {
            z++;
            for(int j = 0; j < mx_strlen(args[i]); j++) {
                if(args[i][j] == 'a') *flag_a = true;
            }
        }
    }
    return z;
}

int Find(char *** list, char * file_name, char * directory, int * location)
{
	DIR * opened_dir;
	struct dirent * directory_structure;
	
	char * temp_dir = (char*)malloc(sizeof(char) * 300);
	if (!temp_dir) return -1;
	
	strcat(directory, "/");	
	opened_dir = opendir(directory);
	if (opened_dir == NULL) {
                free (temp_dir);
                return -1;
        }
	
	while (1) {
		directory_structure = readdir(opened_dir);
		if (!directory_structure) {
            mx_printstr("sdaasdasdasdasd");
			closedir(opened_dir);
			free (temp_dir);
			return 0;
		}
		if (!strcmp(directory_structure->d_name, "..") || 
			!strcmp(directory_structure->d_name, ".")) continue;	
		
		else if (!strcmp(directory_structure->d_name, file_name)) {
			(*list)[*location] = (char*)malloc(sizeof(char) * 300);
			sprintf((*list)[*location], "%s%s", directory, directory_structure->d_name);
			(*location)++;
		}
		else if (directory_structure->d_type == DT_DIR) {
			sprintf(temp_dir, "%s%s", directory, directory_structure->d_name);
			if (Find(list, file_name, temp_dir, location) == -1) {
				closedir(opened_dir);
				free (temp_dir);
				return -1;
			}
		}
	}
				
	return 0;
}




void mx_which(char** args) {
    bool flag_a = false;
    int loca = parse_flag(args,  &flag_a);
    char ** found_list = (char**)malloc(sizeof(char*) * 30);
	if (!found_list) return;

	int counter_location = 0;
	
	char * ini_dir = (char*)malloc(sizeof(char) * 500);
	if (!ini_dir) {
		free (found_list);
		return;
	}

	if (args[loca]) strcpy(ini_dir, args[loca]);

    Find(&found_list, args[loca], ini_dir, &counter_location);

	
	if (counter_location > 0) {
		while (--counter_location >= 0) {
			printf("%s\n", found_list[counter_location]);
			free (found_list[counter_location]);
		}
	}
	else {
		printf("Failed to find the file!\n");
	}

	free (ini_dir);
	free (found_list);

}   



