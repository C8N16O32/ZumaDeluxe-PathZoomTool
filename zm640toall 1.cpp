// zm640toall.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define	FDL 128
int printreso = 1;

struct __P__ {
	float x, y; int buffersize; char **i;
};
struct __Pfloat__ {
	float x, y; int buffersize; float**i;
};

void tempsizeupper(int *size, int addsize, char ***buffer) {
	//用于在需要的时候扩大或调小动态数组
	//创建
	char ** temp;
	temp = new char*[*size];
	memset(temp, 0, *size);
	int i; for (i = 0; i < *size; i++)
	{
		*(temp + i) = new char[4];
		memset(*(temp + i), 0, 4);
	}
	//复制值
	int j; if (*size>0)
		for (i = 0; i < *size; i++)
			for (j = 0; j < 4; j++)
				*(*(temp + i) + j) = *(*(*buffer + i) + j);
	//旧空间释放，旧指针释放
	for (i = 0; i < *size; i++)
		delete[] * (*buffer + i);
	delete[] * buffer;
	*buffer = NULL;
	//创建
	*buffer = new char*[*size + addsize];
	memset(*buffer, 0, *size + addsize);
	for (i = 0; i < *size + addsize; i++)
	{
		*(*buffer + i) = new char[4];
		memset(*(*buffer + i), 0, 4);
	}
	//复制值
	if (*size > 0)
		for (i = 0; i < *size; i++)
			for (j = 0; j < 4; j++)
				*(*(*buffer + i) + j) = *(*(temp + i) + j);
	//temp空间释放，temp指针释放
	for (i = 0; i < *size; i++)
		delete[] * (temp + i);
	delete[] temp; temp = NULL;
	*size += addsize;
}
void tempsizeupper_float(int *size, int addsize, float ***buffer) {
	//用于在需要的时候扩大或调小动态数组
	//创建
	float ** temp;
	temp = new float*[*size];
	memset(temp, 0, *size);
	int i; for (i = 0; i < *size; i++)
	{
		*(temp + i) = new float[4];
		memset(*(temp + i), 0, 4);
	}
	//复制值
	int j; if (*size>0)
		for (i = 0; i < *size; i++)
			for (j = 0; j < 4; j++)
				*(*(temp + i) + j) = *(*(*buffer + i) + j);
	//旧空间释放，旧指针释放
	for (i = 0; i < *size; i++)
		delete[] * (*buffer + i);
	if (*buffer != NULL)delete[] * buffer;
	//创建
	*buffer = new float*[*size + addsize];
	memset(*buffer, 0, *size + addsize);
	for (i = 0; i < *size + addsize; i++)
	{
		*(*buffer + i) = new float[4];
		memset(*(*buffer + i), 0, 4);
	}
	//复制值
	if (*size > 0)
		for (i = 0; i < *size; i++)
			for (j = 0; j < 4; j++)
				*(*(*buffer + i) + j) = *(*(temp + i) + j);
	//temp空间释放，temp指针释放
	for (i = 0; i < *size; i++)
		delete[] * (temp + i);
	delete[] temp;
	*size += addsize;
}

