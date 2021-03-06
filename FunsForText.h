#define L 1337
#include <time.h>

void showContent(char route[])                           //显示指定目录内文本文件内容
{
    FILE *fp = NULL;
    fp = fopen(route,"rb");
    if(fp==NULL){failReboot();}

    char a='\0';
    while(!feof(fp))                                     //显示内容
    {
        a = fgetc(fp);
        putchar(a);
    }
    if(route == "content\\header.dat")
        putchar('\n');

    fclose(fp);
}

void addContent(char route[])                           //为指定文本文件增添内容
{
    FILE *fp = NULL;
    fp = fopen(route,"ab");
    system("cls");
    showContent(route);

    char cont[L];
    gets(cont);
    if(route == "content\\data.dat")
    {
        time_t t;
        struct tm *lt;
        time (&t);
        lt = localtime (&t);
        fprintf(fp,"=%d.%02d.%02d_%02d:%02d:%02d=:",lt->tm_year+1900,lt->tm_mon+1,lt->tm_mday,lt->tm_hour,lt->tm_min,lt->tm_sec);
    }
    fprintf(fp,"%s\n",cont);
    fclose(fp);
}

void removeLines(char route[])                               //按行删除
{
    FILE *fp = NULL,*fp3 = NULL;
    fp = fopen(route,"rb");
    if(fp==NULL){failReboot();}
    FILE *fp2 = fopen("content\\temp.dat","wb");            //生成临时文件

    if(route == "content\\data.dat")
        fp3 = fopen("content\\bin.dat","ab");
    else
        fp3 = fopen("content\\data.dat","ab");

    system("cls");
    if(route == "content\\data.dat" || route == "content\\bin.dat")
    showContent("content\\header.dat");

    char a='\0',b='\0';
    int i = 0;
    int t = 1;
    while(!feof(fp))                                        //为行数编号
    {
        a = fgetc(fp);
        if(feof(fp))
            break;
        if(t==1)
        {
            if(route == "content\\data.dat" || route == "content\\bin.dat")
                printf("%03d ",i+1);
            else
                printf("%02d ",i+1);
            t = 0;
        }
        putchar(a);
        if(a=='\n')
        {
            i++;
            t = 1;
        }
    }
    fclose(fp);

    printf("\nChoose the first line to be ");                   //选择开始行
    if(route == "content\\bin.dat")
        printf("recovered.\n");
    else
        printf("deleted.\n");
    printf("Line No:");

    int choose1,choose2,search=1;
    a='\0';
    scanf("%d",&choose1);
    getchar();

    printf("\nChoose the last line to be ");                    //选择结束行
    if(route == "content\\bin.dat")
        printf("recovered.\n");
    else
        printf("deleted.\n");
    printf("Line No:");
    scanf("%d",&choose2);
    getchar();
    if(choose1 > choose2)
    {
        int temp;
        temp = choose2;
        choose2 = choose1;
        choose1 = temp;
    }
    if(choose1>i || choose1 <= 0 || choose2>i || choose2 <= 0)                             //行不存在
    {
        printf("\nError. Please make sure you've entered the right numbers.\n");
        printf("Press any key to continue...");
        getch();
    }
    else                                                    //删除
    {
        fp = fopen(route,"rb");
        if(fp==NULL){failReboot();}
    while(!feof(fp))
    {
        a = fgetc(fp);
        if(search == choose1)
        {
            if(route != "content\\header.dat")
            fputc(a,fp3);
            while(1)
            {
                a = fgetc(fp);
                if(route != "content\\header.dat")
                    fputc(a,fp3);
                if(a == '\n')
                    search++;
                if(search > choose2)
                {
                    if(a == '\n')
                    {
                        a = fgetc(fp);
                        break;
                    }
                }
            }
        }
        if(a != EOF)
            fputc(a,fp2);                                    //将除选定行之外内容复制到临时文件
        if(a=='\n')
            search++;
    }
        fclose(fp);
        fclose(fp2);
        fclose(fp3);

        fp = fopen(route,"wb");                             //清空原文件并将临时文件内容写进原文件
        fp2 = fopen("content\\temp.dat","rb");
        if(fp2==NULL){failReboot();}
        while(!feof(fp2))
        {
            b = fgetc(fp2);
            if(b != EOF)
                fputc(b,fp);
        }
        fclose(fp);
        fclose(fp2);
        }
    remove("content\\temp.dat");                            //删除临时文件
}

