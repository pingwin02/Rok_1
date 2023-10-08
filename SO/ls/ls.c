#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define WHITE "\x1b[37m"

struct Options {
    int isD; 
    int isR; 
    int isL;
    int isA;
    int isH;
    int isS;
};

void Usage() {
    printf("Składnia: ./ls [OPCJA]... [PLIK]...\n");
    printf("Wypisuje zawartość folderu\n");
    printf("\nOpcje\n-R\twypisuje zawartość wszystkich podfolderów\n");
    printf("-l\twypisuje więcej szczegółów\n");
    printf("-d\tpokazanie katalogów zamiast ich zawartości\n");
    printf("-h\tz opcją -l podaje rozmiary z potęgami bajta\n");
    printf("-a\tbez ukrywania plików zaczynających się od .\n");
    printf("-S\tsortowanie według rozmiaru, największe najpierw\n");
    return;
}

void UpdateDir(char* currentpath, char* homepath, const char* foldername){
    if (foldername == NULL) {
    sprintf(currentpath,"%s",homepath);
    return;
    }

    sprintf(currentpath, "%s/%s", homepath, foldername);
}

char temppath[512];

char* getCreationDate(struct stat mystat) {

    char* time = ctime(&mystat.st_ctime);
    if (time[strlen(time)-1] == '\n') 
        time[strlen(time)-1] = '\0';

    return time;
}

char* getSize(double size, int flag) {

    char* buf = malloc(sizeof(char)* 20);

    if (flag) {
        int i = 0;
        const char* units[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
        while (size > 1024) {
            size /= 1024;
            i++;
        }
        sprintf(buf, "%.2f %s", size, units[i]);
    }
    else {
        sprintf(buf,"%.f", size);
    }

    return buf;
}

char* printPermissions(struct stat fileStat){
    printf(GREEN);
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
}

int alphasort_improved(const struct dirent **a, const struct dirent **b) {
    return strcasecmp((*a)->d_name, (*b)->d_name);
}

int sizesort(const struct dirent **a, const struct dirent **b) {
    struct stat mystatA, mystatB;
    char tmp[512];
    UpdateDir(tmp,temppath, (*a)->d_name);
    stat(tmp, &mystatA);
    UpdateDir(tmp,temppath, (*b)->d_name);
    stat(tmp, &mystatB);

    return mystatA.st_size < mystatB.st_size;
}

void RecDir(char * path, struct Options opt) {
    struct dirent** namelist;
    struct stat mystat;
    char currentPath[512];
    printf(BLUE "\n %s :\n" WHITE, path);
    int n = 0;
    if (opt.isS) {
        UpdateDir(temppath,path,NULL);
        n = scandir(path, &namelist,0, sizesort);
    } else {
        n = scandir(path, &namelist,0, alphasort_improved);
    }
    if (n < 0) {
        perror("scandir");
    }
    else {
        for (int i = 0; i < n; i++) {
            if((strncmp(namelist[i]->d_name, ".", 1) || opt.isA) && !opt.isD) {
                if (opt.isL) {
                    UpdateDir(currentPath, path, namelist[i]->d_name);
                    stat(currentPath, &mystat);
                    printPermissions(mystat);
                    char* size = getSize(mystat.st_size,opt.isH);
                    printf(" %d %s %s\t %s\t %s %s\n" WHITE, mystat.st_uid, getpwuid(mystat.st_uid)->pw_name, 
                    getgrgid(mystat.st_gid)->gr_name, size, getCreationDate(mystat), namelist[i]->d_name);
                    free(size);
                } else {
                    printf(GREEN "%s\t" WHITE, namelist[i]->d_name);
                }
            }
        }
        if (opt.isR) {
            for (int i = 0; i < n; i++) {
                if(strncmp(namelist[i]->d_name, ".", 1)) {
                    if(namelist[i]->d_type == 4) {
                        UpdateDir(currentPath, path, namelist[i]->d_name);
                        RecDir(currentPath, opt);
                    }
                }
            }
        }
        while (n--) {
            free(namelist[n]);
        } 
        free(namelist);
    }
}

int main(int argc, char ** argv) {

    char* path;

    if (argc != 1 && argv[argc-1][0] != '-') {
        path = argv[argc-1];
    }
    else {
        path = ".";
    }

    struct Options opt;

    opt.isD = 0; opt.isR = 0; opt.isL = 0; opt.isA = 0; opt.isH = 0; opt.isS = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strchr(argv[i],'R')) {
                opt.isR = 1;
            }
            if (strchr(argv[i],'l')) {
                opt.isL = 1;
            }
            if (strchr(argv[i],'d')) {
                opt.isD = 1;
            }
            if (strchr(argv[i],'a')) {
                opt.isA = 1;
            }
            if (strchr(argv[i],'h')) {
                opt.isH = 1;
            }
            if (strchr(argv[i],'S')) {
                opt.isS = 1;
            }
            if (!strcmp(argv[i], "--help")) {
                Usage();
                return 0;
            }
        }
    }
    RecDir(path,opt);
    printf("\n");

    return 0;
}