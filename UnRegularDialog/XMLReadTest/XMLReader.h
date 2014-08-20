#pragma once

#define FOREACH_NODE(a,b)\
	long cnt = 0; \
	IXMLDOMNodePtr a;\
	b->get_length(&cnt);\
	for(int i = 0; i < cnt && SUCCEEDED(b->get_item(i,&a)); i++, a = NULL)

class XMLReader
{
public:
	XMLReader(void);
	~XMLReader(void);

public:
	static bool GetRootNodeListFromXMLFile(IXMLDOMNodeListPtr& rootNodeList,const CString xmlPath);
	static bool GetFirstNodeFromNodelist(IXMLDOMNodePtr& node, CString nodeName,IXMLDOMNodeListPtr nodeList,int nodeNum = 1);
	static bool GetNodelistOfNode(IXMLDOMNodeListPtr& nodelist ,IXMLDOMNodePtr node);
	static bool GetNodeName(CString& nodeName,IXMLDOMNodePtr node);
	static bool GetNodeText(CString& nodeText,IXMLDOMNodePtr node);
};

