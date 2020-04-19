#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/xmlmemory.h>
typedef struct Ta{
	char * a;
	xmlChar* b;
}a_t;
typedef struct TSemaphore
{
		xmlChar*   ID;
		xmlChar*  SignalNumber;
}semaphore_t;

typedef struct Device
{
		xmlChar*   DeviceID;
		xmlChar*   DeviceType;
			int  psemaphores_size = 0;
		semaphore_t*  psemaphores;
}device_t;
typedef struct Info
{
		xmlChar*   FSUID;
		int  pdevices_size = 0;
		device_t*  pdevices;
}info_t;
typedef struct PK_Type
{
		xmlChar*   pname;
}PK_Type_t;
typedef struct Request
{
		xmlDocPtr pdoc;
		PK_Type_t*   ppktype;
		info_t*  pinfo;
}request_t;

//public   function 
int yaxmlcreateXmlStructFromXmlDoc(xmlDocPtr pdoc, request_t *pxml);
int yaxmlfreeXmlDoc(xmlDocPtr pdoc);
int yaxmlfreeXmlStruct(request_t *pxml);