int input_main(char list[][FDL], int *W0, int*W1, int *H0, int*H1) {

	//输入分辨率
	int w0 = 640, w1 = 0, h0 = 480, h1 = 0;
	printf("Width and Height(W after):");
	while (w1 == 0)scanf("%d", &w1);
	printf("Width and Height(H after):");
	while (h1 == 0)scanf("%d", &h1);

	//输入文件名
	int i = 0; char temp[256][FDL] = { "" };
	FILE *fptest = NULL;
	do {
		if (i == 0)printf("file name %d:(xxx.dat: input     help: looking help    end: finish input    "
			"\n\t\t\t\tbefore: input Width and Height(before)     \n\t\t\t\tnoreso: Overwrite source file )\n", i + 1);
		else printf("file name %d:\n", i + 1);
		scanf("%*[^\n]"); scanf("%*c");
		memset(temp[i], 0, FDL);
		scanf("%[^\n\"]", temp[i]);
		if (strlen(temp[i]) < 3)continue;
		if (strcmp(temp[i], "end") == 0)
		{
			memset(temp[i], 0, FDL); break;
		}
		if (strcmp(temp[i],"before")==0) {
			scanf("%*[^\n]"); scanf("%*c");
			printf("Width and Height(W before):");
			scanf("%d", &w0);
			printf("Width and Height(H before):");
			scanf("%d", &h0);
			continue;
		}
		if (strcmp(temp[i], "noreso") == 0) {
			printreso = 0;
			continue;
		}
		if (strcmp(temp[i], "help") == 0)
		{
			printf("[输入方式1]将.dat文件直接拖拽到命令行窗口中以输入完整路径。 新文件将保存在此路径中。 [输入方式2]输入之前，请将.dat文件放置在与此程序相同的文件夹中。 此时，您只需要输入文件名（例如xxxx.dat）即可，而不是完整路径。 新文件将保存在此文件夹中。 \n"
				"可以连续输入多个文件名(最大256个) 文件名必须带后缀(.dat) 输入end完成键入 推荐在Excel写好一列复制黏贴\n");
			printf("[Input method 1] Drag the .dat file directly into the command line window (enter the full path). The new file will be saved in this path. [Input Method 2] Put the .dat file in the same folder as this program before inputting. At this time, you only need to enter the file name (such as xxxx.dat) instead of the full path. The new file will be saved in this folder. \n"
				"You can enter multiple file names consecutively(up to 256). Enter \"end\" to finish input. It is recommended to write a column in Excel and copy&paste\n");
			printf("made by C8N16O32\n\n");
			continue;
		}
		fptest = fopen(temp[i], "r");
		if (fptest != NULL) { fclose(fptest); }
		else { printf("wrong input\n"); continue; }
		i++;
	} while (1);
	int I = i;
	//向外传值
	for (i = 0; i < I; i++)
		strcat(*(list + i), temp[i]);
	*H0 = h0; *W0 = w0; *H1 = h1; *W1 = w1;

	//返回值
	return I;
}

int wenjian_read(char* filename, float *p1x, float *p1y, int* buffersize, char ***buffer) {
	//文件结构：文件头 12字节 关键点块大小 4字节 路径信息总数 4字节  路径信息1 两个f32两个int8 路径信息2 两个i8两个i8
	FILE* fp = NULL;
	fp = fopen(filename, "rb");
	int i = 0;

	//略过关键点块
	fseek(fp, 12, SEEK_SET);
	int point1zonesize = 0;
	fread(&point1zonesize, sizeof(int), 1, fp);

	//路径总数
	fseek(fp, 16 + point1zonesize, SEEK_SET);
	int point2zonesize = 0;
	fread(&point2zonesize, sizeof(int), 1, fp);

	//路径信息1
	float sx = 0, sy = 0;
	char **data = NULL;
	i = 0; tempsizeupper(&i, point2zonesize, &data);
	fread(&sx, sizeof(float), 1, fp);
	fread(&sy, sizeof(float), 1, fp);
	*(*(data + 0) + 0) = '0'; *(*(data + 0) + 1) = '0';
	fread(*(data + 0) + 2, sizeof(char), 1, fp);
	fread(*(data + 0) + 3, sizeof(char), 1, fp);

	//路径信息n
	int j;
	for (i = 1; i < point2zonesize; i++)
		for (j = 0; j < 4; j++)
			fread(*(data + i) + j, sizeof(char), 1, fp);
	fclose(fp);

	//传值
	if (*buffersize < point2zonesize)
		tempsizeupper(buffersize, point2zonesize - *buffersize, buffer);
	for (i = 1; i < point2zonesize; i++) {
		for (j = 0; j < 4; j++)
			*(*(*buffer + i) + j) = *(*(data + i) + j);
		delete[] * (data + i);
	}
	delete[] data;
	*p1x = sx; *p1y = sy;

	return 0;
}

