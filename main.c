#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
//Lesson 11
void ls_files(const char *path, bool R);
void help(void);

int main(int argc, char **argv) {
    if(argc > 1){
        if(strcmp(argv[1], "-h") == 0){
            help();
        } else if(strcmp(argv[1], "-f") == 0){
            if(argv[2]){
                ls_files(argv[2], true);
            } else{
                ls_files(".", true);
            }
        }
    } else{
        ls_files(".", false);
    }

    return 0;
}

void help(void){
    printf("Prototype: ./main [option][directory (default '.')]\n");
    printf("Options:\n");
    printf("-f recursive\n");
    printf("-h description\n");
}


void ls_files(const char *path, bool R) {
    DIR *dir;
    struct dirent *ent;

    struct stat file_info;
    char *new_dir;
    size_t needed;
    int N = 1;
    char drents[N][256];

    dir = opendir(path);

    printf("%s:\n", path);
    while ((ent=readdir(dir)) != false) {
        if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0){
            continue;
        }
        stat(ent->d_name, &file_info);
        if((file_info.st_mode & S_IFMT) == S_IFDIR){
            printf("\x1b[36m%s\x1b[0m ", ent->d_name);
            if(R == true){
                needed = snprintf(new_dir, 0, "%s/%s", path, ent->d_name) + 1;
                new_dir = malloc(needed);
                sprintf(new_dir, "%s/%s", path, ent->d_name);
                for (int i = 0; i < strlen(new_dir) + 1; ++i) {
                    drents[N - 1][i] = new_dir[i];
                }
                N++;
            }
        } else{
            printf("%s ", ent->d_name);
        }
    }
    printf("\n\n");
    if(R == true){
        N --;
        for (int i = 0; i < N; ++i) {
            ls_files(drents[i], true);
        }
    }

    closedir(dir);

}


