#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>

const char character_list[1000]="qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
static const char *dirpath = "/home/nanda/shift4/";

static int xmp_getattr(const char *path, struct stat *stbuf){
    int res;
    char fpath[1000]; char final[1000];
    int key = 17;
	char x; int i,j;
	char enkrip[strlen(path)];
	strcpy(enkrip,path);
	for(i=0;i<strlen(enkrip);i++) {
		x=enkrip[i];
		if(x=='/') {
			enkrip[i]=x;
		}
		else {
			j=0;
			while(x!=character_list[j]) {
				j++;
			}
			j=(j+key)%strlen(character_list);
			enkrip[i]=character_list[j];
		}
	}
	puts(enkrip);
	strcpy(fpath,enkrip);
    sprintf(fpath,"%s%s",dirpath,path);
    //
    res = lstat(fpath, stbuf);
    if(res == -1){
        return -errno;
    }
    return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,off_t offset, struct fuse_file_info *fi){
    char final[1000];
	int key = 17;
    char x;
    int i,j;
	if(strcmp(path,"/") == 0){
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else{
		char enkrip[strlen(path)];
		strcpy(enkrip,path);
		for(i=0;i<strlen(enkrip);i++) {
			x=enkrip[i];
			if(x=='/') {
				enkrip[i]=x;
			}
			else {
				j=0;
				while(x!=character_list[j]) {
					j++;
				}
				j=(j+key)%strlen(character_list);
				enkrip[i]=character_list[j];
			}
		}
		sprintf(final,"%s%s",dirpath,enkrip);
	}
//
    char fpath[1000];
    int mode=atoi("0333");
    /*if(strcmp(path,"/") == 0){
        path=dirpath;
        sprintf(fpath,"%s",path);
    }
    else sprintf(fpath, "%s%s",dirpath,path);*/
    int res = 0;
    DIR *dp;
    struct dirent *de;

    (void) offset;
	(void) fi;

    dp = opendir(fpath);
    if(dp==NULL){ return -errno; }

    freopen("home/nanda/shift4/filemiris.txt","w",stdout);
    while((de = readdir(dp))!=NULL){
        struct stat sb;
        stat(de->d_name,&sb);

        struct passwd *pw = getpwuid(sb.st_uid);
        struct group *gr = getgrgid(sb.st_gid);
        
        if((strcmp(pw->pw_name,"chipset")||strcmp(pw->pw_name,"ic_controller")) && strcmp(gr->gr_name,"rusak") && chmod(de->d_name,mode)>=0){
            printf("%s\t%d\t%d\t%s\n",de->d_name,sb.st_uid,sb.st_gid,ctime(&sb.st_atime));
        }
        else if{
            strcpy(dekrip,de->d_name);
				for(i=0;i<strlen(dekrip);i++) {
					x=dekrip[i];
					if(x=='/') {
						dekrip[i]=x;
					}
					else {
						j=0;
						while(x!=character_list[j]) {
							j++;
						}
						if(j<17) {
							j=j+strlen(character_list);
						}
						j=(j-key)%strlen(character_list);
						dekrip[i]=character_list[j];
					}
				}

				strcpy(de->d_name,dekrip);

				//res = (filler(buf, de->d_name, &st, 0));
					//if(res!=0) break;
        }
        remove(de->d_name);
        res = filler(buf, de->d_name, &sb,0);
        if(res!=0) break;
    }
    fclose(stdout);
    closedir(dp);
    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,struct fuse_file_info *fi)
{
	char final[1000];
	int res = 0;
	int fd = 0 ;
	(void) fi;
	int key = 17;
	char x;
	int i,j;
	char fpath[1000];
	char enkrip[strlen(path)];
	strcpy(enkrip,path);

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		for(i=0;i<strlen(enkrip);i++) {
			x=enkrip[i];
			if(x=='/') {
				enkrip[i]=x;
			}
			else {
				j=0;
				while(x!=character_list[j]) {
					j++;
				}
				j=(j+key)%strlen(character_list);
				enkrip[i]=character_list[j];
			}
		}
		sprintf(final,"%s%s",dirpath,enkrip);
	}

	strcpy(fpath,final);

	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	//close(fd);
	return res;
}

static int xmp_mknod(const char *path,mode_t mode, dev_t rdev){
    char filename[1001],fpath[1001];
    sprintf(fpath,"%s%s",dirpath,filename);
    return 0;
}