int lujing_forge_somemath(float *a1x, float *a1y, float a0x, float a0y, float b1x, float b1y, float b0x, float b0y) {
	//对b1进行检查
	if (sqrt((double)((b1x - a0x)*(b1x - a0x) + (b1y - a0y)*(b1y - a0y))) < 1.0)return 1;
	//方向向量 此长度
	float dx = b1x - b0x, dy = b1y - b0y, dxdy = dx*dy, d = (float)sqrt(dx*dx + dy*dy);
	//归一化方向向量 归一化法向向量(左旋90度)
	float dx1 = dx / d, dy1 = dy / d, dxdy1 = dx1*dy1, dx2 = -dy1, dy2 = dx1;
	//直线方程 点与直线距离
	float base = (b0x*dx2 + b0y*dy2), basea0 = (a0x*dx2 + a0y*dy2), dbase = basea0 - base;
	//往前的距离
	float len = sqrt(1 - (fabs(dbase) > 1 ? 1 : dbase*dbase));
	//算出新的点
	float a1xtemp = a0x - dbase*dx2 + len*dx1, a1ytemp = a0y - dbase*dy2 + len*dy1;
	//传值
	//printf("%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2lf\n", a1xtemp, a1ytemp, b1x, b1y,dbase,len,sqrt((double)((a1xtemp - a0x)*(a1xtemp - a0x) + (a1ytemp - a0y)*(a1ytemp - a0y))));
	*a1x = a1xtemp; *a1y = a1ytemp;
	return 0;
}