void removeLine(char route[])                               //按行删除
{
    FILE *fp = NULL,*fp3 = NULL;
    fp = fopen(route,"rb");
    if(fp==NULL){failReboot();}
    FILE *fp2 = fopen("content\\temp.dat","wb");            //生成临时文件

    if(route == "content\\data.dat")
        fp3 = fopen("content\\bin.dat","ab");
    else
        fp3 = fopen("content\\data.dat","ab");

    system("cls");
    if(route == "content\\data.dat" || route == "content\\bin.dat")
    showContent("content\\header.dat");

    char a='\0',b='\0';
    int i = 0;
    int t = 1;
    while(!feof(fp))                                        //为行数编号
    {
        a = fgetc(fp);
        if(feof(fp))
            break;
        if(t==1)
        {
            if(route == "content\\data.dat" || route == "content\\bin.dat")
                printf("%03d ",i+1);
            else
                printf("%02d ",i+1);
            t = 0;
        }
        putchar(a);
        if(a=='\n')
        {
            i++;
            t = 1;
        }
    }
    fclose(fp);

    printf("\nChoose the line to be ");           //选择一行删除
    if(route == "content\\bin.dat")
        printf("recovered.\n");
    else
        printf("deleted.\n");

    printf("Line No:");
    int choose,search=1;
    a='\0';
    scanf("%d",&choose);
    getchar();
    if(choose>i || choose <= 0)                             //行不存在
    {
        printf("\nLine doesn't exist.\n");
        printf("Press any key to continue...");
        getch();
    }
    else                                                    //删除
    {
        fp = fopen(route,"rb");
        if(fp==NULL){failReboot();}

    while(!feof(fp))
    {
        a = fgetc(fp);
        if(search == choose)
        {
            if(route != "content\\header.dat")
                fputc(a,fp3);

            while(a != '\n')
            {
                a = fgetc(fp);
                if(route != "content\\header.dat")
                    fputc(a,fp3);
            }
        }
        if(a != EOF)
            fputc(a,fp2);                                    //将除选定行之外内容复制到临时文件
        if(a=='\n')
            search++;
    }
        fclose(fp);
        fclose(fp2);
        fclose(fp3);

        fp = fopen(route,"wb");                             //清空原文件并将临时文件内容写进原文件
        fp2 = fopen("content\\temp.dat","rb");
        if(fp2==NULL){failReboot();}
        search = 1;
        while(!feof(fp2))
        {
            b = fgetc(fp2);
            if(b == '\n')
            {
                if(search == choose)
                    b = fgetc(fp2);
                search++;
            }
            if(b != EOF)
                fputc(b,fp);
        }
        fclose(fp);
        fclose(fp2);
        }
    remove("content\\temp.dat");                            //删除临时文件
}

void clearContent(char route[])                             //清空
{
    FILE *fp = NULL,*fp2 = NULL;
    fp = fopen(route,"rb");
    if(fp==NULL){failReboot();}

    system("cls");
    if(route == "content\\data.dat")
        fp2 = fopen("content\\bin.dat","ab");

    showContent("content\\header.dat");

    printf("Are you sure? 1 = Yes,0 = No");
    char c;
    choose:
    c = getch();
    if(c = '1')
    {
        char a = '\0';
        while(!feof(fp))
        {
            a = fgetc(fp);
            if(a != EOF)
                fputc(a,fp2);
        }
    }
    fclose(fp2);
    switch(c)
    {
        case '1':fp = fopen(route,"wb");break;
        case '0':break;
        default:goto choose;
    }
    fclose(fp);
}

void insertContent(char route[])
{
    FILE *fp = NULL,*fp2 = NULL;
    fp = fopen(route,"rb");
    if(fp==NULL){failReboot();}
    fp2 = fopen("content\\temp.dat","wb");
    system("cls");
    if(route == "content\\data.dat")
        showContent("content\\header.dat");

    char a='\0',b='\0';
    int i = 0;
    int t = 1;
    while(!feof(fp))                                        //为行数编号
    {
        a = fgetc(fp);
        if(feof(fp))
            break;
        if(t==1)
        {
            if(route == "content\\data.dat" || route == "content\\bin.dat")
                printf("%03d ",i+1);
            else
                printf("%02d ",i+1);
            t = 0;
        }
        putchar(a);
        if(a=='\n')
        {
            i++;
            t = 1;
        }
    }
    fclose(fp);

    printf("\nChoose the line to insert after.\n");           //选择一行
    printf("Line No:");
    int choose,search=1;
    a='\0';
    scanf("%d",&choose);
    getchar();
    if(choose>i || choose <=0 )                             //行不存在
    {
        printf("\nLine doesn't exist.\n");
        printf("Press any key to continue...");
        getch();
    }
    else
    {
        fp = fopen(route,"rb");
        if(fp==NULL){failReboot();}
    printf("Now enter the content: ");                      //输入插入内容
    char cont[L];
    gets(cont);
    while(!feof(fp))
    {
        a = fgetc(fp);
        if(search == choose)
        {
            fputc(a,fp2);
            while(a != '\n')
            {
                a = fgetc(fp);
                fputc(a,fp2);
            }
            if(route == "content\\data.dat")
            {
                time_t t;
                struct tm *lt;
                time (&t);
                lt = localtime (&t);
                fprintf(fp2,"=%d.%02d.%02d_%02d:%02d:%02d=:",lt->tm_year+1900,lt->tm_mon+1,lt->tm_mday,lt->tm_hour,lt->tm_min,lt->tm_sec);
            }
            fprintf(fp2,"%s",cont);                         //在完成复制指定行后插入内容
        }
        if(a != EOF)
            fputc(a,fp2);

        if(a=='\n')
            search++;
        }
        fclose(fp);
        fclose(fp2);

        fp = fopen(route,"wb");                             //清空原文件并将临时文件内容写进原文件
        fp2 = fopen("content\\temp.dat","rb");
        if(fp2==NULL){failReboot();}
        search = 1;
        while(!feof(fp2))
        {
            b = fgetc(fp2);
            if(b != EOF)
                fputc(b,fp);
        }
        fclose(fp);
        fclose(fp2);
        }
    remove("content\\temp.dat");                            //删除临时文件
}

void failReboot()                                        //读取失败重新初始化
{
    printf("Failed to read file, rebooting...");
    delay(30);
    main_menu();//Write where you want it back next.
}

void delay(int T)                                        //延时
{
    int i,t;
    for(t=0;t<T;t++)
    {
        i=0;
        while(i<600000)
        {
            i++;
        }
    }
}