static int xmp_create(const char *path,mode_t mode, struct fuse_file_info* fi){
    int res;
    char filename[1001],fpath[1001];
    char final[1000];
    int key = 17;
	char x; int i,j;
	char enkrip[strlen(path)];
	strcpy(enkrip,path);
	if(strcmp(path,"/") == 0){
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		char enkrip[strlen(path)];
		strcpy(enkrip,path);
		for(i=0;i<strlen(enkrip);i++) {
			x=enkrip[i];
			if(x=='/') {
				enkrip[i]=x;
			}
			else {
				j=0;
				while(x!=character_list[j]) {
					j++;
				}
				j=(j+17)%strlen(character_list);
				enkrip[i]=character_list[j];
			}
		}
		sprintf(final,"%s%s",dirpath,enkrip);
	}

    (void) fi;

    strcpy(filename,fpath);
    memset(fpath,0,sizeof(fpath));
    sprintf(fpath,"%s%s",dirpath,filename);
    int idx = strlen(fpath);
    while(true){
        if(fpath[--idx]=='/') break;
    }
    while(true){
        if(fpath[--idx]=='/') break;
    }
    idx+=1;

    char dir_youtube[1001],dir_temp[1001];
    char mode_p[4]="0640";
    i=atoi(mode_p);
    memset(dir_temp,0,sizeof(dir_temp));
    strncat(dir_temp,(fpath+idx),16*sizeof(char));

    if(strcmp(dir_youtube,dir_temp)==0) res = creat(fpath,i);
    else res = creat(fpath,mode);

    if(res==-1) return -errno;
    close(res);

    memset(filename,0,sizeof(filename));
    strcpy(filename,fpath);

    if(strcmp(dir_youtube,dir_temp)==0){
        strcat(filename,".iz1");
        char *argv[]={"cp",filename,fpath};
        pid_t child_id = fork();
        if(child_id==0) execlp(argv[0],argv[0],argv[1],argv[2],NULL);
        remove(fpath);
        chmod(filename,i);    
    }
    return 0;
}

static int xmp_chmod(const char *path, mode_t mode){
    int res;
    char filename[1001],fpath[1001];
    char final[1000];
    int key = 17;
	char x; int i,j;
	char enkrip[strlen(path)];
	strcpy(enkrip,path);
	if(strcmp(path,"/") == 0){
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		char enkrip[strlen(path)];
		strcpy(enkrip,path);
		for(i=0;i<strlen(enkrip);i++) {
			x=enkrip[i];
			if(x=='/') {
				enkrip[i]=x;
			}
			else {
				j=0;
				while(x!=character_list[j]) {
					j++;
				}
				j=(j+17)%strlen(character_list);
				enkrip[i]=character_list[j];
			}
		}
		sprintf(final,"%s%s",dirpath,enkrip);
	}

    memset(fpath,0,sizeof(fpath));
    strcpy(filename,path);
    strcpy(fpath,dirpath);
    strcat(fpath,filename);

    char dir_youtube[1001],dir_temp[1001];
    memset(dir_temp,0,sizeof(dir_temp));

    if(strcmp(dir_youtube,dir_temp)==0){
        const char *ext = strrchr(fpath,'.');
        if(strcmp(ext,".iz1")==0){
            char *argv[4]={"zenity","--warning","--text='File ekstensi iz1 tidak boleh diubah permissionnya.\n'",NULL};
            pid_t child_id = fork();
            
            if(!child_id) execv("/usr/bin/zenity",argv);
            return 0;
        }
        else res = chmod(fpath,mode);
    }
    else res = chmod(fpath,mode);

    if(res==-1) return -errno;
    return 0;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid){
    int res;
    char filename[1001],fpath[1001];
    strcpy(filename,path);
    strcpy(fpath,dirpath);
    strcat(fpath,filename);
    res = lchown(fpath,uid,gid);
    if(res == -1){
        return errno;
    }
    return 0;
}

