#include "command_functions.h"

void show_command (command * C)
{
    int i;

    printf ("\tRaw command: \"%s\"\n", C->raw_command);
    printf ("\tNumber of arguments: %d\n", C->argc);

    for (i=0; i<=C->argc; i++)
        if (C->argv[i] != NULL)
            printf ("\t\targv[%d]: \"%s\"\n", i, C->argv[i]);
        else
            printf ("\t\targv[%d]: NULL\n", i);

    if (C->input)
        printf ("\tInput: \"%s\"\n", C->input);

    if (C->output)
        printf ("\tOutput: \"%s\"\n", C->output);

    if (C->output_err)
        printf ("\tErr. output: \"%s\"\n", C->output_err);

    printf ("\tExecute in background: %s\n",
            C->background ? "Yes" : "No");
}

void exec_cmd(command * C, char *initpath)
{
	//execute the command C
    if (!C->argc)
    {
    	return;
    }
    else if (strcmp(C->argv[0],"help")==0)
    {
        printf("%s\n", HELP);
        return;
    }
    else if (strcmp(C->argv[0],"mypwd")==0)
    {
    	if(!C->argv[1])
    	{
        	char *cwd= mypwd();
        	printf("%s\n", cwd);
        	free(cwd);
    	}
    	else
    		printf("Too many arguments\n");
    	return;
    }
    else if (strcmp(C->argv[0],"myls")==0)
    {
        myls(C->argv[1], C->argv[2]);
        return;
    }
    else if (strcmp(C->argv[0],"mymkdir")==0)
    {
    	//create as much directories as arguments passed
        int i = 1;
        while(C->argv[i])
        {
            mymkdir(C->argv[i]);
            i++;
        }
        return;
    }
    else if (strcmp(C->argv[0],"myrmdir")==0)
    {
    	//remove as much directories as arguments passed
        int i = 1;
        while(C->argv[i])
        {
            myrmdir(C->argv[i]);
            i++;
        }
        return;
    }
    else if (strcmp(C->argv[0],"mycd")==0)
    {
        mycd(C->argv[1], initpath);
        return;
    }
    else if (strcmp(C->argv[0],"mycat")==0)
    {
    	//view as much directories as arguments passed
        int i = 1;
        while(C->argv[i])
        {
            mycat(C->argv[i]);
            i++;
        }
        return;
    }
    else if (strcmp(C->argv[0],"mycp")==0)
    {
        mycp(C->argv[1], C->argv[2]);
        return;
    }
    else if (strcmp(C->argv[0],"myrm")==0)
    {
    	//remove as much files as arguments passed
        int i = 1;
        while(C->argv[i])
        {
            myrm(C->argv[i]);
            i++;
        }
        return;
    }
    else if (strcmp(C->argv[0],"exit")==0)
    {
        exit(0);
    }
    else
        printf("Command not found! :'(\n");
}

char *mypwd()
{
	//return current working directory
    size_t size = pathconf(".", _PC_PATH_MAX);
    char *buf = (char *)malloc(size);

    return getcwd(buf, size);
}

void myls(char *arg1, char *arg2)
{
	char *cwd = mypwd();
    DIR *folder;
    struct dirent *dir;

    if (arg1)
    {
        //ls -l | ls folder | ls -l folder
        if (strcmp(arg1,"-l")==0)
        {
            if (arg2)
            {
                //ls -l folder
                if ((folder = opendir(arg2))!=NULL)
                    print_dir_details(folder, arg2);
                else
                    printf("%s\n", strerror(errno));
            }
            else
            {
                //ls -l
                if ((folder = opendir(cwd))!=NULL)
                    print_dir_details(folder, cwd);
                else
                    printf("%s\n", strerror(errno));
            }
        }
        else
        {
            //ls folder
            if ((folder = opendir(arg1))!=NULL)
            {
                while ((dir = readdir(folder)) != NULL)
                    printf("%s\t", dir->d_name);
                printf("\n");
            }
            else
                printf("%s\n", strerror(errno));
        }
    }
    else
    {
        //ls
        if ((folder = opendir(cwd))!=NULL)
        {
            while ((dir = readdir(folder)) != NULL)
                printf("%s\t", dir->d_name);
            printf("\n");
        }
        else
            printf("%s\n", strerror(errno));
    }
    free(cwd);
}

void mymkdir(char *inputPath)
{
	//make a new directory
    if((mkdir(inputPath, S_IRWXU))==-1)
        printf("%s\n",  strerror(errno));
}

void myrmdir(char *inputPath)
{
	//delete a directory
    if((rmdir(inputPath))==-1)
        printf("%s\n",  strerror(errno));
}

