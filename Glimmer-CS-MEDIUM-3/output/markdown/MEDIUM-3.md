# MEDIUM-3：初识Linux系统

## 第一境:算者--命令行参数与路径

### 任务1.1

(1) ***绝对路径和相对路径:*** 绝对路径与当前工作目录无关,永远指同一个目录;相对路径代表指定目录与当前工作目录的相对位置关系.

(2) ***命令:***

- 绝对路径命令为 `cd /var/backups/turing/`
- 相对命令路径为`cd ../../../var/backups/turing/`

### 任务1.2

(1) ***含义如下:***

- argc:表示命令行参数的总个数,包含程序本身的名称;
- argv[]:一个字符指针数组,每个元素指向一个命令行参数字符串.

(2) ***针对任务1.1的命令：***
>因为上述命令好像只有声明函数这句,就按任务1.1的绝对路径命令来算

- argc的值为**2**;
- `argv[0]`指向程序名`cd`;
- `argv[1]`指向路径`/var/backups/turing/`;
- `argv[2]`不存在,其值为`NULL`.

## 第二境：算王--重建ls命令与位运算

### 任务2.1

(1) ***关于头文件***

- 见过的:
  - `<stdio.h>`打印
  - `<string.h>`字符串处理
  - `<stdlib.h>`内存分配,程序退出
  - `<time.h>`时间处理.
- 没见过的(Linux系统专属):
  - `<dirent.h>`
  - `<sys/stat.h>`
  - `<sys/types.h>`
  
(2) ***`<dirent.h>`和`<sys/stat.h>`***

- `<dirent.h>`
  - 关键结构体:`DIR`,`struct dirent`;
  - 关键函数:`opendir()`,`readdir()`,`closedir()`;
  - 作用:遍历目录内容.
- `<sys/stat.h>`
  - 关键结构体:`struct stat`;
  - 关键函数:`stat()`;
  - 作用:查询文件的元数据.

### 任务2.2

```c
void parse_permissions(mode_t mode, char *perms) {

    // 权限字符对照表
    char rwx[] = {'r', 'w', 'x'};

    // 请补全代码写在 TO DO 与 END OF TO DO 之间：
    // TO DO

    for(int i = 0; i <= 8; i++)
        perms[i] = (mode & (1 << (8 - i))) ? rwx[i % 3] : '-';

    // END OF TO DO

    perms[9] = '\0'; // 字符串结尾
}
```

## 第三境：算尊—— 深入理解 Inode 与文件树

### 任务3.1

(1) ***Inode存了哪些信息?***

- 文件大小,权限,所有者,时间戳,链接数,指向数据块的指针,文件类型.

(2) ***Inode不含什么?***

- 文件名,所在路径,文件具体内容.

(3) ***目录***

- 1.`.`代表当前目录,`..`代表父目录.
- 2.在根目录`/`下,`.`和`..`的`inode编号相同,都等于根目录的inode.

### 任务3.2

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

ino_t get_inode(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) == -1) {
        perror("stat failed");
        exit(EXIT_FAILURE);
    }
    return statbuf.st_ino;
}

int main(){

    char names[1000][256];
    int n = 0;

    while(1){
        
        ino_t cur = get_inode(".");
        chdir("..");

        ino_t par = get_inode(".");
        if (cur == par) break;

        DIR* dir = opendir(".");
        struct dirent* entry;
        
        while((entry = readdir(dir)) != NULL){

            if (strcmp(entry->d_name , ".") == 0 || strcmp(entry->d_name , "..") == 0)continue;

            if (get_inode(entry->d_name) == cur){
              strcpy(names[n] , entry->d_name);
              n++;
              break;
            }
        }
        closedir(dir);
    }

    if (n == 0){
      printf("/\n");}

    else{
        for(int i = n - 1; i >= 0; i--){
            printf("/%s",names[i]);
        }
    }
    return 0;
}
```

>本题借助AI生成原理与示例并分块学习,以上代码为对照示例模仿写出来的,语法不够熟练,但可以理解算法

- 思考过程:
  - 要在不使用cwd的情况下求绝对路径,需要回到父目录的对照表查询编号对应的名字,逐行查询,直到查询成功就停止循环;
  - 查询之前保存自己的编号;
  - 之后再回到下一个父目录,此时出现了问题:父目录的具体个数不知道,于是设置了while循环,直到`..`指向自己(根目录)就停止,程序判断为爬之后的编号等于爬之前的,引入par;
  - 查询完毕后想要打印,需要一个起存放作用的数组,由于readdir会复用内存,所以一旦查到名字就strcpy保存在里面;
  - 但是因为是从里向外查询,数组中的名字是倒序,于是建立for循环,使i = n - 1,每打印一次就-1,这样就可以把names[i]倒序打印;
  - 如果本来就在根目录,直接打印`/`即可.

## 最终境：算帝—— 递归与文件筛选

### 任务4.1

```c
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// 递归查找指定文件，若找到则打印其相对路径
void find_file(const char *current_path, const char *target_name) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    if (!(dir = opendir(current_path))) {
        return; // 无法打开目录则跳过
    }

    while ((entry = readdir(dir)) != NULL) {
        // 忽略当前目录 . 和父目录 .. 防止无限死循环
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", current_path, entry->d_name);

        if (stat(full_path, &statbuf) == -1) continue;

        // 请补全代码写在 TO DO 与 END OF TO DO 之间：
        // 要求：
        // 1. 检查当前 entry 的文件名是否与 target_name 匹配，若匹配则打印 full_path。
        // 2. 如果当前 entry 是一个目录，则需要对其进行深度优先的递归查找。
        // （提示：若(statbuf.st_mode & S_IFMT) == S_IFDIR则statbuf为目录文件）
        // TO DO

      if (strcmp(entry->d_name, target_name) == 0)
    printf("%s\n", full_path);

if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
    find_file(full_path, target_name);

        // END OF TO DO
    }
    closedir(dir);
}
```