static int xmp_mkdir(const char *path, mode_t mode){
    int res,idx;
    char filename[1001],fpath[1001];
    char final[1000];
    int key = 17;
	char x; int i,j;
	char enkrip[strlen(path)];
	strcpy(enkrip,path);
	if(strcmp(path,"/") == 0){
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		char enkrip[strlen(path)];
		strcpy(enkrip,path);
		for(i=0;i<strlen(enkrip);i++) {
			x=enkrip[i];
			if(x=='/') {
				enkrip[i]=x;
			}
			else {
				j=0;
				while(x!=character_list[j]) {
					j++;
				}
				j=(j+17)%strlen(character_list);
				enkrip[i]=character_list[j];
			}
		}
		sprintf(final,"%s%s",dirpath,enkrip);
	}

    strcpy(filename,fpath);
    memset(fpath,0,sizeof(fpath));
    sprintf(fpath,"%s%s",dirpath,filename);
    idx = strlen(fpath);
    while(true){
        if(fpath[--idx]=='/') break;
    }
    while(true){
        if(fpath[--idx]=='/') break;
    }
    idx+=1;

    char dir_youtube[1001],dir_temp[1001];
    memset(dir_temp,0,sizeof(dir_temp));
    strncat(dir_temp,(fpath+idx),16*sizeof(char));

    if(strcmp(dir_youtube,dir_temp)==0) res = mkdir(fpath,0750);
    else res = mkdir(fpath,mode);
    if(res == -1) return -errno;
    return 0;
}

static int xmp_write(const char *path, const char *buf, size_t size,off_t offset, struct fuse_file_info *fi){
    int fdir,res;
    char filename[1001],fpath[1001],source_dir[1001];
    char final[1000];
    int key = 17;
	char x; int i,j;
	char enkrip[strlen(path)];
	strcpy(enkrip,path);
	if(strcmp(path,"/") == 0){
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		char enkrip[strlen(path)];
		strcpy(enkrip,path);
		for(i=0;i<strlen(enkrip);i++) {
			x=enkrip[i];
			if(x=='/') {
				enkrip[i]=x;
			}
			else {
				j=0;
				while(x!=character_list[j]) {
					j++;
				}
				j=(j+17)%strlen(character_list);
				enkrip[i]=character_list[j];
			}
		}
		sprintf(final,"%s%s",dirpath,enkrip);
	}


    strcpy(filename,path);
    memset(fpath,0,sizeof(fpath));
    strcpy(fpath,dirpath);
    strcat(fpath,filename);
    strcpy(source_dir,fpath);

    fdir=open(fpath,O_WRONLY); 
    if(fdir==-1) return -errno;
    res = pwrite(fdir,buf,size,offset);
    if(res==-1) res=-errno;
    close(fdir);

    int idx=strlen(fpath);
    while(true){
        if(fpath[--idx]=='/') break;
    }
    strcpy(filename,fpath+idx);
    fpath[idx]=0;
    strcat(fpath,"----"); //encrypt?
    
    char *argv[]={"mkdir",fpath,"0750"};
    pid_t child_id = fork();
    if(child_id==0) execlp(argv[0],argv[0],argv[1],argv[2],NULL);

    const char *ext = strrchr(filename,'.');
    char ext_file[101];
    idx=(int)(ext-filename);
    if(idx>0){ strcpy(ext_file,filename+idx); filename[idx]=0; }
    else memset(ext_file,0,sizeof(ext_file));

    char fname_time[50];
    time_t now;
    time(&now);
    struct tm *cur_time = localtime(&now);
    strftime(fname_time,50,"/%Y-%m-%d_%H:%M:%S",cur_time); //encrypt?
    

    char fpath_temp[1001];
    sprintf(fpath_temp,"%s%s%s%s",fpath,filename,fname_time,ext_file);
    (void) fi;

    if(fpath_temp[0]!='.'){
        pid_t child_id = fork();
        if(!child_id){
            char *arg[]={"cp",source_dir,fpath_temp,NULL};
            execlp(arg[0],arg[0],arg[1],arg[2],NULL);
        }
    }

    return res;
}

