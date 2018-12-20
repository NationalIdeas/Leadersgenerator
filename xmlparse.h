#pragma once
#include "stdafx.h"

#include <msxml6.h>


namespace HOI3XML
{
    //declaration;
    int writeXML(CString filename = _T(""));
    int readXML(CString filename = _T(""));
    int FormatDOMDocument (IXMLDOMDocument *pDoc, IStream *pStream);


	

    //definition;
    int writeXML(CString filename)
    {
        CString szMessage;
        szMessage = _T("写XML成功！");
        HRESULT hr = S_OK;
        CComVariant FileName;//COM版的Variant;

        CoInitialize(NULL);//必须要初始化COM;
        IXMLDOMDocumentPtr pXMLDom = NULL;//DOM操作的智能指针;
        hr = pXMLDom.CreateInstance(__uuidof(DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
        pXMLDom->put_preserveWhiteSpace(VARIANT_TRUE);

        VARIANT_BOOL VBool;
        pXMLDom->get_async(&VBool);
        pXMLDom->get_validateOnParse(&VBool);
        pXMLDom->get_resolveExternals(&VBool);


        IXMLDOMProcessingInstructionPtr pPI = NULL;
        pXMLDom->createProcessingInstruction(_T("xml"),_T("version='1.0' encoding='UTF-8'"),&pPI);//声明;
        pXMLDom->appendChild(pPI,NULL);

        CString root;
        root = _T("root");
        IXMLDOMElementPtr pRoot = NULL;
        pXMLDom->createElement(root.GetBuffer(),&pRoot);//根元素;
        CComVariant var = _T("15");
        pRoot->setAttribute(_T("Property"),var);//设置属性;


    { IXMLDOMElementPtr pElement = NULL;
        pXMLDom->createElement(_T("name"),&pElement);
        pElement->put_text(_T("wa ng"));
        CComVariant var2 = _T("12");
        pElement->setAttribute(_T("ID"),var2 );
        pRoot->appendChild(pElement,NULL);
        pXMLDom->appendChild(pRoot,NULL);}

    { IXMLDOMElementPtr pElement = NULL;
    pXMLDom->createElement(_T("name"),&pElement);
    pElement->put_text(_T("li"));
    CComVariant var2 = _T("13");
    pElement->setAttribute(_T("ID"),var2 );
    pRoot->appendChild(pElement,NULL);
    pXMLDom->appendChild(pRoot,NULL);}

//        CreateDirectory(_T(".\\zh"),NULL);//创建文件夹;
        CString szTmp;
//      tmp = _T(".\\zh\\");
        szTmp += filename;

        szTmp = _T("4.xml");

        FileName = szTmp;

        hr = pXMLDom->save(FileName);//保存XML文件;

        CoUninitialize();
        
        return 0;
    }

    int readXML(CString filename )
    {
        CString szMessage;
        
        szMessage = _T("读取XML成功！");
        HRESULT hr = S_OK;
        CComVariant FileName;//COM版的Variant;

        CoInitialize(NULL);//必须要初始化COM;
        IXMLDOMDocumentPtr pXMLDom = NULL;//DOM操作的智能指针;
        hr = pXMLDom.CreateInstance(__uuidof(DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
        

        VARIANT_BOOL VBool;
        pXMLDom->put_async(VARIANT_FALSE);
        pXMLDom->put_validateOnParse(VARIANT_FALSE);
        pXMLDom->put_resolveExternals(VARIANT_FALSE);
        pXMLDom->put_preserveWhiteSpace(VARIANT_TRUE);
        
        IXMLDOMNodeListPtr pList = NULL;
        IXMLDOMNodePtr pNode = NULL;

        BSTR NodeName;
        BSTR QueryString;

        CStdioFile file;
        file.Open(_T("out.txt"),CFile::modeCreate|CFile::modeWrite|CFile::typeText);
        
        QueryString = SysAllocString(_T("//name"));
        NodeName = SysAllocString(_T("s"));

        FileName = _T("4.xml");
        pXMLDom->load(FileName,&VBool);

        pXMLDom->selectSingleNode(QueryString,&pNode);
        if (pNode)
        {
            pNode->get_nodeName(&NodeName);
            szMessage = NodeName;
            file.WriteString(szMessage);
            file.WriteString(_T("\r\n"));

        }


        file.WriteString(_T("next line \r\n"));

        CComVariant valuex;
        pXMLDom->selectNodes(QueryString,&pList);
        if (pList)
        {
            long len;
            hr = pList->get_length(&len);

            for (int i = 0;i<len;i++)
            {
                pList->get_item(i,&pNode);
                pNode->get_nodeName(&NodeName);
                szMessage = NodeName;
                file.WriteString(szMessage);
                file.WriteString(_T("\r\n"));
                pNode->get_nodeValue(&valuex);
                szMessage = valuex.bstrVal;
                file.WriteString(szMessage);
                file.WriteString(_T("\r\n"));
                pNode->get_text(&NodeName);
                szMessage = NodeName;
                file.WriteString(szMessage);
                file.WriteString(_T("\r\n"));
            }
        }

        SysFreeString(NodeName);
        SysFreeString(QueryString);  


        file.Close();
        
        
        
        
        
        
        return 0;

    }



	/*
    int FormatDOMDocument (IXMLDOMDocument *pDoc, IStream *pStream)
    {

        // Create the writer

        CComPtr <IMXWriter> pMXWriter;
        if (FAILED (pMXWriter.CoCreateInstance(__uuidof (MXXMLWriter), NULL, CLSCTX_ALL)))
        {
            return 1;
        }
        CComPtr <ISAXContentHandler> pISAXContentHandler;
        if (FAILED (pMXWriter.QueryInterface(&pISAXContentHandler)))
        {
            return 2;
        }
        CComPtr <ISAXErrorHandler> pISAXErrorHandler;
        if (FAILED (pMXWriter.QueryInterface (&pISAXErrorHandler)))
        {
            return 3;
        }
        CComPtr <ISAXDTDHandler> pISAXDTDHandler;
        if (FAILED (pMXWriter.QueryInterface (&pISAXDTDHandler)))
        {
            return 4;
        }

        if (FAILED (pMXWriter ->put_omitXMLDeclaration (VARIANT_FALSE)) ||
            FAILED (pMXWriter ->put_standalone (VARIANT_TRUE)) ||
            FAILED (pMXWriter ->put_indent (VARIANT_TRUE)) ||
            FAILED (pMXWriter ->put_encoding (L"UTF-8")))
        {
            return 5;
        }

        // Create the SAX reader

        CComPtr <ISAXXMLReader> pSAXReader;
        if (FAILED (pSAXReader.CoCreateInstance (__uuidof (SAXXMLReader), NULL, CLSCTX_ALL)))
        {
            return 6;
        }

        if (FAILED (pSAXReader ->putContentHandler (pISAXContentHandler)) ||
            FAILED (pSAXReader ->putDTDHandler (pISAXDTDHandler)) ||
            FAILED (pSAXReader ->putErrorHandler (pISAXErrorHandler)) ||
            FAILED (pSAXReader ->putProperty (
            L"http://xml.org/sax/properties/lexical-handler", CComVariant (pMXWriter))) ||
            FAILED (pSAXReader ->putProperty (
            L"http://xml.org/sax/properties/declaration-handler", CComVariant (pMXWriter))))
        {
            return 7;
        }

        // Perform the write

        return 
            SUCCEEDED (pMXWriter ->put_output (CComVariant (pStream))) &&
            SUCCEEDED (pSAXReader ->parse (CComVariant (pDoc)));
    }

	*/



}