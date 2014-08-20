#include "StdAfx.h"
#include "XMLReader.h"


XMLReader::XMLReader(void)
{
}


XMLReader::~XMLReader(void)
{
}
//doesn't contain the root node, BTW: how to get the root node name?
bool XMLReader::GetRootNodeListFromXMLFile(IXMLDOMNodeListPtr& rootNodeList,const CString xmlPath)
{
	IXMLDOMDocumentPtr pDoc = NULL;

	assert(pDoc == NULL);

	HRESULT hr;

	hr = pDoc.CreateInstance(__uuidof(DOMDocument));
	if (FAILED(hr))
	{
		return false;
	}

	VARIANT_BOOL bSuccess = VARIANT_FALSE;

	hr = pDoc->load(CComVariant(xmlPath), &bSuccess);
	if(FAILED(hr) || bSuccess == VARIANT_FALSE)
	{
		return false;
	}

	IXMLDOMElementPtr pEle = NULL;

	hr = pDoc->get_documentElement(&pEle);
	if (FAILED(hr))
	{
		return false;
	}

	hr = pEle->get_childNodes(&rootNodeList);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
	
}

bool XMLReader::GetFirstNodeFromNodelist(IXMLDOMNodePtr& node, CString nodeName,IXMLDOMNodeListPtr nodeList,int nodeNum)
{
	if (nodeList == NULL)
	{
		return false;
	}

	FOREACH_NODE(pNode,nodeList)
	{
		CComBSTR bstr;

		if (pNode == NULL)
		{
			return false;
		}

		HRESULT hr = pNode->get_nodeName(&bstr);
		if (FAILED(hr))
		{
			return false;
		}

		if (_tcscmp(bstr,nodeName) == 0)
		{
			node = pNode;

			break;
		}
	}

	return true;
}

bool XMLReader::GetNodelistOfNode(IXMLDOMNodeListPtr& nodelist ,IXMLDOMNodePtr node)
{
	if(node == NULL)
	{
		return false;
	}

	HRESULT hr = node->get_childNodes(&nodelist);
	if (FAILED(hr))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool XMLReader::GetNodeName(CString& nodeName,IXMLDOMNodePtr node)
{
	if (node == NULL)
	{
		return false;
	}

	BSTR bstr;

	HRESULT hr = node->get_nodeName(&bstr);
	if (FAILED(hr))
	{
		return false;
	}
	else
	{
		nodeName = bstr;

		return true;
	}
}

bool XMLReader::GetNodeText(CString& nodeText,IXMLDOMNodePtr node)
{
	if (node == NULL)
	{
		return false;
	}

	BSTR bstr;

	HRESULT hr = node->get_text(&bstr);
	if (FAILED(hr))
	{
		return false;
	}
	else
	{
		nodeText = bstr;

		return true;
	}
}