static int xmp_utimens(const char *path, const struct timespec ts[2]){
	int res;
    struct timeval tv[2];
    char fpath[1000]; char final[1000];
    int key = 17;
	char x; int i,j;
	char enkrip[strlen(path)];
	strcpy(enkrip,path);
    char filename[1001], fpath[1001];
    memset(filename,0,sizeof(filename));
    strcpy(filename,path);
    memset(fpath,0,sizeof(fpath));
    strcpy(fpath,dirpath);
    strcat(fpath,filename);

    if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		for(i=0;i<strlen(enkrip);i++) {
			x=enkrip[i];
			if(x=='/') {
				enkrip[i]=x;
			}
			else {
				j=0;
				while(x!=character_list[j]) {
					j++;
				}
				j=(j+key)%strlen(character_list);
				enkrip[i]=character_list[j];
			}
		}
		sprintf(final,"%s%s",dirpath,enkrip);
	}

	tv[0].tv_sec = ts[0].tv_sec;
	tv[0].tv_usec = ts[0].tv_nsec / 1000;
	tv[1].tv_sec = ts[1].tv_sec;
	tv[1].tv_usec = ts[1].tv_nsec / 1000;

	res = utimes(fpath, tv);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_unlink(const char *path){
    char filename[1001],fpath[1001],cur_filename[1001],file_zip[1001];
    int idx;
    DIR *dp;
    struct dirent *de;
    char fpath[1000]; char final[1000];
    int key = 17;
	char x; int i,j;
	char enkrip[strlen(path)];
	strcpy(enkrip,path);
    if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		for(i=0;i<strlen(enkrip);i++) {
			x=enkrip[i];
			if(x=='/') {
				enkrip[i]=x;
			}
			else {
				j=0;
				while(x!=character_list[j]) {
					j++;
				}
				j=(j+key)%strlen(character_list);
				enkrip[i]=character_list[j];
			}
		}
		sprintf(final,"%s%s",dirpath,enkrip);
	}

    strcpy(filename,path);
    memset(fpath,0,sizeof(fpath));
    strcpy(fpath,dirpath);
    strcat(fpath,filename);
    strcpy(cur_filename,fpath);

    const char *ext_dir = strrchr(fpath,'/');
    char ext_fdir[101];
    idx=(int)(ext_dir-fpath);
    strcpy(ext_fdir,fpath+idx); 
    fpath[idx]=0;
    sprintf(file_zip,"%s/----",fpath); //encrypt?

    char mode_p[4]="0750";
    char *argv[]={"mkdir",file_zip,mode_p};
    pid_t child_id = fork();
    if(child_id==0) execlp(argv[0],argv[0],argv[1],argv[2],NULL);

    const char *ext = strrchr(filename,'.');
    char ext_file[101];
    idx=(int)(ext-filename);
    if(idx>0){ strcpy(ext_file,filename+idx); filename[idx]=0; }
    else memset(ext_file,0,sizeof(ext_file));

    char fname_time[50];
    time_t now;
    time(&now);
    struct tm *cur_time = localtime(&now);
    strftime(fname_time,50,"_%Y-%m-%d_%H:%M:%S",cur_time);

    char file_zip_temp[1001];
    memset(file_zip_temp,0,sizeof(file_zip_temp));
    sprintf(file_zip_temp,"%s%s-------%s%s------",file_zip,filename,fname_time,ext_file); //encrypt
    strcat(fpath,"/-----"); //encrypt

    int st;
    pid_t parent_id = fork();
    if(parent_id>0) waitpid(parent_id,&st,0);
    else if(parent_id==0){
        char *arg[]={"zip","-jm", file_zip_temp,cur_filename};
        execlp(arg[0],arg[0],arg[1],arg[2],arg[3],NULL);
        exit(0);
    }
    else if(parent_id==-1) return -1;
    char p[1001];
    dp = opendir(fpath);
    if(dp==NULL) return 0;
    
    while((de = readdir(dp))!=NULL){
        memset(p,0,sizeof(p));
        sprintf(p,"%s",filename+1);
        if(strcmp(de->d_name,p)==0){
            const char *ext_p = strrchr(de->d_name,'.');
            if(strcmp(ext_p,ext)){
                pid_t parent_id = fork();
                if(parent_id>0) waitpid(parent_id,&st,0);
                else if(parent_id==0){
                    char p_tar[1001];
                    memset(p,0,sizeof(p));
                    strcpy(p,fpath);
                    sprintf(p_tar,"%s/%s",p,de->d_name);
                    char *arg[]={"zip","-jm", file_zip_temp,p};
                    execlp(arg[0],arg[0],arg[1],arg[2],arg[3],NULL);
                    exit(0);
                }
            }
        }
    }

    char file_final[1001],zip_final[1001];
    strcpy(p,file_zip_temp);
    sprintf(file_final,"%s-------",p);
    sprintf(zip_final,"%s.zip",file_zip_temp);

    char *arg[]={"cp",file_final,zip_final};
    pid_t child_id1 = fork();
    if(child_id1==0) execlp(arg[0],arg[0],arg[1],arg[2],NULL);
    remove(fpath);

    return 0;
}

static struct fuse_operations xmp_oper =
{
    .getattr = xmp_getattr,
    .readdir = xmp_readdir,
    .read	= xmp_read,
    .chmod = xmp_chmod,
    .chown = xmp_chown,
    .mknod = xmp_mknod,
    .create = xmp_create,
    .mkdir = xmp_mkdir,
    .write = xmp_write,
    .unlink = xmp_unlink,
    .utimens = xmp_utimens
};

int main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &xmp_oper,NULL);
}