int lujing_forge(float p1x, float p1y, int buffersize1, char **buffer, float *p2x, float *p2y, int *buffersize2, char ***buffer2, int rex0, int rey0, int rex1, int rey1) {
	//流程： 1缩放 2重新布置偏移量(简化版本) 3传值
	int i, j;

	//buffer→temp2:从char偏移量转化到float坐标 并且完成缩放
	double kx = rex1*1.0 / rex0, ky = rey1*1.0 / rey0;
	struct __Pfloat__ temp2 { p1x*kx, p1y*ky, 0, NULL };
	tempsizeupper_float(&temp2.buffersize, buffersize1 - temp2.buffersize, &temp2.i);
	*(*(temp2.i) + 0) = temp2.x;
	*(*(temp2.i) + 1) = temp2.y;
	for (i = 1; i < buffersize1; i++) {
		*(*(temp2.i + i) + 0) = *(*(temp2.i + i - 1) + 0) + *(*(buffer + i) + 0) / 100.0*kx;
		*(*(temp2.i + i) + 1) = *(*(temp2.i + i - 1) + 1) + *(*(buffer + i) + 1) / 100.0*ky;
	}

	//temp2→temp3:重新生成坐标 buffer→temp4:接收char格式的坑道数据
	struct __Pfloat__ temp3 { temp2.x, temp2.y, 0, NULL };
	struct __P__ temp4 { temp3.x, temp3.y, 0, NULL };
	tempsizeupper_float(&temp3.buffersize, 1000, &temp3.i);
	tempsizeupper(&temp4.buffersize, temp3.buffersize - temp4.buffersize, &temp4.i);
	*(*(temp3.i + 0) + 0) = temp3.x; *(*(temp3.i + 0) + 1) = temp3.y;
	*(*(temp4.i + 0) + 2) = *(*(buffer + 0) + 2); *(*(temp4.i + 0) + 3) = *(*(buffer + 0) + 3);
	int ia = 1, ib = 1;
	while (1) {
		if (lujing_forge_somemath(*(temp3.i + ia) + 0, *(temp3.i + ia) + 1, *(*(temp3.i + ia - 1) + 0), *(*(temp3.i + ia - 1) + 1),
			*(*(temp2.i + ib) + 0), *(*(temp2.i + ib) + 1), *(*(temp2.i + ib - 1) + 0), *(*(temp2.i + ib - 1) + 1)))
		{
			if (ib < temp2.buffersize - 1) { ib++; continue; }
			else break;
		}
		if (ia == temp3.buffersize - 1) {
			tempsizeupper_float(&temp3.buffersize, 1000, &temp3.i);
			tempsizeupper(&temp4.buffersize, temp3.buffersize - temp4.buffersize, &temp4.i);
		}
		*(*(temp4.i + ia) + 2) = *(*(buffer + ib) + 2);
		*(*(temp4.i + ia) + 3) = *(*(buffer + ib) + 3);
		ia++;
	}
	for (i = ia; i < temp3.buffersize; i++)
	{
		delete[] * (temp3.i + i); delete[] * (temp4.i + i);
	}
	temp3.buffersize = ia; temp4.buffersize = ia;


	//temp3→temp4:坐标转化到char格式的偏移量
	float t4x = temp4.x, t4y = temp4.y;
	for (i = 1; i < temp4.buffersize; i++) {
		*(*(temp4.i + i) + 0) = (int)((*(*(temp3.i + i) + 0) - t4x) * 100);
		*(*(temp4.i + i) + 1) = (int)((*(*(temp3.i + i) + 1) - t4y) * 100);
		t4x += *(*(temp4.i + i) + 0) / 100.0;
		t4y += *(*(temp4.i + i) + 1) / 100.0;
		//printf("%d\t%d\t%d\t%d\t%d\t", i, *(*(temp4.i + i) + 0), *(*(temp4.i + i) + 1), *(*(temp4.i + i) + 2),*(*(temp4.i + i) + 3));
	}

	//temp4→buffer2:传值
	tempsizeupper(buffersize2, temp4.buffersize, buffer2);
	*p2x = temp4.x; *p2y = temp4.y;
	for (i = 0; i < temp4.buffersize; i++)
		for (j = 0; j < 4; j++)
			*(*(*buffer2 + i) + j) = *(*(temp4.i + i) + j);

	//内存回收
	for (i = 0; i < temp2.buffersize; i++)
		delete[] * (temp2.i + i); delete[]temp2.i;
	for (i = 0; i < temp3.buffersize; i++) {
		delete[] * (temp3.i + i);
		delete[] * (temp4.i + i);
	}
	delete[]temp3.i; delete[]temp4.i;

	return 0;
}

