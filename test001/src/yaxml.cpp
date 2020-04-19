#include "yaxml.h"

int yaxmlcreateXmlStructFromXmlDoc(xmlDocPtr pdoc, request_t *pxml)
{

	xmlNodePtr proot = NULL, pcur = NULL;
	if (pdoc == NULL)

	{
		pxml->pdoc = pdoc;
		printf("error:can't open file!\n");
		return -1;
	}

	/*****************获取xml文档对象的根节对象********************/
	proot = xmlDocGetRootElement(pdoc);

	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		exit(1);
	}

	/*****************查找书店中所有书籍的名称********************/
	pcur = proot->xmlChildrenNode;

	while (pcur != NULL)
	{

		//如同标准C中的char类型一样，xmlChar也有动态内存分配，字符串操作等 相关函数。例如xmlMalloc是动态分配内存的函数；xmlFree是配套的释放内存函数；xmlStrcmp是字符串比较函数等。
		//对于char* ch="book", xmlChar* xch=BAD_CAST(ch)或者xmlChar* xch=(const xmlChar *)(ch)
		//对于xmlChar* xch=BAD_CAST("book")，char* ch=(char *)(xch)

		if (!xmlStrcmp(pcur->name, BAD_CAST("Info")))
		{
			pxml->pinfo = (info_t *)malloc(sizeof(struct Info));
			xmlNodePtr pinfo = pcur->xmlChildrenNode;
			while (pinfo != NULL)
			{
				if (!xmlStrcmp(pinfo->name, BAD_CAST("FSUID"))){
					 pxml->pinfo->FSUID = XML_GET_CONTENT(pinfo->xmlChildrenNode);	
					 pinfo = pinfo->next;
					continue;
				}
				
				if (!xmlStrcmp(pinfo->name, BAD_CAST("DeviceList")))
				{
					xmlNodePtr pdevice = pinfo->xmlChildrenNode;
					int soCnt = 0;
					while (pdevice != NULL)
					{
						if (!xmlStrcmp(pdevice->name, BAD_CAST("Device")))
						{
							soCnt++;
						}
						pdevice = pdevice->next;
					}
					if (soCnt > 0)
					{
						pxml->pinfo->pdevices_size = soCnt;
						pxml->pinfo->pdevices = (device_t *)malloc(sizeof(struct Device) * soCnt);
						soCnt = 0;
						pdevice = pinfo->xmlChildrenNode;
						while (pdevice != NULL)
						{
							if (!xmlStrcmp(pdevice->name, BAD_CAST("Device")))
							{
								 pxml->pinfo->pdevices[soCnt].DeviceID = xmlGetProp(pdevice, BAD_CAST("DeviceID"));
								 pxml->pinfo->pdevices[soCnt].DeviceType = xmlGetProp(pdevice, BAD_CAST("DeviceType"));
								xmlNodePtr psp = pdevice->xmlChildrenNode;
								int spCnt = 0;
								while (psp != NULL)
								{
									if (!xmlStrcmp(psp->name, BAD_CAST("TSemaphore")))
									{
										spCnt++;
									}
									psp = psp->next;
								}
								if (spCnt > 0)
								{
									pxml->pinfo->pdevices[soCnt].psemaphores_size = spCnt;
									pxml->pinfo->pdevices[soCnt].psemaphores = (semaphore_t *)   malloc(sizeof(struct TSemaphore) * spCnt);
									spCnt = 0;
									psp = pdevice->xmlChildrenNode;
									while (psp != NULL)
									{
										if (!xmlStrcmp(psp->name, BAD_CAST("TSemaphore")))
										{
											pxml->pinfo->pdevices[soCnt].psemaphores[spCnt].ID =  xmlGetProp(psp, BAD_CAST("ID"));
											pxml->pinfo->pdevices[soCnt].psemaphores[spCnt].SignalNumber = xmlGetProp(psp, BAD_CAST("SignalNumber"));
											spCnt++;
										}
										psp = psp->next;
									}
								}
								soCnt++;
							}
							pdevice = pdevice->next;
						}
					}
				}
				pinfo = pinfo->next;
			}

			
		}
		if (!xmlStrcmp(pcur->name, BAD_CAST("PK_Type")))
		{
			if (!xmlStrcmp(pcur->xmlChildrenNode->name, BAD_CAST("Name")))
			{
				pxml->ppktype = (PK_Type_t *)malloc(sizeof(struct PK_Type));
			   pxml->ppktype->pname = XML_GET_CONTENT(pcur->xmlChildrenNode->xmlChildrenNode);
			}
		}
		pcur = pcur->next;
	}
}
int  yaxmlfreeXmlDoc(xmlDocPtr  pdoc){
	if (pdoc != NULL)
	{
		/*****************释放资源********************/
		xmlFreeDoc(pdoc);
		xmlCleanupParser();
		xmlMemoryDump();
		return 1;
	}
	return -1;
}

int yaxmlfreeXmlStruct(request_t *pxml)
{
	if (pxml == NULL)
		return 0;

	if (pxml->ppktype != NULL)
	{
		//	if(pxml->ppktype->pname != NULL){
		// 		xmlFree(pxml->ppktype->pname);
		// 	}
		free(pxml->ppktype);
	}

	if (pxml->pinfo != NULL)
	{
		if (pxml->pinfo->pdevices != NULL && pxml->pinfo->pdevices_size > 0)
		{
			for (int i = 0; i < pxml->pinfo->pdevices_size; i++)
			{
				if (pxml->pinfo->pdevices + i != NULL)
				{
					if(pxml->pinfo->pdevices[i].psemaphores != NULL){
						
						free(pxml->pinfo->pdevices[i].psemaphores);
					}
				}
			}
			free(pxml->pinfo->pdevices);
		}
		free(pxml->pinfo);
	}
	free(pxml);
	return 0;
}

int yaxmlprintStruct(request_t *pxml)
{
	if (pxml == NULL)
		return 0;
	if (pxml->pdoc != NULL)
	{
		/*****************释放资源********************/
		xmlFreeDoc(pxml->pdoc);
		xmlCleanupParser();
		xmlMemoryDump();
	}

	if (pxml->ppktype != NULL)
	{
		//	if(pxml->ppktype->pname != NULL){
		// 		xmlFree(pxml->ppktype->pname);
		// 	}
		free(pxml->ppktype);
	}

	if (pxml->pinfo != NULL)
	{
		if (pxml->pinfo->pdevices != NULL && pxml->pinfo->pdevices_size > 0)
		{
			for (int i = 0; i < pxml->pinfo->pdevices_size; i++)
			{
				if (pxml->pinfo->pdevices + i != NULL)
				{
					for (int j = 0; j < pxml->pinfo->pdevices[i].psemaphores_size; j++)
					{
						if (pxml->pinfo->pdevices[i].psemaphores + i != NULL)
						{
							free(pxml->pinfo->pdevices[i].psemaphores + i);
						}
					}
					free(pxml->pinfo->pdevices + i);
				}
			}
		}

		free(pxml->pinfo);
	}

	return 0;
}