void mycd(char *inputPath, char *init)
{
    if (inputPath)
    {
    	//go to the passed directory, if passed
        if((chdir(inputPath))==-1)
            printf("%s\n", strerror(errno));
    }
    else
    {
    	//if no directoy passed go to the initial launch directory
        if((chdir(init))==-1)
            printf("%s\n", strerror(errno));
    }
}

void mycat(char *inputPath)
{
	//print the contents of a file
    int fd;
    char *file;
    struct stat statbuf;
    off_t off = 0;			//bytes currently read

    if((fd = open(inputPath, O_RDONLY))==-1)
    {
        printf("%s\n", strerror(errno));
        return;
    }

    if (fstat(fd, &statbuf)==0)
        if (S_ISDIR(statbuf.st_mode))
        {
            printf("Is a directory\n");
            return;
        }

    //while file size > bytes read, read again
    while(lseek(fd, 0, SEEK_END) > off)
    {
	    file = (char *)mmap(NULL, BUFSIZE, PROT_READ, MAP_SHARED, fd, off);
	    printf("%s", file);
	    off+=BUFSIZE;
	    munmap((void *)file, BUFSIZE);
	}
	printf("\n");
    close(fd);
}

void mycp(char *file1, char *file2)
{
	//copy one file into another file
    int f1fd, f2fd;		//file descriptors for both files
    char data[BUFSIZE];	//maximum size you can read
    ssize_t _size;		//real size read
    struct stat statbuf;

    if((f1fd = open(file1, O_RDONLY))==-1)
    {
        printf("%s\n", strerror(errno));
        return;
    }    

    if (fstat(f1fd, &statbuf)==0)
        if (S_ISDIR(statbuf.st_mode))
        {
            printf("Is a directory\n");
            return;
        }

    f2fd = creat(file2, 0666);

    //while you can read more data [bufsize] write the bytes read
    while((_size = read(f1fd, data, sizeof(data)))>0)
        write(f2fd, data, _size);

    close(f1fd);
    close(f2fd);
}

void myrm(char *inputPath)
{
	//remove (unlink) file passed
    if((unlink(inputPath))==-1)
        printf("%s\n", strerror(errno));
}

char *parse_permissions(mode_t mode)
{
	//create one readable string from the permissions -rwxrw-r-- type
    static char perm[11];
    char *permissions = perm;
    
    int i;
    for (i = 0; i < 10; ++i)	//initialize the string to ----------
    {
        permissions[i]='-';
    }

    if (S_ISDIR(mode))      //is directory
        permissions[0]='d';

    if (S_ISFIFO(mode))     //is pipe
        permissions[0]='p';

    // ...and all posible file types

    if (mode & S_IRUSR)     //owner read permission
        permissions[1]='r';

    if (mode & S_IWUSR)     //owner write permission
        permissions[2]='w';

    if (mode & S_IXUSR)     //owner execute permission
        permissions[3]='x';

    if (mode & S_IRGRP)     //group read permission
        permissions[4]='r';

    if (mode & S_IWGRP)     //group write permission
        permissions[5]='w';

    if (mode & S_IXGRP)     //group execute permission
        permissions[6]='x';

    if (mode & S_IROTH)     //others read permission
        permissions[7]='r';

    if (mode & S_IWOTH)     //others write permission
        permissions[8]='w';

    if (mode & S_IXOTH)     //others execute permission
        permissions[9]='x';

    return permissions;    
}

void print_dir_details(DIR *tdir, char *inputPath)
{
	//print the data form passed DIR and path
    struct dirent *dir;
    struct stat statbuf;

    struct passwd *pwd;
    struct group *grp;
    struct tm *tm;
    char datestring[256];

    while ((dir = readdir(tdir)) != NULL)
    {
    	//create the complete path
        char *completePath = (char *)malloc(strlen(inputPath)+1+strlen(dir->d_name)+1);
        strcpy(completePath, inputPath);
        strcat(completePath, "/");
        strcat(completePath, dir->d_name);

        if (stat(completePath, &statbuf)==0)
        {
            //size
            printf(" %llu\t", (long long unsigned int)statbuf.st_size); //%lld to compile in Mac OS X | %zu to compile in linux

            //user id
            if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
                printf(" %s", pwd->pw_name);
            else
                printf(" %s", strerror(errno));

            //group id
            if ((grp = getgrgid(statbuf.st_gid)) != NULL)
                printf(" %s", grp->gr_name);
            else
                printf(" %s", strerror(errno));  

            //types & permissions
            printf(" %s ", parse_permissions(statbuf.st_mode));

            //last modification time
            tm = localtime(&statbuf.st_mtime);
            strftime(datestring, sizeof(datestring), "%b %d %X", tm); //%b %d %X - Month, day and hour
            printf(" %s ", datestring);  

            //name
            printf(" %s\n", dir->d_name);                           
        }
        else
            printf(" %s\n", strerror(errno));

        free(completePath);
    }
}