int wenjian_write(char*filename, int w, int h, float sx, float sy, int buffersize, char**buffer) {
	//文件结构：文件头 12字节 关键点块大小 4字节 路径信息总数 4字节  路径信息1 两个f32两个int8 路径信息2 两个i8两个i8

	//1 再次打开原文件，获取前半部分的内容
	FILE* fp = NULL;
	fp = fopen(filename, "rb");
	int i = 0;
	//关键点块
	fseek(fp, 12, SEEK_SET);
	int point1zonesize = 0;
	fread(&point1zonesize, sizeof(int), 1, fp);
	char talk_old[8000] = "";//前部内容
	fseek(fp, 16+4, SEEK_SET);
	fread(talk_old, sizeof(char), point1zonesize-4, fp);
	fclose(fp);

	//2 准备待写入的内容
	static char filehead[] = { 0x43,0x55,0x52,0x56,0x02,0x00,0x00,0x00,0x01,0x00,0x00,0x00 };
	int blocksize = 4 + strlen(talk_old), numofkeypoint = 0, i32bsize = buffersize;
	static char selfhead[] = "\r\n\r\n"
		"\t _   _      ___          _       _            ___ ___ _  _ _  __  ___ _______\r\n"
		"\t| | | |_ __/ __| __ __ _| |___  | |__ _  _   / __( _ ) \\| / |/ / / _ \\__ /_  )\r\n"
		"\t| |_| | '_ \\__ \\/ _/ _` | / -_) | '_ \\ || | | (__/ _ \\ .` | / _ \\ (_) |_ \\/ /\r\n"
		"\t \\___/| .__/___/\\__\\__,_|_\\___| |_.__/\\_, |  \\___\\___/_|\\_|_\\___/\\___/___/___|\r\n"
		"\t      |_|                             |__/\r\n\r\n";
	int selfcheck = 0;
	if (strstr(talk_old, selfhead) == NULL)
	{
		selfcheck = 1;
		blocksize += strlen(selfhead);
	}

	char filenamenew[FDL+32] = "", reso[32] = "", temp1[FDL+32] = "", *temp2 = NULL, temp3[FDL+32] = "";
	if (printreso) {
		sprintf(reso, "(%dx%d)", w, h);
		temp2 = strstr(filename, ".dat");
		strncpy(temp1, filename, temp2 - filename);
		strncpy(temp3, temp2, strlen(filename) - (temp2 - filename));
		strcat(filenamenew, temp1);
		strcat(filenamenew, reso);
		strcat(filenamenew, temp3);
	}
	else strcat(filenamenew, filename);
	//3 写入文件

	fp = NULL;
	fp = fopen(filenamenew, "wb");
	fwrite(filehead, sizeof(char), 12, fp);//文件头
	//为了可读性 (可以这么做是因为新文件头最后换了一行 全部填入了\20)
	blocksize += 2;
	//为了可读性 end
	fwrite(&blocksize, sizeof(int), 1, fp);//关键点块大小
	fwrite(&numofkeypoint, sizeof(int), 1, fp);//关键点数量=0
	fwrite(talk_old, sizeof(char), strlen(talk_old), fp);//旧的文件头信息
	if (selfcheck)fwrite(selfhead, sizeof(char), strlen(selfhead), fp);//新文件头信息
	//为了可读性 (可以这么做是因为新文件头最后换了一行 全部填入了\20)
	fwrite("\20\20", sizeof(char), 2, fp);
	//为了可读性 end
	fwrite(&i32bsize, sizeof(_int32), 1, fp);//路径总数
	fwrite(&sx, sizeof(float), 1, fp);//以下是关键点1
	fwrite(&sy, sizeof(float), 1, fp);
	fwrite(*buffer + 2, sizeof(char), 1, fp);
	fwrite(*buffer + 3, sizeof(char), 1, fp);
	int j;	//以下是其余关键点
	for (i = 1; i < buffersize; i++)
		for (j = 0; j < 4; j++)
			fwrite(*(buffer + i) + j, sizeof(char), 1, fp);
	fclose(fp);

	return 0;
}

int main()
{
	//tsyysr=提示语与输入
	char fileindexlist[256][FDL] = { "" };
	int w0, w1, h0, h1, i, I;
	I = input_main(fileindexlist, &w0, &w1, &h0, &h1);

	//处理多个dat
	int filei; struct __P__ p1 = { 0,0,0,NULL }, p2 = { 0,0,0,NULL };
	for (filei = 0; filei < I; filei++) {
		//读取文件
		wenjian_read(fileindexlist[filei], &p1.x, &p1.y, &p1.buffersize, &p1.i);//可以传结构体 但是内部会过于复杂
		//转化轨道
		lujing_forge(p1.x, p1.y, p1.buffersize, p1.i, &p2.x, &p2.y, &p2.buffersize, &p2.i, w0, h0, w1, h1);
		//写回文件
		wenjian_write(fileindexlist[filei], w1, h1, p2.x, p2.y, p2.buffersize, p2.i);
		//释放内存,初始化
		for (i = 0; i < p1.buffersize; i++)delete[] * (p1.i + i); delete[]p1.i; p1.i = NULL; p1.buffersize = 0; p1.x = 0; p1.y = 0;
		for (i = 0; i < p2.buffersize; i++)delete[] * (p2.i + i); delete[]p2.i; p2.i = NULL; p2.buffersize = 0; p2.x = 0; p2.y = 0;
	}

	//结束
	return 0;
}
