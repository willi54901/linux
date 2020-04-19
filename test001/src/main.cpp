
#include <stdio.h>
#include <unistd.h>
//#include <string.h>
#include"yaxml.h"
#include "YAThread.h"

void  testFreeStruct(){
	printf("struct ta size = %d\n",sizeof( struct Ta));
	a_t* pa =  (a_t*)malloc(sizeof( struct Ta)*3);
	printf("p_struct ta size = %d\n",sizeof( pa));
	printf("struct 实例ta size = %d\n",sizeof( &pa));
	char * cs = "dddd";
	pa->a = cs;
	printf("a= %s\n",pa->a);
	printf("p_struct ta size = %d\n",sizeof( pa));
	printf("struct 实例ta size = %d\n",sizeof( &pa));
     cs  = "ssssfff";
	 pa->a = cs;
	printf("a= %s\n",pa->a);
	free(pa);
	info_t *pinfo = (Info*)malloc(sizeof( struct Info));

   pinfo->pdevices =  (Device*)malloc(sizeof( struct Device)*3);

	printf("info devices  size = %d\n",sizeof( pinfo->pdevices ));

	printf("p_so size = %d\n",sizeof( &pinfo->pdevices ));
	free( pinfo->pdevices );
	free( pinfo );
	// printf("p_struct ta size = %d\n",sizeof( psp));
	// printf("struct 实例ta size = %d\n",sizeof( &psp));

	// char * cs = "dddd";
	// pa->a = cs;
	// printf("a= %s\n",pa->a);
	// printf("p_struct ta size = %d\n",sizeof( psp));
	// printf("struct 实例ta size = %d\n",sizeof( &psp));
   //  cs  = "ssss";
	//printf("a= %s\n",pa->a);
//	free(psp);

}
void *task(void *str)
{
	//	sleep(1);
	printf((char *)str);
	return NULL;
}

int xmlTest()
{
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL, pcur = NULL;
	/*****************打开xml文档********************/
	xmlKeepBlanksDefault(0);									//必须加上，防止程序把元素前后的空白文本符号当作一个node
	pdoc = xmlReadFile("a.xml", "UTF-8", XML_PARSE_RECOVER); //libxml只能解析UTF-8格式数据

	if (pdoc == NULL)
	{
		printf("error:can't open file!\n");
		exit(1);
	}
	xmlChar *xmlbuff;
	int buffersize;
	xmlDocDumpFormatMemory(pdoc, &xmlbuff, &buffersize, 1);
	printf("xml size = %d\n%s\n", buffersize,xmlbuff);
	yaxmlfreeXmlDoc(pdoc);


	 time_t t_start, t_end;
    t_start = time(NULL) ;
	printf("计时开始\n");	
	for(int i =0 ;i<100000;i++){
		pdoc = xmlParseMemory((char *)xmlbuff,xmlStrlen(xmlbuff)+1);
		request_t*  pxml =(request_t*)malloc(sizeof( struct Request)); ;
		yaxmlcreateXmlStructFromXmlDoc(pdoc,pxml);
		yaxmlfreeXmlStruct(pxml);
		yaxmlfreeXmlDoc(pdoc);
	}
    t_end = time(NULL) ;
    printf("计时结束   time: %.0f s\n", difftime(t_end,t_start)) ;

	return 0;
}

int main(int argc, char const *argv[])
{
	int loop = 0;
	YAThread th = YAThread();
	th.createFixedPools(1, 100, 2048);
    xmlTest();
	//testFreeStruct();
	while (loop < 10000)
	{
		loop++;
		sleep(3);
		char str[] = "Helloworld-----------------------------------------------------------33\n";
		printf("put task  0x%x\n", loop);

		//			 th.threadpool_add_task(task,str);
	}
	return 0;
}
